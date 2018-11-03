/*
** sol.h | The Sol Vector Library | Main Header
** https://github.com/davidgarland/sol
*/

#ifndef SOL_H
#define SOL_H

/*
** Scalar Accessors
*/

#ifdef __GNUC__
  #define x(V) V[0]
  #define y(V) V[1]
  #define z(V) V[2]
  #define w(V) V[3]
#else
  #define x(V) V.x
  #define y(V) V.y
  #define z(V) V.z
  #define w(V) V.w
#endif

#endif /* SOL_H */
