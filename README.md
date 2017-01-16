mJS: Restricted JavaScript engine
====================================

[![License](https://img.shields.io/badge/license-GPL_2-green.svg)](https://github.com/cesanta/mjs/blob/master/LICENSE)

# Overview

mJS is designed for microcontrollers with limited resources. Main design
goals are: small footprint and simple C/C++ interoperability. mJS
implements a strict subset of ES6 (JavaScript version 6).

- Any valid mJS code is always a valid ES6 code.
- Any valid ES6 code is not necessarily a valid mJS code.

On 32-bit ARM mJS engine takes about 25k of flash memory, and less than 10k
of RAM.

# Restrictions

- No standard library. No String, Number, RegExp, Date, Function, etc.
- No nested functions, no closures. All functions are top-level only.
- No exceptions.
- Strict mode only.
- No `var`, only `let`.
- No `for..in`, `for..of`, `=>`.
- No getters, setters, `valueOf`, prototypes, classes, template strings.
- No destructors, generators, proxies, promises.
- mJS strings are byte strings. NOT Unicode strings. `'ы'.length === 2`,
  `'ы'[0] === '\xd1'`, `'ы'[1] === '\x8b'`.

# Built-in API

- `print(arg1, ...);` - print arguments to stdout, separated by space.
- `let f = ffi('int foo(int)');` - import C function into mJS. See next section.
- `load('file.js', obj);` - execute file `file.js`. `obj` paramenter is
  optional, `obj` is a global namespace object. If not specified, a current
  global namespace is passed to the script, which allows `file.js` to modify
  current namespace (`global` object).
- `let obj = JSON.parse(str);` - parse JSON string and return parsed value. Conforms to
  the [standard JSON.parse() API](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/parse)
- `let str = JSON.stringify(value[, replacer[, space]]);` - stringify mJS value.
  Conforms to the [standard JSON.stringify() API](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/stringify)

# C/C++ interoperability

mJS requires no glue code. The mJS's Foreign Function Interface (FFI)
allows the user to call an existing C function with an arbitrary signature.
Currently mJS provides a simple implementation of the FFI trampoline
that supports up to 6 32-bit arguments, or up to 2 64-bit arguments:

```javascript
let printf = ffi('int printf(char *, int, char *)');
printf('Hi %d %s\n', 123, 'foo');
```

Thus, only functions with a up to four simple arguments
(`int`, `double`, `char *`, `void *`) are supported. In order to import
more complex functions (e.g. that uses structures as arguments), write wrappers.

mJS FFI is a unique feature. In majority of cases, it makes it unnecessary
to use engine API for embedding. `ffi()` the functions you need directly from C!

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
linker script. mJS resolver uses `dlsym`-compatible signature:

```C
typedef void *(mjs_ffi_resolver_t)(void *handle, const char *symbol);
void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym);
```

Here is an example of manually implemented symbol resolver:

```C
void *my_dlsym(void *handle, const char *name) {
  if (strcmp(name, "func1") == 0) return func1;
  if (strcmp(name, "func2") == 0) return func2;
  return NULL;
  (void) handle;
}

...
  struct mjs *mjs = mjs_create();
  mjs_set_ffi_resolver(mjs, my_dlsym);
...

```

# Real life application

mJS is used in [Mongoose OS](https://github.com/cesanta/mongoose-os) - an open
source embedded operating system for low-power connected microcontrollers.
It provides scripting abilities - example of exporting
[GPIO API](https://github.com/cesanta/mongoose-os/blob/master/fw/examples/mjs_hello/fs/api_gpio.js)
and [LED blink example](https://github.com/cesanta/mongoose-os/blob/master/fw/examples/mjs_hello/fs/init.js).
Note that all that made with zero amount of glue code. JS API is just an FFI-ed C API.

On UNIX or Mac system, a standard `dlsym()` symbol resolver is used.
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


# Licensing

mJS is released under commercial and [GNU GPL v.2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html)
open source licenses.

Commercial Projects: Once your project becomes commercialised GPLv2 licensing
dictates that you need to either open your source fully or purchase a
commercial license. Cesanta offer full, royalty-free commercial licenses
without any GPL restrictions. If your needs require a custom license, we’d be
happy to work on a solution with you. [Contact us for pricing.]
(https://www.cesanta.com/contact)

Prototyping: While your project is still in prototyping stage and not for sale,
you can use MJS’s open source code without license restrictions.
