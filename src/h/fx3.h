/*
** fx3.h | The Sol Vector Library | Code for f32x3 and f64x3.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_FX3_H
#define SOL_FX3_H

#ifdef SOL_GNU
  #define FX3_OP(A, OP, B) A OP B
  #define FX3_OPF(V, OP, F) V OP F
  #define FX3_FOP(F, OP, V) F OP V
  #define FX3_OP2(A, AB, B, BC, C) (A AB B) BC C
#else
  #define FX3_OP(A, OP, B) {x(A) OP x(B), y(A) OP y(B), z(A) OP z(B)}
  #define FX3_OPF(V, OP, F) {x(V) OP F, y(V) OP F, z(V) OP F}
  #define FX3_FOP(F, OP, V) {F OP x(V), F OP y(V), F OP z(V)}
  #define FX3_OP2(A, AB, B, BC, C) {(x(A) AB x(B)) BC x(C), (y(A) AB y(B)) BC y(C), (z(A) AB z(B)) BC z(C)}
#endif

#define FX3(T, V, Q) \
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
/* Vector Transformations */\
_sol_ \
V V##_rot(V v, Q q) { \
  return V##_zero(); \
} \
\
_sol_ \
V V##_scale(V v, T f) { \
 return V##_mulf(V##_norm(v), f); \
} \
\
/* Vector Math */ \
_sol_ \
V V##_norm(V v) { \
  return V##_divf(v, V##_mag(v)); \
} \
\
_sol_ \
T V##_mag(V v) { \
 return T##_sqrt(V##_dot(v, v)); \
} \
\
_sol_ \
V V##_proj(V a, V b) {                                    \
  return V##_mulf(a, V##_dot(a, b) / T##_sq(V##_mag(a))); \
}                                                         \
\
_sol_ \
V V##_rej(V a, V b) { \
  return V##_sub(a, V##_proj(a, b)); \
} \
\
_sol_ \
T V##_angle(V a, V b) {                                       \
  return T##_acos(V##_dot(a, b) / (V##_mag(a) / V##_mag(b))); \
}                                                             \
\
_sol_ \
V V##_cross(V a, V b) {                                \
  const V va = V##_yzx(a);                             \
  const V vb = V##_yzx(b);                             \
  const V c = V##_sub(V##_mul(a, vb), V##_mul(b, va)); \
  return V##_yzx(c);                                   \
}                                                      \
\
_sol_ \
T V##_dot(V a, V b) {            \
  return V##_sum(V##_mul(a, b)); \
}                                \
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
}                                       \
\
_sol_ \
V V##_yzx(V v) { \
  return V##_zero(); /* TODO */ \
}

FX3(f32, f32x3, f32x4)
FX3(f64, f64x3, f64x4)

#undef FX3
#undef FX3_OPF
#undef FX3_FOP
#undef FX3_OP2

_sol_
f32x3 f32x2_swiz(f32x3 v, i32x3 m) {
  #if defined(SOL_GNU) && defined(__AVX__)
    return (f32x4) _mm_blendv_ps(v, v, (f32x4) m);
  #else
    f32x3 out;
    x(out) = vec(v)[x(m)];
    y(out) = vec(v)[y(m)];
    z(out) = vec(v)[z(m)];
    return out;
  #endif
}

_sol_
f64x3 f64x3_swiz(f64x3 v, i64x3 m) {
  #if defined(SOL_GNU) && defined(__AVX__)  
    return (f64x4) _mm256_blendv_pd(v, v, (f64x4) m);
  #else
    f64x3 out;
    x(out) = vec(v)[x(m)];
    y(out) = vec(v)[y(m)];
    z(out) = vec(v)[z(m)];
    return out;
  #endif
}

#endif /* SOL_FX3_H */
