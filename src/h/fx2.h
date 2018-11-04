/*
** fx2.h | The Sol Vector Library | Code for f32x2 and f64x2.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_FX2_H
#define SOL_FX2_H

#ifdef __GNUC__
  #define FX2_OP(A, OP, B) A OP B
  #define FX2_OPF(V, OP, F) V OP F
  #define FX2_FOP(F, OP, V) F OP V
#else
  #define FX2_OP(A, OP, B) {x(A) OP x(B), y(A) OP y(B)}
  #define FX2_OPF(V, OP, F) {x(V) OP F, y(V) OP F}
  #define FX2_FOP(F, OP, V) {F OP x(V), F OP y(V)}
#endif

#define FX2(T, V) \
\
/* Initializers */ \
\
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
}                       \
\
/* Basic Math */ \
\
V V##_add(V a, V b) {            \
  const V out = FX2_OP(a, +, b); \
  return out;                    \
}                                \
\
V V##_addf(V v, T f) {            \
  const V out = FX2_OPF(v, +, f); \
  return out;                     \
}                                 \
\
V V##_sub(V a, V b) {            \
  const V out = FX2_OP(a, -, b); \
  return out;                    \
}                                \
\
V V##_subf(V v, T f) {            \
  const V out = FX2_OPF(v, -, f); \
  return out;                     \
}                                 \
\
V V##_fsub(T f, V v) {            \
  const V out = FX2_FOP(f, -, v); \
  return out;                     \
}

FX2(f32, f32x2);
FX2(f64, f64x2);

#undef FX2
#undef FX2_OP
#undef FX2_OPF
#undef FX2_FOP

#endif /* SOL_FX2_H */
