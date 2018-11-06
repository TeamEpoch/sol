/*
** fx1.h | The Sol Vector Library | Code for f32 and f64.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_FX1_H
#define SOL_FX1_H

#define FX1(T) \
\
/* Trig Functions */ \
\
_sol_ \
T T##_sin(T f) {                              \
  return (sizeof(T) == 8) ? sin(f) : sinf(f); \
}                                             \
\
_sol_ \
T T##_cos(T f) {                              \
  return (sizeof(T) == 8) ? cos(f) : cosf(f); \
}                                             \
\
_sol_ \
T T##_tan(T f) {                              \
  return (sizeof(T) == 8) ? tan(f) : tanf(f); \
}                                             \
\
_sol_ \
T T##_asin(T f) {                               \
  return (sizeof(T) == 8) ? asin(f) : asinf(f); \
}                                               \
\
_sol_ \
T T##_acos(T f) {                               \
  return (sizeof(T) == 8) ? acos(f) : acosf(f); \
}                                               \
\
_sol_ \
T T##_atan(T f) {                               \
  return (sizeof(T) == 8) ? atan(f) : atanf(f); \
}                                               \
\
_sol_ \
T T##_atan2(T y, T x) {                                 \
  return (sizeof(T) == 8) ? atan2(y, x) : atan2f(y, x); \
}

FX1(f32)
FX1(f64)

#endif /* SOL_FX1_H */
