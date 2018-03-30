    /////////////////////////////////////////////////////////////////
   // sol_mat2.c ///////////////////////////////////////////////////
  // Description: Adds 2D matrix functionality to Sol. ////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Mat2 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat2_init ///
// Description
//   Initializes a 2x2 matrix in left-to-right,
//   top-to-bottom order.
// Arguments
//   f11, f12: Scalar (Float)
//   f21, f22: Scalar (Float)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_init(Float f11, Float f12,
               Float f21, Float f22) {
  return mat2_initv(vec2_init(f11, f12),
                    vec2_init(f21, f22));
}

/// mat2_initv ///
// Description
//   Initializes a 2x2 matrix using two vectors
//   in top-to-bottom order.
// Arguments
//   v1: Vector (Vec2)
//   v2: Vector (Vec2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_initv(Vec2 v1, Vec2 v2) {
  Mat2 out;
  out.v[0] = v1;
  out.v[1] = v2;
  return out;
}

/// mat2_initf ///
// Description
//   Initializes a 2x2 matrix using a single
//   scalar for all values.
// Arguments
//   f: Scalar (Float)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_initf(Float f) {
  return mat2_init(f, f,
                   f, f);
}

/// mat2_iden ///
// Description
//   Returns the identity 2x2 matrix.
// Arguments
//   void
// Returns
//   Identity Matrix (Mat2)

_sol_
Mat2 mat2_iden(void) {
  return mat2_init((Float) 1, (Float) 0,
                   (Float) 0, (Float) 1);
}

/// mat2_zero ///
// Description
//   Initializes a 2x2 matrix using zeroes
//   for all values.
// Arguments
//   void
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_zero(void) {
  return mat2_initf((Float) 0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat2 Core Operations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat2_row ///
// Description
//   Returns the specified row of
//   the 2x2 matrix.
// Arguments
//   m: Matrix (Mat2)
//   row: Row Number (size_t)
// Returns
//   Vector (Vec2)

_sol_
Vec2 mat2_row(Mat2 m, size_t row) {
  return m.v[row];
}

/// mat2_col ///
// Description
//   Returns the specified column of
//   the 2x2 matrix.
// Arguments
//   m: Matrix (Mat2)
//   col: Column Number (size_t)
// Returns
//   Vector (Vec2)

_sol_
Vec2 mat2_col(Mat2 m, size_t col) {
  return vec2_init(m.f[0][col], 
                   m.f[1][col]);
}

/// mat2_f ///
// Description
//   Returns the scalar at the given
//   co-ordinates in the 2x2 matrix.
// Arguments
//   m: Matrix (Mat2)
//   row: Row Number (size_t)
//   col: Column Number (size_t)
// Returns
//   Scalar (Float)

_sol_
Float mat2_f(Mat2 m, size_t row, size_t col) {
  return m.f[row][col];
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat2 Advanced Functions ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat2_dot ///
// Description
//   Properly multiplies two matrices
//   using dot products.
// Arguments
//   a: Matrix (Mat2)
//   b: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_dot(Mat2 a, Mat2 b) {
  const Vec2 a0 = mat2_row(a, 0);
  const Vec2 a1 = mat2_row(a, 1);
  const Vec2 b0 = mat2_col(b, 0);
  const Vec2 b1 = mat2_col(b, 1);
  return mat2_init(vec2_dot(a0, b0), 
                   vec2_dot(a0, b1),
                   vec2_dot(a1, b0), 
                   vec2_dot(a1, b1));
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat2 Basic Functions //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat2_fma ///
// Description
//   Performs fused multiply add on two
//   matrices.
// Arguments
//   a: Matrix (Mat2)
//   b: Matrix (Mat2)
//   c: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_fma(Mat2 a, Mat2 b, Mat2 c) {
  return mat2_initv(vec2_fma(a.v[0], b.v[0], c.v[0]),
                    vec2_fma(a.v[1], b.v[1], c.v[1]));
}

/// mat2_add ///
// Description
//   Adds two matrices element-wise.
// Arguments
//   a: Matrix (Mat2)
//   b: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_add(Mat2 a, Mat2 b) {
  #if defined(__clang__)
    return mat2_initv(a.v[0] + b.v[0],
                      a.v[1] + b.v[1]);
  #else
    Mat2 out;
    out.v4 = a.v4 + b.v4;
    return out;
  #endif
}

/// mat2_addf ///
// Description
//   Adds a scalar to each element of
//   a matrix.
// Arguments
//   m: Matrix (Mat2)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_addf(Mat2 m, Float f) {
  return mat2_add(m, mat2_initf(f));
}

/// mat2_sub ///
// Description
//   Subtracts one matrix element-wise
//   from another.
// Arguments
//   a: Matrix (Mat2)
//   b: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_sub(Mat2 a, Mat2 b) {
  return mat2_initv(vec2_sub(a.v[0], b.v[0]),
                    vec2_sub(a.v[1], b.v[1]));
}

/// mat2_subf ///
// Description
//   Subtracts a scalar from each element
//   of a matrix.
// Arguments
//   m: Matrix (Mat2)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_subf(Mat2 m, Float f) {
  return mat2_sub(m, mat2_initf(f));
}

/// mat2_fsub ///
// Description
//   Subtracts each element of a matrix from
//   a scalar.
// Arguments
//   f: Scalar (Float)
//   m: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_fsub(Float f, Mat2 m) {
  return mat2_sub(mat2_initf(f), m);
}

/// mat2_mul ///
// Description
//   Multiplies two matrices element-wise
// Arguments
//   a: Matrix (Mat2)
//   b: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_mul(Mat2 a, Mat2 b) {
  return mat2_initv(vec2_mul(a.v[0], b.v[0]),
                    vec2_mul(a.v[1], b.v[1]));
}

/// mat2_mulf ///
// Description
//   Multiplies two matrices element-wise.
// Arguments
//   m: Matrix (Mat2)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_mulf(Mat2 m, Float f) {
  return mat2_mul(m, mat2_initf(f));
}

/// mat2_div ///
// Description
//   Divides each element of one matrix
//   by another.
// Arguments
//   a: Matrix (Mat2)
//   b: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_div(Mat2 a, Mat2 b) {
  return mat2_initv(vec2_mul(a.v[0], b.v[0]),
                    vec2_mul(a.v[1], b.v[1]));
}

/// mat2_divf ///
// Description
//   Divides each element of a matrix
//   by a scalar.
// Arguments
//   m: Matrix (Mat2)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_divf(Mat2 m, Float f) {
  return mat2_div(m, mat2_initf(f));
}

/// mat2_fdiv ///
// Description
//   Divides a scalar by each element
//   of a matrix.
// Arguments
//   f: Scalar (Float)
//   m: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_fdiv(Float f, Mat2 m) {
  return mat2_div(mat2_initf(f), m);
}

/// mat2_avg ///
// Description
//   Averages two matrices element-wise.
// Arguments
//   a: Matrix (Mat2)
//   b: Matrix (Mat2)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_avg(Mat2 a, Mat2 b) {
  return mat2_initv(vec2_avg(a.v[0], b.v[0]),
                    vec2_avg(a.v[1], b.v[1]));
}

/// mat2_avgf ///
// Description
//   Averages each element of a matrix
//   with a scalar.
// Arguments
//   m: Matrix (Mat2)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat2)

_sol_
Mat2 mat2_avgf(Mat2 m, Float f) {
  return mat2_avg(m, mat2_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat2 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat2_print ///
// Description
//   Show a matrix's elements in stdout.
// Arguments
//   m: Matrix (Mat2)
// Returns
//   void

_sol_
void mat2_print(Mat2 m) {
  vec2_print(m.v[0]);
  vec2_print(m.v[1]);
}

