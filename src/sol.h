/*
** sol.h | The Sol Vector Library | Main Header
** https://github.com/davidgarland/sol
*/

#ifndef SOL_H
#define SOL_H

/*
** Dependencies
*/

#ifdef __AVX__
  #include <x86intrin.h>
#endif

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

/*
** Config Defaults
*/

#define SOL_D_GNU true

/*
** Config Handling
*/

#if !defined(SOL_GNU) && !defined(SOL_N_GNU) && SOL_D_GNU
  #define SOL_GNU
#elif defined(SOL_GNU) && defined(SOL_N_GNU)
  #undef SOL_GNU
#endif

/*
** Scalar Types
*/

typedef float    f32;
typedef double   f64;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t   u8;
typedef uint32_t u32;
typedef uint64_t u64;

/*
** Vector Types
*/

#ifdef SOL_GNU /* SIMD Execution */
  #define vectype(T, S) __attribute__((vector_size(S * sizeof(T))))
  
  /* f32 */
  typedef f32 f32x2 vectype(f32, 2);
  typedef f32 f32x3 vectype(f32, 4);
  typedef f32 f32x4 vectype(f32, 4);
  /* f64 */
  typedef f64 f64x2 vectype(f64, 2);
  typedef f64 f64x3 vectype(f64, 4);
  typedef f64 f64x4 vectype(f64, 4);
  /* i32 */
  typedef i32 i32x2 vectype(i32, 2);
  typedef i32 i32x3 vectype(i32, 4);
  typedef i32 i32x4 vectype(i32, 4);
  /* i64 */
  typedef i64 i64x2 vectype(i64, 2);
  typedef i64 i64x3 vectype(i64, 4);
  typedef i64 i64x4 vectype(i64, 4);
  /* u8 */
  typedef u8 u8x2 vectype(u8, 2);
  typedef u8 u8x3 vectype(u8, 4);
  typedef u8 u8x4 vectype(u8, 4);
  /* u32 */
  typedef u32 u32x2 vectype(u32, 2);
  typedef u32 u32x3 vectype(u32, 4);
  typedef u32 u32x4 vectype(u32, 4);
  /* u64 */
  typedef u64 u64x2 vectype(u64, 2);
  typedef u64 u64x3 vectype(u64, 4);
  typedef u64 u64x4 vectype(u64, 4);

  #undef vectype
#else /* Scalar Execution */
  /* f32 */
  typedef struct { f32 x, y; }       f32x2;
  typedef struct { f32 x, y, z; }    f32x3;
  typedef struct { f32 x, y, z, w; } f32x4;
  /* f64 */
  typedef struct { f64 x, y; }       f64x2;
  typedef struct { f64 x, y, z; }    f64x3;
  typedef struct { f64 x, y, z, w; } f64x4;
  /* i32 */
  typedef struct { i32 x, y; }       i32x2;
  typedef struct { i32 x, y, z; }    i32x3;
  typedef struct { i32 x, y, z, w; } i32x4;
  /* i64 */
  typedef struct { i64 x, y; }       i64x2;
  typedef struct { i64 x, y, z; }    i64x3;
  typedef struct { i64 x, y, z, w; } i64x4;
  /* u8 */
  typedef struct { u8 x, y; }        u8x2;
  typedef struct { u8 x, y, z; }     u8x3;
  typedef struct { u8 x, y, z, w; }  u8x4;
  /* u32 */
  typedef struct { u32 x, y; }       u32x2;
  typedef struct { u32 x, y, z; }    u32x3;
  typedef struct { u32 x, y, z, w; } u32x4;
  /* u64 */
  typedef struct { u64 x, y; }       u64x2;
  typedef struct { u64 x, y, z; }    u64x3;
  typedef struct { u64 x, y, z, w; } u64x4;
#endif

/*
** Vector Scalar Accessors
*/

#ifdef SOL_GNU
  #define vec(V) V
  #define x(V) V[0]
  #define y(V) V[1]
  #define z(V) V[2]
  #define w(V) V[3]
#else
  #define vec(V) (&V.x)
  #define x(V) V.x
  #define y(V) V.y
  #define z(V) V.z
  #define w(V) V.w
#endif

/*
** Warning Suppression
*/

#if defined(__GNUC__) && !defined(__clang__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpsabi"
#endif

/*
** Constants
*/

static const f32 f32_pi    = 3.14159265358979323846f;
static const f32 f32_tau   = f32_pi * 2;
static const f32 f32_pi_2  = f32_pi / 2;
static const f32 f32_pi_sq = f32_pi * f32_pi;

static const f64 f64_pi    = 3.14159265358979323846;
static const f64 f64_tau   = f64_pi * 2;
static const f64 f64_pi_2  = f64_pi / 2;
static const f64 f64_pi_sq = f64_pi * f64_pi;

/*
** Prototypes
*/

#define _sol_ static inline

#define FX1(T) \
\
_sol_ T T##_sq(T f);               \
_sol_ T T##_sqrt(T f);             \
_sol_ T T##_abs(T f);              \
_sol_ T T##_neg(T f);              \
_sol_ T T##_neg_if(T f, u64 cond); \
_sol_ T T##_mod(T x, T y);         \
\
_sol_ T T##_sin(T f);  \
_sol_ T T##_cos(T f);  \
_sol_ T T##_tan(T f);  \
_sol_ T T##_asin(T f); \
_sol_ T T##_acos(T f); \
_sol_ T T##_atan(T f); \
_sol_ T T##_atan2(T y, T x);

FX1(f32)
FX1(f64)

#undef FX1

#define FX2(T, V) \
\
_sol_ V V##_set(T x, T y); \
_sol_ V V##_setf(T f);     \
_sol_ V V##_zero(void);    \
\
_sol_ V V##_rot(V v, T rad); \
_sol_ V V##_scale(V v, T f); \
\
_sol_ V V##_norm(V v);       \
_sol_ T V##_mag(V v);        \
_sol_ V V##_proj(V a, V b);  \
_sol_ V V##_rej(V a, V b);   \
_sol_ T V##_angle(V a, V b); \
_sol_ T V##_cross(V a, V b); \
_sol_ T V##_dot(V a, V b);   \
\
_sol_ T V##_sum(V v);           \
_sol_ V V##_sq(V v);            \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c);

FX2(f32, f32x2)
FX2(f64, f64x2)

#undef FX2

#define FX3(T, V) \
\
_sol_ V V##_set(T x, T y, T z); \
_sol_ V V##_setf(T f); \
_sol_ V V##_zero(void); \
\
_sol_ V V##_rot(V v, T##x4 q);  \
_sol_ V V##_scale(V v, T f); \
\
_sol_ V V##_norm(V v);       \
_sol_ T V##_mag(V v);        \
_sol_ V V##_proj(V a, V b);  \
_sol_ V V##_rej(V a, V b);   \
_sol_ T V##_angle(V a, V b); \
_sol_ V V##_cross(V a, V b); \
_sol_ T V##_dot(V a, V b);   \
\
_sol_ T V##_sum(V v);           \
_sol_ V V##_sq(V v);            \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \
\
_sol_ V V##_yzx(V v);

FX3(f32, f32x3)
FX3(f64, f64x3)

#undef FX3

static inline f32x3 f32x3_swiz(f32x3 v, u32x3 m);
static inline f64x3 f64x3_swiz(f64x3 v, u64x3 m);

#define FX4(T, V) \
\
_sol_ V V##_set(T x, T y, T z, T w); \
_sol_ V V##_setf(T f);               \
_sol_ V V##_zero(void);              \
\
_sol_ V V##_scale(V v, T f); \
\
_sol_ V V##_norm(V v); \
_sol_ T V##_mag(V v); \
\
_sol_ T V##_sum(V v);           \
_sol_ V V##_sq(V v);            \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \

FX4(f32, f32x4)
FX4(f64, f64x4)

#undef FX4

#define IX2(T, V) \
_sol_ V V##_set(T x, T y); \
_sol_ V V##_setf(T f);     \
_sol_ V V##_zero(void);    \
\
_sol_ T V##_sum(V v); \
_sol_ V V##_sq(V v);  \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \

IX2(i32, i32x2)
IX2(i64, i64x2)

#undef IX2

#define IX3(T, V) \
_sol_ V V##_set(T x, T y, T z); \
_sol_ V V##_setf(T f); \
_sol_ V V##_zero(void); \
\
_sol_ T V##_sum(V v); \
_sol_ V V##_sq(V v);  \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \

IX3(i32, i32x3)
IX3(i64, i64x3)

#undef IX3

#define IX4(T, V) \
_sol_ V V##_set(T x, T y, T z, T w); \
_sol_ V V##_setf(T f);               \
_sol_ V V##_zero(void);              \
\
_sol_ T V##_sum(V v); \
_sol_ V V##_sq(V v);  \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \

IX4(i32, i32x4)
IX4(i64, i64x4)

#undef IX4

#define UX2(T, V) \
_sol_ V V##_set(T x, T y); \
_sol_ V V##_setf(T f);     \
_sol_ V V##_zero(void);    \
\
_sol_ T V##_sum(V v); \
_sol_ V V##_sq(V v);  \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \

UX2(u8,   u8x2)
UX2(u32, u32x2)
UX2(u64, u64x2)

#undef UX2

#define UX3(T, V) \
_sol_ V V##_set(T x, T y, T z); \
_sol_ V V##_setf(T f);          \
_sol_ V V##_zero(void);         \
\
_sol_ T V##_sum(V v); \
_sol_ V V##_sq(V v);  \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \

UX3(u8,   u8x3)
UX3(u32, u32x3)
UX3(u64, u64x3)

#undef UX3
 
#define UX4(T, V) \
_sol_ V V##_set(T x, T y, T z, T w); \
_sol_ V V##_setf(T f);               \
_sol_ V V##_zero(void);              \
\
_sol_ T V##_sum(V v); \
_sol_ V V##_sq(V v);  \
\
_sol_ V V##_add(V a, V b);      \
_sol_ V V##_addf(V v, T f);     \
_sol_ V V##_sub(V a, V b);      \
_sol_ V V##_subf(V v, T f);     \
_sol_ V V##_fsub(T f, V v);     \
_sol_ V V##_mul(V a, V b);      \
_sol_ V V##_mulf(V v, T f);     \
_sol_ V V##_div(V a, V b);      \
_sol_ V V##_divf(V v, T f);     \
_sol_ V V##_fdiv(T f, V v);     \
_sol_ V V##_fma(V a, V b, V c); \
_sol_ V V##_fms(V a, V b, V c); \

UX4(u8,   u8x4)
UX4(u32, u32x4)
UX4(u64, u64x4)

#undef UX4

/*
** Header Inclusion
*/

#include "h/fx1.h"
#include "h/fx2.h"
#include "h/fx3.h"
#include "h/fx4.h"

#include "h/ix1.h"
#include "h/ix2.h"
#include "h/ix3.h"
#include "h/ix4.h"

#include "h/ux1.h"
#include "h/ux2.h"
#include "h/ux3.h"
#include "h/ux4.h"

/*
** Warning Suppression
*/

#if defined(__GNUC__) && !defined(__clang__)
  #pragma GCC diagnostic pop /* -Wpsabi */
#endif

#endif /* SOL_H */
