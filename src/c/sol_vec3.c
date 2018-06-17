   //                                                            ///////////////
  // sol_vec3.c | Adds 3D vector/position functionality to Sol. ///////////////
 // https://github.com/davidgarland/sol                        ///////////////
//                                                            ///////////////

#include "../sol.h"

  //                     ///////////////////////////////////////////////////////
 // Vec3 Initialization ///////////////////////////////////////////////////////
//                     ///////////////////////////////////////////////////////

/// vec3_init ///
// Description
//   Initializes a vector in XYZ order.
// Arguments
//   x: Dimension (Float)
//   y: Dimension (Float)
//   z: Dimension (Float)
// Returns
//   Vector (Vec3) = {x, y, z}

_sol_
Vec3 vec3_init(Float x, Float y, Float z) {
  const Vec3 out = {x, y, z, (Float) 0};
  return out;
}

/// vec3_initf ///
// Description
//   Initializes a vector's XYZ values using a single scalar.
// Arguments
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {f, f, f}

_sol_
Vec3 vec3_initf(Float f) {
  const Vec3 out = {f, f, f, (Float) 0};
  return out;
}

/// vec3_zero ///
// Description
//   Initializes a vector's XYZ values as zero.
// Arguments
//   void
// Returns
//   Vector (Vec3) = {0, 0, 0}

_sol_
Vec3 vec3_zero(void) {
  const Vec3 out = {(Float) 0, (Float) 0, (Float) 0, (Float) 0};
  return out;
}

  //                      //////////////////////////////////////////////////////
 // Vec3 Core Operations //////////////////////////////////////////////////////
//                      //////////////////////////////////////////////////////

/// vec3_norm ///
// Description
//   Normalizes a vector such that the magnitude is 1.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Normalized Vector (Vec3)

_sol_
Vec3 vec3_norm(Vec3 v) {
  return v / vec3_mag(v);
}

/// vec3_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Magnitude (Float)

_sol_
Float vec3_mag(Vec3 v) {
  return flt_sqrt(vec3_dot(v, v));
}

/// vec3_eq ///
// Description
//   Tests two vectors for equality.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
//   ep: Epsilon (Float)
// Returns
//   Equality (bool)

_sol_
bool vec3_eq(Vec3 a, Vec3 b, Float ep) {
  const Vec3 c = a - b;
  return (flt_abs(c[X]) < ep)
      && (flt_abs(c[Y]) < ep)
      && (flt_abs(c[Z]) < ep);
}

/// vec3_yzx ///
// Description
//   Shuffles a vector into YZX order.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Vector (Vec3)

_sol_
Vec3 vec3_yzx(Vec3 v) {
  const Vec3 out = {v[Y], v[Z], v[X]};
  return out;
}

  //                          //////////////////////////////////////////////////
 // Vec3 Advanced Operations //////////////////////////////////////////////////
//                          //////////////////////////////////////////////////

/// vec3_rot ///
// Description
//   Rotates a vector by an axis/angle. Note that the angle is in degrees.
// Arguments
//   v: Vector (Vec3)
//   aa: Axis/Angle (Vec4)
// Returns
//   Vector (Vec3)

_sol_
Vec3 vec3_rot(Vec3 v, Vec4 aa) {
  return vec3_rotq(v, cv_axis_quat(aa));
}

/// vec3_rotq ///
// Description
//   Rotates a vector by a unit quaternion.
// Arguments
//   v: Vector (Vec3)
//   q: Quaternion (Vec4)
// Returns
//   Vector (Vec3)

_sol_
Vec3 vec3_rotq(Vec3 v, Vec4 q) {
  const Vec3 qv = {q[X], q[Y], q[Z]};
  const Vec3 t = vec3_cross(qv, v) * 2;
  return v + (t * q[W]) + vec3_cross(qv, t);
}

  //                    ////////////////////////////////////////////////////////
 // Vec3 Advanced Math ////////////////////////////////////////////////////////
//                    ////////////////////////////////////////////////////////

/// vec3_proj ///
// Description
//   Gets the projection of vector a onto b.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Projection (Vec3)

_sol_
Vec3 vec3_proj(Vec3 a, Vec3 b) {
  const Float ma = vec3_mag(a);
  const Float d = ma * ma;
  const Float f = vec3_dot(a, b) / d;
  return a * f;
}

/// vec3_rej ///
// Description
//   Gets the rejection of vector a from b.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Rejection (Vec3)

_sol_
Vec3 vec3_rej(Vec3 a, Vec3 b) {
  return a - vec3_proj(a, b);
}

/// vec3_angle ///
// Description
//   Gets the angle between two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Angle (Float)

_sol_
Float vec3_angle(Vec3 a, Vec3 b) {
  return flt_acos(vec3_dot(a, b) / (vec3_mag(a) / vec3_mag(b)));
}

/// vec3_cross ///
// Description
//   Gets the cross product of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Cross Product (Vec3)

_sol_
Vec3 vec3_cross(Vec3 a, Vec3 b) {
  const Vec3 va = vec3_yzx(a);
  const Vec3 vb = vec3_yzx(b);
  const Vec3 c = (a * vb) - (b * va);
  return vec3_yzx(c);
}

/// vec3_dot ///
// Description
//   Gets the dot product of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Dot Product (Float)

_sol_
Float vec3_dot(Vec3 a, Vec3 b) {
  return vec3_sum(a * b);
}

  //                 ///////////////////////////////////////////////////////////
 // Vec3 Basic Math ///////////////////////////////////////////////////////////
//                 ///////////////////////////////////////////////////////////

/// vec3_sum ///
// Description
//   Gets the sum of all of the dimensions of a vector.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Sum (Float) = a.x + a.y + a.z

_sol_
Float vec3_sum(Vec3 v) {
  return v[X] + v[Y] + v[Z];
}

/// vec3_fma ///
// Description
//   Multiplies the elements of two vectors
//   then adds the elements of a third.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
//   c: Vector (Vec3)
// Returns
//   Vector (Vec3) = {(a.xyz * b.xyz) + c.xyz}

_sol_
Vec3 vec3_fma(Vec3 a, Vec3 b, Vec3 c) {
  return (a * b) + c;
}

/// vec3_fms ///
// Description
//   Multiplies the elements of two vectors
//   then subtracts the elements of a third.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
//   c: Vector (Vec3)
// Returns
//   Vector (Vec3) = {(a.xyz * b.xyz) - c.xyz}

_sol_
Vec3 vec3_fms(Vec3 a, Vec3 b, Vec3 c) {
  return (a * b) - c;
}

/// vec3_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz + b.xyz}

_sol_
Vec3 vec3_add(Vec3 a, Vec3 b) {
  return a + b;
}

/// vec3_addf ///
// Description
//   Adds a scalar to each element of a vector.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz + f}

_sol_
Vec3 vec3_addf(Vec3 v, Float f) {
  return v + f;
}

/// vec3_sub ///
// Description
//   Subtracts the elements of one vector from another.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz - b.xyz}

_sol_
Vec3 vec3_sub(Vec3 a, Vec3 b) {
  return a - b;
}

/// vec3_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz - f}

_sol_
Vec3 vec3_subf(Vec3 v, Float f) {
  return v - f;
}

/// vec3_fsub ///
// Description
//   Subtracts each element of a vector from a scalar.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec3)
// Returns
//   Vector (Vec3) = {f - v.xyz}

_sol_
Vec3 vec3_fsub(Float f, Vec3 v) {
  return f - v;
}

/// vec3_mul ///
// Description
//   Multiplies the elements of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz * b.xyz}

_sol_
Vec3 vec3_mul(Vec3 a, Vec3 b) {
  return a * b;
}

/// vec3_mulf ///
// Description
//   Multiplies each element of a vector by a scalar.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz * f}

_sol_
Vec3 vec3_mulf(Vec3 v, Float f) {
  return v * f;
}

/// vec3_div ///
// Description
//   Divides each element of one vector by another.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz / b.xyz}

_sol_
Vec3 vec3_div(Vec3 a, Vec3 b) {
  return a / b;
}

/// vec3_divf ///
// Description
//   Divide each element of a vector by a scalar.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz / f}

_sol_
Vec3 vec3_divf(Vec3 v, Float f) {
  return v / f;
}

/// vec3_fdiv ///
// Description
//   Divide a scalar by each element of a vector.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec3)
// Returns
//   Vector (Vec3) = {f / v.xyz}

_sol_
Vec3 vec3_fdiv(Float f, Vec3 v) {
  return f / v;
}

/// vec3_avg ///
// Description
//   Average each element of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {(a.xyz + b.xyz) / 2}

_sol_
Vec3 vec3_avg(Vec3 a, Vec3 b) {
  return (a + b) * ((Float) 0.5);
}

/// vec3_avgf ///
// Description
//   Average each element of a vector with a float.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {(v.xyz + f) / 2}

_sol_
Vec3 vec3_avgf(Vec3 v, Float f) {
  return (v + f) * ((Float) 0.5);
}

  //                  //////////////////////////////////////////////////////////
 // Vec3 Terminal IO //////////////////////////////////////////////////////////
//                  //////////////////////////////////////////////////////////

/// vec3_print ///
// Description
//   Shows a vector's elements in stdout with a newline appended.
// Arguments
//   v: Vector (Vec3)
// Returns
//   void

_sol_
void vec3_print(Vec3 v) {
  printf("(" SOL_F_FMT ", " SOL_F_FMT ", " SOL_F_FMT ")\n", (FloatCast) v[X],
                                                            (FloatCast) v[Y],
                                                            (FloatCast) v[Z]);
}
