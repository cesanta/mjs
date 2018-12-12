mJS: Restricted JavaScript engine
====================================

[![License](https://img.shields.io/badge/license-GPL_2-green.svg)](https://github.com/cesanta/mjs/blob/master/LICENSE)

# Overview

mJS is designed for microcontrollers with limited resources. Main design
goals are: small footprint and simple C/C++ interoperability. mJS
implements a strict subset of ES6 (JavaScript version 6):

- Any valid mJS code is a valid ES6 code.
- Any valid ES6 code is not necessarily a valid mJS code.

On 32-bit ARM mJS engine takes about 50k of flash memory, and less than 1k
of RAM (see [intro article](http://goo.gl/zJYyWF)).
mJS is part of [MongooseOS](https://mongoose-os.com), 
where it enables scripting for IoT devices.

# Restrictions

- No standard library. No String, Number, RegExp, Date, Function, etc.
- **`JSON.parse()`** and **`JSON.stringify()`** are available.
- No closures, only lexical scoping (i.e. nested functions are allowed).
- No exceptions.
- No `new`. In order to create an object with a custom prototype, use
  **`Object.create()`**, which is available.
- Strict mode only.
- No `var`, only `let`.
- No `for..of`, `=>`, destructors, generators, proxies, promises.
- No getters, setters, `valueOf`, prototypes, classes, template strings.
- No `==` or `!=`, only `===` and `!==`.
- mJS strings are byte strings, not Unicode strings: `'ы'.length === 2`,
  `'ы'[0] === '\xd1'`, `'ы'[1] === '\x8b'`.
  mJS string can represent any binary data chunk.

# Built-in API


<dl>
  <dt><tt>print(arg1, arg2, ...);</tt></dt>
  <dd>Print arguments to stdout, separated by space.</dd>

  <dt><tt>load('file.js', obj);</tt></dt>
  <dd>Execute file <tt>file.js</tt>. <tt>obj</tt> paramenter is
  optional. <tt>obj</tt> is a global namespace object.
  If not specified, a current global namespace is passed to the script,
  which allows <tt>file.js</tt> to modify the current namespace.</dd>

  <dt><tt>die(message);</tt></dt>
  <dd>Exit interpreter with the given error message</dd>

  <dt><tt>let value = JSON.parse(str);</tt></dt>
  <dd>Parse JSON string and return parsed value.</dd>

  <dt><tt>let str = JSON.stringify(value);</tt></dt>
  <dd>Get string representation of the mJS value.</dd>

  <dt><tt>let proto = {foo: 1}; let o = Object.create(proto);</tt></dt>
  <dd>Create an object with the provided prototype.</dd>

  <dt><tt>'some_string'.slice(start, end);</tt></dt>
  <dd>Return a substring between two indices. Example:
      <tt>'abcdef'.slice(1,3) === 'bc';</tt></dd>

  <dt><tt>'abc'.at(0);</tt></dt>
  <dd>Return numeric byte value at given string index. Example:
      <tt>'abc'.at(0) === 0x61;</tt></dd>

  <dt><tt>'abc'.indexOf(substr[, fromIndex]);</tt></dt>
  <dd>Return index of first occurence of substr within the string or `-1`
  if not found.
      <tt>'abc'.indexOf('bc') === 1;</tt></dd>

  <dt><tt>chr(n);</tt></dt>
  <dd>Return 1-byte string whose ASCII code is the integer `n`. If `n` is
    not numeric or outside of `0-255` range, `null` is returned. Example:
      <tt>chr(0x61) === 'a';</tt></dd>

  <dt><tt>let a = [1,2,3,4,5]; a.splice(start, deleteCount, ...);</tt></dt>
  <dd>Change the contents of an array by removing existing elements and/or
    adding new elements. Example:
  <tt>let a = [1,2,3,4,5]; a.splice(1, 2, 100, 101, 102); a === [1,100,101,102,4,5];</tt></dd>

  <dt><tt>let s = mkstr(ptrVar, length);</tt></dt>
  <dd>Create a string backed by a C memory chunk. A string <tt>s</tt> starts
  at memory location <tt>ptrVar</tt>, and is <tt>length</tt> bytes long.</dd>

  <dt><tt>let s = mkstr(ptrVar, offset, length, copy = false);</tt></dt>
  <dd>Like `mkstr(ptrVar, length)`, but string <tt>s</tt> starts
  at memory location <tt>ptrVar + offset</tt>, and the caller can specify
  whether the string needs to be copied to the internal mjs buffer. By default
  it's not copied.</dd>

  <dt><tt>let f = ffi('int foo(int)');</tt></dt>
  <dd>Import C function into mJS. See next section.</dd>

  <dt><tt>gc(full);</tt></dt>
  <dd>Perform garbage collection. If `full` is `true`, reclaim RAM to OS.</dd>
</dl>

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
(e.g. the ones that use structures as arguments), write wrappers.

## Callbacks

Callbacks are implemented similarly. Consider that you have a C function
that takes a callback and user data `void *` pointer, which should be marked
as `userdata` in the signature:

```C
void timer(int seconds, void (*callback)(int, void *), void *user_data);
```

This is how to make an mJS callback - note the usage of `userdata`:

```javascript
let Timer = {
  set: ffi('void timer(int, void (*)(int, userdata), userdata)')
};

Timer.set(200, function(t) {
  print('Time now: ', t);
}, null);
```

## Symbol resolver

In order to make FFI work, mJS must be able to get the address of a C
function by its name. On POSIX systems, `dlsym()` API can do that. On
Windows, `GetProcAddress()`. On embedded systems, a system resolver should
be either manually written, or be implemented with some aid from a firmware
linker script. mJS resolver uses `dlsym`-compatible signature.

## Converting structs to objects

mJS provides a helper to facilitate coversion of C structs to JS objects.
The functions is called `s2o` and takes two parameters: foreign pointer to
the struct and foreign pointer to the struct's descriptor which specifies
names and offsets of the struct's members. Here's an simple example:

C/C++ side code:
```c
#include "mjs.h"

struct my_struct {
  int a;
  const char *b;
  double c;
  struct mg_str d;
  struct mg_str *e;
  float f;
  bool g;
};

static const struct mjs_c_struct_member my_struct_descr[] = {
  {"a", offsetof(struct my_struct, a), MJS_STRUCT_FIELD_TYPE_INT, NULL},
  {"b", offsetof(struct my_struct, b), MJS_STRUCT_FIELD_TYPE_CHAR_PTR, NULL},
  {"c", offsetof(struct my_struct, c), MJS_STRUCT_FIELD_TYPE_DOUBLE, NULL},
  {"d", offsetof(struct my_struct, d), MJS_STRUCT_FIELD_TYPE_MG_STR, NULL},
  {"e", offsetof(struct my_struct, e), MJS_STRUCT_FIELD_TYPE_MG_STR_PTR, NULL},
  {"f", offsetof(struct my_struct, f), MJS_STRUCT_FIELD_TYPE_FLOAT, NULL},
  {"g", offsetof(struct my_struct, g), MJS_STRUCT_FIELD_TYPE_BOOL, NULL},
  {NULL, 0, MJS_STRUCT_FIELD_TYPE_INVALID, NULL},
};

const struct mjs_c_struct_member *get_my_struct_descr(void) {
  return my_struct_descr;
};
```

JS side code:
```js
// Assuming `s` is a foreign pointer to an instance of `my_struct`, obtained elsewhere.
let sd = ffi('void *get_my_struct_descr(void)')();
let o = s2o(s, sd);
print(o.a, o.b);
```

Nested structs are also supported - use `MJS_STRUCT_FIELD_TYPE_STRUCT` field type
and provide pointer to the definition:

```c
struct my_struct2 {
  int8_t i8;
  int16_t i16;
  uint8_t u8;
  uint16_t u16;
};

static const struct mjs_c_struct_member my_struct2_descr[] = {
  {"i8", offsetof(struct my_struct2, i8), MJS_STRUCT_FIELD_TYPE_INT8, NULL},
  {"i16", offsetof(struct my_struct2, i16), MJS_STRUCT_FIELD_TYPE_INT16, NULL},
  {"u8", offsetof(struct my_struct2, u8), MJS_STRUCT_FIELD_TYPE_UINT8, NULL},
  {"u16", offsetof(struct my_struct2, u16), MJS_STRUCT_FIELD_TYPE_UINT16, NULL},
  {NULL, 0, MJS_STRUCT_FIELD_TYPE_INVALID, NULL},
};

struct my_struct {
  struct my_struct2 s;
  struct my_struct2 *sp;
};

static const struct mjs_c_struct_member my_struct_descr[] = {
  {"s", offsetof(struct my_struct, s), MJS_STRUCT_FIELD_TYPE_STRUCT, my_struct2_descr},
  {"sp", offsetof(struct my_struct, sp), MJS_STRUCT_FIELD_TYPE_STRUCT_PTR, my_struct2_descr},
  {NULL, 0, MJS_STRUCT_FIELD_TYPE_INVALID, NULL},
};
```

For complicated cases, a custom conversion function can be invoked that returns value:
```c
mjs_val_t custom_value_func(struct mjs *mjs, void *ap) {
  /* Do something with ap, construct and return mjs_val_t */
}

static const struct mjs_c_struct_member my_struct_descr[] = {
  ...
  {"x", offsetof(struct my_struct, x), MJS_STRUCT_FIELD_TYPE_CUSTOM, custom_value_func},
  ...
};
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

Build:
```
$ make
```

Use as a simple calculator:
```
$ ./build/mjs -e '1 + 2 * 3'
7
```

FFI standard C functions:
```
$ ./build/mjs -e 'ffi("double sin(double)")(1.23)'
0.942489
```

View generated bytecode:
```
$ ./build/mjs -l 3 -e '2 + 2'
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

The stand-alone binary uses `dlsym()` symbol resolver, that's why
`ffi("double sin(double)")(1.23)` works.

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
