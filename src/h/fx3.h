/*
** fx3.h | The Sol Vector Library | Code for f32x3 and f64x3.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_FX3_H
#define SOL_FX3_H

#ifdef __GNUC__
  #define FX3_OP(A, OP, B) A OP B
  #define FX3_OPF(V, OP, F) V OP F
  #define FX3_FOP(F, OP, V) F OP V
  #define FX3_OP2(A, AB, B, BC, C) (A AB B) BC C
#else
  #define FX3_OP(A, OP, B) {x(A) OP x(B), y(A) OP y(B), z(A) OP z(B)}
  #define FX3_OPF(V, OP, F) {x(V) OP F, y(V) OP F, z(V) OP F}
  #define FX3_FOP(F, OP, V) {F OP x(V), F OP y(V), F OP z(V)}
  #define FX3_OP2(A, AB, B, BC, C) {(x(A) OP x(B)) OP x(C), (y(A) OP y(B)) OP y(C), (z(A) OP z(B)) OP z(C)}
#endif

#define FX3(T, V) \
\
_sol_ \
V V##_set(T x, T y, T z) { \
  const V out = {x, y, z}; \
  return out;              \
}                          \
\
_sol_ \
V V##_setf(T f) {          \
  return V##_set(f, f, f); \
}                          \
\
_sol_ \
V V##_zero(void) {        \
  return V##_setf((T) 0); \
}                         \
\
_sol_ \
T V##_sum(V v) {             \
  return x(v) + y(v) + z(v); \
}                            \
\
_sol_ \
V V##_add(V a, V b) {            \
  const V out = FX3_OP(a, +, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_addf(V v, T f) {            \
  const V out = FX3_OPF(v, +, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_sub(V a, V b) {            \
  const V out = FX3_OP(a, -, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_subf(V v, T f) {            \
  const V out = FX3_OPF(v, -, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fsub(T f, V v) {            \
  const V out = FX3_FOP(f, -, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_mul(V a, V b) {            \
  const V out = FX3_OP(a, *, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_mulf(V v, T f) {            \
  const V out = FX3_OPF(v, *, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_div(V a, V b) {            \
  const V out = FX3_OP(a, /, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_divf(V v, T f) {            \
  const V out = FX3_OPF(v, /, f); \
  return out;                     \
}                                 \
 \
_sol_ \
V V##_fdiv(T f, V v) {            \
  const V out = FX3_FOP(f, /, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fma(V a, V b, V c) {              \
  const V out = FX3_OP2(a, *, b, +, c); \
  return out;                           \
}                                       \
\
_sol_ \
V V##_fms(V a, V b, V c) {              \
  const V out = FX3_OP2(a, *, b, -, c); \
  return out;                           \
}

FX3(f32, f32x3)
FX3(f64, f64x3)

#endif /* SOL_FX3_H */
