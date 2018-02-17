    //////////////////////////////////////s///////////////////////////
   // sol_mat4.c ///////////////////////////////////////////////////
  // Description: Adds 4D matrix functionality to Sol. ////////////
 // Author: David Garland (https://github.com/davidgarland/sol) //
/////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
 // Local Headers /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "../sol.h"

  //////////////////////////////////////////////////////////////////////////////
 // Mat4 Initialization ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat4_init ///
// Description
//   Initializes a 4x4 matrix in left-to-right,
//   top-to-bottom order.
// Arguments
//   f11, f12, f13, f14: Scalar (Float)
//   f21, f22, f23, f24: Scalar (Float)
//   f31, f32, f33, f34: Scalar (Float)
//   f41, f42, f43, f44: Scalar (Float)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_init(Float f11, Float f12, Float f13, Float f14,
               Float f21, Float f22, Float f23, Float f24,
               Float f31, Float f32, Float f33, Float f34,
               Float f41, Float f42, Float f43, Float f44) {
  return mat4_initv(vec4_init(f11, f12, f13, f14),
                    vec4_init(f21, f22, f23, f24),
                    vec4_init(f31, f32, f33, f34),
                    vec4_init(f41, f42, f43, f44));
}

/// mat4_initv ///
// Description
//   Initializes a 4x4 matrix using four vectors
//   in top-to-bottom order.
// Arguments
//   v1: Vector (Vec4)
//   v2: Vector (Vec4)
//   v3: Vector (Vec4)
//   v4: Vector (Vec4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_initv(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4) {
  Mat4 out;
  out.v[0] = v1;
  out.v[1] = v2;
  out.v[2] = v3;
  out.v[3] = v4;
  return out;
}

/// mat4_initf ///
// Description
//   Initializes a 4x4 matrix using a single
//   scalar for all values
// Arguments
//   f: Scalar (Float)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_initf(Float f) {
  return mat4_init(f, f, f, f,
                   f, f, f, f,
                   f, f, f, f,
                   f, f, f, f);
}

/// mat4_zero ///
// Description
//   Initializes a 4x4 matrix using zero
//   for all values.
// Arguments
//   void
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_zero(void) {
  return mat4_initf(0);
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat4 Basic Functions //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat4_add ///
// Description
//   Adds two matrices element-wise.
// Arguments
//   a: Matrix (Mat4)
//   b: Matrix (Mat4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_add(Mat4 a, Mat4 b) {
  return mat4_initv(vec4_add(a.v[0], b.v[0]),
                    vec4_add(a.v[1], b.v[1]),
                    vec4_add(a.v[2], b.v[2]),
                    vec4_add(a.v[3], b.v[3]));
}

/// mat4_addf ///
// Description
//   Adds a scalar to each element of
//   a matrix.
// Arguments
//   m: Matrix (Mat4)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_addf(Mat4 m, Float f) {
  return mat4_add(m, mat4_initf(f));
}

/// mat4_sub ///
// Description
//   Subtracts each element of one matrix
//   from another.
// Arguments
//   a: Matrix (Mat4)
//   b: Matrix (Mat4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_sub(Mat4 a, Mat4 b) {
  return mat4_initv(vec4_sub(a.v[0], b.v[0]),
                    vec4_sub(a.v[1], b.v[1]),
                    vec4_sub(a.v[2], b.v[2]),
                    vec4_sub(a.v[3], b.v[3]));
}

/// mat4_subf ///
// Description
//   Subtracts a scalar from each element
//   of a matrix.
// Arguments
//   m: Matrix (Mat4)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_subf(Mat4 m, Float f) {
  return mat4_sub(m, mat4_initf(f));
}

/// mat4_fsub ///
// Description
//   Subtracts each element of a matrix
//   from a scalar.
// Arguments
//   f: Scalar (Float)
//   m: Matrix (Mat4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_fsub(Float f, Mat4 m) {
  return mat4_sub(mat4_initf(f), m);
}

/// mat4_mul ///
// Description
//   Multiplies two matrices element-wise.
// Arguments
//   a: Matrix (Mat4)
//   b: Matrix (Mat4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_mul(Mat4 a, Mat4 b) {
  return mat4_initv(vec4_mul(a.v[0], b.v[0]),
                    vec4_mul(a.v[1], b.v[1]),
                    vec4_mul(a.v[2], b.v[2]),
                    vec4_mul(a.v[3], b.v[3]));
}

/// mat4_mulf ///
// Description
//   Multiplies each element of a matrix
//   by a scalar
// Arguments
//   m: Matrix (Mat4)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_mulf(Mat4 m, Float f) {
  return mat4_mul(m, mat4_initf(f));
}

/// mat4_div ///
// Description
//   Divides each element of one matrix
//   by another.
// Arguments
//   a: Matrix (Mat4)
//   b: Matrix (Mat4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_div(Mat4 a, Mat4 b) {
  return mat4_initv(vec4_div(a.v[0], b.v[0]),
                    vec4_div(a.v[1], b.v[1]),
                    vec4_div(a.v[2], b.v[2]),
                    vec4_div(a.v[3], b.v[3]));
}

/// mat4_divf ///
// Description
//   Divides each element of a matrix
//   by a scalar
// Arguments
//   m: Matrix (Mat4)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_divf(Mat4 m, Float f) {
  return mat4_div(m, mat4_initf(f));
}

/// mat4_fdiv ///
// Description
//   Divides a scalar by each element
//   of a matrix.
// Arguments
//   f: Scalar (Float)
//   m: Matrix (Mat4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_fdiv(Float f, Mat4 m) {
  return mat4_div(mat4_initf(f), m);
}

/// mat4_avg ///
// Description
//   Averages two matrices element-wise.
// Arguments
//   a: Matrix (Mat4)
//   b: Matrix (Mat4)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_avg(Mat4 a, Mat4 b) {
  return mat4_initv(vec4_avg(a.v[0], b.v[0]),
                    vec4_avg(a.v[1], b.v[1]),
                    vec4_avg(a.v[2], b.v[2]),
                    vec4_avg(a.v[3], b.v[3]));
}

/// mat4_avgf ///
// Description
//   Averages each element of a matrix
//   with a scalar.
// Arguments
//   m: Matrix (Mat4)
//   f: Scalar (Float)
// Returns
//   Matrix (Mat4)

sol
Mat4 mat4_avgf(Mat4 m, Float f) {
  return mat4_avg(m, mat4_initf(f));
}

  //////////////////////////////////////////////////////////////////////////////
 // Mat4 Terminal IO //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/// mat4_print ///
// Description
//   Show a matrix's elements in stdout.
// Arguments
//   m: Matrix (Mat4)
// Returns
//   void

sol
void mat4_print(Mat4 m) {
  vec4_print(m.v[0]);
  vec4_print(m.v[1]);
  vec4_print(m.v[2]);
  vec4_print(m.v[3]);
}

