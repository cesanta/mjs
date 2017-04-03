let a = function() {
  return function() {
    return true;
  };
};

let b = function() {
  for (let i = 3; i < 100; i++) return i;
};

let c = function() {
  let i, res = 0;
  for (i = 0; i < 10; i++) {
    if (i < 2) continue;
    res += i;
    break;
  }
  return res;
};

let d = function() {
  let i = -5;
  for (let i = 3; i < 100; i++) 1;
  return i;
};


a()() && b() === 3 && d() === -5 && c() === 2;
