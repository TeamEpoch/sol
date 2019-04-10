/*
** ux3.h | The Sol Vector Library | Code for u32x3 and u64x3.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_UX3_H
#define SOL_UX3_H

#ifdef SOL_GNU
  #define UX3_OP(A, OP, B) A OP B
  #define UX3_OPF(V, OP, F) V OP F
  #define UX3_FOP(F, OP, V) F OP V
  #define UX3_OP2(A, AB, B, BC, C) (A AB B) BC C
#else
  #define UX3_OP(A, OP, B) {x(A) OP x(B), y(A) OP y(B), z(A) OP z(B)}
  #define UX3_OPF(V, OP, F) {x(V) OP F, y(V) OP F, z(V) OP F}
  #define UX3_FOP(F, OP, V) {F OP x(V), F OP y(V), F OP z(V)}
  #define UX3_OP2(A, AB, B, BC, C) {(x(A) AB x(B)) BC x(C), (y(A) AB y(B)) BC y(C), (z(A) AB z(B)) BC z(C)}
#endif

#define UX3(T, V) \
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
V V##_zero(void) {    \
  return V##_setf(0); \
}                     \
\
/* Basic Math */\
\
_sol_ \
T V##_sum(V v) {             \
  return x(v) + y(v) + z(v); \
}                            \
\
_sol_ \
V V##_sq(V v) {         \
  return V##_mul(v, v); \
}                       \
\
_sol_ \
V V##_add(V a, V b) {            \
  const V out = UX3_OP(a, +, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_addf(V v, T f) {            \
  const V out = UX3_OPF(v, +, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_sub(V a, V b) {            \
  const V out = UX3_OP(a, -, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_subf(V v, T f) {            \
  const V out = UX3_OPF(v, -, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fsub(T f, V v) {            \
  const V out = UX3_FOP(f, -, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_mul(V a, V b) {            \
  const V out = UX3_OP(a, *, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_mulf(V v, T f) {            \
  const V out = UX3_OPF(v, *, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_div(V a, V b) {            \
  const V out = UX3_OP(a, /, b); \
  return out;                    \
}                                \
\
_sol_ \
V V##_divf(V v, T f) {            \
  const V out = UX3_OPF(v, /, f); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fdiv(T f, V v) {            \
  const V out = UX3_FOP(f, /, v); \
  return out;                     \
}                                 \
\
_sol_ \
V V##_fma(V a, V b, V c) {              \
  const V out = UX3_OP2(a, *, b, +, c); \
  return out;                           \
}                                       \
\
_sol_ \
V V##_fms(V a, V b, V c) {              \
  const V out = UX3_OP2(a, *, b, -, c); \
  return out;                           \
}                                       \

UX3(u8,   u8x3)
UX3(u32, u32x3)
UX3(u64, u64x3)

#undef UX3
#undef UX3_OP
#undef UX3_OPF
#undef UX3_FOP
#undef UX3_OP2

#endif /* SOL_UX3_H */
