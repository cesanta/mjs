/**
 * Print arguments to stdout, separated by space.
 */
declare function print(...args: any): void;

/**
 * Execute specified file.
 * @param file a `.js` file path
 * @param globalNamespace global namespace object. If not specified,
 *  a current global namespace is passed to the script, which allows `file`
 *  to modify the current namespace.
 */
declare function load(path: string, globalNamespace?: object): any;

/**
 * Exit interpreter with the given error message
 */
declare function die(errorMessage: string): never;

/**
 * Return numeric byte value at given string index.
 * @param asciiCode must be in range `0-255` (inclusive)
 * @returns 1-byte string (or `null` if asciiCode is incorrect)
 * @example chr(0x61) === 'a';
 */
declare function chr(asciiCode: number): string | null;

/**
 * Create a string backed by a C memory chunk.
 * A returned string starts at memory location `ptrValue`,
 * and is `length` bytes long.
 */
declare function mkstr(ptrValue: unknown, length: number): string;

/**
 * Like `mkstr(ptrValue, length)`, but the returned string starts at
 * memory location `ptrValue + offset`, and the caller can specify
 * whether the string needs to be copied to the internal mjs buffer.
 * By default it's not copied.
 */
declare function mkstr(ptrValue: unknown, offset: number, length: number, copy: boolean = false): string;

/**
 * Import native C function into mJS.
 */
declare function ffi(nativeSignature: string): (...args: any) => any;

/**
 * Perform garbage collection.
 * @param full if `true`, reclaim RAM to OS.
 */
declare function gc(full: boolean): void;

declare namespace JSON {
  /**
   * Parse JSON string and return parsed value.
   */
  export function parse(jsonString: string): any;

  /**
   * Get string representation of the mJS value.
   */
  export function stringify(jsValue: any): string;
}

declare namespace Object {
  /**
   * Create an object with the provided prototype.
   * @example let proto = {foo: 1}; let o = Object.create(proto);
   */
  export function create(prototype: object): object;
}

interface String {
  /**
   * Return a substring between two indices.
   * @example 'abcdef'.slice(1,3) === 'bc';
   */
  slice(start: number, end: number): string;

  /**
   * Return numeric byte value at given string index.
   * @example 'abc'.at(0) === 0x61;
   */
  at(index: number): number;

  /**
   * Return index of first occurrence of substr within the string.
   * @returns index or `-1` if not found.
   * @example 'abc'.indexOf('bc') === 1;
   */
  indexOf(substring: string): number;
}

interface Array<T> {
  /**
   * Change the contents of an array by removing existing elements
   * and/or adding new elements.
   * @example let a = [1,2,3,4,5]; a.splice(1, 2, 100, 101, 102); a === [1,100,101,102,4,5];
   */
  splice(startIndex: number, deleteCount: number, ...insertElements?: any): T[];
}

/*
Recommended VSCode settings (.vscode/settings.json):
{
  "typescript.suggest.autoImports": false,
  "javascript.suggest.autoImports": false,
  "typescript.suggest.includeAutomaticOptionalChainCompletions": false,
  "javascript.suggest.includeAutomaticOptionalChainCompletions": false,
}
*/
