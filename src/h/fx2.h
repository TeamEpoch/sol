/*
** fx2.h | The Sol Vector Library | Code for f32x2 and f64x2.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_FX2_H
#define SOL_FX2_H

/*
** Convenience Macros
*/

#ifdef SOL_GNU
  #define FX2_OP(A, OP, B) A OP B
  #define FX2_OPF(V, OP, F) V OP F
  #define FX2_FOP(F, OP, V) F OP V
  #define FX2_OP2(A, AB, B, BC, C) (A AB B) BC C
#else
  #define FX2_OP(A, OP, B) {x(A) OP x(B), y(A) OP y(B)}
  #define FX2_OPF(V, OP, F) {x(V) OP F, y(V) OP F}
  #define FX2_FOP(F, OP, V) {F OP x(V), F OP y(V)}
  #define FX2_OP2(A, AB, B, BC, C) {(x(A) AB x(B)) BC x(C), (y(A) AB y(B)) BC y(C)}
#endif

/*
** Definer Macros
*/

#define FX2(T, V) \
\
/* Initializers */ \
\
_sol_ \
V V##_set(T x, T y) {   \
  const V out = {x, y}; \
  return out;           \
}                       \
\
_sol_ \
V V##_setf(T f) {       \
  return V##_set(f, f); \
}                       \
\
_sol_ \
V V##_zero(void) {      \
  return V##_setf(0);   \
}                       \
\
/* Vector Transformations */\
\
_sol_ \
V V##_rot(V v, T rad) {                  \
  const T cs = T##_cos(rad);             \
  const T sn = T##_sin(rad);             \
  return V##_set(x(v) * cs - y(v) * sn,  \
                 x(v) * sn + y(v) * cs); \
}                                        \
\
_sol_ \
V V##_scale(V v, T f) {            \
  return V##_mulf(V##_norm(v), f); \
}                                  \
\
/* Vector Math */ \
\
_sol_ \
V V##_norm(V v) {                 \
  return V##_divf(v, V##_mag(v)); \
}                                 \
\
_sol_ \
T V##_mag(V v) {                  \
  return T##_sqrt(V##_dot(v, v)); \
}                                 \
\
_sol_ \
V V##_proj(V a, V b) {                               \
  const T f = V##_mag(a) * T##_cos(V##_angle(a, b)); \
  return V##_mulf(b, f);                             \
} \
\
_sol_ \
V V##_rej(V a, V b) {                \
  return V##_sub(a, V##_proj(a, b)); \
}                                    \
\
_sol_ \
T V##_angle(V a, V b) {                             \
  return T##_atan2(V##_cross(a, b), V##_dot(a, b)); \
}                                                   \
\
_sol_ \
T V##_cross(V a, V b) { \
  return x(a) * y(b)    \
       - x(b) * y(a);   \
}                       \
\
_sol_ \
T V##_dot(V a, V b) {            \
  return V##_sum(V##_mul(a, b)); \
}                                \
\
/* Basic Math */ \
\
_sol_ \
T V##_sum(V v) {      \
  return x(v) + y(v); \
}                     \
\
_sol_ \
V V##_sq(V v) {         \
  return V##_mul(v, v); \
}                       \
\
_sol_ \
V V##_add(V a, V b) {            \
  const V out = FX2_OP(a, +, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_addf(V v, T f) {            \
  const V out = FX2_OPF(v, +, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_sub(V a, V b) {            \
  const V out = FX2_OP(a, -, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_subf(V v, T f) {            \
  const V out = FX2_OPF(v, -, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fsub(T f, V v) {            \
  const V out = FX2_FOP(f, -, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_mul(V a, V b) {            \
  const V out = FX2_OP(a, *, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_mulf(V v, T f) {            \
  const V out = FX2_OPF(v, *, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_div(V a, V b) {            \
  const V out = FX2_OP(a, /, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_divf(V v, T f) {            \
  const V out = FX2_OPF(v, /, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fdiv(T f, V v) {            \
  const V out = FX2_FOP(f, /, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fma(V a, V b, V c) {              \
  const V out = FX2_OP2(a, *, b, +, c); \
  return out;                           \
}                                       \
\
_sol_ \
V V##_fms(V a, V b, V c) {              \
  const V out = FX2_OP2(a, *, b, -, c); \
  return out;                           \
}

FX2(f32, f32x2)
FX2(f64, f64x2)

#undef FX2
#undef FX2_OP
#undef FX2_OPF
#undef FX2_FOP
#undef FX2_OP2

#endif /* SOL_FX2_H */
