# Sol
## 0.2.4

Sol exposes fully portable vector operations for C and Nim that use SIMD when
possible, but use scalar operations otherwise.

### Examples

First, a simple example in C:

```C
#include <stdio.h>
#include <sol/sol.h>

int main() {
  f32x2 v = f32x2_set(0, 1);      // Initialize a vector at x = 0, y = 1.
  v = f32x2_rot(v, f32_pi);       // Rotate by pi radians counterclockwise. (180 degrees.)
  printf("%f, %f\n", x(v), y(v)); // Prints 0, -1.
  x(v) = 5;                       // Setting can also be done via the scalar accessor; it is a macro, not a function.
  printf("%f, %f\n", x(v), y(v)); // Prints 5, -1.
  return 0;
}
```

And the same thing in Nim:

```Nim
import sol

var v: float32x2 = f32x2(0, 1) # Here more idiomatic names like "float32x2" are used for types. "f32x2" is analogous to "f32x2_set".
v = v.rot(f32_pi)              # Functions are overloaded instead of having the type name in them, for brevity.
echo v                         # Stringify is overloaded for the vector types; no need to format.
v.x = 5
echo v
```

### Documentation

#### Types

##### Scalars

C Sol exposes the scalar types `f32`, `f64`, `i8`, `i16`, `i32`, `i64`, `u8`,
`u16`, `u32`, and `u64`. The reason for these new names is because ARM NEON
SIMD intrinsics already used the names `float32x2_t` and such, and I didn't want
the name to be similar to those.

In Nim, the existing scalar types are used-- `float32`, `float64`, `int8`,
`int16`, `int32`, `int64`, `uint8`, `uint16`, `uint32`, and `uint64`.

##### Vectors

All of the vector types in C are broken down into the name format `TxW`, where
`T` is the scalar type being vectored and `W` is the width of the vector. For
instance, `f64x3` is a `3`-wide vector of `f64`s. As it stands, 2- 3- and
4-wide vectors exist for each scalar type.

Nim is the same, but with the corresponding scalar names; for example, `f64x3`
is instead `float64x3`.

#### Functions & Constants

##### Scalars

The C scalar function names are of the form `T_f`, where `T` is the scalar type
you are working with and `f` is the name of the function. For example, `f32_cos`
is `cos` for `f32`.

| Name                 | Description                                                                                 |
| -------------------- | ------------------------------------------------------------------------------------------- |
| T_pi                 | The mathematical constant pi.                                                               |
| T_tau                | The same as T_pi * 2.                                                                       |
| T_pi_2               | The same as T_pi / 2.                                                                       |
| T_pi_sq              | The same as T_pi * T_pi.                                                                    |
| T_sq(T f)            | Square `f`. Useful for avoiding common sub-expressions.                                     |
| T_sqrt(T f)          | Find the square root of `f`.                                                                |
| T_abs(T f)           | Find the absolute value of a `f`.                                                           |
| T_abs_neg(T f)       | The same as `-T_abs(f)`, except faster.                                                     |
| T_neg_if(T f, u64 c) | Negate `f` if `c` is true.                                                                  |
| T_mod(T x, T y)      | Find `x` modulo `y`.                                                                        |
| T_sin(T f)           | Find the sine of `f`. Calculated using `T_cos(T_pi_2 - f)`.                                 |
| T_cos(T f)           | Find the cosine of `f`. Calculated [like so](https://www.desmos.com/calculator/ellzidi5cv). |
| T_tan(T f)           | Find the tangent of `f`. Calculated using `T_sin(f) / T_cos(f)`.                            |
| T_asin(T f)          | Find the arcsine of `f`. Calls out to libm.                                                 |
| T_acos(T f)          | Find the arccosine of `f`. Calls out to libm.                                               |
| T_atan(T f)          | Find the arctangent of `f`. Calls out to libm.                                              |
| T_atan2(T x, T y)    | Find the 2-input arctan of `x` and `y`. Calls out to libm.                                  |

##### Vectors

TODO
