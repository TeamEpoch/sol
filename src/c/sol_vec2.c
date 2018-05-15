    /////////////////////////////////////////////////////////////////
   // sol_vec2.c ///////////////////////////////////////////////////
  // Description: Adds 2D vector/position functionality to Sol. ///
 // Source: https://github.com/davidgarland/sol //////////////////
/////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_init ///
// Description
//   Initializes a vector in XY order.
// Arguments
//   x: Dimension (Float)
//   y: Dimension (Float)
// Returns
//   Vector (Vec2) = {x, y}

_sol_
Vec2 vec2_init(Float x, Float y) {
  const Vec2 out = {x, y};
  return out;
}

/// vec2_initf ///
// Description
//   Initializes a vector's XY values using a single float.
// Arguments
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {f, f}

_sol_
Vec2 vec2_initf(Float f) {
  Vec2 out = {f, f};
  return out;
}

/// vec2_zero ///
// Description
//   Initizlies a vector's XYZ values as zero.
// Arguments
//   void
// Returns
//   Vector (Vec2) = {0, 0}

_sol_
Vec2 vec2_zero(void) {
  Vec2 out = {(Float) 0, (Float) 0};
  return out;
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Core Operations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_norm ///
// Description
//   Normalizes a vector such that the magnitude is 1.
// Arguments
//   v: Vector (Vec2)
// Returns
//   Normalized Vector (Vec2)

_sol_
Vec2 vec2_norm(Vec2 v) {
  return v / vec2_mag(v);
}

/// vec2_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   v: Vector (Vec2)
// Returns
//   Magnitude (Float)

_sol_
Float vec2_mag(Vec2 v) {
  return flt_sqrt(vec2_dot(v, v));
}

/// vec2_eq ///
// Description
//   Tests two vectors for equality.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
//   ep: Epsilon (Float)
// Returns
//   Equality (Bool)

_sol_
bool vec2_eq(Vec2 a, Vec2 b, Float ep) {
  const Vec2 c = a - b;
  return (flt_abs(c[X]) < ep)
      && (flt_abs(c[Y]) < ep);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Advanced Operations //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// vec2_rot ///
// Description
//   Rotate a 2D vector counterclockwise in degrees.
// Arguments
//   v: Vector (Vec2)
//   deg: Degrees (Float)
// Returns
//   Vector (Vec2)

_sol_
Vec2 vec2_rot(Vec2 v, Float deg) {
  return vec2_rotr(v, cv_deg_rad(deg));
}

/// vec2_rotr ///
// Description
//   Rotate a 2D vector counterclockwise in radians.
// Arguments
//   v: Vector (Vec2)
//   rad: Radians (Float)
// Returns
//   Vector (Vec2)

_sol_
Vec2 vec2_rotr(Vec2 v, Float rad) {
  const Float cs = flt_cos(rad);
  const Float sn = flt_sin(rad);
  return vec2_init((v[X] * cs) - (v[Y] * sn),
                   (v[X] * sn) + (v[Y] * cs));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Advanced Math ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_proj ///
// Description
//   Gets the projection of vector a onto b.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Projection (Vec2)

_sol_
Vec2 vec2_proj(Vec2 a, Vec2 b) {
  const Float f = vec2_mag(a) * flt_cos(vec2_angle(a, b));
  return b * f;
}

/// vec2_rej ///
// Description
//   Gets the rejection of a from b.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Rejection (Vec2)

_sol_
Vec2 vec2_rej(Vec2 a, Vec2 b) {
  return a - vec2_proj(a, b);
}

/// vec2_angle ///
// Description
//   Gets the angle between two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Angle (Float)

_sol_
Float vec2_angle(Vec2 a, Vec2 b) {
  return flt_atan2(vec2_cross(a, b), vec2_dot(a, b));
}

/// vec2_cross ///
// Description
//   Gets the cross product of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Cross Product (Float)

_sol_
Float vec2_cross(Vec2 a, Vec2 b) {
  return (a[X] * b[Y])
       - (b[X] * a[Y]);
}

/// vec2_dot ///
// Description
//   Gets the dot product of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Dot Product (Float)

_sol_
Float vec2_dot(Vec2 a, Vec2 b) {
  return vec2_sum(a * b);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_sum ///
// Description
//   Gets the sum of all of the dimensions of a vector.
// Arguments
//   v: Vector (Vec2)
// Returns
//   Sum (Float) = a.x + a.y

_sol_
Float vec2_sum(Vec2 v) {
  return v[X] + v[Y];
}

/// vec2_fma ///
// Description
//   Multiplies the elements of two vectors 
//   then adds the elements of a third.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
//   c: Vector (Vec2)
// Returns
//   Vector (Vec2) = {(a.xy * b.xy) + c.xy}

_sol_
Vec2 vec2_fma(Vec2 a, Vec2 b, Vec2 c) {
  return (a * b) + c;
}

/// vec2_fms ///
// Description
//   Multiplies the elements of two vectors
//   then subtracts the elements of a third.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
//   c: Vector (Vec2)
// Returns
//   Vector (Vec2) = {(a.xy * b.xy) - c.xy}

_sol_
Vec2 vec2_fms(Vec2 a, Vec2 b, Vec2 c) {
  return (a * b) - c;
}

/// vec2_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xy + b.xy}

_sol_
Vec2 vec2_add(Vec2 a, Vec2 b) {
  return a + b;
}

/// vec2_addf ///
// Description
//   Adds a float to each element of a vector.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz + f}

_sol_
Vec2 vec2_addf(Vec2 v, Float f) {
  return v + f;
}

/// vec2_sub ///
// Description
//   Subtract the elements of one vector from another.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xyz - b.xyz}

_sol_
Vec2 vec2_sub(Vec2 a, Vec2 b) {
  return a - b;
}

/// vec2_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz - f}

_sol_
Vec2 vec2_subf(Vec2 v, Float f) {
  return v - f;
}

/// vec2_fsub ///
// Description
//   Subtracts each element of a vector from a float.
// Arguments
//   f: Scalar (_sol__f)
//   v: Vector (Vec2)
// Returns
//   Vector (Vec2) = {f - v.xyz}

_sol_
Vec2 vec2_fsub(Float f, Vec2 v) {
  return f - v;
}

/// vec2_mul ///
// Description
//   Multiplies the elements of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xyz * b.xyz}

_sol_
Vec2 vec2_mul(Vec2 a, Vec2 b) {
  return a * b;
}

/// vec2_mulf ///
// Description
//   Multiplies each element of a vector by a float.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz * f}

_sol_
Vec2 vec2_mulf(Vec2 v, Float f) {
  return v * f;
}

/// vec2_div ///
// Description
//   Divide the elements of one vector by another.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xyz / b.xyz}

_sol_
Vec2 vec2_div(Vec2 a, Vec2 b) {
  return a / b;
}

/// vec2_divf ///
// Description
//   Divide the elements of a vector by a float.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz / f}

_sol_
Vec2 vec2_divf(Vec2 v, Float f) {
  return v / f;
}

/// vec2_fdiv ///
// Description
//   Divide a float by each element of a vector.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec2)
// Returns
//   Vector (Vec2) = {f / v.xyz}

_sol_
Vec2 vec2_fdiv(Float f, Vec2 v) {
  return f / v;
}

/// vec2_avg ///
// Description
//   Average each element of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {(a.xyz + b.xyz) / 2}

_sol_
Vec2 vec2_avg(Vec2 a, Vec2 b) {
  return (a + b) * ((Float) 0.5);
}

/// vec2_avgf ///
// Description
//   Average each element of a vector with a float.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {(v.xyz + f) / 2}

_sol_
Vec2 vec2_avgf(Vec2 v, Float f) {
  return (v + f) * ((Float) 0.5);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_print ///
// Description
//   Show a vector's elements in stdout.
// Arguments
//   v: Vector (Vec2)
// Returns
//   void

_sol_
void vec2_print(Vec2 v) {
  printf("(" SOL_F_FMT ", " SOL_F_FMT ")\n", (FloatCast) v[X],
                                             (FloatCast) v[Y]);
}
