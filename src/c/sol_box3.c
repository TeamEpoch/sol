    /////////////////////////////////////////////////////////////////
   // sol_box3.h ///////////////////////////////////////////////////
  // Description: Adds 3D bounding boxes to Sol. //////////////////
 // Source: https://github.com/davidgarland/sol //////////////////
/////////////////////////////////////////////////////////////////

#include "../sol.h"

/// box3_init ///
// Description
//   Initializes a bounding box with
//   lower and upper bounds.
// Arguments
//   lower: Bounds (Vec3)
//   upper: Bounds (Vec3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_init(Vec3 lower, Vec3 upper) {
  Box3 out;
  out.lower = lower;
  out.upper = upper;
  return out;
}

/// box3_initv ///
// Description
//   Initializes a bounding box with
//   a single position as the lower and
//   upper bounds.
// Arguments
//   v: Bounds (Vec3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_initv(Vec3 v) {
  return box3_init(v, v);
}

/// box3_initf ///
// Description
//   Initializes a bounding box with a
//   single scalar as the XYZ dimensions for 
//   the position of the lower and upper bounds.
// Arguments
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_initf(Float f) {
  return box3_initv(vec3_initf(f));
}

/// box3_zero ///
// Description
//   Initializes a bounding box with
//   all dimensions zeroed out.
// Arguments
//   void
// Returns
//   Bounding Box (Box3) 

_sol_
Box3 box3_zero(void) {
  return box3_initf((Float) 0);
}

  //////////////////////////
 // Box3 Core Operations //
//////////////////////////

/// box3_pos ///
// Description
//   Finds the center position of
//   a bounding box.
// Arguments
//   b: Bounding Box (Box3)
// Returns
//   Position (Vec3)

_sol_
Vec3 box3_pos(Box3 b) {
  return vec3_avg(b.lower, b.upper);
}

/// box3_x ///
// Description
//   Finds the width of a bounding box.
// Arguments
//   b: Bounding Box (Box3)
// Returns
//   Width (Float)

_sol_
Float box3_x(Box3 b) {
  return b.upper[X] - b.lower[X];
}

/// box3_y ///
// Description
//   Finds the height of a bounding box.
// Arguments
//   b: Bounding Box (Box3)
// Returns
//   Height (Float)

_sol_
Float box3_y(Box3 b) {
  return b.upper[Y] - b.lower[Y];
}

/// box3_z ///
// Description
//   Finds the depth of a bounding box.
// Arguments
//   b: Bounding Box (Box3)
// Returns
//   Depth (Float)

_sol_
Float box3_z(Box3 b) {
  return b.upper[Z] - b.lower[Z];
}

/// box3_pip ///
// Description
//   Performs a point-in-polygon test on a
//   point and an axis-aligned bounding box.
// Arguments
//   b: Bounding Box (Box3)
//   v: Point (Vec3)
// Returns
//   Point In Polygon (bool)

_sol_
bool box3_pip(Box3 b, Vec3 v) {
  return (b.lower[X] <= v[X]) && (v[X] <= b.upper[X])
      && (b.lower[Y] <= v[Y]) && (v[Y] <= b.upper[Y])
      && (b.lower[Z] <= v[Z]) && (v[Z] <= b.upper[Z]);
}

  /////////////////////
 // Box3 Basic Math //
/////////////////////

/// box3_add ///
// Description
//   Adds the lower and upper bounds
//   of two bounding boxes.
// Arguments
//   a: Bounding Box (Box3)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_add(Box3 a, Box3 b) {
  return box3_init(vec3_add(a.lower, b.lower),
                   vec3_add(a.upper, b.upper));
}

/// box3_addv ///
// Description
//   Adds a vector to the lower and
//   upper bounds of a bounding box.
// Arguments
//   b: Bounding Box (Box3)
//   v: Vector (Vec3)
// Returns
//   Bounding Box (Box3) 

_sol_
Box3 box3_addv(Box3 b, Vec3 v) {
  return box3_add(b, box3_initv(v));
}

/// box3_addf ///
// Description
//   Adds a scalar to the lower and
//   upper bounds of a bounding box.
// Arguments
//   b: Bounding Box (Box3)
//   f: Scalar (Float)
// Returns
//   Scalar (Float)

_sol_
Box3 box3_addf(Box3 b, Float f) {
  return box3_add(b, box3_initf(f));
}

/// box3_sub ///
// Description
//   Subtracts the lower and upper bounds
//   of one bounding box from another.
// Arguments
//   a: Bounding Box (Box3)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_sub(Box3 a, Box3 b) {
  return box3_init(vec3_sub(a.lower, b.lower),
                   vec3_sub(a.upper, b.upper));
}

/// box3_subv ///
// Description
//   Subtracts a vector from the lower
//   and upper bounds of a bounding box.
// Arguments
//   b: Bounding Box (Box3)
//   v: Vector (Vec3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_subv(Box3 b, Vec3 v) {
  return box3_sub(b, box3_initv(v));
}

/// box3_vsub ///
// Description
//   Subtracts the lower and upper bounds
//   of a bounding box from a vector.
// Arguments
//   v: Vector (Vec3)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_vsub(Vec3 v, Box3 b) {
  return box3_sub(box3_initv(v), b);
}

/// box3_subf ///
// Description
//   Subtracts a scalar from the lower and
//   upper bounds of a bounding box.
// Arguments
//   b: Bounding Box (Box3)
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_subf(Box3 b, Float f) {
  return box3_sub(b, box3_initf(f));
}

/// box3_fsub ///
// Description
//   Subtracts the lower and upper bounds of
//   a bounding box from a scalar.
// Arguments
//   f: Scalar (Float)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_fsub(Float f, Box3 b) {
  return box3_sub(box3_initf(f), b);
}

/// box3_mul ///
// Description
//   Multiplies the lower and upper bounds
//   of one bounding box by another.
// Arguments
//   a: Bounding Box (Box3)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_mul(Box3 a, Box3 b) {
  return box3_init(vec3_mul(a.lower, b.lower),
                   vec3_mul(a.upper, b.upper));
}

/// box3_mulv ///
// Description
//   Multiplies the lower and upper bounds
//   of a bounding box by a vector.
// Arguments
//   b: Bounding Box (Box3)
//   v: Vector (Vec3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_mulv(Box3 b, Vec3 v) {
  return box3_mul(b, box3_initv(v));
}

/// box3_mulf ///
// Description
//   Multiplies the lower and upper bounds
//   of a bounding box by a scalar.
// Arguments
//   b: Bounding Box (Box3)
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_mulf(Box3 b, Float f) {
  return box3_mul(b, box3_initf(f));
}

/// box3_div ///
// Description
//   Divides the lower and upper bounds
//   of a bounding box by another.
// Arguments
//   a: Bounding Box (Box3)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_div(Box3 a, Box3 b) {
  return box3_init(vec3_mul(a.lower, b.lower),
                   vec3_mul(a.upper, b.upper));
}

/// box3_divv ///
// Description
//   Divides the lower and upper bounds
//   of a bounding box by a vector.
// Arguments
//   b: Bounding Box (Box3)
//   v: Vector (Vec3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_divv(Box3 b, Vec3 v) {
  return box3_div(b, box3_initv(v));
}

/// box3_vdiv ///
// Description
//   Divides a vector by the lower and
//   upper bounds of a bounding box.
// Arguments
//   v: Vector (Vec3)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_vdiv(Vec3 v, Box3 b) {
  return box3_div(box3_initv(v), b);
}

/// box3_divf ///
// Description
//   Divides the lower and upper bounds
//   of a bounding box by a scalar.
// Arguments
//   b: Bounding Box (Box3)
//   f: Scalar (Float)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_divf(Box3 b, Float f) {
  return box3_div(b, box3_initf(f));
}

/// box3_fdiv ///
// Description
//   Divides a scalar by the lower and
//   upper bounds of a bounding box.
// Arguments
//   f: Scalar (Float)
//   b: Bounding Box (Box3)
// Returns
//   Bounding Box (Box3)

_sol_
Box3 box3_fdiv(Float f, Box3 b) {
  return box3_div(box3_initf(f), b);
}
