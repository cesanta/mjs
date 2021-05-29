let a = function() {
  let y = 17;
  let boo = function() {
    return y;
  };
  return boo();
};

a() === 17;
