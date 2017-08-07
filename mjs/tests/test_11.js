let s = '{"a": 1, "b": "foo", "c": true, "d": [null], "e": "1\\n2"}';
let o = JSON.parse(s);
let z = JSON.parse('""');  // Zero-length string
let s2 = JSON.stringify(o);
s2 === '{"e":"1\\n2","d":[null],"c":true,"b":"foo","a":1}' && o.c && o.a === 1 && o.e === '1\n2' && z === '';
