   /////////////////////////////////////////////////////////////////
  // sol_sph3.c | 3D sphere functionality for Sol. ////////////////
 // Source: https://github.com/davidgarland/sol //////////////////
/////////////////////////////////////////////////////////////////

#ifndef SOL_SPH3_H
#define SOL_SPH3_H

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Sph3 Initializers /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// sph3_init ///
// Description
//   Initializes a new sphere with
//   a position and radius.
// Arguments
//   pos: Position (Vec3)
//   rad: Radius (Float)
// Returns
//   Sphere (Sph3)

_sol_
Sph3 sph3_init(Vec3 pos, Float rad) {
  const Sph3 out = {pos, rad};
  return out;
}

/// sph3_zero ///
// Description
//   Initializes a new sphere at (0, 0)
//   with a radius of 0.
// Arguments
//   pos: Position (Vec3)
//   rad: Radius (Float)
// Returns
//   Sphere (Sph3)

_sol_
Sph3 sph3_zero(void) {
  return sph3_init(vec3_zero(), (Float) 0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Sph3 Advanced Functions ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// sph3_pip ///
// Description
//   Performs a point-in-polygon test on
//   a sphere within an epsilon.
// Arguments
//   s: Sphere (Sph3)
//   p: Point (Vec3)
//   ep: Epsilon (Float)
// Returns
//   Point in Polygon (bool)

_sol_
bool sph3_pip(Sph3 s, Vec3 p) {
  return flt_abs(vec3_mag(p - s.pos)) < s.rad;
}

#endif
