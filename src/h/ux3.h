/*
** ux3.h | The Sol Vector Library | Code for u32x3 and u64x3.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_UX3_H
#define SOL_UX3_H

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
}

UX3(u8,   u8x3)
UX3(u32, u32x3)
UX3(u64, u64x3)

#undef UX3

#endif /* SOL_UX3_H */
