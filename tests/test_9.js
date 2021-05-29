let o = {};
load('tests/module1.js');
let a = o.foo === undefined;
load('tests/module1.js', o);
let b = o.foo === 1;
a && b && foo + 2 + o.foo === 4;
