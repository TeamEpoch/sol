/*
** fx2.h | The Sol Vector Library | Code for f32x2 and f64x2.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_FX2_H
#define SOL_FX2_H

#define FX2(T, V) \
\
/* Initializers */      \
V V##_set(T x, T y) {   \
  const V out = {x, y}; \
  return out;           \
}                       \
                        \
V V##_setf(T f) {       \
  return V##_set(f, f); \
}                       \
                        \
V V##_zero(void) {      \
  return V##_setf(0);   \
}

FX2(f32, f32x2)
FX2(f64, f64x2)

#endif /* SOL_FX2_H */
