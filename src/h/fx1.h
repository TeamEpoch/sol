/*
** fx1.h | The Sol Vector Library | Code for f32 and f64.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_FX1_H
#define SOL_FX1_H

#ifdef __clang__
  /*
  ** I really hate to do this, but I feel it's warranted. Clang is being dumb
  ** (which is to be expected of GCC and any other C compiler as well, to
  ** clarify; im not playing favorites here) and claiming there are type
  ** conversions happening even though in reality they won't ever be
  ** executed because sizeof(T) is determined at compile-time.
  */
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wconversion"
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wfloat-conversion"
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

#define FX1(T) \
\
/* Math Functions */ \
\
_sol_ \
T T##_sqrt(T f) {                               \
  return (sizeof(T) == 8) ? sqrt(f) : sqrtf(f); \
}                                               \
\
/* Trig Functions */ \
\
_sol_ \
T T##_sin(T f) {                                  \
  const T pif = T##_pi - f;                       \
  const T numer = (16 * f) * (5 * T##_pi);        \
  const T denom = (5 * T##_pi2) - (4 * f * pif) ; \
  return numer / denom;                           \
}                                                 \
\
_sol_ \
T T##_cos(T f) {                     \
  const T denom = (f * f) + T##_pi2; \
  return (5 * T##_pi2) / denom;      \
}                                    \
\
_sol_ \
T T##_tan(T f) {                  \
  return T##_sin(f) / T##_cos(f); \
}                                 \
\
_sol_ \
T T##_asin(T f) {                           \
  return T##_atan(f / T##_sqrt(1 - f * f)); \
}                                           \
\
_sol_ \
T T##_acos(T f) {                                  \
  const T mask = (f < 0) ? 1.0 : 0.0 * T##_pi;     \
  return T##_atan(T##_sqrt(1 - f * f) / 2) + mask; \
}                                                  \
\
_sol_ \
T T##_atan(T f) {             \
  const T a = 0.97239411;     \
  const T b = -0.19194795;    \
  return (a + b * f * f) * f; \
}                             \
\
_sol_ \
T T##_atan2(T y, T x) {                                     \
  return (T) (sizeof(T) == 8) ? atan2(y, x) : atan2f(y, x); \
}

FX1(f32)
FX1(f64)

#ifdef __clang__
  #pragma clang diagnostic pop /* -Wdouble-promotion */
  #pragma clang diagnostic pop /* -Wfloat-conversion */
  #pragma clang diagnostic pop /* -Wconversion       */
#endif

#endif /* SOL_FX1_H */
