    //////////////////////////////////////////////////////////////////////
   // sol_vec4.c ////////////////////////////////////////////////////////
  // Description: Adds 4D quaternion/axis-angle functionality to Sol. //
 // Source: https://github.com/davidgarland/sol ///////////////////////
//////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_init ///
// Description
//   Initializes a vector in XYZW order.
// Arguments
//   x: Dimension (Float)
//   y: Dimension (Float)
//   z: Dimension (Float)
//   w: Dimension (Float)
// Returns
//   Vector (Vec4) = {x, y, z, w}

_sol_
Vec4 vec4_init(Float x, Float y, Float z, Float w) {
  const Vec4 out = {x, y, z, w};
  return out;
}

/// vec4_initf ///
// Description
//   Initializes a vector's XYZW values using a single float.
// Arguments
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {f, f, f, f}

_sol_
Vec4 vec4_initf(Float f) {
  const Vec4 out = {f, f, f, f};
  return out;
}

/// vec4_zero ///
// Description
//   Initializes a vector's XYZW values as zero.
// Arguments
//   void
// Returns
//   Vector (Vec4) = {0, 0, 0, 0}

_sol_
Vec4 vec4_zero(void) {
  const Vec4 out = {(Float) 0, (Float) 0, (Float) 0, (Float) 0};
  return out;
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Core Operations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_norm ///
// Description
//   Normalizes a vector such that the magnitude is 1.
// Arguments
//   v: Vector (Vec4)
// Returns
//   Normalized Vector (Vec4)

_sol_
Vec4 vec4_norm(Vec4 v) {
  return v / vec4_mag(v);
}

/// vec4_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   Vector (Vec4)
// Returns
//   Magnitude (Float)

_sol_
Float vec4_mag(Vec4 v) {
  return flt_sqrt(vec4_sum(v * v));
}

/// vec4_eq ///
// Description
//   Tests two vectors for equality.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Equality (bool)

_sol_
bool vec4_eq(Vec4 a, Vec4 b, Float ep) {
  const Vec4 c = a - b;
  return (flt_abs(c[X]) < ep)
      && (flt_abs(c[Y]) < ep)
      && (flt_abs(c[Z]) < ep)
      && (flt_abs(c[W]) < ep);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Advanced Math ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_dot ///
// Description
//   Finds the dot product of two vectors.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Dot Product (Float)

_sol_
Float vec4_dot(Vec4 a, Vec4 b) {
  return vec4_sum(a * b);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_sum ///
// Description
//   Gets the sum of all the dimensions of a vector.
// Arguments
//   v: Vector (Vec4)
// Returns
//   Scalar (Float) = v.x + v.y + v.z + v.w

_sol_
Float vec4_sum(Vec4 v) {
  return v[X] + v[Y] + v[Z] + v[W];
}

/// vec4_fma ///
// Description
//   Multiplies the elements of two vectors then adds the elements of a third.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
//   c: Vector (Vec4)
// Returns
//   Vector (Vec4) = {(a.xyzw * b.xyzw) + c.xyzw}

_sol_
Vec4 vec4_fma(Vec4 a, Vec4 b, Vec4 c) {
  return (a * b) + c;
}

/// vec4_fms ///
// Description
//   Multiplies the elements of two vectors
//   then subtracts the elements of a third.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
//   c: Vector (Vec4)
// Returns
//   Vector (Vec4) = {(a.xyzw * b.xyzw) - c.xyzw}

_sol_
Vec4 vec4_fms(Vec4 a, Vec4 b, Vec4 c) {
  return (a * b) - c;
}

/// vec4_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw + b.xyzw}

_sol_
Vec4 vec4_add(Vec4 a, Vec4 b) {
  return a + b;
}

/// vec4_addf ///
// Description
//   Adds a scalar to each element of a vector.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw + f}

_sol_
Vec4 vec4_addf(Vec4 v, Float f) {
  return v + f;
}

/// vec4_sub ///
// Description
//   Subtract the elements of one vector from another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw - b.xyzw}

_sol_
Vec4 vec4_sub(Vec4 a, Vec4 b) {
  return a - b;
}

/// vec4_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw - f}

_sol_
Vec4 vec4_subf(Vec4 v, Float f) {
  return v - f;
}

/// vec4_fsub ///
// Description
//   Subtracts each of a vector'e elements from a scalar.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec4)
// Returns
//   Vector (Vec4) = {f - v.xyzw}

_sol_
Vec4 vec4_fsub(Float f, Vec4 v) {
  return f - v;
}

/// vec4_mul ///
// Description
//   Multiplies the elements of one vector by another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw * b.xyzw}

_sol_
Vec4 vec4_mul(Vec4 a, Vec4 b) {
  return a * b;
}

/// vec4_mulf ///
// Description
//   Multiplies the elements of a vector by a scalar.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw * f}

_sol_
Vec4 vec4_mulf(Vec4 v, Float f) {
  return v * f;
}

/// vec4_div ///
// Description
//   Divides the elements of one vector by another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw / b.xyzw}

_sol_
Vec4 vec4_div(Vec4 a, Vec4 b) {
  return a / b;
}

/// vec4_divf ///
// Description
//   Divides the elements of a vector by a scalar.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw / f}

_sol_
Vec4 vec4_divf(Vec4 v, Float f) {
  return v / f;
}

/// vec4_fdiv ///
// Description
//   Divides a scalar by the elements of a vector.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec4)
// Returns
//   Vector (Vec4) = {f / v.xyzw}

_sol_
Vec4 vec4_fdiv(Float f, Vec4 v) {
  return f / v;
}

/// vec4_avg ///
// Description
//   Averages the elements of one vector with another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {(a.xyzw + b.xyzw) / 2}

_sol_
Vec4 vec4_avg(Vec4 a, Vec4 b) {
  return (a + b) * ((Float) 0.5);
}

/// vec4_avgf ///
// Description
//   Averages the elements of a vector with a scalar.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {(v.xyzw + f) / 2}

_sol_
Vec4 vec4_avgf(Vec4 v, Float f) {
  return (v + f) * ((Float) 0.5);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_print ///
// Description
//   Show a quaternion's elements in stdout with a newline appended.
// Arguments
//   Vector (Vec4)
// Returns
//   void

_sol_
void vec4_print(Vec4 v) {
  printf("(" SOL_F_FMT ", " SOL_F_FMT ", " SOL_F_FMT ", " SOL_F_FMT ")\n", (FloatCast) v[X],
                                                                           (FloatCast) v[Y],
                                                                           (FloatCast) v[Z],
                                                                           (FloatCast) v[W]);
}
