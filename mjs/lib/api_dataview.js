// DataView API.
//
// See the original API definition at [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/DataView).
//
// mJS DataView diverges from the original in the following ways:
//
// - No `ArrayBuffer`; plain pointers should be used instead;
// - Since there are no constructors in mJS, `DataView.create()` should be
//   used instead;
// - No float support yet (will be added)
//
// Example:
//
//   ```javascript
//   load("lib/api_dataview.js");
//   let calloc = ffi('void *calloc(int, int)');
//   let ptr = calloc(100, 1);
//   let dw = DataView.create(ptr, 0, 100);
//
//   dw.setUint8(0xff);
//   ```

let DataView = {
  _prot: {
    getInt8: function(idx) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      return DataView._gets(
        DataView._pk(this._buf, idx), 1, false
      );
    },
    getUint8: function(idx) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      return DataView._getu(
        DataView._pk(this._buf, idx), 1, false
      );
    },
    getInt16: function(idx, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      return DataView._gets(
        DataView._pk(this._buf, idx), 2, !le
      );
    },
    getUint16: function(idx, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      return DataView._getu(
        DataView._pk(this._buf, idx), 2, !le
      );
    },
    getInt32: function(idx, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      return DataView._gets(
        DataView._pk(this._buf, idx), 4, !le
      );
    },
    getUint32: function(idx, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      return DataView._getu(
        DataView._pk(this._buf, idx), 4, !le
      );
    },

    setInt8: function(idx, val) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 1, false
      );
    },
    setUint8: function(idx, val) {
      if (!DataView._cl(idx, this._len, 1)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 1, false
      );
    },
    setInt16: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 2, !le
      );
    },
    setUint16: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 2)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 2, !le
      );
    },
    setInt32: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 4, !le
      );
    },
    setUint32: function(idx, val, le) {
      if (!DataView._cl(idx, this._len, 4)) {
        return undefined;
      }
      DataView._setu(
        DataView._pk(this._buf, idx), val, 4, !le
      );
    },
  },

  create: function(buf, off, len) {
    let ret = Object.create(this._prot);
    if (off !== undefined) {
      buf += off;
    }
    ret._buf = buf;
    ret._len = len;
    return ret;
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
