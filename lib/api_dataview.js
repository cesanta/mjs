// **DataView API**
//
// See the original API definition at [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/DataView).
//
// mJS DataView diverges from the original in the following ways:
//
// - No `ArrayBuffer`; plain pointers should be used instead;
// - Since there are no constructors in mJS, `DataView.create()` should be
//   used instead;
// - No float support yet (will be added)

let DataView = {
  // ## **`DataView.create(buf, offset, len)`**
  // Create a DataView object instance. `buf` is a pointer to a plain byte
  // array, `offset` is an offset in in this buffer to start dataview from, and
  // `len` is a length managed by dataview.
  //
  // Return value: an object with the methods described below.
  //
  // Example:
  //   ```javascript
  //   load("api_dataview.js");
  //   let calloc = ffi('void *calloc(int, int)');
  //   let ptr = calloc(100, 1);
  //   let dw = DataView.create(ptr, 0, 100);
  //
  //   dw.setUint8(2, 0xff);
  //   ```
  create: function(buf, off, len) {
    let ret = Object.create(this._prot);
    if (off !== undefined) {
      buf += off;
    }
    ret._buf = buf;
    ret._len = len;
    return ret;
  },

  _prot: {

    // ## **`myDW.getInt8(idx)`**
    // Get a signed byte value from the dataview's buffer at the given index
    // `idx`. Returned value: a number from -128 to 127.
    getInt8: function(idx) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      return DataView._gets(
        DataView._pk(this._buf, idx), 1, false
      );
    },

    // ## **`myDW.getUint8(idx)`**
    // Get an unsigned byte value from the dataview's buffer at the given index
    // `idx`. Returned value: a number from 0 to 255.
    getUint8: function(idx) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      return DataView._getu(
        DataView._pk(this._buf, idx), 1, false
      );
    },

    // ## **`myDW.getInt16(idx, le)`**
    // Get a signed 2-byte value from the dataview's buffer at the given index
    // `idx`. By default the data interpreted as big-endian; if `le` is true,
    // then little-endian will be used.
    // Returned value: a number from -32768 to 32767.
    getInt16: function(idx, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      return DataView._gets(
        DataView._pk(this._buf, idx), 2, !le
      );
    },

    // ## **`myDW.getUint16(idx, le)`**
    // Get an unsigned 2-byte value from the dataview's buffer at the given
    // index `idx`. By default the data interpreted as big-endian; if `le` is
    // true, then little-endian will be used.
    // Returned value: a number from 0 to 65535.
    getUint16: function(idx, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      return DataView._getu(
        DataView._pk(this._buf, idx), 2, !le
      );
    },

    // ## **`myDW.getInt32(idx, le)`**
    // Get a signed 4-byte value from the dataview's buffer at the given index
    // `idx`. By default the data interpreted as big-endian; if `le` is true,
    // then little-endian will be used.
    // Returned value: a number from -2147483648 to 2147483647.
    getInt32: function(idx, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      return DataView._gets(
        DataView._pk(this._buf, idx), 4, !le
      );
    },

    // ## **`myDW.getUint32(idx, le)`**
    // Get an unsigned 4-byte value from the dataview's buffer at the given
    // index `idx`. By default the data interpreted as big-endian; if `le` is
    // true, then little-endian will be used.
    // Returned value: a number from 0 to 4294967295.
    getUint32: function(idx, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      return DataView._getu(
        DataView._pk(this._buf, idx), 4, !le
      );
    },

    // ## **`myDW.setInt8(idx, val)`**
    // Set a signed byte value into the dataview's buffer at the given index
    // `idx`. `val` should be a number from -128 to 127.
    // Returned value: none.
    setInt8: function(idx, val) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 1, false
      );
    },

    // ## **`myDW.setUint8(idx, val)`**
    // Set an unsigned byte value into the dataview's buffer at the given index
    // `idx`. `val` should be a number from -128 to 127.
    // Returned value: none.
    setUint8: function(idx, val) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 1, false
      );
    },

    // ## **`myDW.setInt16(idx, val, le)`**
    // Set a signed 2-byte value into the dataview's buffer at the given index
    // `idx`. `val` should be a number from -32768 to 32767. By default the
    // data is written in big-endian format; if `le` is true, then
    // little-endian will be used.
    // Returned value: none.
    setInt16: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 2, !le
      );
    },

    // ## **`myDW.setUint16(idx, val, le)`**
    // Set an unsigned 2-byte value into the dataview's buffer at the given
    // index `idx`. `val` should be a number from 0 to 65535. By default the
    // data is written in big-endian format; if `le` is true, then
    // little-endian will be used.
    // Returned value: none.
    setUint16: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 2, !le
      );
    },

    // ## **`myDW.setInt32(idx, val, le)`**
    // Set a signed 4-byte value into the dataview's buffer at the given index
    // `idx`. `val` should be a number from -2147483648 to 2147483647. By
    // default the data is written in big-endian format; if `le` is true, then
    // little-endian will be used.
    // Returned value: none.
    setInt32: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 4, !le
      );
    },

    // ## **`myDW.setUint32(idx, val, le)`**
    // Set an unsigned 4-byte value into the dataview's buffer at the given
    // index `idx`. `val` should be a number from 0 to 4294967295. By default
    // the data is written in big-endian format; if `le` is true, then
    // little-endian will be used.
    // Returned value: none.
    setUint32: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 4, !le
      );
    },
  },

  _cl: function(idx, len, ilen) {
    if (len !== undefined && idx + ilen > len) {
      die(DataView._errm);
      return false;
    }
    return true;
  },

  _p: ffi('void *mjs_mem_to_ptr(int)'),
  _pk: ffi('void *mjs_mem_get_ptr(void *, int)'),
  _getu: ffi('double mjs_mem_get_uint(void *, int, int)'),
  _gets: ffi('double mjs_mem_get_int(void *, int, int)'),
  _setu: ffi('void mjs_mem_set_uint(void *, int, int, int)'),
  _errm: "Offset is outside of the bounds of the DataView", 
};
