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

/// ray3_sump ///
// Description
//   Finds the sum of all of the elements of the position element of a ray.
// Arguments
//   r: Ray (Ray3)
// Returns
//   Sum (Float)

sol
Float ray3_sump(Ray3 r) {
  return vec3_sum(r.pos);
}

/// ray3_sumv ///
// Description
//   Finds the sum of all of the elements of the vector element of a ray.
// Arguments
//   r: Ray (Ray3)
// Returns
//   Sum (Float)

sol
Float ray3_sumv(Ray3 r) {
  return vec3_sum(r.vec);
}

/// ray3_addp ///
// Description
//   Adds a position to the position element of a ray.
// Arguments
//   r: Ray (Ray3)
//   p: Position (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_addp(Ray3 r, Vec3 p) {
  return ray3_init(vec3_add(r.pos, p), r.vec);
}

/// ray3_addpf ///
// Description
//   Adds a scalar to both elements of the position element of a ray.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_addpf(Ray3 r, Float f) {
  return ray3_addp(r, vec3_initf(f));
}

/// ray3_addv ///
// Description
//   Adds a vector to the vector element of a ray.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_addv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_add(r.vec, v));
}

/// ray3_addvf ///
// Description
//   Adds a scalar to both elements of the vector element of a ray.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_addvf(Ray3 r, Float f) {
  return ray3_addv(r, vec3_initf(f));
}

/// ray3_subp ///
// Description
//   Subtracts a vector from the position element of a ray.
// Arguments
//   r: Ray (Ray3)
//   p: Position (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_subp(Ray3 r, Vec3 p) {
  return ray3_init(vec3_sub(r.pos, p), r.vec);
}

/// ray3_subpf ///
// Description
//   Subtracts a scalar from both elements of the position element of a ray.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_subpf(Ray3 r, Float f) {
  return ray3_subp(r, vec3_initf(f));
}

/// ray3_psub ///
// Description
//   Subtracts a ray's position element from a position.
// Arguments
//   p: Position (Vec3)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_psub(Vec3 p, Ray3 r) {
  return ray3_init(vec3_sub(p, r.pos), r.vec);
}

/// ray3_pfsub ///
// Description
//   Subtracts a ray's position element from a position comprised of a single
//   scalar.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_pfsub(Float f, Ray3 r) {
  return ray3_psub(vec3_initf(f), r);
}

/// ray3_subv ///
// Description
//   Subtracts a vector from the vector element of a ray.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_subv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_sub(r.vec, v));
}

/// ray3_subvf ///
// Description
//   Subtracts a vector comprised of a single scalar from the vector element of
//   a ray.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_subvf(Ray3 r, Float f) {
  return ray3_subv(r, vec3_initf(f));
}

/// ray3_vsub ///
// Description
//   Subtracts the vector element of a ray from a vector.
// Arguments
//   v: Vector (Vec3)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_vsub(Vec3 v, Ray3 r) {
  return ray3_init(r.pos, vec3_sub(v, r.vec));
}

/// ray3_vfsub ///
// Description
//   Subtracts the vector element of a ray from a vector comprised of a single
//   scalar value.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_vfsub(Float f, Ray3 r) {
  return ray3_vsub(vec3_initf(f), r);
}

/// ray3_mulp ///
// Description
//   Multiplies the position element of a vector by a position.
// Arguments
//   r: Ray (Ray3)
//   p: Position (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_mulp(Ray3 r, Vec3 p) {
  return ray3_init(vec3_mul(r.pos, p), r.vec);
}

/// ray3_mulpf ///
// Description
//   Multiplies the position element of a ray by a position comprised of
//   a single scalar value.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_mulpf(Ray3 r, Float f) {
  return ray3_mulp(r, vec3_initf(f));
}

/// ray3_mulv ///
// Description
//   Multiplies the vector element of a ray by a vector.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_mulv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_mul(r.vec, v));
}

/// ray3_mulvf ///
// Description
//   Multiplies the vector element of a ray by a vector comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_mulvf(Ray3 r, Float f) {
  return ray3_mulv(r, vec3_initf(f));
}

/// ray3_divp ///
// Description
//   Divides the position element of a ray by a position.
// Arguments
//   r: Ray (Ray3)
//   p: Position (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_divp(Ray3 r, Vec3 p) {
  return ray3_init(vec3_div(r.pos, p), r.vec);
}

/// ray3_divpf ///
// Description
//   Divides the position element of a ray by a position comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_divpf(Ray3 r, Float f) {
  return ray3_divp(r, vec3_initf(f));
}

/// ray3_pdiv ///
// Description
//   Divides a position by the position element of a ray.
// Arguments
//   p: Position (Vec3)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_pdiv(Vec3 p, Ray3 r) {
  return ray3_init(vec3_div(p, r.pos), r.vec);
}

/// ray3_pfdiv ///
// Description
//   Divides a position comprised of a single scalar by the position element of
//   a ray.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_pfdiv(Float f, Ray3 r) {
  return ray3_pdiv(vec3_initf(f), r);
}

/// ray3_divv ///
// Description
//   Divides the vector element of a ray by a vector.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_divv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_div(r.vec, v));
}

/// ray3_divvf ///
// Description
//   Divides the vector element of a ray by a vector comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_divvf(Ray3 r, Float f) {
  return ray3_divv(r, vec3_initf(f));
}

/// ray3_vdiv ///
// Description
//   Divides a vector by the vector element of a ray.
// Arguments
//   v: Vector (Vec3)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_vdiv(Vec3 v, Ray3 r) {
  return ray3_init(r.pos, vec3_div(v, r.vec));
}

/// ray3_vfdiv ///
// Description
//   Divides a vector comprised of a single scalar value by the vector element
//   of a ray.
// Arguments
//   f: Scalar (Float)
//   r: Ray (Ray3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_vfdiv(Float f, Ray3 r) {
  return ray3_vdiv(vec3_initf(f), r);
}

/// ray3_avgp ///
// Description
//   Averages a ray's position element with a position.
// Arguments
//   r: Ray (Ray3)
//   p: Position (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_avgp(Ray3 r, Vec3 p) {
  return ray3_init(vec3_avg(r.pos, p), r.vec);
}

/// ray3_avgpf ///
// Description
//   Averages a ray's position element with a position comprised of a single
//   scalar value.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_avgpf(Ray3 r, Float f) {
  return ray3_avgp(r, vec3_initf(f));
}

/// ray3_avgv ///
// Description
//   Averages a ray's vector element with a vector.
// Arguments
//   r: Ray (Ray3)
//   v: Vector (Vec3)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_avgv(Ray3 r, Vec3 v) {
  return ray3_init(r.pos, vec3_avg(r.vec, v));
}

/// ray3_avgvf ///
// Description
//   Averages a ray's vector element with a vector comprised of a single scalar
//   value.
// Arguments
//   r: Ray (Ray3)
//   f: Scalar (Float)
// Returns
//   Ray (Ray3)

sol
Ray3 ray3_avgvf(Ray3 r, Float f) {
  return ray3_avgv(r, vec3_initf(f));
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

