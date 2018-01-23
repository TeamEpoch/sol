    /////////////////////////////////////////////////////////////////
   // sol_vec2.h ///////////////////////////////////////////////////
  // Description: Adds 2D vector/position functionality to Sol. ///
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

#ifndef SOL_VEC2_H
#define SOL_VEC2_H

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

sol
Vec2 vec2_init(Float x, Float y) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.avx64 = _mm_set_pd(x, y);
  #elif defined(SOL_AVX_32)
        out.avx32 = _mm_set_ps(x, y, 0, 0);
  #else
        out.x = x;
        out.y = y;
  #endif
  return out;
}

/// vec2_initf ///
// Description
//   Initializes a vector's XY values using a single float.
// Arguments
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {f, f}

sol
Vec2 vec2_initf(Float f) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.avx64 = _mm_set1_pd(f);
  #elif defined(SOL_AVX_32)
        out.avx32 = _mm_set1_ps(f);
  #elif defined(SOL_NEON_64)
        out.neon64 = vdup_n_f64(f);
  #elif defined(SOL_NEON)
        out.neon32 = vdup_n_f32(f);
  #else
        out = vec2_init(f, f);
  #endif
  return out;
}

/// vec2_zero ///
// Description
//   Initizlies a vector's XYZ values as zero.
// Arguments
//   void
// Returns
//   Vector (Vec2) = {0, 0}

sol
Vec2 vec2_zero(void) {
  return vec2_initf(0);
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

sol
Vec2 vec2_norm(Vec2 v) {
  return vec2_divf(v, vec2_mag(v));
}

/// vec2_mag ///
// Description
//   Finds the magnitude of a vector.
// Arguments
//   v: Vector (Vec2)
// Returns
//   Magnitude (Float)

sol
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

sol
bool vec2_eq(Vec2 a, Vec2 b, Float ep) {
  const Vec2 c = vec2_sub(a, b);
  if (flt_abs(c.x) < ep) {
    if (flt_abs(c.y) < ep) {
      return true;
    }
  }
  return false;
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

sol
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

sol
Vec2 vec2_rotr(Vec2 v, Float rad) {
  const Float cs = flt_cos(rad);
  const Float sn = flt_sin(rad);
  return vec2_init((v.x * cs) - (v.y * sn),
                   (v.x * sn) + (v.y * cs));
}

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Advanced Math ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// vec2_cross ///
// Description
//   Gets the cross product of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Cross Product (Float)

sol
Float vec2_cross(Vec2 a, Vec2 b) {
  return (a.x * b.y)
       - (b.x * a.y);
}

/// vec2_dot ///
// Description
//   Gets the dot product of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Dot Product (Float)

sol
Float vec2_dot(Vec2 a, Vec2 b) {
  return vec2_sum(vec2_mul(a, b));
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

sol
Float vec2_sum(Vec2 v) {
  return v.x + v.y;
}

/// vec2_fma ///
// Description
//   Multiplies the elements of two vectors then adds the elements of a third.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
//   c: Vector (Vec2)
// Returns
//   Vector (Vec2) = {(a.xy * b.xy) + c.xy}

sol
Vec2 vec2_fma(Vec2 a, Vec2 b, Vec2 c) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.avx64 = _mm_add_pd(a.avx64, b.avx64, c.avx64);
  #elif defined(SOL_AVX_32)
        out.avx32 = _mm_add_ps(a.avx32, b.avx32, c.avx32);
  #elif defined(SOL_NEON_64)
        out.neon64 = vfma_f64(a.neon64, b.neon64, c.neon64);
  #elif defined(SOL_NEON_32)
        out.neon32 = vfma_f32(a.neon32, b.neon32, c.neon32);
  #else
        out = vec2_add(vec2_mul(a, b), c);
  #endif
  return out;
}



/// vec2_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xy + b.xy}

sol
Vec2 vec2_add(Vec2 a, Vec2 b) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.avx64 = _mm_add_pd(a.avx64, b.avx64);
  #elif defined(SOL_AVX_32)
        out.avx32 = _mm_add_ps(a.avx32, b.avx32);
  #elif defined(SOL_NEON_64)
        out.neon64 = vadd_f64(a.neon64, b.neon64);
  #elif defined(SOL_NEON_32)
        out.neon32 = vadd_f32(a.neon32, b.neon32);
  #else
        out.x = a.x + b.x;
        out.y = a.y + b.y;
  #endif
  return out;
}

/// vec2_addf ///
// Description
//   Adds a float to each element of a vector.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz + f}

sol
Vec2 vec2_addf(Vec2 v, Float f) {
  return vec2_add(v, vec2_initf(f));
}

/// vec2_sub ///
// Description
//   Subtract the elements of one vector from another.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xyz - b.xyz}

sol
Vec2 vec2_sub(Vec2 a, Vec2 b) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.avx64 = _mm_sub_pd(a.avx64, b.avx64);
  #elif defined(SOL_AVX_32)
        out.avx32 = _mm_sub_ps(a.avx32, b.avx32);
  #elif defined(SOL_NEON_64)
        out.neon64 = vsub_f64(a.neon64, b.neon64);
  #elif defined(SOL_NEON_32)
        out.neon32 = vsub_f32(a.neon32, b.neon32);
  #else
        out.x = a.x - b.x;
        out.y = a.y - b.y;
  #endif
  return out;
}

/// vec2_subf ///
// Description
//   Subtracts a scalar from each element of a vector.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz - f}

sol
Vec2 vec2_subf(Vec2 v, Float f) {
  return vec2_sub(v, vec2_initf(f));
}

/// vec2_fsub ///
// Description
//   Subtracts each element of a vector from a float.
// Arguments
//   f: Scalar (sol_f)
//   v: Vector (Vec2)
// Returns
//   Vector (Vec2) = {f - v.xyz}

sol
Vec2 vec2_fsub(Float f, Vec2 v) {
  return vec2_sub(vec2_initf(f), v);
}

/// vec2_mul ///
// Description
//   Multiplies the elements of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xyz * b.xyz}

sol
Vec2 vec2_mul(Vec2 a, Vec2 b) {
  Vec2 out;
  #if defined(SOL_AVX_64)
        out.avx64 = _mm_mul_pd(a.avx64, b.avx64);
  #elif defined(SOL_AVX_32)
        out.avx32 = _mm_mul_ps(a.avx32, b.avx32);
  #elif defined(SOL_NEON_64)
        out.neon64 = vmul_f64(a.neon64, b.neon64);
  #elif defined(SOL_NEON_32)
        out.neon32 = vmul_f32(a.neon32, b.neon32);
  #else
        out.x = a.x * b.x;
        out.y = a.y * b.y;
  #endif
  return out;
}

/// vec2_mulf ///
// Description
//   Multiplies each element of a vector by a float.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz * f}

sol
Vec2 vec2_mulf(Vec2 v, Float f) {
  return vec2_mul(v, vec2_initf(f));
}

/// vec2_div ///
// Description
//   Divide the elements of one vector by another.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xyz / b.xyz}

sol
Vec2 vec2_div(Vec2 a, Vec2 b) {
  Vec2 out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  return out;
}

/// vec2_divf ///
// Description
//   Divide the elements of a vector by a float.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {v.xyz / f}

sol
Vec2 vec2_divf(Vec2 v, Float f) {
  return vec2_div(v, vec2_initf(f));
}

/// vec2_fdiv ///
// Description
//   Divide a float by each element of a vector.
// Arguments
//   f: Scalar (Float)
//   v: Vector (Vec2)
// Returns
//   Vector (Vec2) = {f / v.xyz}

sol
Vec2 vec2_fdiv(Float f, Vec2 v) {
  return vec2_div(vec2_initf(f), v);
}

/// vec2_avg ///
// Description
//   Average each element of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {(a.xyz + b.xyz) / 2}

sol
Vec2 vec2_avg(Vec2 a, Vec2 b) {
  return vec2_divf(vec2_add(a, b), 2);
}

/// vec2_avgf ///
// Description
//   Average each element of a vector with a float.
// Arguments
//   v: Vector (Vec2)
//   f: Scalar (Float)
// Returns
//   Vector (Vec2) = {(v.xyz + f) / 2}

sol
Vec2 vec2_avgf(Vec2 v, Float f) {
  return vec2_avg(v, vec2_initf(f));
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

sol
void vec2_print(Vec2 v) {
  printf("(" SOL_F_FMT ", " SOL_F_FMT ")\n", (FloatCast) v.x,
                                             (FloatCast) v.y);
}

#endif // SOL_VEC2_H
