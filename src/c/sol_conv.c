    /////////////////////////////////////////////////////////////////
   // sol_conv.c ///////////////////////////////////////////////////
  // Description: Adds conversion functions to Sol. ///////////////
 // Source: https://github.com/davidgarland/sol //////////////////
/////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Vector Conversion /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// cv_axis_quat ///
// Description
//   Converts an axis-angle representation
//   into a quaternion. The "w" element of
//   Vec4 is used for the angle, which is
//   in degrees.
// Arguments
//   axis: Axis-Angle (Vec4)
// Returns
//   Quaternion (Vec4)

_sol_
Vec4 cv_axis_quat(Vec4 axis) {
  const Float w = cv_deg_rad(axis[W]) / 2;
  const Float s = flt_sin(w);
  return vec4_init(axis[X] * s,
                   axis[Y] * s,
                   axis[Z] * s,
                   flt_cos(w));
}

/// cv_quat_axis ///
// Description
//   Converts a quaternion into its axis-angle
//   representation. The "w" element of Vec4 is
//   used for the angle, which is in degrees.
// Arguments
//   quat: Quaternion (Vec4)
// Returns
//   Axis-Angle (Vec4)

_sol_
Vec4 cv_quat_axis(Vec4 quat) {
  const Float s = flt_sqrt(1 - (quat[W] * 2));
  return vec4_init(quat[X] * s,
                   quat[Y] * s,
                   quat[Z] * s,
                   cv_rad_deg(2 * flt_acos(quat[W])));
}

  ////////////////////
 // Vector Casting //
////////////////////

/// cv_vec3_vec2 ///
// Description
//   Converts a 3D vector into a 2D vector,
//   dropping the Z value.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Vector (Vec2)

_sol_
Vec2 cv_vec3_vec2(Vec3 v) {
  return vec2_init(v[X], v[Y]);
}

/// cv_vec4_vec2 ///
// Description
//   Converts a 4D vector into a 2D vector,
//   dropping the Z and W values.
// Arguments
//   v: Vector (Vec4)
// Returns
//   Vector (Vec2)

_sol_
Vec2 cv_vec4_vec2(Vec4 v) {
  return vec2_init(v[X], v[Y]);
}

/// cv_vec2_vec3 ///
// Description
//   Converts a 2D vector into a 3D vector,
//   appending the Z value.
// Arguments
//   v: Vector (Vec2)
//   z: Dimension (Float)
// Returns
//   Vector (Vec3)

_sol_
Vec3 cv_vec2_vec3(Vec2 v, Float z) {
  return vec3_init(v[X], v[Y], z);
}

/// cv_vec4_vec3 ///
// Description
//   Converts a 4D vector into a 3D vector,
//   dropping the W value.
// Arguments
//   v: Vector (Vec4)
// Returns
//   Vector (Vec3)

_sol_
Vec3 cv_vec4_vec3(Vec4 v) {
  return vec3_init(v[X], v[Y], v[Z]);
}

/// cv_vec2_vec4 ///
// Description
//   Converts a 2D vector into a 4D vector,
//   appending the Z and W values.
// Arguments
//   v: Vector (Vec2)
//   z: Dimension (Float)
//   w: Dimension (Float)
// Returns
//   Vector (Vec4)

_sol_
Vec4 cv_vec2_vec4(Vec2 v, Float z, Float w) {
  return vec4_init(v[X], v[Y], z, w);
}

/// cv_vec3_vec4 ///
// Description
//   Converts a 3D vector into a 4D vector,
//   appending the W value.
// Arguments
//   v: Vector (Vec3)
//   w: Dimension (Float)
// Returns
//   Vector (Vec4)

_sol_
Vec4 cv_vec3_vec4(Vec3 v, Float w) {
  return vec4_init(v[X], v[Y], v[Z], w);
}

  //////////////////////////////////////////////////////////////////////////////
 // Scalar Conversion /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// cv_deg_rad ///
// Description
//   Converts degrees to radians.
// Arguments
//   deg: Degrees (Float)
// Returns
//   rad: Radians (Float)

_sol_
Float cv_deg_rad(Float deg) {
  return deg * ((Float) (sol_pi / 180));
}

/// cv_rad_deg ///
// Description
//   Converts radians to degrees.
// Arguments
//   rad: Radians (Float)
// Returns
//   deg: Degrees (Float)

_sol_
Float cv_rad_deg(Float rad) {
  return rad * ((Float) (180 / sol_pi));
}
