   //                                                   ////////////////////////
  // sol_sph2.c | Adds 2D sphere functionality to Sol. ////////////////////////
 // https://github.com/davidgarland/sol               ////////////////////////
//                                                   ////////////////////////

#include "../sol.h"

  //                   /////////////////////////////////////////////////////////
 // Sph2 Initializers /////////////////////////////////////////////////////////
//                   /////////////////////////////////////////////////////////

/// sph2_init ///
// Description
//   Initialize a sphere with a position and
//   radius.
// Aruments
//   pos: Position (Vec2)
//   rad: Radius (Float)
// Returns
//   Sphere (Sph2)

_sol_
Sph2 sph2_init(Vec2 pos, Float rad) {
  Sph2 out = {pos, rad};
  return out;
}

/// sph2_zero ///
// Description
//   Initializes a sphere at the origin with
//   a radius of zero.
// Arguments
//   void
// Returns
//   Sphere (Sph2)

_sol_
Sph2 sph2_zero(void) {
  return sph2_init(vec2_zero(), (Float) 0);
}

  //                         ///////////////////////////////////////////////////
 // Sph2 Advanced Functions ///////////////////////////////////////////////////
//                         ///////////////////////////////////////////////////

/// sph2_pip ///
// Description
//   Perform a point-in-polygon test on a sphere.
// Arguments
//   s: Sphere (Sph2)
//   p: Point (Vec2)
// Returns
//   Point In Polygon (bool)

_sol_
bool sph2_pip(Sph2 s, Vec2 p) {
  return flt_abs(vec2_mag(p - s.pos)) < s.rad;
}
