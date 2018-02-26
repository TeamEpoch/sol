    //////////////////////////////////////////////////////////////////
   // sol.h /////////////////////////////////////////////////////////
  // Description: A vector library written only in C. //////////////
 // Author: David Garland (https://github.com/davidgarland/sol) ///
//////////////////////////////////////////////////////////////////

#ifndef SOL_H
#define SOL_H

#ifdef __cplusplus
  extern "C" {
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Standard Headers //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

  //////////////////////////////////////////////////////////////////////////////
 // Default Config ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define SOL_F_SIZE_DEFAULT 64 // Set the size of the Float type.
#define SOL_SIMD_DEFAULT   0  // Set SIMD mode. 0: NONE, 1: AUTO, 2: AVX, 3: NEON

#define SOL_INLINE_DEFAULT false // Enables function inlining.
#define SOL_FAM_DEFAULT    true // Enables C99 "Flexible Array Members" (FAM.)

#define SOL_ASSERT false // Enables runtime assertions. May run much slower.
#define SOL_DEBUG  false // Enables developer debug messages. Not for end users.

  //////////////////////////////////////////////////////////////////////////////
 // Config Defaults Handling //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

  ////////////////
 // SOL_F_SIZE //
////////////////

#if !defined(SOL_F_SIZE)
  #if SOL_F_SIZE_DEFAULT > 64
    #define SOL_F_SIZE 80
  #elif SOL_F_SIZE_DEFAULT > 32
    #define SOL_F_SIZE 64
  #else
    #define SOL_F_SIZE 32
  #endif
  #define SOL_F_SIZE_AUTO
#endif

  /////////////
 // SOL_FAM //
/////////////

#if !defined(SOL_FAM) && !defined(SOL_NO_FAM)
  #if SOL_FAM_DEFAULT == true
    #define SOL_FAM
    #define SOL_FAM_AUTO
  #endif
#else
  #ifdef SOL_NO_FAM
    #ifdef SOL_FAM
      #undef SOL_FAM
    #endif
  #endif
#endif

  //////////////
 // SOL_SIMD //
//////////////

#if defined(SOL_AVX) || defined(SOL_AVX2) || defined(SOL_NEON)
  #if !defined(SOL_SIMD)
    #define SOL_SIMD
  #endif
#endif

#if !defined(SOL_SIMD) && !defined(SOL_NO_SIMD)
  #if SOL_SIMD_DEFAULT == 1
    #if defined(__AVX__) || defined(__AVX2__)
      #define SOL_AVX
      #if defined(__AVX2__)
        #define SOL_AVX2
      #endif
    #elif defined(__ARM_NEON__)
      #define SOL_NEON
    #endif 
  #elif SOL_SIMD_DEFAULT == 2
    #define SOL_AVX
  #elif SOL_SIMD_DEFAULT == 3
    #define SOL_NEON
  #endif
#else
  #if defined(SOL_NO_SIMD)
    #if defined(SOL_AVX)
      #undef SOL_AVX
    #endif
    #if defined(SOL_AVX_64)
      #undef SOL_AVX_64
    #endif
    #if defined(SOL_AVX_32)
      #undef SOL_AVX_32
    #endif
    #if defined(SOL_NEON)
      #undef SOL_NEON
    #endif
    #if defined(SOL_NEON_64)
      #undef SOL_NEON_64
    #endif
    #if defined(SOL_NEON_32)
      #undef SOL_NEON_32
    #endif
  #endif
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Config Checks /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if defined(SOL_SIMD)
  #if SOL_F_SIZE > 64
    #undef SOL_F_SIZE
    #define SOL_F_SIZE 64
  #endif
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Config Application ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if defined(SOL_SIMD)
  #if defined(SOL_AVX2)
    #if SOL_F_SIZE > 32
      #define SOL_AVX2_64
    #else
      #define SOL_AVX2_32
    #endif
  #endif
  #if defined(SOL_AVX)
    #include <x86intrin.h>
    #if SOL_F_SIZE > 32
      #define SOL_AVX_64
    #else
      #define SOL_AVX_32
    #endif
  #endif
  #if defined(SOL_NEON)
    #include <arm_neon.h>
    #if SOL_F_SIZE > 32
      #define SOL_NEON_64
    #else
      #define SOL_NEON_32
    #endif
  #endif
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Core Macros ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef SOL_INLINE
  #define sol_inline static inline
#else
  #define sol_inline
#endif

#define sol sol_inline

  //////////////////////////////////////////////////////////////////////////////
 // Core Type Definitions /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if SOL_F_SIZE > 64
  typedef long double Float;
  typedef long double FloatCast;
  #define SOL_F_FMT "%Le"
#elif SOL_F_SIZE > 32
  typedef double Float;
  typedef double FloatCast;
  #define SOL_F_FMT "%e"
#else
  typedef float Float;
  typedef double FloatCast;
  #define SOL_F_FMT "%f"
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Math Constants ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// sol_pi ///
// Description
//   The constant used to equal the value of Pi for Sol's internal calculations.

static const Float sol_pi = ((Float)(3.14159265358979323846));

/// sol_tau ///
// Description
//   A constant which is equal to two times the value of Pi for Sol's internal
//   calculations.

static const Float sol_tau = ((Float)(6.28318530717958647692));

/// sol_g ///
// Description
//   A constant which is equal to the acceleration of gravity in m/s/s.

static const Float sol_g = ((Float)(9.80665));

/// sol_c ///
// Description
//   A constant which is equal to the speed of light in m/s.

static const Float sol_c = ((Float)(299792000));

  //////////////////////////////////////////////////////////////////////////////
 // Struct Type Definitions ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// Vec2 ///
// Description
//   A type comprised of two floats to represent a 2D vector or position.
// Fields
//   x: Dimension (Float)
//   y: Dimension (Float)
//   f: Dimensions (Float[2])

typedef union {
  struct {
    Float x, y;
  };
  Float f[2];
  #if defined(SOL_AVX_64)
    __m128d avx64;
  #elif defined(SOL_AVX_32)
    __m128 avx32;
  #elif defined(SOL_NEON_64)
    f64x2_t neon64;
  #elif defined(SOL_NEON_32)
    f32x2_t neon32;
  #endif
} Vec2;

/// Vec3 ///
// Description
//   A type comprised of three floats to represent a 3D vector or position.
// Fields
//   x: Dimension (sol_f)
//   y: Dimension (sol_f)
//   z: Dimension (sol_F)
//   f: Dimensions (Float[3])

typedef union {
  struct {
    Float x, y, z;
  };
  Float f[3];
  #if defined(SOL_AVX_64)
    __m256d avx64;
  #elif defined(SOL_AVX_32)
    __m128 avx32;
  #elif defined(SOL_NEON_64)
    f64x4_t neon64;
  #elif defined(SOL_NEON_32)
    f32x4_t neon32;
  #endif
} Vec3;

/// Vec4 ///
// Description
//   A type comprised of four floats to represent a quaternion or axis/angle
//   rotation.
// Fields
//   x: Dimension (Float)
//   y: Dimension (Float)
//   z: Dimension (Float)
//   w: Dimension (Float)
//   f: Dimensions (Float[4])

typedef union {
  struct {
    Float x, y, z, w;
  };
  Float f[4];
  #if defined(SOL_AVX_64)
    __m256d avx64;
  #elif defined(SOL_AVX)
    __m128 avx32;
  #elif defined(SOL_NEON_64)
    f64x4_t neon64;
  #elif defined(SOL_NEON)
    f32x4_t neon32;
  #endif
} Vec4;

/// Ray2 ///
// Description
//   A type comprised of a 2D position and vector pair which represent
//   a ray.
// Fields
//   pos: Position (Vec2)
//   vec: Vector (Vec2)

typedef struct {
  Vec2 pos, vec;
} Ray2;

/// Ray3 ///
// Description
//   A type comprised of a 3D position and vector pair which represent
//   a ray.
// Fields
//   pos: Position (Vec3)
//   vec: Vector (Vec3)

typedef struct {
  Vec3 pos, vec;
} Ray3;

/// Seg2 ///
// Description
//   A type comprised of two 2D positions that represent a line segment.
// Fields
//   orig: Position (Vec2)
//   dest: Position (Vec2)

typedef struct {
  Vec2 orig, dest;
} Seg2;

/// Seg3 ///
// Description
//   A type comprised of two 3D positions that represent a line segment.
// Fields
//   orig: Position (Vec3)
//   dest: Position (Vec3)

typedef struct {
  Vec3 orig, dest;
} Seg3;

/// Mat2 ///
// Description
//   A type comprised of a 2x2 matrix of Float types, or two 2D
//   vectors.
// Fields
//   v: Vector Matrix (Vec2[2])
//   f: Float Matrix (Float[2][2])

typedef union {
  Vec2 v[2];
  Float f[2][2];
} Mat2;

/// Mat3 ///
// Description
//   A type comprised of a 3x3 matrix of Float types, or three
//   3D vectors.
// Fields
//   v: Vector Matrix (Vec3[3])
//   f: Float Matrix (Float[3][3])

typedef union {
  Vec3 v[3];
  Float f[3][3];
} Mat3;

/// Mat4 ///
// Description
//   A type comprised of a 4x4 matrix of Float types, or four
//   4D vectors.
// Fields
//   v: Vector Matrix (Vec4[4])
//   f: Float Matrix (Float[4][4])

typedef union {
  Vec4 v[4];
  Float f[4][4];
} Mat4;

/// Box2 ///
// Description
//   A type comprised of two 2D positions that represent a bounding box.
// Fields
//   lower: Position (Vec2)
//   upper: Position (Vec2)

typedef struct {
  Vec2 lower, upper;
} Box2;

/// Box3 ///
// Description
//   A type comprised of two 3D positions that represent a bounding box.
// Fields
//   upper: Position (Vec3)
//   lower: Position (Vec3)

typedef struct {
  Vec3 lower, upper;
} Box3;

/// Sph2 ///
// Description
//   A type comprised of a 2D position and a radius that represent a bounding
//   sphere.
// Fields
//   pos: Position (Vec2)
//   rad: Radius (Float)

typedef struct {
  Vec2 pos;
  Float rad;
} Sph2;

/// Sph3 ///
// Description
//   A type comprised of a 3D position and a radius that represent a bounding
//   sphere.
// Fields
//   pos: Position (Vec3)
//   rad: Radius (Float)

typedef struct {
  Vec3 pos;
  Float rad;
} Sph3;

  //////////////////////////////////////////////////////////////////////////////
 // Header Functions //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// sol_prefetch ///
// Description
//   A light wrapper over the compiler
//   extension called __builtin_prefetch.
// Arguments
//   p: Pointer (void*)
//   rw: Read/Write (int) {0 = Read, 1 = Write}
//   locality: Temporal Locality (int) {0 to 3; 0 = Lowest, 3 = Highest}
// Returns
//   void

#if defined(__clang__) || defined(__GNUC__)
  #define sol_prefetch(p, rw, locality) __builtin_prefetch(p, rw, locality)
#else
  #define sol_prefetch(p, rw, locality)
#endif

  //////////////////////////////////////////////////////////////////////////////
 // Float Function Declarations ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Float flt_clamp(Float f, Float lower, Float upper);
Float flt_abs(Float f);

Float flt_pow(Float a, Float b);
Float flt_sqrt(Float f);

Float flt_tan(Float f);
Float flt_atan(Float f);
Float flt_atan2(Float y, Float x);
Float flt_sin(Float f);
Float flt_asin(Float f);
Float flt_cos(Float f);
Float flt_acos(Float f);

  //////////////////////////////////////////////////////////////////////////////
 // Conversion Function Declarations //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec4 cv_axis_quat(Vec4 axis);
Vec4 cv_quat_axis(Vec4 quat);

Vec2 cv_vec3_vec2(Vec3 v);
Vec2 cv_vec4_vec2(Vec4 v);
Vec3 cv_vec2_vec3(Vec2 v, Float z);
Vec3 cv_vec4_vec3(Vec4 v);
Vec4 cv_vec2_vec4(Vec2 v, Float z, Float w);
Vec4 cv_vec3_vec4(Vec3 v, Float w);

Float cv_deg_rad(Float deg);
Float cv_rad_deg(Float rad);

  //////////////////////////////////////////////////////////////////////////////
 // Vec2 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec2 vec2_init(Float x, Float y);
Vec2 vec2_initf(Float f);
Vec2 vec2_zero(void);

Vec2 vec2_norm(Vec2 v);
Float vec2_mag(Vec2 v);
bool vec2_eq(Vec2 a, Vec2 b, Float ep);

Vec2 vec2_rot(Vec2 v, Float deg);
Vec2 vec2_rotr(Vec2 v, Float rad);

Vec2 vec2_proj(Vec2 a, Vec2 b);
Vec2 vec2_rej(Vec2 a, Vec2 b);
Float vec2_angle(Vec2 a, Vec2 b);
Float vec2_cross(Vec2 a, Vec2 b);
Float vec2_dot(Vec2 a, Vec2 b);

Float vec2_sum(Vec2 v);
Vec2 vec2_fma(Vec2 a, Vec2 b, Vec2 c);
Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_addf(Vec2 v, Float f);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_subf(Vec2 v, Float f);
Vec2 vec2_fsub(Float f, Vec2 v);
Vec2 vec2_mul(Vec2 a, Vec2 b);
Vec2 vec2_mulf(Vec2 v, Float f);
Vec2 vec2_div(Vec2 a, Vec2 b);
Vec2 vec2_divf(Vec2 v, Float f);
Vec2 vec2_fdiv(Float f, Vec2 v);
Vec2 vec2_pow(Vec2 a, Vec2 b);
Vec2 vec2_powf(Vec2 v, Float f);
Vec2 vec2_fpow(Float f, Vec2 v);
Vec2 vec2_avg(Vec2 a, Vec2 b);
Vec2 vec2_avgf(Vec2 v, Float f);

void vec2_print(Vec2 v);

  //////////////////////////////////////////////////////////////////////////////
 // Vec3 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec3 vec3_init(Float x, Float y, Float z);
Vec3 vec3_initf(Float f);
Vec3 vec3_zero(void);

Vec3 vec3_norm(Vec3 v);
Float vec3_mag(Vec3 v);
bool vec3_eq(Vec3 a, Vec3 b, Float ep);
Vec3 vec3_yzx(Vec3 v);

Vec3 vec3_rot(Vec3 v, Vec4 aa);
Vec3 vec3_rotq(Vec3 v, Vec4 q);

Vec3 vec3_proj(Vec3 a, Vec3 b);
Vec3 vec3_rej(Vec3 a, Vec3 b);
Float vec3_angle(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Float vec3_dot(Vec3 a, Vec3 b);

Float vec3_sum(Vec3 v);
Vec3 vec3_fma(Vec3 a, Vec3 b, Vec3 c);
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_addf(Vec3 v, Float f);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_subf(Vec3 v, Float f);
Vec3 vec3_fsub(Float f, Vec3 v);
Vec3 vec3_mul(Vec3 a, Vec3 b);
Vec3 vec3_mulf(Vec3 v, Float f);
Vec3 vec3_div(Vec3 a, Vec3 b);
Vec3 vec3_divf(Vec3 v, Float f);
Vec3 vec3_fdiv(Float f, Vec3 v);
Vec3 vec3_pow(Vec3 a, Vec3 b);
Vec3 vec3_powf(Vec3 v, Float f);
Vec3 vec3_fpow(Float f, Vec3 v);
Vec3 vec3_avg(Vec3 a, Vec3 b);
Vec3 vec3_avgf(Vec3 v, Float f);
void vec3_print(Vec3 v);

  //////////////////////////////////////////////////////////////////////////////
 // Vec4 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Vec4 vec4_init(Float x, Float y, Float z, Float w);
Vec4 vec4_initf(Float f);
Vec4 vec4_zero(void);

Vec4 vec4_norm(Vec4 v);
Float vec4_mag(Vec4 v);
bool vec4_eq(Vec4 a, Vec4 b, Float ep);

Float vec4_sum(Vec4 v);
Vec4 vec4_fma(Vec4 a, Vec4 b, Vec4 c);
Vec4 vec4_add(Vec4 a, Vec4 b);
Vec4 vec4_addf(Vec4 v, Float f);
Vec4 vec4_sub(Vec4 a, Vec4 b);
Vec4 vec4_subf(Vec4 v, Float f);
Vec4 vec4_fsub(Float f, Vec4 v);
Vec4 vec4_mul(Vec4 a, Vec4 b);
Vec4 vec4_mulf(Vec4 v, Float f);
Vec4 vec4_div(Vec4 a, Vec4 b);
Vec4 vec4_divf(Vec4 v, Float f);
Vec4 vec4_fdiv(Float f, Vec4 v);
Vec4 vec4_avg(Vec4 a, Vec4 b);
Vec4 vec4_avgf(Vec4 v, Float f);

void vec4_print(Vec4 v);

  //////////////////////////////////////////////////////////////////////////////
 // Ray2 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Ray2 ray2_init(Vec2 pos, Vec2 vec);
Ray2 ray2_initv(Vec2 v);
Ray2 ray2_initf(Float f);
Ray2 ray2_zero(void);

Ray2 ray2_norm(Ray2 r);
Float ray2_mag(Ray2 r);
bool ray2_eq(Ray2 a, Ray2 b, Float ep);

Ray2 ray2_rot(Ray2 r, Float deg);
Ray2 ray2_rotr(Ray2 r, Float rad);

Float ray2_sump(Ray2 r);
Float ray2_sumv(Ray2 r);
Ray2 ray2_addp(Ray2 r, Vec2 p);
Ray2 ray2_addpf(Ray2 r, Float f);
Ray2 ray2_addv(Ray2 r, Vec2 v);
Ray2 ray2_addvf(Ray2 r, Float f);
Ray2 ray2_subp(Ray2 r, Vec2 p);
Ray2 ray2_subpf(Ray2 r, Float f);
Ray2 ray2_psub(Vec2 p, Ray2 r);
Ray2 ray2_pfsub(Float f, Ray2 r);
Ray2 ray2_subv(Ray2 r, Vec2 v);
Ray2 ray2_subvf(Ray2 r, Float f);
Ray2 ray2_vsub(Vec2 v, Ray2 r);
Ray2 ray2_vfsub(Float f, Ray2 r);
Ray2 ray2_mulp(Ray2 r, Vec2 p);
Ray2 ray2_mulpf(Ray2 r, Float f);
Ray2 ray2_mulv(Ray2 r, Vec2 v);
Ray2 ray2_mulvf(Ray2 r, Float f);
Ray2 ray2_divp(Ray2 r, Vec2 p);
Ray2 ray2_divpf(Ray2 r, Float f);
Ray2 ray2_pdiv(Vec2 p, Ray2 r);
Ray2 ray2_pfdiv(Float f, Ray2 r);
Ray2 ray2_divv(Ray2 r, Vec2 v);
Ray2 ray2_divvf(Ray2 r, Float f);
Ray2 ray2_vdiv(Vec2 v, Ray2 r);
Ray2 ray2_vfdiv(Float f, Ray2 r);
Ray2 ray2_avgp(Ray2 r, Vec2 p);
Ray2 ray2_avgpf(Ray2 r, Float f);
Ray2 ray2_avgv(Ray2 r, Vec2 v);
Ray2 ray2_avgvf(Ray2 r, Float f);

void ray2_print(Ray2 r);

  //////////////////////////////////////////////////////////////////////////////
 // Ray3 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Ray3 ray3_init(Vec3 pos, Vec3 vec);
Ray3 ray3_initv(Vec3 v);
Ray3 ray3_initf(Float f);
Ray3 ray3_zero(void);

Ray3 ray3_norm(Ray3 r);
Float ray3_mag(Ray3 r);
bool ray3_eq(Ray3 a, Ray3 b, Float ep);

Ray3 ray3_rot(Ray3 r, Vec4 aa);
Ray3 ray3_rotq(Ray3 r, Vec4 q);

Float ray3_sump(Ray3 r);
Float ray3_sumv(Ray3 r);
Ray3 ray3_addp(Ray3 r, Vec3 p);
Ray3 ray3_addpf(Ray3 r, Float f);
Ray3 ray3_addv(Ray3 r, Vec3 v);
Ray3 ray3_addvf(Ray3 r, Float f);
Ray3 ray3_subp(Ray3 r, Vec3 p);
Ray3 ray3_subpf(Ray3 r, Float f);
Ray3 ray3_psub(Vec3 p, Ray3 r);
Ray3 ray3_pfsub(Float f, Ray3 r);
Ray3 ray3_subv(Ray3 r, Vec3 v);
Ray3 ray3_subvf(Ray3 r, Float f);
Ray3 ray3_vsub(Vec3 v, Ray3 r);
Ray3 ray3_vfsub(Float f, Ray3 r);
Ray3 ray3_mulp(Ray3 r, Vec3 p);
Ray3 ray3_mulpf(Ray3 r, Float f);
Ray3 ray3_mulv(Ray3 r, Vec3 v);
Ray3 ray3_mulvf(Ray3 r, Float f);
Ray3 ray3_divp(Ray3 r, Vec3 p);
Ray3 ray3_divpf(Ray3 r, Float f);
Ray3 ray3_pdiv(Vec3 p, Ray3 r);
Ray3 ray3_pfdiv(Float f, Ray3 r);
Ray3 ray3_divv(Ray3 r, Vec3 v);
Ray3 ray3_divvf(Ray3 r, Float f);
Ray3 ray3_vdiv(Vec3 v, Ray3 r);
Ray3 ray3_vfdiv(Float f, Ray3 r);
Ray3 ray3_avgp(Ray3 r, Vec3 p);
Ray3 ray3_avgpf(Ray3 r, Float f);
Ray3 ray3_avgv(Ray3 r, Vec3 v);
Ray3 ray3_avgvf(Ray3 r, Float f);

void ray3_print(Ray3 r);

  //////////////////////////////////////////////////////////////////////////////
 // Seg2 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Seg2 seg2_init(Vec2 orig, Vec2 dest);
Seg2 seg2_initv(Vec2 v);
Seg2 seg2_initf(Float f);
Seg2 seg2_zero(void);

Seg2 seg2_add(Seg2 a, Seg2 b);
Seg2 seg2_addv(Seg2 s, Vec2 v);
Seg2 seg2_addf(Seg2 s, Float f);
Seg2 seg2_sub(Seg2 a, Seg2 b);
Seg2 seg2_subv(Seg2 s, Vec2 v);
Seg2 seg2_vsub(Vec2 v, Seg2 s);
Seg2 seg2_subf(Seg2 s, Float f);
Seg2 seg2_fsub(Float f, Seg2 s);
Seg2 seg2_mul(Seg2 a, Seg2 b);
Seg2 seg2_mulv(Seg2 s, Vec2 v);
Seg2 seg2_mulf(Seg2 s, Float f);
Seg2 seg2_div(Seg2 a, Seg2 b);
Seg2 seg2_divv(Seg2 s, Vec2 v);
Seg2 seg2_vdiv(Vec2 v, Seg2 s);
Seg2 seg2_divf(Seg2 s, Float f);
Seg2 seg2_fdiv(Float f, Seg2 s);
Seg2 seg2_avg(Seg2 a, Seg2 b);
Seg2 seg2_avgv(Seg2 s, Vec2 v);
Seg2 seg2_avgf(Seg2 s, Float f);

void seg2_print(Seg2 s);

  //////////////////////////////////////////////////////////////////////////////
 // Seg3 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Seg3 seg3_init(Vec3 orig, Vec3 dest);
Seg3 seg3_initv(Vec3 v);
Seg3 seg3_initf(Float f);
Seg3 seg3_zero(void);

Seg3 seg3_add(Seg3 a, Seg3 b);
Seg3 seg3_addv(Seg3 s, Vec3 v);
Seg3 seg3_addf(Seg3 s, Float f);
Seg3 seg3_sub(Seg3 a, Seg3 b);
Seg3 seg3_subv(Seg3 s, Vec3 v);
Seg3 seg3_vsub(Vec3 v, Seg3 s);
Seg3 seg3_subf(Seg3 s, Float f);
Seg3 seg3_fsub(Float f, Seg3 s);
Seg3 seg3_mul(Seg3 a, Seg3 b);
Seg3 seg3_mulv(Seg3 s, Vec3 v);
Seg3 seg3_mulf(Seg3 s, Float f);
Seg3 seg3_div(Seg3 a, Seg3 b);
Seg3 seg3_divv(Seg3 s, Vec3 v);
Seg3 seg3_vdiv(Vec3 v, Seg3 s);
Seg3 seg3_divf(Seg3 s, Float f);
Seg3 seg3_fdiv(Float f, Seg3 s);
Seg3 seg3_avg(Seg3 a, Seg3 b);
Seg3 seg3_avgv(Seg3 s, Vec3 v);
Seg3 seg3_avgf(Seg3 s, Float f);

void seg3_print(Seg3 s);

  //////////////////////////////////////////////////////////////////////////////
 // Mat2 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Mat2 mat2_init(Float f11, Float f12,
                          Float f21, Float f22);
Mat2 mat2_initv(Vec2 v1,
                           Vec2 v2);
Mat2 mat2_initf(Float f);

Mat2 mat2_zero(void);

Mat2 mat2_add(Mat2 a, Mat2 b);
Mat2 mat2_addf(Mat2 m, Float f);
Mat2 mat2_sub(Mat2 a, Mat2 b);
Mat2 mat2_subf(Mat2 m, Float f);
Mat2 mat2_fsub(Float f, Mat2 m);
Mat2 mat2_mul(Mat2 a, Mat2 b);
Mat2 mat2_mulf(Mat2 m, Float f);
Mat2 mat2_div(Mat2 a, Mat2 b);
Mat2 mat2_divf(Mat2 m, Float f);
Mat2 mat2_fdiv(Float f, Mat2 m);
Mat2 mat2_avg(Mat2 a, Mat2 b);
Mat2 mat2_avgf(Mat2 m, Float f);

void mat2_print(Mat2 m);

  //////////////////////////////////////////////////////////////////////////////
 // Mat3 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Mat3 mat3_init(Float f11, Float f12, Float f13,
                          Float f21, Float f22, Float f23,
                          Float f31, Float f32, Float f33);
Mat3 mat3_initv(Vec3 v1,
                           Vec3 v2,
                           Vec3 v3);
Mat3 mat3_initf(Float f);
Mat3 mat3_zero(void);

Mat3 mat3_add(Mat3 a, Mat3 b);
Mat3 mat3_addf(Mat3 m, Float f);
Mat3 mat3_sub(Mat3 a, Mat3 b);
Mat3 mat3_subf(Mat3 m, Float f);
Mat3 mat3_fsub(Float f, Mat3 m);
Mat3 mat3_mul(Mat3 a, Mat3 b);
Mat3 mat3_mulf(Mat3 m, Float f);
Mat3 mat3_div(Mat3 a, Mat3 b);
Mat3 mat3_divf(Mat3 m, Float f);
Mat3 mat3_fdiv(Float f, Mat3 m);
Mat3 mat3_avg(Mat3 a, Mat3 b);
Mat3 mat3_avgf(Mat3 m, Float f);

void mat3_print(Mat3 m);

  //////////////////////////////////////////////////////////////////////////////
 // Mat4 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Mat4 mat4_init(Float f11, Float f12, Float f13, Float f14,
                          Float f21, Float f22, Float f23, Float f24,
                          Float f31, Float f32, Float f33, Float f34,
                          Float f41, Float f42, Float f43, Float f44);
Mat4 mat4_initv(Vec4 v1,
                           Vec4 v2,
                           Vec4 v3,
                           Vec4 v4);
Mat4 mat4_initf(Float f);
Mat4 mat4_zero(void);

Mat4 mat4_add(Mat4 a, Mat4 b);
Mat4 mat4_addf(Mat4 m, Float f);
Mat4 mat4_sub(Mat4 a, Mat4 b);
Mat4 mat4_subf(Mat4 m, Float f);
Mat4 mat4_fsub(Float f, Mat4 m);
Mat4 mat4_mul(Mat4 a, Mat4 b);
Mat4 mat4_mulf(Mat4 m, Float f);
Mat4 mat4_div(Mat4 a, Mat4 b);
Mat4 mat4_divf(Mat4 m, Float f);
Mat4 mat4_fdiv(Float f, Mat4 m);
Mat4 mat4_avg(Mat4 a, Mat4 b);
Mat4 mat4_avgf(Mat4 m, Float f);

void mat4_print(Mat4 m);

  //////////////////////////////////////////////////////////////////////////////
 // Box2 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Box2 box2_init(Vec2 lower, Vec2 upper);
Box2 box2_initv(Vec2 v);
Box2 box2_initf(Float f);
Box2 box2_zero(void);

Vec2 box2_pos(Box2 b);
Float box2_x(Box2 b);
Float box2_y(Box2 b);

bool box2_aabb(Box2 a, Box2 b);
bool box2_pip(Box2 b, Vec2 v);

Box2 box2_add(Box2 a, Box2 b);
Box2 box2_addv(Box2 b, Vec2 v);
Box2 box2_addf(Box2 b, Float f);
Box2 box2_sub(Box2 a, Box2 b);
Box2 box2_subv(Box2 b, Vec2 v);
Box2 box2_vsub(Vec2 v, Box2 b);
Box2 box2_subf(Box2 b, Float f);
Box2 box2_fsub(Float f, Box2 b);
Box2 box2_mul(Box2 a, Box2 b);
Box2 box2_mulv(Box2 b, Vec2 v);
Box2 box2_mulf(Box2 b, Float f);
Box2 box2_div(Box2 a, Box2 b);
Box2 box2_divv(Box2 b, Vec2 v);
Box2 box2_vdiv(Vec2 v, Box2 b);
Box2 box2_divf(Box2 b, Float f);
Box2 box2_fdiv(Float f, Box2 b);

  //////////////////////////////////////////////////////////////////////////////
 // Box3 Function Declarations ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Box3 box3_init(Vec3 lower, Vec3 upper);
Box3 box3_initv(Vec3 v);
Box3 box3_initf(Float f);
Box3 box3_zero(void);

Vec3 box3_pos(Box3 b);
Float box3_x(Box3 b);
Float box3_y(Box3 b);
Float box3_z(Box3 b);

bool box3_aabb(Box3 a, Box3 b);
bool box3_pip(Box3 b, Vec3 v);

Box3 box3_add(Box3 a, Box3 b);
Box3 box3_addv(Box3 b, Vec3 v);
Box3 box3_addf(Box3 b, Float f);
Box3 box3_sub(Box3 a, Box3 b);
Box3 box3_subv(Box3 b, Vec3 v);
Box3 box3_vsub(Vec3 v, Box3 b);
Box3 box3_subf(Box3 b, Float f);
Box3 box3_fsub(Float f, Box3 b);
Box3 box3_mul(Box3 a, Box3 b);
Box3 box3_mulv(Box3 b, Vec3 v);
Box3 box3_mulf(Box3 b, Float f);
Box3 box3_div(Box3 a, Box3 b);
Box3 box3_divv(Box3 b, Vec3 v);
Box3 box3_vdiv(Vec3 v, Box3 b);
Box3 box3_divf(Box3 b, Float f);
Box3 box3_fdiv(Float f, Box3 b);

#ifdef __cplusplus
  } // extern "C"
#endif

#endif // SOL_H
