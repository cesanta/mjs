let Math = {

  // ## **`Math.ceil(x)`**
  // Rounds x upward, returning the smallest integral value that is not less
  // than x.
  ceil: ffi('double ceil(double)'),

  // ## **`Math.floor(x)`**
  // Rounds x downward, returning the largest integral value that is not
  // greater than x.
  floor: ffi('double floor(double)'),

  // ## **`Math.round(x)`**
  // Returns the integral value that is nearest to x, with halfway cases
  // rounded away from zero.
  round: ffi('double round(double)'),

  // ## **`Math.max(x, y)`**
  // Returns the larger of its arguments: either `x` or `y`.
  // If one of the arguments in a NaN, the other is returned.
  max: ffi('double fmax(double, double)'),

  // ## **`Math.min(x, y)`**
  // Returns the smaller of its arguments: either `x` or `y`.
  // If one of the arguments in a NaN, the other is returned.
  min: ffi('double fmin(double, double)'),

  // ## **`Math.abs(x)`**
  // Returns the absolute value of `x`: |x|.
  abs: ffi('double fabs(double)'),

  // ## **`Math.sqrt(x)`**
  // Returns the square root of `x`.
  sqrt: ffi('double sqrt(double)'),

  // ## **`Math.floor(x)`**
  // Returns the base-e exponential function of `x`, which is e raised to the
  // power `x`.
  exp: ffi('double exp(double)'),

  // ## **`Math.log(x)`**
  // Returns the natural logarithm of `x`.
  log: ffi('double log(double)'),

  // ## **`Math.pow(base, exponent)`**
  // Returns `base` raised to the power `exponent`
  pow: ffi('double pow(double, double)'),

  // ## **`Math.sin(x)`**
  // Returns the sine of an angle of `x` radians.
  sin: ffi('double sin(double)'),

  // ## **`Math.cos(x)`**
  // Returns the cosine of an angle of `x` radians.
  cos: ffi('double cos(double)'),

  // ## **`Math.random(x)`**
  // Returns the pseudo-random number from 0.0 to 1.0
  random: function() { return Math.rand() / 0x7fffffff; },

  rand: ffi('int rand()'),
};
