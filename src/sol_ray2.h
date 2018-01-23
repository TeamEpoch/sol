    /////////////////////////////////////////////////////////////////
   // sol_ray2.h ///////////////////////////////////////////////////
  // Description: Adds 2D ray functionality to Sol. ///////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

#ifndef SOL_RAY2_H
#define SOL_RAY2_H

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Ray2 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray2_init ///
// Description
//   Initializes a ray with a position and a vector.
// Arguments
//   pos: Position (Vec2)
//   vec: Vector (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_init(Vec2 pos, Vec2 vec) {
  Ray2 out = {pos, vec};
  return out;
}

/// ray2_initv ///
// Description
//   Initializes a ray at (0, 0) with a vector.
// Arguments
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_initv(Vec2 v) {
  return ray2_init(vec2_zero(), v);
}

/// ray2_initf ///
// Description
//   Initializes a ray at (0, 0) with a single scalar as the XY values of
//   the vector.
// Arguments
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_initf(Float f) {
  return ray2_initv(vec2_initf(f));
}

/// ray2_zero ///
// Description
//   Initializes a ray with both position and vector set to 0.
// Arguments
//   void
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_zero(void) {
  return ray2_init(vec2_initf(0), vec2_initf(0));
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray2 Core Functions ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray2_norm ///
// Description
//   Normalizes the vector element of a ray.
// Arguments
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_norm(Ray2 r) {
  return ray2_init(r.pos, vec2_norm(r.vec));
}

/// ray2_mag ///
// Description
//   Finds the magnitude of a ray's vector element.
// Arguments
//   r: Ray (Ray2)
// Returns
//   Magnitude (Float)

sol
Float ray2_mag(Ray2 r) {
  return vec2_mag(r.vec);
}

/// ray2_eq ///
// Description
//   Tests two rays for equality.
// Arguments
//   a: Ray (Ray2)
//   b: Ray (Ray2)
//   ep: Epsilon (Float)
// Returns
//   Equality (Bool)

sol
bool ray2_eq(Ray2 a, Ray2 b, Float ep) {
  if (vec2_eq(a.pos, b.pos, ep)){
    vec2_eq(a.vec, b.vec, ep);
  }
  return false;
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray2 Advanced Functions ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray2_rot ///
// Description
//   Rotates the vector element of a ray in degrees.
// Arguments
//   r: Ray (Ray2)
//   deg: Degrees (Float)
// Returns
//   Rotated Ray (Ray2)

sol
Ray2 ray2_rot(Ray2 r, Float deg) {
  return ray2_rotr(r, cv_deg_rad(deg));
}

/// ray2_rotr ///
// Description
//   Rotates the vector element of a ray in radians.
// Arguments
//   r: Ray (Ray2)
//   rad: Radians (Float)
// Returns
//   Rotated Ray (Ray2)

sol
Ray2 ray2_rotr(Ray2 r, Float rad) {
  return ray2_init(r.pos, vec2_rotr(r.vec, rad));
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray2 Basic Functions //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray2_sump ///
// Description
//   Finds the sum of all of the elements of the position element of a ray.
// Arguments
//   r: Ray (Ray2)
// Returns
//   Sum (Float)

sol
Float ray2_sump(Ray2 r) {
  return vec2_sum(r.pos);
}

/// ray2_sumv ///
// Description
//   Finds the sum of all of the elements of the vector element of a ray.
// Arguments
//   r: Ray (Ray2)
// Returns
//   Sum (Float)

sol
Float ray2_sumv(Ray2 r) {
  return vec2_sum(r.vec);
}

/// ray2_addp ///
// Description
//   Adds a position to the position element of a ray.
// Arguments
//   r: Ray (Ray2)
//   p: Position (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_addp(Ray2 r, Vec2 p) {
  return ray2_init(vec2_add(r.pos, p), r.vec);
}

/// ray2_addpf ///
// Description
//   Adds a scalar to both elements of the position element of a ray.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_addpf(Ray2 r, Float f) {
  return ray2_addp(r, vec2_initf(f));
}

/// ray2_addv ///
// Description
//   Adds a vector to the vector element of a ray.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_addv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_add(r.vec, v));
}

/// ray2_addvf ///
// Description
//   Adds a scalar to both elements of the vector element of a ray.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_addvf(Ray2 r, Float f) {
  return ray2_addv(r, vec2_initf(f));
}

/// ray2_subp ///
// Description
//   Subtracts a vector from the position element of a ray.
// Arguments
//   r: Ray (Ray2)
//   p: Position (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_subp(Ray2 r, Vec2 p) {
  return ray2_init(vec2_sub(r.pos, p), r.vec);
}

/// ray2_subpf ///
// Description
//   Subtracts a scalar from both elements of the position element of a ray.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_subpf(Ray2 r, Float f) {
  return ray2_subp(r, vec2_initf(f));
}

/// ray2_psub ///
// Description
//   Subtracts a ray's position element from a position.
// Arguments
//   p: Position (Vec2)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_psub(Vec2 p, Ray2 r) {
  return ray2_init(vec2_sub(p, r.pos), r.vec);
}

/// ray2_pfsub ///
// Description
//   Subtracts a ray's position element from a position comprised of a single
//   scalar.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_pfsub(Float f, Ray2 r) {
  return ray2_psub(vec2_initf(f), r);
}

/// ray2_subv ///
// Description
//   Subtracts a vector from the vector element of a ray.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_subv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_sub(r.vec, v));
}

/// ray2_subvf ///
// Description
//   Subtracts a vector comprised of a single scalar from the vector element of
//   a ray.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_subvf(Ray2 r, Float f) {
  return ray2_subv(r, vec2_initf(f));
}

/// ray2_vsub ///
// Description
//   Subtracts the vector element of a ray from a vector.
// Arguments
//   v: Vector (Vec2)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_vsub(Vec2 v, Ray2 r) {
  return ray2_init(r.pos, vec2_sub(v, r.vec));
}

/// ray2_vfsub ///
// Description
//   Subtracts the vector element of a ray from a vector comprised of a single
//   scalar value.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_vfsub(Float f, Ray2 r) {
  return ray2_vsub(vec2_initf(f), r);
}

/// ray2_mulp ///
// Description
//   Multiplies the position element of a vector by a position.
// Arguments
//   r: Ray (Ray2)
//   p: Position (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_mulp(Ray2 r, Vec2 p) {
  return ray2_init(vec2_mul(r.pos, p), r.vec);
}

/// ray2_mulpf ///
// Description
//   Multiplies the position element of a ray by a position comprised of
//   a single scalar value.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_mulpf(Ray2 r, Float f) {
  return ray2_mulp(r, vec2_initf(f));
}

/// ray2_mulv ///
// Description
//   Multiplies the vector element of a ray by a vector.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_mulv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_mul(r.vec, v));
}

/// ray2_mulvf ///
// Description
//   Multiplies the vector element of a ray by a vector comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_mulvf(Ray2 r, Float f) {
  return ray2_mulv(r, vec2_initf(f));
}

/// ray2_divp ///
// Description
//   Divides the position element of a ray by a position.
// Arguments
//   r: Ray (Ray2)
//   p: Position (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_divp(Ray2 r, Vec2 p) {
  return ray2_init(vec2_div(r.pos, p), r.vec);
}

/// ray2_divpf ///
// Description
//   Divides the position element of a ray by a position comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_divpf(Ray2 r, Float f) {
  return ray2_divp(r, vec2_initf(f));
}

/// ray2_pdiv ///
// Description
//   Divides a position by the position element of a ray.
// Arguments
//   p: Position (Vec2)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_pdiv(Vec2 p, Ray2 r) {
  return ray2_init(vec2_div(p, r.pos), r.vec);
}

/// ray2_pfdiv ///
// Description
//   Divides a position comprised of a single scalar by the position element of
//   a ray.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_pfdiv(Float f, Ray2 r) {
  return ray2_pdiv(vec2_initf(f), r);
}

/// ray2_divv ///
// Description
//   Divides the vector element of a ray by a vector.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_divv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_div(r.vec, v));
}

/// ray2_divvf ///
// Description
//   Divides the vector element of a ray by a vector comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_divvf(Ray2 r, Float f) {
  return ray2_divv(r, vec2_initf(f));
}

/// ray2_vdiv ///
// Description
//   Divides a vector by the vector element of a ray.
// Arguments
//   v: Vector (Vec2)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_vdiv(Vec2 v, Ray2 r) {
  return ray2_init(r.pos, vec2_div(v, r.vec));
}

/// ray2_vfdiv ///
// Description
//   Divides a vector comprised of a single scalar value by the vector element
//   of a ray.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_vfdiv(Float f, Ray2 r) {
  return ray2_vdiv(vec2_initf(f), r);
}

/// ray2_avgp ///
// Description
//   Averages a ray's position element with a position.
// Arguments
//   r: Ray (Ray2)
//   p: Position (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_avgp(Ray2 r, Vec2 p) {
  return ray2_init(vec2_avg(r.pos, p), r.vec);
}

/// ray2_avgpf ///
// Description
//   Averages a ray's position element with a position comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_avgpf(Ray2 r, Float f) {
  return ray2_avgp(r, vec2_initf(f));
}

/// ray2_avgv ///
// Description
//   Averages a ray's vector element with a vector.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_avgv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_avg(r.vec, v));
}

/// ray2_avgvf ///
// Description
//   Averages a ray's vector element with a vector comprised of a single scalar
//   value.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2)

sol
Ray2 ray2_avgvf(Ray2 r, Float f) {
  return ray2_avgv(r, vec2_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray2 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray2_print ///
// Description
//   Show a ray's elements in stdout.
// Arguments
//   r: Ray (Ray2)
// Returns
//   void

sol
void ray2_print(Ray2 r) {
  vec2_print(r.pos);
  vec2_print(r.vec);
}

#endif // SOL_RAY2_H
