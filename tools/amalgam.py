#!/usr/bin/env python3
#
# Generate a reversible amalgamation of several C source files
# along with their required internal headers.
#
# This script assumes that there are a bunch of C files, a bunch
# of private header files and one public header file.
#
# The script takes a list of C file names, parses `#include` directives
# found in them and recursively resolves dependencies in such a way
# that a header referenced from an included header will be emitted before the
# header that depends on it. All headers will always be emitted before the
# source files.
#
# all it does is to wrap the C body in a preprocessor guard.
#
# TODO(mkm): make it work also for mongoose where we also generate
# the public header from a bunch of unamalgamated header files.
# Currently this script can handle mongoose amalgamation because it doesn't
# flip the --autoinc flag.
#

import argparse
import fnmatch
import io
import re
import sys
import os

parser = argparse.ArgumentParser(description='Produce an amalgamated source')
parser.add_argument('--prefix', default="NS",
                    help='prefix for MODULE_LINES guard')
parser.add_argument('--srcdir', default=".", help='source dir')
parser.add_argument('--ignore', default="",
                    help='comma separated list of include files to leave alone')
# hack, teach amalgam to render the LICENSE file instead
parser.add_argument('--first', type=str, help='put this file in first position.'
                    ' Usually contains licensing info')
parser.add_argument('--public-header', dest="public",
                    help='name of the public header file that will be'
                    ' included at the beginning of the file')
parser.add_argument('--autoinc', action='store_true',
                    help='automatically embed include files')
parser.add_argument('--autoinc-ignore', default="",
                    help='comma separated list of includes to not amalgam')
parser.add_argument('--strict', action='store_true',
                    help='fail loudly if an include file cannot be resolved')
parser.add_argument('--norel', action='store_true',
                    help="do not try to compute a friendly relative path")
parser.add_argument('-I', default=['.'], dest='include_path', help='include path', action='append')
parser.add_argument('sources', nargs='*', help='sources')
parser.add_argument('--license', dest="license", help='License file')

class File(object):
    def __init__(self, name, parent_name):
        self.name = name
        self.parent_name = parent_name
        self.buf = io.StringIO()
        emit_file(self.buf, self.name, self.parent_name)

    def emit(self):
        print('%s' % self.buf.getvalue(), end='')

    def __repr__(self):
        if self.parent_name:
            return '(%s included from %s)' % (self.name, self.parent_name)
        return '(%s)' % self.name


args = parser.parse_args()

includes = []

already_included = set()

ignore_patterns = [i.strip() for i in args.ignore.split(',')]
autoinc_ignore_patterns = [i.strip() for i in args.autoinc_ignore.split(',')]


def should_ignore(name):
    for p in ignore_patterns:
        if fnmatch.fnmatch(name, p):
            return True
    return False


def should_ignore_autoinc(name, parent_name):
    if name in already_included:
        return True
    if not (args.strict or os.path.exists(resolve(name, parent_name))):
        return True
    for p in autoinc_ignore_patterns:
        if fnmatch.fnmatch(name, p):
            return True
    return False


def resolve(path, parent_name):
    path_from_parent = None
    if parent_name != None and not os.path.isabs(path):
        # calculate the path relative to the "parent_name" file, i.e. to the file
        # which includes the current one.
        path_from_parent = os.path.join(os.path.dirname(parent_name), path)

    if os.path.isabs(path) or os.path.exists(path):
        p = path
    elif path_from_parent != None and os.path.exists(path_from_parent):
        p = path_from_parent
    else:
        for ip in args.include_path:
            p = os.path.join(ip, path)
            if os.path.exists(p):
                break
    if os.path.exists(p) and not args.norel:
        p = os.path.realpath(p).replace('%s%s' % (os.getcwd(), os.sep), '')
    return p.replace(os.sep, '/')


def emit_line_directive(out, name, parent_name):
    print ('''#ifdef %(prefix)s_MODULE_LINES
#line 1 "%(name)s"
#endif''' % dict(
    prefix = args.prefix,
    name = resolve(name, parent_name),
), file=out)


def emit_body(out, name, parent_name):
    resolved_name = resolve(name, parent_name)
    if not args.strict and not os.path.exists(resolved_name):
        print('#include "%s"' % name, file=out)
        return

    with open(resolved_name) as f:
        in_comment = False
        comment = ''
        for l in f:
            if in_comment:
                comment += l
                if re.match('\s*\*/$', l):
                    in_comment = False
                    if not re.match('.*Copyright.*Cesanta', comment, re.M | re.S):
                        out.write(comment)
                continue

            if re.match('/\*$', l):
                in_comment = True
                comment = l
                continue

            match = re.match('( *#include "(.*)")', l)
            if match:
                all_match, path_to_include = match.groups()
                if not should_ignore(path_to_include):
                    l = '/* Amalgamated: %s */\n' % all_match
                    if args.autoinc:
                        if not should_ignore_autoinc(path_to_include, parent_name):
                            already_included.add(path_to_include)
                            includes.append(File(path_to_include, resolved_name))
            if l is not None:
                out.write(l)


def emit_file(out, name, parent_name):
    emit_line_directive(out, name, parent_name)
    emit_body(out, name, parent_name)


sources = []

for f in args.sources:
    for p in ignore_patterns:
        if fnmatch.fnmatch(f, p):
            break
    else:
        sources.append(File(f, None))

parts = includes + sources

if args.first:
    for inc in reversed(args.first.split(',')):
        for i, f in enumerate(parts):
            if f.name == inc:
                del parts[i]
                parts.insert(0, f)
                break

# emit

if sys.platform == "win32":
    import os, msvcrt
    msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)

if args.license:
    with open(args.license) as f:
        print(f.read())

if args.public:
    print('#include "%s"' % args.public)

for f in parts:
    f.emit()
