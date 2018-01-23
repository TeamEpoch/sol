    /////////////////////////////////////////////////////////////////
   // sol_mat3.h ///////////////////////////////////////////////////
  // Description: Adds 3D matrix functionality to Sol. ////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

#ifndef SOL_MAT3_H
#define SOL_MAT3_H

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Mat3 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat3_init ///
// Description
//   Initializes a 3x3 matrix in left-to-right,
//   top-to-bottom order.
// Arguments
//   f11, f12, f13: Scalar (Float)
//   f21, f22, f23: Scalar (Float)
//   f31, f32, f33: Scalar (Float)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_init(Float f11, Float f12, Float f13,
               Float f21, Float f22, Float f23,
               Float f31, Float f32, Float f33) {
  return mat3_initv(vec3_init(f11, f12, f13),
                    vec3_init(f21, f22, f23),
                    vec3_init(f31, f32, f33));
}

/// mat3_initv ///
// Description
//   Initializes a 3x3 matrix using three
//   vectors in top-to-bottom order.
// Arguments
//   v1: Vector (Vec3)
//   v2: Vector (Vec3)
//   v3: Vector (Vec3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_initv(Vec3 v1, Vec3 v2, Vec3 v3) {
  Mat3 out;
  out.v[0] = v1;
  out.v[1] = v2;
  out.v[2] = v3;
  return out;
}

/// mat3_initf ///
// Description
//   Initializes a 3x3 matrix using a single
//   Float for all values.
// Arguments
//   f: Scalar (Float)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_initf(Float f) {
  return mat3_init(f, f, f,
                   f, f, f,
                   f, f, f);
}

/// mat3_zero ///
// Description
//   Initializes a 3x3 matrix using zeroes
//   for all values.
// Arguments
//   void
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_zero(void) {
  return mat3_initf(0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat3 Basic Math ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat3_add ///
// Description
//   Adds two 3x3 matrices together
//   element-wise.
// Argments
//   a: Matrix (Mat3)
//   b: Matrix (Mat3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_add(Mat3 a, Mat3 b) {
  return mat3_initv(vec3_add(a.v[0], b.v[0]),
                    vec3_add(a.v[1], b.v[1]),
                    vec3_add(a.v[2], b.v[2]));
}

/// mat3_addf ///
// Description
//   Adds a scalar to each element
//   of a matrix.
// Arguments
//   m: Matrix (Mat3)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_addf(Mat3 m, Float f) {
  return mat3_add(m, mat3_initf(f));
}

/// mat3_sub ///
// Description
//   Subtracts each element of one matrix
//   from another
// Arguments
//   a: Matrix (Mat3)
//   b: Matrix (Mat3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_sub(Mat3 a, Mat3 b) {
  return mat3_initv(vec3_sub(a.v[0], b.v[0]),
                    vec3_sub(a.v[1], b.v[1]),
                    vec3_sub(a.v[2], b.v[2]));
}

/// mat3_subf ///
// Description
//   Subtracts a scalar from each element
//   of a matrix.
// Arguments
//   m: Matrix (Mat3)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_subf(Mat3 m, Float f) {
  return mat3_sub(m, mat3_initf(f));
}

/// mat3_fsub ///
// Description
//   Subtracts each element of a matrix
//   from a scalar.
// Arguments
//   f: Scalar (Float)
//   m: Matrix (Mat3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_fsub(Float f, Mat3 m) {
  return mat3_sub(mat3_initf(f), m);
}

/// mat3_mul ///
// Description
//   Multiplies two matrices element-wise.
// Arguments
//   a: Matrix (Mat3)
//   b: Matrix (Mat3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_mul(Mat3 a, Mat3 b) {
  return mat3_initv(vec3_mul(a.v[0], b.v[0]),
                    vec3_mul(a.v[1], b.v[1]),
                    vec3_mul(a.v[2], b.v[2]));
}

/// mat3_mulf ///
// Description
//   Multiplies each element of a matrix by
//   a scalar.
// Arguments
//   m: Matrix (Mat3)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_mulf(Mat3 m, Float f) {
  return mat3_mul(m, mat3_initf(f));
}

/// mat3_div ///
// Description
//   Divides each element of one matrix
//   by another.
// Arguments
//   a: Matrix (Mat3)
//   b: Matrix (Mat3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_div(Mat3 a, Mat3 b) {
  return mat3_initv(vec3_div(a.v[0], b.v[0]),
                    vec3_div(a.v[1], b.v[1]),
                    vec3_div(a.v[2], b.v[2]));
}

/// mat3_divf ///
// Description
//   Divides each element of a matrix
//   by a scalar.
// Arguments
//   m: Matrix (Mat3)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_divf(Mat3 m, Float f) {
  return mat3_div(m, mat3_initf(f));
}

/// mat3_fdiv ///
// Description
//   Divides each element of a matrix by
//   a scalar.
// Arguments
//   f: Scalar (Float)
//   m: Matrix (Mat3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_fdiv(Float f, Mat3 m) {
  return mat3_div(mat3_initf(f), m);
}

/// mat3_avg ///
// Description
//   Averages two matrices element-wise
// Arguments
//   a: Matrix (Mat3)
//   b: Matrix (Mat3)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_avg(Mat3 a, Mat3 b) {
  return mat3_initv(vec3_avg(a.v[0], b.v[0]),
                    vec3_avg(a.v[1], b.v[1]),
                    vec3_avg(a.v[2], b.v[2]));
}

/// mat3_avgf ///
// Description
//   Averages each element of a matrix
//   with a scalar
// Arguments
//   m: Matrix (Mat3)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat3)

sol
Mat3 mat3_avgf(Mat3 m, Float f) {
  return mat3_avg(m, mat3_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat3 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat3_print ///
// Description
//   Show a matrix's elements in stdout.
// Arguments
//   m: Matrix (Mat3)
// Returns
//   void

sol
void mat3_print(Mat3 m) {
  vec3_print(m.v[0]);
  vec3_print(m.v[1]);
  vec3_print(m.v[2]);
}

#endif // SOL_MAT3_H
