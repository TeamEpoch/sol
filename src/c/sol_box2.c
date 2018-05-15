    /////////////////////////////////////////////////////////////////
   // sol_box2.c ///////////////////////////////////////////////////
  // Description: Adds 2D bounding boxes to Sol. //////////////////
 // Source: https://github.com/davidgarland/sol //////////////////
/////////////////////////////////////////////////////////////////

#include "../sol.h"

  /////////////////////////
 // Box2 Initialization //
/////////////////////////

/// box2_init ///
// Description
//   Initializes a bounding box with lower and upper
//   bounds.
// Arguments
//   lower: Bounds (Vec2)
//   upper: Bounds (Vec2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_init(Vec2 lower, Vec2 upper) {
  Box2 out;
  out.lower = lower;
  out.upper = upper;
  return out;
}

/// box2_initv ///
// Description
//   Initializes a bounding box with the same
//   position as lower and upper bounds.
// Arguments
//   v: Bounds (Vec2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_initv(Vec2 v) {
  return box2_init(v, v);
}

/// box2_initf ///
// Description
//   Initializes a bounding box with a scalar
//   as the XY dimensions for the position of
//   the lower and upper bounds.
// Arguments
//   f: Bounds (Float)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_initf(Float f) {
  return box2_initv(vec2_initf(f));
}

/// box2_zero ///
// Description
//   Initializes a bounding box with all
//   dimensions zeroed out.
// Arguments
//   void
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_zero(void) {
  return box2_initf((Float) 0);
}

  //////////////////////////
 // Box2 Core Operations //
//////////////////////////

/// box2_pos ///
// Description
//   Finds the position of a
//   bounding box.
// Arguments
//   b: Bounding Box (Box2)
// Returns
//   Position (Vec2)

_sol_
Vec2 box2_pos(Box2 b) {
  return vec2_avg(b.lower, b.upper);
}

/// box2_x ///
// Description
//   Finds the width 
// Arguments
//   b: Bounding Box (Box2)
// Returns
//   Box Width (Float)

_sol_
Float box2_x(Box2 b) {
  return b.upper[X] - b.lower[X];
}

/// box2_y ///
// Description
//   Finds the height of a bounding box.
// Arguments
//   b: Bounding Box (Box2)
// Returns
//   Box Height (Float)

_sol_
Float box2_y(Box2 b) {
  return b.upper[Y] - b.lower[Y];
}

/// box2_pip ///
// Description
//   Does a point-in-polygon test with a
//   point and a bounding box.
// Arguments
//   b: Bounding Box (Box2)
//   v: Point (Vec2)
// Returns
//   Point In Polygon (bool)

_sol_ 
bool box2_pip(Box2 b, Vec2 v) {
  return (b.lower[X] >= v[X]) && (v[X] <= b.upper[X])
      && (b.lower[Y] >= v[Y]) && (v[Y] <= b.upper[Y]);
}

  /////////////////////
 // Box2 Basic Math //
/////////////////////

/// box2_add ///
// Description
//   Adds the lower and upper bounds of one bounding
//   box to that of another.
// Arguments
//   a: Bounding Box (Box2)
//   b: Bounding Box (Box2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_add(Box2 a, Box2 b) {
  return box2_init(vec2_add(a.lower, b.lower),
                   vec2_add(a.upper, b.upper));
}

/// box2_addv ///
// Description
//   Adds a vector to the lower and upper bounds
//   of a bounding box.
// Arguments
//   b: Bounding Box (Box2)
//   v: Vector (Vec2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_addv(Box2 b, Vec2 v) {
  return box2_add(b, box2_initv(v));
}

/// box2_addf ///
// Description
//   Adds a scalar to the lower and upper bounds
//   of a bounding box.
// Arguments
//   b: Bounding Box (Box2)
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_addf(Box2 b, Float f) {
  return box2_addv(b, vec2_initf(f));
}

/// box2_sub ///
// Description
//   Subtracts the lower and upper bounds of
//   one bounding box from another.
// Arguments
//   a: Bounding Box (Box2)
//   b: Bounding Box (Box2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_sub(Box2 a, Box2 b) {
  return box2_init(vec2_sub(a.lower, b.lower),
                   vec2_sub(a.upper, b.upper));
}

/// box2_subv ///
// Description
//   Subtracts a vector from the lower
//   and upper bounds of a bounding box.
// Arguments
//   b: Bounding Box (Box2)
//   v: Vector (Vec2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_subv(Box2 b, Vec2 v) {
  return box2_sub(b, box2_initv(v));
}

/// box2_vsub ///
// Description
//   Subtracts the lower and upper bounds
//   of a bounding box from a vector.
// Arguments
//   v: Vector (Vec2)
//   b: Bounding Box (Box2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_vsub(Vec2 v, Box2 b) {
  return box2_sub(box2_initv(v), b);
}

/// box2_subf ///
// Description
//   Subtracts a scalar from the lower
//   and upper bounds of a bounding box
// Arguments
//   b: Bounding Box (Box2)
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_subf(Box2 b, Float f) {
  return box2_subv(b, vec2_initf(f));
}

/// box2_fsub ///
// Description
//   Subtracts the lower and upper bounds
//   of a bounding box from a scalar.
// Arguments
//   f: Scalar (Float)
//   b: Bounding Box (Box2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_fsub(Float f, Box2 b) {
  return box2_vsub(vec2_initf(f), b);
}

/// box2_mul ///
// Description
//   Multiplies the lower and upper bounds
//   of a bounding box by another.
// Arguments
//   a: Bounding Box (Box2)
//   b: Bounding Box (Box2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_mul(Box2 a, Box2 b) {
  return box2_init(vec2_mul(a.lower, b.lower),
                   vec2_mul(a.upper, b.upper));
}

/// box2_mulv ///
// Description
//   Multiplies the lower and upper bounds
//   of a bounding box by a vector.
// Arguments
//   b: Bounding Box (Box2)
//   v: Vector (Vec2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_mulv(Box2 b, Vec2 v) {
  return box2_mul(b, box2_initv(v));
}

/// box2_mulf ///
// Description
//   Multiplies the lower and upper bounds
//   of a bounding box by a scalar.
// Arguments
//   b: Bounding Box (Box2)
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_mulf(Box2 b, Float f) {
  return box2_mulv(b, vec2_initf(f));
}

/// box2_div ///
// Description
//   Divides the lower and upper bounds
//   of a bounding box by another.
// Arguments
//   a: Bounding Box (Box2)
//   b: Bounding Box (Box2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_div(Box2 a, Box2 b) {
  return box2_init(vec2_div(a.lower, b.lower),
                   vec2_div(a.upper, b.upper));
}

/// box2_divv ///
// Description
//   Divides the lower and upper bounds
//   of a bounding box by a vector.
// Arguments
//   b: Bounding Box (Box2)
//   v: Vector (Vec2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_divv(Box2 b, Vec2 v) {
  return box2_div(b, box2_initv(v));
}

/// box2_vdiv ///
// Description
//   Divides a vector by the lower and
//   upper bounds of a bounding box.
// Arguments
//   v: Vector (Vec2)
//   b: Bounding Box (Box2)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_vdiv(Vec2 v, Box2 b) {
  return box2_div(box2_initv(v), b);
}

/// box2_divf ///
// Description
//   Divides the lower and upper bounds
//   of a bounding box by a scalar.
// Arguments
//   b: Bounding Box (Box2)
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box2)

_sol_
Box2 box2_divf(Box2 b, Float f) {
  return box2_divv(b, vec2_initf(f));
}

/// box2_fdiv ///
// Description
//   Divides a scalar by the lower and
//   upper bounds of a bounding box.
// Arguments
//   f: Scalar (Float)
//   b: Bounding Box (Box2)

_sol_
Box2 box2_fdiv(Float f, Box2 b) {
  return box2_vdiv(vec2_initf(f), b);
}

