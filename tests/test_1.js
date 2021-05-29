let o = {a: 1, 'b': 2, c: {d: 3}, d: [1, 2, 3, 'xx']};
let a = 'foo', b = 'bar';
let s1 = 'a' + "b";
let s2 = 'abcdef' + "123456";
1 - 2 + 3 + o['a'] + o.c.d + o.b === 8 && a === "foo" && a !== b &&
    s1 === 'ab' && s2 === 'abcdef123456' && o.d[0] === 1 && o.d[3] === 'xx' &&
    o.d[4] === undefined;
