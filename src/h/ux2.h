/*
** ux2.h | The Sol Vector Library | Code for u32x2 and u64x2.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_UX2_H
#define SOL_UX2_H

#define UX2(T, V) \
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
}

UX2(u8,   u8x2)
UX2(u32, u32x2)
UX2(u64, u64x2)

#undef UX2

#endif /* SOL_UX2_H */
