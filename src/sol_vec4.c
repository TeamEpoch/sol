    //////////////////////////////////////////////////////////////////////
   // sol_vec4.c ////////////////////////////////////////////////////////
  // Description: Adds 4D quaternion/axis-angle functionality to Sol. //
 // Author: David Garland (https://github.com/davidgarland/sol) ///////
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

sol
Vec4 vec4_init(Float x, Float y, Float z, Float w) {
  Vec4 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_set_pd(x, y, z, w);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_set_ps(x, y, z, w);
  #else
    out.x = x;
    out.y = y;
    out.z = z;
    out.w = w;
  #endif
  return out;
}

/// vec4_initf ///
// Description
//   Initializes a vector's XYZW values using a single float.
// Arguments
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {f, f, f, f}

sol
Vec4 vec4_initf(Float f) {
  Vec4 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_set1_pd(f);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_set1_ps(f);
  #elif defined(SOL_NEON_64)
    out.neon64 = vdupq_n_f64(f);
  #elif defined(SOL_NEON_32)
    out.neon32 = vdupq_n_f32(f);
  #else
    out = vec4_init(f, f, f, f);
  #endif
  return out;
}

/// vec4_zero ///
// Description
//   Initializes a vector's XYZW values as zero.
// Arguments
//   void
// Returns
//   Vector (Vec4) = {0, 0, 0, 0}

sol
Vec4 vec4_zero(void) {
  return vec4_initf(0);
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

sol
Vec4 vec4_norm(Vec4 v) {
  return vec4_divf(v, vec4_mag(v));
}

/// vec4_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   Vector (Vec4)
// Returns
//   Magnitude (Float)

sol
Float vec4_mag(Vec4 v) {
  return flt_sqrt(vec4_sum(vec4_mul(v, v)));
}

/// vec4_eq ///
// Description
//   Tests two vectors for equality.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Equality (bool)

sol
bool vec4_eq(Vec4 a, Vec4 b, Float ep) {
  const Vec4 c = vec4_sub(a, b);
  if (c.x < ep) {
    if (c.y < ep) {
      if (c.z < ep) {
        if (c.w < ep) {
          return true;
        }
      }
    }
  }
  return false;
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Basic Functions //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec4_sum ///
// Description
//   Gets the sum of all the dimensions of a vector.
// Arguments
//   v: Vector (Vec4)
// Returns
//   Scalar (Float) = v.x + v.y + v.z + v.w

sol
Float vec4_sum(Vec4 v) {
  return v.x + v.y + v.z + v.w;
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

sol
Vec4 vec4_fma(Vec4 a, Vec4 b, Vec4 c) {
  Vec4 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_fmadd_pd(a.avx64, b.avx64, c.avx64);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_fmadd_ps(a.avx32, b.avx32, c.avx32);
  #elif defined(SOL_NEON_64)
    out.neon64 = vfmaq_f64(a.neon64, b.neon64, c.neon64);
  #elif defined(SOL_NEON_32)
    out.neon32 = vfmaq_f32(a.neon32, b.neon32, c.neon32);
  #else
    out = vec4_add(vec4_mul(a, b), c);
  #endif
  return out;
}

/// vec4_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw + b.xyzw}

sol
Vec4 vec4_add(Vec4 a, Vec4 b) {
  Vec4 out;
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
    out.w = a.w + b.w;
  #endif
  return out;
}

/// vec4_addf ///
// Description
//   Adds a scalar to each element of a vector.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw + f}

sol
Vec4 vec4_addf(Vec4 v, Float f) {
  return vec4_add(v, vec4_initf(f));
}

/// vec4_sub ///
// Description
//   Subtract the elements of one vector from another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw - b.xyzw}

sol
Vec4 vec4_sub(Vec4 a, Vec4 b) {
  Vec4 out;
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
    out.w = a.w - b.w;
  #endif
  return out;
}

/// vec4_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw - f}

sol
Vec4 vec4_subf(Vec4 v, Float f) {
  return vec4_sub(v, vec4_initf(f));
}

/// vec4_fsub ///
// Description
//   Subtracts each of a vector'e elements from a scalar.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec4)
// Returns
//   Vector (Vec4) = {f - v.xyzw}

sol
Vec4 vec4_fsub(Float f, Vec4 v) {
  return vec4_sub(vec4_initf(f), v);
}

/// vec4_mul ///
// Description
//   Multiplies the elements of one vector by another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw * b.xyzw}

sol
Vec4 vec4_mul(Vec4 a, Vec4 b) {
  Vec4 out;
  #if defined(SOL_AVX_64)
    out.avx64 = _mm256_mul_pd(a.avx64, b.avx64);
  #elif defined(SOL_AVX_32)
    out.avx32 = _mm_mul_ps(a.avx32, b.avx32);
  #elif defined(SOL_NEON_64)
    out.neon64 = vmulq_f64(a.neon64, b.neon64);
  #elif defined(SOL_NEON_32)
    out.neon32 = vmulq_f32(a.neon32, b.neon32);
  #else
    out.x = a.x * b.x;
    out.y = a.y * b.y;
    out.z = a.z * b.z;
    out.w = a.w * b.w;
  #endif
  return out;
}

/// vec4_mulf ///
// Description
//   Multiplies the elements of a vector by a scalar.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw * f}

sol
Vec4 vec4_mulf(Vec4 v, Float f) {
  return vec4_mul(v, vec4_initf(f));
}

/// vec4_div ///
// Description
//   Divides the elements of one vector by another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {a.xyzw / b.xyzw}

sol
Vec4 vec4_div(Vec4 a, Vec4 b) {
  Vec4 out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  out.z = a.z / b.z;
  out.w = a.w / b.w;
  return out;
}

/// vec4_divf ///
// Description
//   Divides the elements of a vector by a scalar.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {v.xyzw / f}

sol
Vec4 vec4_divf(Vec4 v, Float f) {
  return vec4_div(v, vec4_initf(f));
}

/// vec4_fdiv ///
// Description
//   Divides a scalar by the elements of a vector.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec4)
// Returns
//   Vector (Vec4) = {f / v.xyzw}

sol
Vec4 vec4_fdiv(Float f, Vec4 v) {
  return vec4_div(vec4_initf(f), v);
}

/// vec4_avg ///
// Description
//   Averages the elements of one vector with another.
// Arguments
//   a: Vector (Vec4)
//   b: Vector (Vec4)
// Returns
//   Vector (Vec4) = {(a.xyzw + b.xyzw) / 2}

sol
Vec4 vec4_avg(Vec4 a, Vec4 b) {
  return vec4_divf(vec4_mul(a, b), 2);
}

/// vec4_avgf ///
// Description
//   Averages the elements of a vector with a scalar.
// Arguments
//   v: Vector (Vec4)
//   f: Scalar (Float)
// Returns
//   Vector (Vec4) = {(v.xyzw + f) / 2}

sol
Vec4 vec4_avgf(Vec4 v, Float f) {
  return vec4_avg(v, vec4_initf(f));
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

sol
void vec4_print(Vec4 v) {
  printf("(" SOL_F_FMT ", " SOL_F_FMT ", " SOL_F_FMT ", " SOL_F_FMT ")\n", (FloatCast) v.x,
                                                                           (FloatCast) v.y,
                                                                           (FloatCast) v.z,
                                                                           (FloatCast) v.w);
}
