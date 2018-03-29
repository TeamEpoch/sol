    /////////////////////////////////////////////////////////////////
   // sol_ray2.h ///////////////////////////////////////////////////
  // Description: Adds 2D ray functionality to Sol. ///////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

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

_sol_
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

_sol_
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

_sol_
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

_sol_
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

_sol_
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

_sol_
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

_sol_
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

_sol_
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

_sol_
Ray2 ray2_rotr(Ray2 r, Float rad) {
  return ray2_init(r.pos, vec2_rotr(r.vec, rad));
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray2 Basic Functions //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray2_add ///
// Description
//   Adds the vector element of one ray with that
//   of another.
// Aruments
//   a: Ray (Ray2)
//   b: Ray (Ray2)
// Returns
//   Ray (Ray2) = {a.pos, a.vec.xy + b.vec.xy}

_sol_
Ray2 ray2_add(Ray2 a, Ray2 b) {
  return ray2_init(a.pos, vec2_add(a.vec, b.vec));
}

/// ray2_addv ///
// Description
//   Adds a vector to the vector element of a ray.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy + v.xyz}

_sol_
Ray2 ray2_addv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_add(r.vec, v));
}

/// ray2_addf ///
// Description
//   Adds a scalar to the vector element of a ray.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy + f}

_sol_
Ray2 ray2_addf(Ray2 r, Float f) {
  return ray2_init(r.pos, vec2_addf(r.vec, f));
}

/// ray2_sub ///
// Description
//   Subtracts the vector element of one ray
//   from that of another.
// Arguments
//   a: Ray (Ray2)
//   b: Ray (Ray2)
// Returns
//   Ray (Ray2) = {a.pos, a.vec.xy + b.vec.xyz}

_sol_
Ray2 ray2_sub(Ray2 a, Ray2 b) {
  return ray2_init(a.pos, vec2_sub(a.vec, b.vec));
}

/// ray2_subv ///
// Description
//   Subtracts a vector from the vector element
//   of a ray.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy - v.xyz}

_sol_
Ray2 ray2_subv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_sub(r.vec, v));
}

/// ray2_vsub ///
// Description
//   Subtracts the vector element of a ray
//   from a vector.
// Arguments
//   v: Vector (Vec2)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2) = {r.pos, v.xy - r.vec.xyz}

_sol_
Ray2 ray2_vsub(Vec2 v, Ray2 r) {
  return ray2_init(r.pos, vec2_sub(v, r.vec));
}

/// ray2_subf ///
// Description
//   Subtracts a scalar from the vector element
//   of a ray.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy - f}

_sol_
Ray2 ray2_subf(Ray2 r, Float f) {
  return ray2_init(r.pos, vec2_subf(r.vec, f));
}

/// ray2_fsub ///
// Description
//   Subtracts the vector element of a ray from
//   a scalar.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2) = {r.pos, f - r.vec.xy}

_sol_
Ray2 ray2_fsub(Float f, Ray2 r) {
  return ray2_init(r.pos, vec2_fsub(f, r.vec));
}

/// ray2_mul ///
// Description
//   Multiplies the vector element of one ray
//   by that of another.
// Arguments
//   a: Ray (Ray2)
//   b: Ray (Ray2)
// Returns
//   Ray (Ray2) = {a.pos, a.vec.xy * b.vec.xyz}

_sol_
Ray2 ray2_mul(Ray2 a, Ray2 b) {
  return ray2_init(a.pos, vec2_mul(a.vec, b.vec));
}

/// ray2_mulv ///
// Description
//   Multiplies the vector element of a ray by
//   a vector.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy * v.xyz}

_sol_
Ray2 ray2_mulv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_mul(r.vec, v));
}

/// ray2_mulf ///
// Description
//   Multiplies the vector element of a ray
//   by a scalar.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy * f}

_sol_
Ray2 ray2_mulf(Ray2 r, Float f) {
  return ray2_init(r.pos, vec2_mulf(r.vec, f));
}

/// ray2_div ///
// Description
//   Divides the vector element of one ray by
//   that of another.
// Arguments
//   a: Ray (Ray2)
//   b: Ray (Ray2)
// Returns
//   Ray (Ray2) = {a.pos, a.vec.xy / b.vec.xyz}

_sol_
Ray2 ray2_div(Ray2 a, Ray2 b) {
  return ray2_init(a.pos, vec2_div(a.vec, b.vec));
}

/// ray2_divv ///
// Description
//   Divides the vector element of a ray by
//   a vector.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy / v.xyz}

_sol_
Ray2 ray2_divv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_div(r.vec, v));
}

/// ray2_vdiv ///
// Description
//   Divides a vector by the vector element
//   of a ray.
// Arguments
//   v: Vector (Vec2)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2) = {r.pos, v.xy / r.vec.xyz}

_sol_
Ray2 ray2_vdiv(Vec2 v, Ray2 r) {
  return ray2_init(r.pos, vec2_div(v, r.vec));
}

/// ray2_divf ///
// Description
//   Divides the vector element of a ray by
//   a scalar.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2) = {r.pos, r.vec.xy + f}

_sol_
Ray2 ray2_divf(Ray2 r, Float f) {
  return ray2_init(r.pos, vec2_divf(r.vec, f));
}

/// ray2_fdiv ///
// Description
//   Divides a scalar by the vector element
//   of a ray.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray2)
// Returns
//   Ray (Ray2) = {r.pos, f / r.vec.xy}

_sol_
Ray2 ray2_fdiv(Float f, Ray2 r) {
  return ray2_init(r.pos, vec2_fdiv(f, r.vec));
}

/// ray2_avg ///
// Description
//   Averages the vector element of one ray
//   by that of another.
// Arguments
//   a: Ray (Ray2)
//   b: Ray (Ray2)
// Returns
//   Ray (Ray2) = {a.pos, (a.vec.xy + b.vec.xy) / 2}

_sol_
Ray2 ray2_avg(Ray2 a, Ray2 b) {
  return ray2_init(a.pos, vec2_avg(a.vec, b.vec));
}

/// ray2_avgv ///
// Description
//   Averages the vector element of a ray
//   with a vector.
// Arguments
//   r: Ray (Ray2)
//   v: Vector (Vec2)
// Returns
//   Ray (Ray2) = {r.pos, (r.vec.xyz + v.xyz) / 2}

_sol_
Ray2 ray2_avgv(Ray2 r, Vec2 v) {
  return ray2_init(r.pos, vec2_avg(r.vec, v));
}

/// ray2_avgf ///
// Description
//   Averages the vector element of a ray
//   with a scalar.
// Arguments
//   r: Ray (Ray2)
//   f: Scalar (Float)
// Returns
//   Ray (Ray2) = {r.pos, (r.vec.xyz + f) / 2}

_sol_
Ray2 ray2_avgf(Ray2 r, Float f) {
  return ray2_init(r.pos, vec2_avgf(r.vec, f));
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

_sol_
void ray2_print(Ray2 r) {
  vec2_print(r.pos);
  vec2_print(r.vec);
}
