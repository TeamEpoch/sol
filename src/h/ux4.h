/*
** ux4.h | The Sol Vector Library | Code for u32x4 and u64x4.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_UX4_H
#define SOL_UX4_H

#define UX4(T, V) \
\
_sol_ \
V V##_set(T x, T y, T z, T w) { \
  const V out = {x, y, z, w};   \
  return out;                   \
}                               \
\
_sol_ \
V V##_setf(T f) {              \
  return V##_setf(f, f, f, f); \
}

#endif /* SOL_UX4_H */
