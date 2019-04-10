/*
** ix2.h | The Sol Vector Library | Code for i32x2 and i64x2.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_IX2_H
#define SOL_IX2_H

#ifdef SOL_GNU
  #define IX2_OP(A, OP, B) A OP B
  #define IX2_OPF(V, OP, F) V OP F
  #define IX2_FOP(F, OP, V) F OP V
  #define IX2_OP2(A, AB, B, BC, C) (A AB B) BC C
#else
  #define IX2_OP(A, OP, B) {x(A) OP x(B), y(A) OP y(B)}
  #define IX2_OPF(V, OP, F) {x(V) OP F, y(V) OP F}
  #define IX2_FOP(F, OP, V) {F OP x(V), F OP y(V)}
  #define IX2_OP2(A, AB, B, BC, C) {(x(A) AB x(B)) BC x(C), (y(A) AB y(B)) BC y(C)}
#endif

#define IX2(T, V) \
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
V V##_zero(void) {    \
  return V##_setf(0); \
}                     \
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
  const V out = IX2_OP(a, +, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_addf(V v, T f) {            \
  const V out = IX2_OPF(v, +, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_sub(V a, V b) {            \
  const V out = IX2_OP(a, -, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_subf(V v, T f) {            \
  const V out = IX2_OPF(v, -, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fsub(T f, V v) {            \
  const V out = IX2_FOP(f, -, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_mul(V a, V b) {            \
  const V out = IX2_OP(a, *, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_mulf(V v, T f) {            \
  const V out = IX2_OPF(v, *, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_div(V a, V b) {            \
  const V out = IX2_OP(a, /, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_divf(V v, T f) {            \
  const V out = IX2_OPF(v, /, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fdiv(T f, V v) {            \
  const V out = IX2_FOP(f, /, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fma(V a, V b, V c) {              \
  const V out = IX2_OP2(a, *, b, +, c); \
  return out;                           \
}                                       \
\
_sol_ \
V V##_fms(V a, V b, V c) {              \
  const V out = IX2_OP2(a, *, b, -, c); \
  return out;                           \
}                                       \

IX2(i32, i32x2)
IX2(i64, i64x2)

#undef IX2
#undef IX2_OP
#undef IX2_OPF
#undef IX2_FOP
#undef IX2_OP2

#endif /* SOL_IX2_H */
