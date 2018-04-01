    /////////////////////////////////////////////////////////////////
   // sol_seg2.c ///////////////////////////////////////////////////
  // Description: Adds 2D line segment functionality to Sol. //////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Seg2 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// seg2_init ///
// Description
//   Initializes a segment with two positions.
// Arguments
//   orig: Origin Position (Vec2)
//   dest: Destination Position (Vec2)
// Returns
//   Segment (Seg2) = {orig, dest}

_sol_
Seg2 seg2_init(Vec2 orig, Vec2 dest) {
  Seg2 out = {orig, dest};
  return out;
}

/// seg2_initv ///
// Description
//   Initializes a segment with a single position as the origin and destination.
// Arguments
//   v: Position (Vec2)
// Returns
//   Segment (Seg2) = {v, v}

_sol_
Seg2 seg2_initv(Vec2 v) {
  return seg2_init(v, v);
}

/// seg2_initf ///
// Description
//   Initializes a segment with a single position as the origin and destination.
//   The position is a vector filled with a single scalar in all lanes.
// Arguments
//   f: Scalar (Float)
// Returns
//   Segment (Seg2) = {{f, f}, {f, f}}

_sol_
Seg2 seg2_initf(Float f) {
  return seg2_initv(vec2_initf(f));
}

/// seg2_zero ///
// Description
//   Initializes a segment with the origin and destination positions set to
//   a vector whose lanes are both zeroed out.
// Arguments
//   void
// Returns
//   Segment (Seg2) = {{0, 0}, {0, 0}}

_sol_
Seg2 seg2_zero(void) {
  return seg2_initf((Float) 0);
}

  /////////////////////////////
 // Seg2 Advanced Functions //
/////////////////////////////

/// seg2_on ///
// Description
//   Checks if a point is on a line segment
//   within a given epsilon.
// Arguments
//   s: Segment (Seg2)
//   p: Point (Vec2)
// Returns
//   Point On Segment (bool)

_sol_
bool seg2_on(Seg2 s, Vec2 p, Float ep) {
  const Vec2 st = s.dest - s.orig;
  const Vec2 pt = p - s.orig;
  return flt_abs(vec2_cross(st, pt)) < ep;
}

/// seg2_left ///
// Description
//   Checks if a point is to the left of
//   a line segment.
// Arguments
//   s: Segment (Seg2)
//   p: Point (Vec2)
// Returns
//   Point Left of Segment (bool)

_sol_
bool seg2_left(Seg2 s, Vec2 p) {
  const Vec2 st = s.dest - s.orig;
  const Vec2 pt = p - s.orig;
  return vec2_cross(st, pt) > 0;
}

/// seg2_right ///
// Description
//   Checks if a point is to the right of
//   a line segment.
// Arguments
//   s: Segment (Seg2)
//   p: Point (Vec20
// Returns
//   Point Right of Segment (bool)

_sol_
bool seg2_right(Seg2 s, Vec2 p) {
  const Vec2 st = vec2_sub(s.dest, s.orig);
  const Vec2 pt = p - s.orig;
  return vec2_cross(st, pt) < 0;
}

  /////////////////////
 // Seg2 Basic Math //
/////////////////////

/// seg2_add ///
// Description
//   Adds two segments together.
// Arguments
//   a: Segment (Seg2)
//   b: Segment (Seg2)
// Returns
//   Segment (Seg2) = {s.orig.xy + b.orig.xy, a.dest.xy + b.dest.xy}

_sol_
Seg2 seg2_add(Seg2 a, Seg2 b) {
  return seg2_init(vec2_add(a.orig, b.orig),
		   vec2_add(a.dest, b.dest));
}

/// seg2_addv ///
// Description
//   Adds a vector to a segment.
// Arguments
//   s: Segment (Seg2)
//   v: Vector (Seg2)
// Returns
//   Segment (Seg2) = {s.orig.xy + v.xy, s.dest.xy + v.xy}

_sol_
Seg2 seg2_addv(Seg2 s, Vec2 v) {
  return seg2_add(s, seg2_initv(v));
}

/// seg2_addf ///
// Description
//   Adds a scalar to a segment.
// Arguments
//   s: Segment (Seg2)
//   f: Scalar (Float)
// Returns
//   Segment (Seg2) = {s.orig.xy + f, s.dest.xy + f}

_sol_
Seg2 seg2_addf(Seg2 s, Float f) {
  return seg2_addv(s, vec2_initf(f));
}

/// seg2_sub ///
// Description
//   Subtracts one segment from another.
// Arguments
//   a: Segment (Seg2)
//   b: Segment (Seg2)
// Returns
//   Segment (Seg2) = {a.orig.xy - b.orig.xy, a.dest.xy - b.dest.xy}

_sol_
Seg2 seg2_sub(Seg2 a, Seg2 b) {
  return seg2_init(vec2_sub(a.orig, b.orig),
		               vec2_sub(a.dest, b.dest));
}

/// seg2_subv ///
// Description
//   Subtracts a vector from a segment.
// Arguments
//   s: Segment (Seg2)
//   v: Vector (Vec2)
// Returns
//   Segment (Seg2) = {s.orig.xy - v.xy, s.dest.xy - v.xy}

_sol_
Seg2 seg2_subv(Seg2 s, Vec2 v) {
  return seg2_sub(s, seg2_initv(v));
}

/// seg2_vsub ///
// Description
//   Subtracts a segment from a vector.
// Arguments
//   v: Vector (Vec2)
//   s: Segment (Seg2)
// Returns
//   Segment (Seg2) = {v.xy - s.orig.xy, v.xy - x.dest.xy}

_sol_
Seg2 seg2_vsub(Vec2 v, Seg2 s) {
  return seg2_sub(seg2_initv(v), s);
}

/// seg2_subf ///
// Description
//   Subtracts a scalar from a segment.
// Arguments
//   s: Segment (Seg2)
//   f: Scalar (Float)
// Returns
//   Segment (Seg2) = {s.orig.xy - f, s.dest.xy - f}

_sol_
Seg2 seg2_subf(Seg2 s, Float f) {
  return seg2_subv(s, vec2_initf(f));
}

/// seg2_fsub ///
// Description
//   Subtracts a segment from a scalar.
// Arguments
//   f: Scalar (Float)
//   s: Segment (Seg2)
// Returns
//   Segment (Seg2) = {f - s.orig.xy, f - s.dest.xy}

_sol_
Seg2 seg2_fsub(Float f, Seg2 s) {
  return seg2_vsub(vec2_initf(f), s);
}

/// seg2_mul ///
// Description
//   Multiplies two segments together.
// Arguments
//   a: Segment (Seg2)
//   b: Segment (Seg2)
// Returns
//   Segment (Seg2) = {a.orig.xy * b.orig.xy, a.dest.xy * b.dest.xy}

_sol_
Seg2 seg2_mul(Seg2 a, Seg2 b) {
  return seg2_init(vec2_mul(a.orig, b.orig),
		               vec2_mul(a.dest, b.dest));
}

/// seg2_mulf ///
// Description
//   Multiplies a segment by a scalar.
// Arguments
//   s: Segment (Seg2)
//   f: Scalar (Float)
// Returns
//   Segment (Seg2) {s.orig.xy * f, s.dest.xy * f}

_sol_
Seg2 seg2_mulf(Seg2 s, Float f) {
  return seg2_mul(s, seg2_initf(f));
}

/// seg2_div ///
// Description
//   Divides one scalar by another.
// Arguments
//   a: Segment (Seg2)
//   b: Segment (Seg2)
// Returns
//   Segment (Seg2) {a.orig.xy * b.orig.xy, a.dest.xy * b.dest.xy}

_sol_
Seg2 seg2_div(Seg2 a, Seg2 b) {
  return seg2_init(vec2_div(a.orig, b.orig),
		               vec2_div(a.dest, b.dest));
}

/// seg2_divv ///
// Description
//   Divides a segment by a vector.
// Arguments
//   s: Segment (Seg2)
//   v: Vector (Vec2)
// Returns
//   Segment (Seg2) {s.orig.xy / v.xy, s.dest.xy / v.xy}

_sol_
Seg2 seg2_divv(Seg2 s, Vec2 v) {
  return seg2_sub(s, seg2_initv(v));
}

/// seg2_vdiv ///
// Description
//   Divides a vector by a segment.
// Arguments
//   v: Vector (Vec2)
//   s: Segment (Seg2)
// Returns
//   Segment (Seg2) {v.xy / s.orig.xy, v.xy / s.dest.xy}

_sol_
Seg2 seg2_vdiv(Vec2 v, Seg2 s) {
  return seg2_div(seg2_initv(v), s);
}

/// seg2_divf ///
// Description
//   Divides a segment by a scalar.
// Arguments
//   s: Segment (Seg2)
//   f: Scalar (Float)
// Returns
//   Segment (Seg2) {s.orig.xyz * f, s.dest.xyz * f}

_sol_
Seg2 seg2_divf(Seg2 s, Float f) {
  return seg2_divv(s, vec2_initf(f));
}

/// seg2_fdiv ///
// Description
//   Divides a scalar by a segment.
// Arguments
//   f: Scalar (Float)
//   s: Segment (Seg2)
// Returns
//   Segment (Seg2) {f * s.orig.xyz, f * s.dest.xyz}

_sol_
Seg2 seg2_fdiv(Float f, Seg2 s) {
  return seg2_vdiv(vec2_initf(f), s);
}

/// seg2_avg ///
// Description
//   Averages one segment with another.
// Arguments
//   a: Segment (Seg2)
//   b: Segment (Seg2)
// Returns
//   Segment (Seg2) {(a.orig.xy + b.orig.xy) / 2, (a.dest.xy + b.dest.xy) / 2}

_sol_
Seg2 seg2_avg(Seg2 a, Seg2 b) {
  return seg2_subf(seg2_add(a, b), 2);
}

/// seg2_avgv ///
// Description
//   Averages a segment with a vector.
// Arguments
//   s: Segment (Seg2)
//   v: Vector (Vec2)
// Returns
//   Segment (Seg2) {(s.orig.xy + v.xy) / 2, (s.dest.xy + v.xy) / 2}

_sol_
Seg2 seg2_avgv(Seg2 s, Vec2 v) {
  return seg2_avg(s, seg2_initv(v));
}

/// seg2_avgf ///
// Description
//   Averages a segment with a scalar.
// Arguments
//   s: Segment (Seg2)
//   f: Scalar (Float)
// Returns
//   Segment (Seg2) {(s.orig.xy + f) / 2, (s.dest.xy + f) / 2}

_sol_
Seg2 seg2_avgf(Seg2 s, Float f) {
  return seg2_avgv(s, vec2_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Seg2 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// seg2_print ///
// Description
//   Shows a segment's elements in stdout.
// Arguments
//   s: Segment (Seg2)
// Returns
//   void

_sol_
void seg2_print(Seg2 s) {
  vec2_print(s.orig);
  vec2_print(s.dest);
}
