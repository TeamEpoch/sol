    /////////////////////////////////////////////////////////////////
   // sol_ray3.h ///////////////////////////////////////////////////
  // Description: Adds 3D ray functionality to Sol. ///////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Ray3 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray3_init ///
// Description
//   Initializes a ray with a position and vector.
// Arguments
//   pos: Position (Vec3)
//   vec: Vector (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_init(Vec3 pos, Vec3 vec) {
  Ray3 out = {pos, vec};
  return out;
}

/// ray3_initv ///
// Description
//   Initializes a ray at (0, 0, 0) with a vector.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_initv(Vec3 v) {
  return ray3_init(vec3_zero(), v);
}

/// ray3_initf ///
// Description
//   Initializes a ray at (0, 0, 0) with a scalar as the XYZ values of the
//   vector.
// Arguments
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_initf(Float f) {
  return ray3_initv(vec3_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray3 Core Functions ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray3_norm ///
// Description
//   Normalizes the vector element of a ray.
// Arguments
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_norm(Ray3 r) {
  return ray3_init(r.pos, vec3_norm(r.vec));
}

/// ray3_mag ///
// Description
//   Finds the magnitude of a ray's vector element.
// Arguments
//   r: Ray (Ray3)
// Returns
//   Magnitude (Float)

sol
Float ray3_mag(Ray3 r) {
  return vec3_mag(r.vec);
}

/// ray3_eq ///
// Description
//   Tests two rays for equality.
// Arguments
//   a: Ray (Ray3)
//   b: Ray (Ray3)
//   ep: Epsilon (Float)
// Returns
//   Equality (Bool)

sol
bool ray3_eq(Ray3 a, Ray3 b, Float ep) {
  if (vec3_eq(a.pos, b.pos, ep)){
    return vec3_eq(a.vec, b.vec, ep);
  }
  return false;
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray3 Advanced Math ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray3_rot ///
// Description
//   Rotates the vector element of a ray by an axis/angle pair.
// Arguments
//   r: Ray (Ray3)
//   aa: Axis/Angle (Vec4)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_rot(Ray3 r, Vec4 aa) {
  return ray3_rotq(r, cv_axis_quat(aa));
}

/// ray3_rotq ///
// Description
//   Rotates the vector element of a ray by a unit quaternion.
// Arguments
//   r: Ray (Ray3)
//   q: Quaternion (Vec4)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_rotq(Ray3 r, Vec4 q) {
  return ray3_init(r.pos, vec3_rotq(r.vec, q));
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray3 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray3_add ///
// Description
//   Adds the vector element of one ray to
//   that of another.
// Arguments
//   a: Ray (Ray3)
//   b: Ray (Ray3)
// Returns
//   Ray (Ray3) = {a.pos, a.vec.xyz + b.vec.xyz}

sol
Ray3 ray3_add(Ray3 a, Ray3 b) {
  return ray3_init(a.pos, vec3_add(a.vec, b.vec));
}

/// ray3_addv ///
// Description
//   Adds a vector to the vector element
//   of a ray.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3) = {r.pos, r.vec.xyz + v.xyz}

sol
Ray3 ray3_addv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_add(r.vec, v));
}

/// ray3_addf ///
// Description
//   Adds a scalar to the vector element
//   of a ray.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3) = {r.pos, r.vec.xyz + f}

sol
Ray3 ray3_addf(Ray3 r, Float f) {
  return ray3_init(r.pos, vec3_addf(r.vec, f));
}

/// ray3_sub ///
// Description
//   Subtracts the vector element of one ray
//   from that of another.
// Arguments
//   a: Ray (Ray3)
//   b: Ray (Ray3)
// Returns
//   Ray (Ray3) = {r.pos, a.vec.xyz + b.vec.xyz}

sol
Ray3 ray3_sub(Ray3 a, Ray3 b) {
  return ray3_init(a.pos, vec3_sub(a.vec, b.vec));
}

/// ray3_subv ///
// Description
//   Subtracts a vector from the vector
//   element of a ray.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3) = {r.pos, r.vec.xyz - v.xyz}

sol
Ray3 ray3_subv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_sub(r.vec, v));
}

/// ray3_vsub ///
// Description
//   Subtracts the vector element of a ray
//   from a vector.
// Arguments
//   v: Vector (Vec3)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3) = {r.pos, v.xyz - r.vec.xyz}

sol
Ray3 ray3_vsub(Vec3 v, Ray3 r) {
  return ray3_init(r.pos, vec3_sub(v, r.vec));
}

/// ray3_subf ///
// Description
//   Subtracts a scalar from the vector
//   element of a ray.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3) = {r.pos, r.vec.xyz - f}

sol
Ray3 ray3_subf(Ray3 r, Float f) {
  return ray3_init(r.pos, vec3_subf(r.vec, f));
}

/// ray3_fsub ///
// Description
//   Subtracts the vector element of a ray
//   from a scalar.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3) = {r.pos, f - r.vec.xyz}

sol
Ray3 ray3_fsub(Float f, Ray3 r) {
  return ray3_init(r.pos, vec3_fsub(f, r.vec));
}

/// ray3_mul ///
// Description
//   Multiplies the vector element of one ray
//   by that of another.
// Arguments
//   a: Ray (Ray3)
//   b: Ray (Ray3)
// Returns
//   Ray (Ray3) = {a.pos, a.vec.xyz * b.vec.xyz}

sol
Ray3 ray3_mul(Ray3 a, Ray3 b) {
  return ray3_init(a.pos, vec3_mul(a.vec, b.vec));
}

/// ray3_mulv ///
// Description
//   Multiplies the vector element of a ray by
//   a vector.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3) = {r.pos, v.vec.xyz * v.xyz}

sol
Ray3 ray3_mulv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_mul(r.vec, v));
}

/// ray3_mulf ///
// Description
//   Multiplies the vector element of a ray by
//   a scalar.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3) = {r.pos, r.vec.xyz * f}

sol
Ray3 ray3_mulf(Ray3 r, Float f) {
  return ray3_init(r.pos, vec3_mulf(r.vec, f));
}

/// ray3_div ///
// Description
//   Divides the vector element of one ray by
//   that of another.
// Arguments
//   a: Ray (Ray3)
//   b: Ray (Ray3)
// Returns
//   Ray (Ray3) = {a.pos, a.vec.xyz / b.vec.xyz}

sol
Ray3 ray3_div(Ray3 a, Ray3 b) {
  return ray3_init(a.pos, vec3_div(a.vec, b.vec));
}

/// ray3_divv ///
// Description
//   Divides the vector element of a ray by
//   a vector.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3) = {r.pos, r.vec.xyz / v.xyz}

sol
Ray3 ray3_divv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_div(r.vec, v));
}

/// ray3_vdiv ///
// Description
//   Divides a vector by the vector element
//   of a ray.
// Arguments
//   v: Vector (Vec3)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3) = {r.pos, v.xyz / r.vec.xyz}

sol
Ray3 ray3_vdiv(Vec3 v, Ray3 r) {
  return ray3_init(r.pos, vec3_div(v, r.vec));
}

/// ray3_avg ///
// Description
//   Averages the vector element of one ray
//   by that of another.
// Arguments
//   a: Ray (Ray3)
//   b: Ray (Ray3)
// Returns
//   Ray (Ray3) = {a.pos, (a.vec.xyz + b.vec.xyz) / 2}

sol
Ray3 ray3_avg(Ray3 a, Ray3 b) {
  return ray3_init(a.pos, vec3_avg(a.vec, b.vec));
}

/// ray3_avgv ///
// Description
//   Averages the vector element of a ray with
//   a vector.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3) = {r.pos, (r.vec.xyz + v.xyz) / 2}

sol
Ray3 ray3_avgv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_avg(r.vec, v));
}

/// ray3_avgf ///
// Description
//   Averages the vector element of a ray with
//   a scalar.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3) = {r.pos, (r.vec.xyz + f) / 2}

sol
Ray3 ray3_avgf(Ray3 r, Float f) {
  return ray3_init(r.pos, vec3_avgf(r.vec, f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Ray3 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// ray3_print ///
// Description
//   Show a ray's elements in stdout.
// Arguments
//   r: Ray (Ray3)
// Returns
//   void

sol
void ray3_print(Ray3 r) {
  vec3_print(r.pos);
  vec3_print(r.vec);
}

