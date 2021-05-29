let x = 1;

let a = function() {
  let x = 2;
  {
    let y = 3;
    return y;
  }
};

let b = function() {
  return x;
};

a() === 3 && b() === 1 && x === 1;