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

#define FX1(T, U) \
\
/* Math Functions */ \
\
_sol_ \
T T##_sq(T f) { \
  return f * f; \
}               \
\
_sol_ \
T T##_sqrt(T f) {                               \
  return (sizeof(T) == 8) ? sqrt(f) : sqrtf(f); \
}                                               \
\
_sol_ \
T T##_abs(T f) {                              \
  U* u = ((U*) &f);                           \
  *u &= (sizeof(T) == 8) ? 0x7fffffffffffffff \
      : 0x7fffffff;                           \
  return f;                                   \
}                                             \
\
_sol_ \
T T##_neg(T f) {                               \
  U* u = ((U*) &f);                            \
  *u |= (sizeof(T) == 8) ? ~0x7fffffffffffffff \
      : ~0x7fffffff;                           \
  return f;                                    \
}                                              \
\
_sol_ \
T T##_neg_if(T f, u64 cond) {                         \
  if (cond)                                           \
    cond |= (sizeof(T) == 8) ? ~0ull : ~0u;           \
  U* u = ((U*) &f);                                   \
  *u |= (sizeof(T) == 8) ? cond & ~0x7fffffffffffffff \
      : cond & ~0x7fffffff;                           \
  return f;                                           \
}                                                     \
\
_sol_ \
T T##_mod(T x, T y) { \
  x = x / y;          \
  if (sizeof(T) == 8) \
    x -= (i64) x;     \
  else                \
    x -= (i32) x;     \
  return x * y;       \
}                     \
\
/* Trig Functions */ \
\
_sol_ \
T T##_sin(T f) {                \
  return T##_cos(f - T##_pi_2); \
}                               \
\
_sol_ \
T T##_cos_raw(T f) {                \
  float f2 = f * f;                 \
  float numer = T##_pi_sq - 4 * f2; \
  return numer / (T##_pi_sq + f2);  \
}                                   \
\
_sol_ \
T T##_cos(T f) {                              \
  float fp2 = f + T##_pi_2;                   \
  float s = -T##_mod(fp2, T##_pi) + T##_pi_2; \
  float o = T##_cos_raw(s);                   \
  u64 cond = T##_mod(fp2, T##_tau) > T##_pi;  \
  o = T##_neg_if(o, cond);                    \
  return o;                                   \
}                                             \
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

FX1(f32, u32)
FX1(f64, u64)

#ifdef __clang__
  #pragma clang diagnostic pop /* -Wdouble-promotion */
  #pragma clang diagnostic pop /* -Wfloat-conversion */
  #pragma clang diagnostic pop /* -Wconversion       */
#endif

#endif /* SOL_FX1_H */
