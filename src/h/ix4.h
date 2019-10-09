/*
** ix4.h | The Sol Vector Library | Code for i32x4 and i64x4.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_IX4_H
#define SOL_IX4_H

#ifdef SOL_GNU
  #define IX4_OP(A, OP, B) A OP B
  #define IX4_OPF(V, OP, F) V OP F
  #define IX4_FOP(F, OP, V) F OP V
  #define IX4_OP2(A, AB, B, BC, C) (A AB B) BC C
#else
  #define IX4_OP(A, OP, B) {x(A) OP x(B), y(A) OP y(B), z(A) OP z(B), w(A) OP w(B)}
  #define IX4_OPF(V, OP, F) {x(V) OP F, y(V) OP F, z(V) OP F, w(V) OP F}
  #define IX4_FOP(F, OP, V) {F OP x(V), F OP y(V), F OP z(V), F OP w(V)}
  #define IX4_OP2(A, AB, B, BC, C) {(x(A) AB x(B)) BC x(C), (y(A) AB y(B)) BC y(C), (z(A) AB z(B)) BC z(C), (w(A) AB w(B)) BC w(C)}
#endif

#define IX4(T, V) \
\
/* Initializers */ \
\
_sol_ \
V V##_set(T x, T y, T z, T w) { \
  const V out = {x, y, z, w};   \
  return out;                   \
} \
\
_sol_ \
V V##_setf(T f) {             \
  return V##_set(f, f, f, f); \
}                             \
\
_sol_ \
V V##_zero(void) {          \
  return V##_setf((T) 0);   \
}                           \
\
/* Basic Math */ \
\
_sol_ \
T V##_sum(V v) {                    \
  return x(v) + y(v) + z(v) + w(v); \
}                                   \
\
_sol_ \
V V##_add(V a, V b) {              \
  const V out = IX4_OP(a, +, b);   \
  return out;                      \
}                                  \
\
_sol_ \
V V##_addf(V v, T f) {              \
  const V out = IX4_OPF(v, +, f);   \
  return out;                       \
}                                   \
\
_sol_ \
V V##_sub(V a, V b) {              \
  const V out = IX4_OP(a, -, b);   \
  return out;                      \
}                                  \
\
_sol_ \
V V##_subf(V v, T f) {              \
  const V out = IX4_OPF(v, -, f);   \
  return out;                       \
}                                   \
\
_sol_ \
V V##_mul(V a, V b) {              \
  const V out = IX4_OP(a, *, b);   \
  return out;                      \
}                                  \
\
_sol_ \
V V##_mulf(V v, T f) {              \
  const V out = IX4_OPF(v, *, f);   \
  return out;                       \
}                                   \
\
_sol_ \
V V##_div(V a, V b) {              \
  const V out = IX4_OP(a, /, b);   \
  return out;                      \
}                                  \
\
_sol_ \
V V##_divf(V v, T f) {              \
  const V out = IX4_OPF(v, /, f);   \
  return out;                       \
}                                   \
\
_sol_ \
V V##_fdiv(T f, V v) {              \
  const V out = IX4_FOP(f, /, v);   \
  return out;                       \
}                                   \
\
_sol_ \
V V##_fma(V a, V b, V c) {                \
  const V out = IX4_OP2(a, *, b, +, c); \
  return out;                           \
}                                         \
\
_sol_ \
V V##_fms(V a, V b, V c) {                \
  const V out = IX4_OP2(a, *, b, -, c); \
  return out;                           \
}                                         \

IX4(i8,   i8x4)
IX4(i16, i16x4)
IX4(i32, i32x4)
IX4(i64, i64x4)

#undef IX4
#undef IX4_OP
#undef IX4_OPF
#undef IX4_FOP
#undef IX4_OP2

#endif /* SOL_IX4_H */
