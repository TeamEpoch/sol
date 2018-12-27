/*
** ix2.h | The Sol Vector Library | Code for i32x2 and i64x2.
** https://github.com/davidgarland/sol
*/

#ifndef SOL_IX2_H
#define SOL_IX2_H

#define IX2(T, V) \
\
V V##_set(T x, T y) { \
  const V out = {x, y}; \
  return out; \
} \
\

#endif /* SOL_IX2_H */
