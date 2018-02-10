    /////////////////////////////////////////////////////////////////
   // sol_vec3.h ///////////////////////////////////////////////////
  // Description: Adds 3D vector/position functionality to Sol. ///
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

#ifndef SOL_VEC3_H
#define SOL_VEC3_H

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_init ///
// Description
//   Initializes a vector in XYZ order.
// Arguments
//   x: Dimension (Float)
//   y: Dimension (Float)
//   z: Dimension (Float)
// Returns
//   Vector (Vec3) = {x, y, z}

sol
Vec3 vec3_init(Float x, Float y, Float z) {
  Vec3 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_set_pd(x, y, z, 0);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_set_ps(x, y, z, 0);
  #else
    out.x = x;
    out.y = y;
    out.z = z;
  #endif
  return out;
}

/// vec3_initf ///
// Description
//   Initializes a vector's XYZ values using a single scalar.
// Arguments
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {f, f, f}

sol
Vec3 vec3_initf(Float f) {
  Vec3 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_set1_pd(f);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_set1_ps(f);
  #elif defined(SOL_NEON_64)
    out.neon64 = vdupq_n_f64(f);
  #elif defined(SOL_NEON_32)
    out.neon32 = vdupq_n_f32(f);
  #else
    out = vec3_init(f, f, f);
  #endif
  return out;
}

/// vec3_zero ///
// Description
//   Initializes a vector's XYZ values as zero.
// Arguments
//   void
// Returns
//   Vector (Vec3) = {0, 0, 0}

sol
Vec3 vec3_zero(void) {
  return vec3_initf(0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Core Operations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_norm ///
// Description
//   Normalizes a vector such that the magnitude is 1.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Normalized Vector (Vec3)

sol
Vec3 vec3_norm(Vec3 v) {
  return vec3_divf(v, vec3_mag(v));
}

/// vec3_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Magnitude (Float)

sol
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

sol
bool vec3_eq(Vec3 a, Vec3 b, Float ep) {
  const Vec3 c = vec3_sub(a, b);
  if (c.x < ep) {
    if (c.y < ep) {
      if (c.z < ep) {
        return true;
      }
    }
  }
  return false;
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Advanced Operations //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_rot ///
// Description
//   Rotates a vector by an axis/angle. Note that the angle is in degrees.
// Arguments
//   v: Vector (Vec3)
//   aa: Axis/Angle (Vec4)
// Returns
//   Vector (Vec3)

sol
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

sol
Vec3 vec3_rotq(Vec3 v, Vec4 q) {
  const Vec3 qv = vec3_init(q.x, q.y, q.z);
  const Vec3 t = vec3_mulf(vec3_cross(qv, v), 2);
  return vec3_add(v, vec3_add(vec3_mulf(t, q.w), vec3_cross(qv, t)));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Advanced Math ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_proj ///
// Description
//   Gets the projection of vector a onto b.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Projection (Vec3)

sol
Vec3 vec3_proj(Vec3 a, Vec3 b) {
  const Float ma = vec3_mag(a);
  const Float d = ma * ma;
  const Float f = vec3_dot(a, b) / d;
  return vec3_mulf(a, f);
}


/// vec3_rej ///
// Description
//   Gets the rejection of vector a from b.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Rejection (Vec3)

sol
Vec3 vec3_rej(Vec3 a, Vec3 b) {
  return vec3_sub(a, vec3_proj(a, b));
}

/// vec3_angle ///
// Description
//   Gets the angle between two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Angle (Float)

sol
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

sol
Vec3 vec3_cross(Vec3 a, Vec3 b) {
  const Vec3 va = vec3_init(a.y * b.z,
                            a.z * b.x,
                            a.x * b.y);
  const Vec3 vb = vec3_init(a.z * b.y,
                            a.x * b.z,
                            a.y * b.x);
  return vec3_sub(va, vb);
}

/// vec3_dot ///
// Description
//   Gets the dot product of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Dot Product (Float)

sol
Float vec3_dot(Vec3 a, Vec3 b) {
  return vec3_sum(vec3_mul(a, b));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_sum ///
// Description
//   Gets the sum of all of the dimensions of a vector.
// Arguments
//   v: Vector (Vec3)
// Returns
//   Sum (Float) = a.x + a.y + a.z

sol
Float vec3_sum(Vec3 v) {
  return v.x + v.y + v.z;
}

/// vec3_fma ///
// Description
//   Multiplies the elements of two vectors then adds the elements of a third.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
//   c: Vector (Vec3)
// Returns
//   Vector (Vec3) = {(a.xyz * b.xyz) + c.xyz}

sol
Vec3 vec3_fma(Vec3 a, Vec3 b, Vec3 c) {
  Vec3 out;
  #if defined(SOL_AVX2_64)
    out.avx64 = _mm256_fmadd_pd(a.avx64, b.avx64, c.avx64);
  #elif defined(SOL_AVX2_32)
    out.avx32 = _mm_fmadd_ps(a.avx32, b.avx32, c.avx32);
  #elif defined(SOL_NEON_64)
    out.neon64 = vfmaq_f64(a.neon64, b.neon64, c.neon64);
  #elif defined(SOL_NEON_32)
    out.neon32 = vfmaq_f32(a.neon32, b.neon32, c.neon32);
  #else
    out = vec3_add(vec3_mul(a, b), c);
  #endif
  return out;
}

/// vec3_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz + b.xyz}

sol
Vec3 vec3_add(Vec3 a, Vec3 b) {
  Vec3 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_add_pd(a.avx64, b.avx64);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_add_ps(a.avx32, b.avx32);
  #elif defined(SOL_NEON_64)
    out.neon64 = vaddq_f64(a.neon64, b.neon64);
  #elif defined(SOL_NEON_32)
    out.neon32 = vaddq_f32(a.neon32, b.neon32);
  #else
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;
  #endif
  return out;
}

/// vec3_addf ///
// Description
//   Adds a scalar to each element of a vector.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz + f}

sol
Vec3 vec3_addf(Vec3 v, Float f) {
  return vec3_add(v, vec3_initf(f));
}

/// vec3_sub ///
// Description
//   Subtracts the elements of one vector from another.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz - b.xyz}

sol
Vec3 vec3_sub(Vec3 a, Vec3 b) {
  Vec3 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_add_pd(a.avx64, b.avx64);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_add_ps(a.avx32, b.avx32);
  #elif defined(SOL_NEON_64)
    out.neon64 = vsubq_f64(a.neon64, b.neon64);
  #elif defined(SOL_NEON_32)
    out.neon32 = vsubq_f32(a.neon32, b.neon32);
  #else
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;
  #endif
  return out;
}

/// vec3_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz - f}

sol
Vec3 vec3_subf(Vec3 v, Float f) {
  return vec3_sub(v, vec3_initf(f));
}

/// vec3_fsub ///
// Description
//   Subtracts each element of a vector from a scalar.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec3)
// Returns
//   Vector (Vec3) = {f - v.xyz}

sol
Vec3 vec3_fsub(Float f, Vec3 v) {
  return vec3_sub(vec3_initf(f), v);
}

/// vec3_mul ///
// Description
//   Multiplies the elements of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz * b.xyz}

sol
Vec3 vec3_mul(Vec3 a, Vec3 b) {
  Vec3 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_add_pd(a.avx64, b.avx64);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_add_ps(a.avx32, b.avx32);
  #elif defined(SOL_NEON_64)
    out.neon64 = vmulq_f64(a.neon64, b.neon64);
  #elif defined(SOL_NEON_32)
    out.neon32 = vmulq_f32(a.neon32, b.neon32);
  #else
    out.x = a.x * b.x;
    out.y = a.y * b.y;
    out.z = a.z * b.z;
  #endif
  return out;
}

/// vec3_mulf ///
// Description
//   Multiplies each element of a vector by a scalar.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz * f}

sol
Vec3 vec3_mulf(Vec3 v, Float f) {
  return vec3_mul(v, vec3_initf(f));
}

/// vec3_div ///
// Description
//   Divides each element of one vector by another.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz / b.xyz}

sol
Vec3 vec3_div(Vec3 a, Vec3 b) {
  Vec3 out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  out.z = a.z / b.z;
  return out;
}

/// vec3_divf ///
// Description
//   Divide each element of a vector by a scalar.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz / f}

sol
Vec3 vec3_divf(Vec3 v, Float f) {
  return vec3_div(v, vec3_initf(f));
}

/// vec3_fdiv ///
// Description
//   Divide a scalar by each element of a vector.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec3)
// Returns
//   Vector (Vec3) = {f / v.xyz}

sol
Vec3 vec3_fdiv(Float f, Vec3 v) {
  return vec3_div(vec3_initf(f), v);
}

/// vec3_pow ///
// Description
//   Find a vector to the power of another.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {a.xyz ^ b.xyz}

sol
Vec3 vec3_pow(Vec3 a, Vec3 b) {
  Vec3 out;
  out.x = flt_pow(a.x, b.x);
  out.y = flt_pow(a.y, b.y);
  out.z = flt_pow(a.z, b.z);
  return out;
}

/// vec3_powf ///
// Description
//   Find a vector to the power of a scalar.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {v.xyz ^ f}

sol
Vec3 vec3_powf(Vec3 v, Float f) {
  return vec3_pow(v, vec3_initf(f));
}

/// vec3_fpow ///
// Description
//   Find a scalar to the power of a vector.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec3)
// Returns
//   Vector (Vec3) = {f ^ v.xyz}

sol
Vec3 vec3_fpow(Float f, Vec3 v) {
  return vec3_pow(vec3_initf(f), v);
}

/// vec3_avg ///
// Description
//   Average each element of two vectors.
// Arguments
//   a: Vector (Vec3)
//   b: Vector (Vec3)
// Returns
//   Vector (Vec3) = {(a.xyz + b.xyz) / 2}

sol
Vec3 vec3_avg(Vec3 a, Vec3 b) {
  return vec3_divf(vec3_add(a, b), 2);
}

/// vec3_avgf ///
// Description
//   Average each element of a vector with a float.
// Arguments
//   v: Vector (Vec3)
//   f: Scalar (Float)
// Returns
//   Vector (Vec3) = {(v.xyz + f) / 2}

sol
Vec3 vec3_avgf(Vec3 v, Float f) {
  return vec3_avg(v, vec3_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec3_print ///
// Description
//   Shows a vector's elements in stdout with a newline appended.
// Arguments
//   v: Vector (Vec3)
// Returns
//   void

sol
void vec3_print(Vec3 v) {
  printf("(" SOL_F_FMT ", " SOL_F_FMT ", " SOL_F_FMT ")\n", (FloatCast) v.x,
                                                            (FloatCast) v.y,
                                                            (FloatCast) v.z);
}

#endif // SOL_VEC3_H
