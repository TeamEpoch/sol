    /////////////////////////////////////////////////////////////////
   // sol_seg3.c ///////////////////////////////////////////////////
  // Description: Adds 3D line segment functionality to Sol. //////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Seg2 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// seg3_init ///
// Description
//   Initializes a segment with two positions.
// Arguments
//   orig: Origin Position (Vec3)
//   dest: Destination Position (Vec3)
// Returns
//   Segment (Seg3) = {orig, dest}

sol
Seg3 seg3_init(Vec3 orig, Vec3 dest) {
  Seg3 out = {orig, dest};
  return out;
}

/// seg3_initv ///
// Description
//   Initializes a segment with a single position as the origin and destination.
// Arguments
//   v: Position (Vec3)
// Returns
//   Segment (Seg3) = {v, v}

sol
Seg3 seg3_initv(Vec3 v) {
  return seg3_init(v, v);
}

/// seg3_initf ///
// Description
//   Initializes a segment with a single position as the origin and destination.
//   The position is a vector filled with a single scalar in all lanes.
// Arguments
//   f: Scalar (Float)
// Returns
//   Segment (Seg3) = {{f, f}, {f, f}}

sol
Seg3 seg3_initf(Float f) {
  return seg3_initv(vec3_initf(f));
}

/// seg3_zero ///
// Description
//   Initializes a segment with the origin and destination positions set to
//   a vector whose lanes are both zeroed out.
// Arguments
//   void
// Returns
//   Segment (Seg3) = {{0, 0}, {0, 0}}

sol
Seg3 seg3_zero(void) {
  return seg3_initf(0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Seg3 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// seg3_add ///
// Description
//   Adds two segments together.
// Arguments
//   a: Segment (Seg3)
//   b: Segment (Seg3)
// Returns
//   Segment (Seg3) = {a.orig.xyz + b.orig.xyz, a.dest.xyz + b.dest.xyz}

sol
Seg3 seg3_add(Seg3 a, Seg3 b) {
  return seg3_init(vec3_add(a.orig, b.orig),
                   vec3_add(a.dest, b.dest));
}

/// seg3_addv ///
// Description
//   Adds a vector to a segment.
// Arguments
//   s: Segment (Seg3)
//   v: Vector (Vec3)
// Returns
//   Segment (Seg3) = {s.orig.xyz + v.xyz, s.dest.xyz + v.xyz}

sol
Seg3 seg3_addv(Seg3 s, Vec3 v) {
  return seg3_add(s, seg3_initv(v));
}

/// seg3_addf ///
// Description
//   Adds a scalar to a segment.
// Arguments
//   s: Segment (Seg3)
//   f: Scalar (Float)
// Returns
//   Segment (Seg3) = {s.orig.xyz + f, s.dest.xyz + f}

sol
Seg3 seg3_addf(Seg3 s, Float f) {
  return seg3_addv(s, vec3_initf(f));
}

/// seg3_sub ///
// Description
//   Subtracts one segment from another.
// Arguments
//   a: Segment (Seg3)
//   b: Segment (Seg3)
// Returns
//   Segment (Seg3) = {a.orig.xyz - b.orig.xyz, a.dest.xyz - b.dest.xyz}

sol
Seg3 seg3_sub(Seg3 a, Seg3 b) {
  return seg3_init(vec3_sub(a.orig, b.orig),
                   vec3_sub(a.dest, b.dest));
}

/// seg3_subv ///
// Description
//   Subtracts a vector from a segment.
// Arguments
//   s: Segment (Seg3)
//   v: Vector (Vec3)
// Returns
//   Segment (Seg3) = {s.orig.xyz - v.xyz, s.dest.xyz - v.xyz}

sol
Seg3 seg3_subv(Seg3 s, Vec3 v) {
  return seg3_sub(s, seg3_initv(v));
}

/// seg3_vsub ///
// Description
//   Subtracts a segment from a vector.
// Arguments
//   v: Vector (Vec3)
//   s: Segment (Seg3)
// Returns
//   Segment (Seg3) = {v.xyz - s.orig.xyz, v.xyz - s.dest.xyz}

sol
Seg3 seg3_vsub(Vec3 v, Seg3 s) {
  return seg3_sub(seg3_initv(v), s);
}

/// seg3_subf ///
// Description
//   Subtracts a scalar from a segment.
// Arguments
//   s: Segment (Seg3)
//   f: Scalar (Float)
// Returns
//   Segment (Seg3) = {s.orig.xyz - f, s.dest.xyz - f}

sol
Seg3 seg3_subf(Seg3 s, Float f) {
  return seg3_subv(s,vec3_initf(f));
}

/// seg3_fsub ///
// Description
//   Subtracts a segment from a scalar.
// Arguments
//   f: Scalar (Float)
//   s: Segment (Seg3)
// Returns
//   Segment (Seg3) = {f - s.orig.xyz, f - s.dest.xyz}

sol
Seg3 seg3_fsub(Float f, Seg3 s) {
  return seg3_vsub(vec3_initf(f), s);
}

/// seg3_mul ///
// Description
//   Multiplies one segment by another.
// Arguments
//   a: Segment (Seg3)
//   b: Segment (Seg3)
// Returns
//   Segment (Seg3) = {a.orig.xyz * b.orig.xyz, a.dest.xyz * b.dest.xyz}

sol
Seg3 seg3_mul(Seg3 a, Seg3 b) {
  return seg3_init(vec3_mul(a.orig, b.orig),
                   vec3_mul(a.dest, b.dest));
}

/// seg3_mulv ///
// Description
//   Multiplies a segment by a vector.
// Arguments
//   s: Segment (Seg3)
//   v: Vector (Vec3)
// Returns
//   Segment (Seg3) = {s.orig.xyz * v.xyz, s.dest.xyz * v.xyz}

sol
Seg3 seg3_mulv(Seg3 s, Vec3 v) {
  return seg3_mul(s, seg3_initv(v));
}

/// seg3_mulf ///
// Description
//   Multiplies a segment by a scalar.
// Arguments
//   s: Segment (Seg3)
//   f: Scalar (Float)
// Returns
//   Segment (Seg3) = {s.orig.xyz * f, s.dest.xyz * f}

sol
Seg3 seg3_mulf(Seg3 s, Float f) {
  return seg3_mulv(s, vec3_initf(f));
}

/// seg3_div ///
// Description
//   Divides one segment by another.
// Arguments
//   a: Segment (Seg3)
//   b: Segment (Seg3)
// Returns
//   Segment (Seg3) = {a.orig.xyz / b.orig.xyz, a.dest.xyz / b.dest.xyz}

sol
Seg3 seg3_div(Seg3 a, Seg3 b) {
  return seg3_init(vec3_div(a.orig, b.orig),
                   vec3_div(a.dest, b.dest));
}

/// seg3_divv ///
// Description
//   Divides a segment by a vector.
// Arguments
//   s: Segment (Seg3)
//   v: Vector (Vec3)
// Returns
//   Segment (Seg3) = {s.orig.xyz / v.xyz, s.dest.xyz / v.xyz}

sol
Seg3 seg3_divv(Seg3 s, Vec3 v) {
  return seg3_div(s, seg3_initv(v));
}

/// seg3_vdiv ///
// Description
//   Divides a vector by a segment.
// Arguments
//   v: Vector (Vec3)
//   s: Segment (Seg3)
// Returns
//   Segment (Seg3) = {v.xyz / s.orig.xyz, v.xyz / s.dest.xyz}

sol
Seg3 seg3_vdiv(Vec3 v, Seg3 s) {
  return seg3_div(seg3_initv(v), s);
}

/// seg3_divf ///
// Description
//   Divides a vector by a segment.
// Arguments
//   s: Segment (Seg3)
//   f: Scalar (Float)
// Returns
//   Segment (Seg3) = {s.orig.xyz / f, s.dest.xyz / f}

sol
Seg3 seg3_divf(Seg3 s, Float f) {
  return seg3_divv(s, vec3_initf(f));
}

/// seg3_fdiv ///
// Description
//   Divides a scalar by a segment.
// Arguments
//   f: Scalar (Float)
//   s: Segment (Seg3)
// Returns
//   Segment (Seg3) = {f / s.orig.xyz, f / s.dest.xyz}

sol
Seg3 seg3_fdiv(Float f, Seg3 s) {
  return seg3_vdiv(vec3_initf(f), s);
}

/// seg3_avg ///
// Description
//   Averages one segment with another.
// Arguments
//   a: Segment (Seg3)
//   b: Segment (Seg3)
// Returns
//   Segment (Seg3) = {(a.orig.xyz + b.orig.xyz) / 2,
//                     (a.dest.xyz + b.dest.xyz) / 2}

sol
Seg3 seg3_avg(Seg3 a, Seg3 b) {
  return seg3_subf(seg3_add(a, b), 2);
}

/// seg3_avgv ///
// Description
//   Averages a segment with a vector.
// Arguments
//   s: Segment (Seg3)
//   v: Vector (Vec3)
// Returns
//   Segment (Seg3) = {(s.orig.xyz + v.xyz) / 2, (s.dest.xyz + v.xyz) / 2}

sol
Seg3 seg3_avgv(Seg3 s, Vec3 v) {
  return seg3_avg(s, seg3_initv(v));
}

/// seg3_avgf ///
// Description
//   Averages a segment with a scalar.
// Arguments
//   s: Segment (Seg3)
//   f: Scalar (Float)
// Returns
//   Segment (Seg3) = {(s.orig.xyz + f) / 2, (s.dest.xyz + f) / 2}

sol
Seg3 seg3_avgf(Seg3 s, Float f) {
  return seg3_avgv(s, vec3_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Seg3 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// seg3_print ///
// Description
//   Shows a segment's elements in stdout.
// Arguments
//   s: Segment (Seg3)
// Returns
//   void

sol
void seg3_print(Seg3 s) {
  vec3_print(s.orig);
  vec3_print(s.dest);
}
