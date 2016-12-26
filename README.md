MJS: Embedded JavaScript-like engine
====================================

[![License](https://img.shields.io/badge/license-GPL_2-green.svg)](https://github.com/cesanta/mjs/blob/master/LICENSE)

# Overview

MJS is designed for microcontrollers with limited resources. Main design
goals are: small footprint and simple C/C++ interoperability. MJS
implements a strict subset of ES6 (JavaScript version 6).

- Any valid MJS code is always a valid ES6 code.
- Any valid ES6 code is not necessarily a valid MJS code.

On 32-bit ARM MJS engine takes about 25k of flash memory, and less than 10k
of RAM.

# Restrictions

- No standard library.
- No nested functions, no closures. All functions are top-level only.
- No exceptions.
- Strict mode only.
- No `var`, only `let`.
- No `for..in`, `for..of`, `=>` syntax.
- No getters, setters, `valueOf`, prototypes, classes, template strings.
- No destructors, generators, proxies, promises.

# C/C++ interoperability

MJS requires no glue code. The MJS's Foreign Function Interface (FFI)
allows the user to call an existing C function with an arbitrary signature.
Currently MJS provides a simple implementation of the FFI trampoline
that only supports a few arguments (4 32-bit arguments or 2 64-bit ones):

```javascript
let printf = ffi('int printf(char *, int, char *)');
printf('Hi %d %s\n', 123, 'foo');
```

Thus, only functions with a up to four simple arguments
(`int`, `double`, `char *`, `void *`) are supported. In order to import
more complex functions (e.g. that uses structures as arguments), write wrappers.

## Callbacks

Callbacks are implemented similarly. Consider that you have a C function
that takes a callback and user data pointer:

```C
void timer(int seconds, void (*callback)(int, void *), void *udata);
```

This is how to make an MJS callback:

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

In order to make FFI work, MJS must be able to get the address of a C
function by its name. On POSIX systems, `dlsym()` API can do that. On
Windows, `GetProcAddress()`. On embedded systems, a system resolver should
be either manually written, or be implemented with some aid from a firmware
linker script. MJS resolver uses `dlsym`-compatible signature:

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

# Licensing

MJS is released under commercial and [GNU GPL v.2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html)
open source licenses.

Commercial Projects: Once your project becomes commercialised GPLv2 licensing
dictates that you need to either open your source fully or purchase a
commercial license. Cesanta offer full, royalty-free commercial licenses
without any GPL restrictions. If your needs require a custom license, we’d be
happy to work on a solution with you. [Contact us for pricing.]
(https://www.cesanta.com/contact)

Prototyping: While your project is still in prototyping stage and not for sale,
you can use MJS’s open source code without license restrictions.
