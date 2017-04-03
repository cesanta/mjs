let s = '{"a": 1, "b": "foo", "c": true, "d": [null]}';
let o = JSON.parse(s);
let s2 = JSON.stringify(o);
s2 === '{"d":[null],"c":true,"b":"foo","a":1}' && o.c && o.a === 1;
