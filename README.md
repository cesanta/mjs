mJS: Restricted JavaScript engine
====================================

[![License](https://img.shields.io/badge/license-GPL_2-green.svg)](https://github.com/cesanta/mjs/blob/master/LICENSE)

# Overview

mJS is designed for microcontrollers with limited resources. Main design
goals are: small footprint and simple C/C++ interoperability. mJS
implements a strict subset of ES6 (JavaScript version 6).

- Any valid mJS code is always a valid ES6 code.
- Any valid ES6 code is not necessarily a valid mJS code.

On 32-bit ARM mJS engine takes about 25k of flash memory, and less than 1k
of RAM. See [intro article](http://goo.gl/zJYyWF) for more details.

mJS is part of [MongooseOS](https://mongoose-os.com) - an open
source operating system for low-power connected microcontrollers. It
implements scripting for fast prototyping.

# Restrictions

- No standard library. No String, Number, RegExp, Date, Function, etc.
  The only standard methods available are `JSON.parse()` and `JSON.stringify()`.
- No closures, only lexical scoping. That means that nested functions are
  allowed, but returning a nested function is prohibited.
- No exceptions.
- Strict mode only.
- No `var`, only `let`.
- No `for..in`, `for..of`, `=>`.
- No getters, setters, `valueOf`, prototypes, classes, template strings.
- No destructors, generators, proxies, promises.
- No `==` or `!=`, only `===` and `!==`.
- mJS strings are byte strings, not Unicode strings. `'ы'.length === 2`,
  `'ы'[0] === '\xd1'`, `'ы'[1] === '\x8b'`. That means that mJS string
  can represent any binary data chunk.

# Built-in API

- `print(arg1, ...);` - print arguments to stdout, separated by space.
- `let f = ffi('int foo(int)');` - import C function into mJS. See next section.
- `load('file.js', obj);` - execute file `file.js`. `obj` paramenter is
  optional, `obj` is a global namespace object. If not specified, a current
  global namespace is passed to the script, which allows `file.js` to modify
  the current namespace.
- `let value = JSON.parse(str);` - parse JSON string and return parsed value.
- `let str = JSON.stringify(value);` - stringify mJS value.
- `"abcdef".slice(1,3) === "bc"` - the `slice(start, end)`
  string method returns a substring between two indices.
- `"abcdef".charCodeAt(0) === 0x61` - the `charCodeAt(index)`
  string method returns an byte value at the given index.
- `let foo = ffi('void *foo(void)'); let ptr = foo(); ptr[0] === 17;` - mJS can access memory using C `void *` pointer subscripts `ptrVar[index]`. Return byte value at that location.
- `let foo = ffi('void *foo(void)'); let ptr = foo(); let s = fstr(ptr, 3, 10);` - create a string backed by a C memory chunk, `fstr(ptrVar, offset, length)`. A string `s` starts at memory location `ptrVar + offset`, and is `length` bytes long. Short form is also available: `fstr(ptrVar, length)`.

# C/C++ interoperability

mJS requires no glue code. The mJS's Foreign Function Interface (FFI)
allows the user to call an existing C function with an arbitrary signature.
Currently mJS provides a simple implementation of the FFI trampoline
that supports up to 6 32-bit arguments, or up to 2 64-bit arguments:

```javascript
let floor = ffi('double floor(double)');
print(floor(1.23456));
```

Function arguments should be simple: only `int`, `double`, `char *`, `void *`
are supported. Use `char *` for NUL-terminated C strings, `void *` for any
other pointers. In order to import more complex functions
(e.g. the ones that use structures as arguments), please write wrappers.

mJS FFI is a unique feature. In majority of cases, it makes it unnecessary
to use embedding API. Just `ffi()` the functions you need directly from C!
See example below on how to try FFI functionality from the UNIX shell.

## Callbacks

Callbacks are implemented similarly. Consider that you have a C function
that takes a callback and user data `void *` pointer, which should be marked
as `userdata` in the signature:

```C
void timer(int seconds, void (*callback)(int, void *), void *user_data);
```

This is how to make an mJS callback - note the usage of `userdata`:

```javascript
let timer = ffi('void timer(int, void (*)(int, userdata), userdata)');
let callback = function(time, data) {
  print('Time now: ', time, ' called: ', data.num_calls, ' times');
};
let callback_data = { num_calls: 0 };
timer(1, callback, callback_data);
```

In this example, `callback_data` is a context object that is preserved between
callback invocations. Note that if that object is inlined into the
call like this: `timer(1, callback, { num_calls: 0 })` then that would
result in the memory leak. If you plan to pass a context object to the callback,
define it once and reuse for all subsequent invocations.

## Symbol resolver

In order to make FFI work, mJS must be able to get the address of a C
function by its name. On POSIX systems, `dlsym()` API can do that. On
Windows, `GetProcAddress()`. On embedded systems, a system resolver should
be either manually written, or be implemented with some aid from a firmware
linker script. mJS resolver uses `dlsym`-compatible signature. 

On UNIX/Mac systems, a standard `dlsym()` symbol resolver is used.
You can run this example that loads and calls stdlib's `system()` function:

```
$ cc mjs.c -DMJS_MAIN -D_DARWIN_C_SOURCE -o /tmp/mjs
$ /tmp/mjs -e "let f=ffi('int system(char *)'); f('ls -l')"
total 1312
-rw-r--r--  1 lsm  staff     693 15 Jan 19:09 LICENSE
-rw-r--r--  1 lsm  staff    5151 15 Jan 19:09 README.md
-rwxr-xr-x  1 lsm  staff  156192 15 Jan 20:12 a.out
-rw-r--r--  1 lsm  staff  471212 15 Jan 20:11 mjs.c
-rw-r--r--  1 lsm  staff   22274 15 Jan 19:09 mjs.h
0.000000
```

# Complete embedding example

We export C function `foo` to the JS environment and call it from the JS.

```c
#include "strings.h"
#include "mjs.h"

void foo(int x) {
  printf("Hello %d!\n", x);
}

void *my_dlsym(void *handle, const char *name) {
  if (strcmp(name, "foo") == 0) return foo;
  return NULL;
}

int main(void) {
  struct mjs *mjs = mjs_create();
  mjs_set_ffi_resolver(mjs, my_dlsym);
  mjs_exec(mjs, "let f = ffi('void foo(int)'); f(1234)", NULL);
  return 0;
}
```

Compile & run:

```
$ cc main.c mjs.c -o /tmp/x && /tmp/x
Hello 1234!
```

# Build stand-alone mJS binary

```
$ make                              # Build
$ ./build/mjs -e '1 + 2 * 3'        # Use as a simple calculator
7
$ ./build/mjs -e 'ffi("double sin(double)")(1.23)'
0.942489
$ ./build/mjs -d -e '2 + 2'         # Dump bytecode
------- MJS VM DUMP BEGIN
    DATA_STACK (0 elems):
    CALL_STACK (0 elems):
        SCOPES (1 elems):  [<object>]
  LOOP_OFFSETS (0 elems):
  CODE:
  0   BCODE_HDR [<stdin>] size:28
  21  PUSH_INT  2
  23  PUSH_INT  2
  25  EXPR      +
  27  EXIT
  28  NOP
------- MJS VM DUMP END
4
```

# Licensing

mJS is released under commercial and
[GNU GPL v.2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html)
open source licenses.

Commercial Projects: once your project becomes commercialised, GPLv2 licensing
dictates that you need to either open your source fully or purchase a
commercial license. Cesanta offer full, royalty-free commercial licenses
without any GPL restrictions. If your needs require a custom license, we’d be
happy to work on a solution with you.
[Contact us for pricing](https://mongoose-os.com/contact.html)

Prototyping: While your project is still in prototyping stage and not for sale,
you can use MJS’s open source code without license restrictions.
