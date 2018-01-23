    /////////////////////////////////////////////////////////////////
   // sol_conv.h ///////////////////////////////////////////////////
  // Description: Adds conversion functions to Sol. ///////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

#ifndef SOL_CONV_H
#define SOL_CONV_H

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

sol
Vec4 cv_axis_quat(Vec4 axis) {
  const Float w = cv_deg_rad(axis.w) / 2;
  const Float s = flt_sin(w);
  return vec4_init(axis.x * s,
                   axis.y * s,
                   axis.z * s,
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

sol
Vec4 cv_quat_axis(Vec4 quat) {
  const Float s = flt_sqrt(1 - (quat.w * 2));
  return vec4_init(quat.x * s,
                   quat.y * s,
                   quat.z * s,
                   cv_rad_deg(2 * flt_acos(quat.w)));
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

sol
Vec2 cv_vec3_vec2(Vec3 v) {
  return vec2_init(v.x, v.y);
}

/// cv_vec4_vec2 ///
// Description
//   Converts a 4D vector into a 2D vector,
//   dropping the Z and W values.
// Arguments
//   v: Vector (Vec4)
// Returns
//   Vector (Vec2)

sol
Vec2 cv_vec4_vec2(Vec4 v) {
  return vec2_init(v.x, v.y);
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

sol
Vec3 cv_vec2_vec3(Vec2 v, Float z) {
  return vec3_init(v.x, v.y, z);
}

/// cv_vec4_vec3 ///
// Description
//   Converts a 4D vector into a 3D vector,
//   dropping the W value.
// Arguments
//   v: Vector (Vec4)
// Returns
//   Vector (Vec3)

sol
Vec3 cv_vec4_vec3(Vec4 v) {
  return vec3_init(v.x, v.y, v.z);
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

sol
Vec4 cv_vec2_vec4(Vec2 v, Float z, Float w) {
  return vec4_init(v.x, v.y, z, w);
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

sol
Vec4 cv_vec3_vec4(Vec3 v, Float w) {
  return vec4_init(v.x, v.y, v.z, w);
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

sol
Float cv_deg_rad(Float deg) {
  return deg * ((Float) (M_PI / 180));
}

/// cv_rad_deg ///
// Description
//   Converts radians to degrees.
// Arguments
//   rad: Radians (Float)
// Returns
//   deg: Degrees (Float)

sol
Float cv_rad_deg(Float rad) {
  return rad * ((Float) (180 / M_PI));
}

#endif // SOL_CONV_H
