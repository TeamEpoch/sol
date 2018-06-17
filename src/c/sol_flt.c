   //                                               ////////////////////////////
  // sol_flt.c | Adds misc Float functions to Sol. ////////////////////////////
 // https://github.com/davidgarland/sol           ////////////////////////////
//                                               ////////////////////////////

#include "../sol.h"

  //                 ///////////////////////////////////////////////////////////
 // Basic Functions ///////////////////////////////////////////////////////////
//                 ///////////////////////////////////////////////////////////

/// flt_clamp ///
// Description
//   Clamps a Float to a specific lower/upper bounds.
// Arguments
//   f: Scalar (Float)
//   lower: Lower Bound (Float)
//   upper: Upper Bound (Float)
// Returns
//   Clamped Scalar (Float)

_sol_
Float flt_clamp(Float f, Float lower, Float upper) {
  return (f > upper) ? upper : (f < lower) ? lower : f;
}

/// flt_abs ///
// Description
//   A wrapper for fabsf/fabs/fabsl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Scalar (Float)
// Returns
//   Ab_sol_ute Value (Float)

_sol_
Float flt_abs(Float f) {
  #if SOL_FSIZE > 64
    return fabsl(f);
  #elif SOL_FSIZE > 32
    return fabs(f);
  #else
    return fabsf(f);
  #endif
}

/// flt_pow ///
// Description
//   A wrapper for powf/pow/powl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   a: Base (Float)
//   b: Exponent (Float)
// Returns
//   Power (Float)

_sol_
Float flt_pow(Float a, Float b) {
  #if SOL_FSIZE > 64
    return powl(a, b);
  #elif SOL_FSIZE > 32
    return pow(a, b);
  #else
    return powf(a, b);
  #endif
}

/// flt_sqrt ///
// Description
//   A wrapper for sqrtf/sqrt/sqrtl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Radicand (Float)
// Returns
//   Square Root (Float)

_sol_
Float flt_sqrt(Float f) {
  #if SOL_FSIZE > 64
    return sqrtl(f);
  #elif SOL_FSIZE > 32
    return sqrt(f);
  #else
    return sqrtf(f);
  #endif
}

  //                         ///////////////////////////////////////////////////
 // Trigonometric Functions ///////////////////////////////////////////////////
//                         ///////////////////////////////////////////////////

/// flt_tan ///
// Description
//   A wrapper for tanf/tan/tanl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Angle (Float)
// Returns
//   Tangent (Float)

_sol_
Float flt_tan(Float f) {
  #if SOL_FSIZE > 64
    return tanl(f);
  #elif SOL_FSIZE > 32
    return tan(f);
  #else
    return tanf(f);
  #endif
}

/// flt_atan ///
// Description
//   A wrapper for atanf/atan/atanl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Angle (Float)
// Returns
//   Arctangent (Float)

_sol_
Float flt_atan(Float f) {
  #if SOL_FSIZE > 64
    return atanl(f);
  #elif SOL_FSIZE > 32
    return atan(f);
  #else
    return atanf(f);
  #endif
}

/// flt_atan2 ///
// Description
//   A wrapper for atan2f/atan2/atan2l which respects
//   the accuracy of Sol's Float type.
// Arguments
//   y: Dimension (Float)
//   x: Dimension (Float)
// Returns
//   Arctangent (Float)

_sol_
Float flt_atan2(Float y, Float x) {
  #if SOL_FSIZE > 64
    return atan2l(y, x);
  #elif SOL_FSIZE > 32
    return atan2(y, x);
  #else
    return atan2f(y, x);
  #endif
}

/// flt_sin ///
// Description
//   A wrapper for sinf/sin/sinl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Angle (Float)
// Returns
//   Sine (Float)

_sol_
Float flt_sin(Float f) {
  #if SOL_FSIZE > 64
    return sinl(f);
  #elif SOL_FSIZE > 32
    return sin(f);
  #else
    return sinf(f);
  #endif
}

/// flt_asin ///
// Description
//   A wrapper for asinf/asin/asinl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Angle (Float)
// Returns
//   Arcsine (Float)

_sol_
Float flt_asin(Float f) {
  #if SOL_FSIZE > 64
    return asinl(f);
  #elif SOL_FSIZE > 32
    return asin(f);
  #else
    return asinf(f);
  #endif
}

/// flt_cos ///
// Description
//   A wrapper for cosf/cos/cosl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Angle
// Returns
//   Cosine (Float)

_sol_
Float flt_cos(Float f) {
  #if SOL_FSIZE > 64
    return cosl(f);
  #elif SOL_FSIZE > 32
    return cos(f);
  #else
    return cosf(f);
  #endif
}

/// flt_acos ///
// Description
//   A wrapper for acosf/acos/acosl which respects
//   the accuracy of Sol's Float type.
// Arguments
//   f: Angle
// Returns
//   Arc-cosine (Float)

_sol_
Float flt_acos(Float f) {
  #if SOL_FSIZE > 64
    return acosl(f);
  #elif SOL_FSIZE > 32
    return acos(f);
  #else
    return acosf(f);
 #endif
}
