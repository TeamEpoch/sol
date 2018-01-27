    /////////////////////////////////////////////////////////////////
   // sol_flt.h ////////////////////////////////////////////////////
  // Description: Adds misc Float functions to Sol. ///////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

#ifndef SOL_FLT_H
#define SOL_FLT_H

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Basic Functions ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// flt_clamp ///
// Description
//   Clamps a Float to a specific lower/upper bounds.
// Arguments
//   f: Scalar (Float)
//   lower: Lower Bound (Float)
//   upper: Upper Bound (Float)
// Returns
//   Clamped Scalar (Float)

sol
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
//   Absolute Value (Float)

sol
Float flt_abs(Float f) {
  #if SOL_F_SIZE > 64
    return fabsl(f);
  #elif SOL_F_SIZE > 32
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

sol
Float flt_pow(Float a, Float b) {
  #if SOL_F_SIZE > 64
    return powl(a, b);
  #elif SOL_F_SIZE > 32
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

sol
Float flt_sqrt(Float f) {
  #if SOL_F_SIZE > 64
    return sqrtl(f);
  #elif SOL_F_SIZE > 32
    return sqrt(f);
  #else
    return sqrtf(f);
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

sol
Float flt_sin(Float f) {
  #if SOL_F_SIZE > 64
    return sinl(f);
  #elif SOL_F_SIZE > 32
    return sin(f);
  #else
    return sinf(f);
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

sol
Float flt_cos(Float f) {
  #if SOL_F_SIZE > 64
    return cosl(f);
  #elif SOL_F_SIZE > 32
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

sol
Float flt_acos(Float f) {
  #if SOL_F_SIZE > 64
    return acosl(f);
  #elif SOL_F_SIZE > 32
    return acos(f);
  #else
    return acosf(f);
  #endif
}

#endif // SOL_FLT_H
