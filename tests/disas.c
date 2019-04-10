#include "../sol.h"

f32x2 fma32x2(f32x2 a, f32x2 b, f32x2 c) {
  return f32x2_fma(a, b, c);
}

f32x4 fma32x4(f32x4 a, f32x4 b, f32x4 c) {
  return f32x4_fma(a, b, c);
}

f64x2 fma64x2(f64x2 a, f64x2 b, f64x2 c) {
  return f64x2_fma(a, b, c);
}

f64x4 fma64x4(f64x4 a, f64x4 b, f64x4 c) {
  return f64x4_fma(a, b, c);
}
