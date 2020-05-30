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
| T T_pi                 | The mathematical constant pi.                                                               |
| T T_tau                | The same as T_pi * 2.                                                                       |
| T T_pi_2               | The same as T_pi / 2.                                                                       |
| T T_pi_sq              | The same as T_pi * T_pi.                                                                    |
| T T_sq(T f)            | Square `f`. Useful for avoiding common sub-expressions.                                     |
| T T_sqrt(T f)          | Find the square root of `f`.                                                                |
| T T_abs(T f)           | Find the absolute value of a `f`.                                                           |
| T T_abs_neg(T f)       | The same as `-T_abs(f)`, except faster.                                                     |
| T T_neg_if(T f, u64 c) | Negate `f` if `c` is true.                                                                  |
| T T_mod(T x, T y)      | Find `x` modulo `y`.                                                                        |
| T T_sin(T f)           | Find the sine of `f`. Calculated using `T_cos(T_pi_2 - f)`.                                 |
| T T_cos(T f)           | Find the cosine of `f`. Calculated [like so](https://www.desmos.com/calculator/ellzidi5cv). |
| T T_tan(T f)           | Find the tangent of `f`. Calculated using `T_sin(f) / T_cos(f)`.                            |
| T T_asin(T f)          | Find the arcsine of `f`. Calls out to libm.                                                 |
| T T_acos(T f)          | Find the arccosine of `f`. Calls out to libm.                                               |
| T T_atan(T f)          | Find the arctangent of `f`. Calls out to libm.                                              |
| T T_atan2(T x, T y)    | Find the 2-input arctan of `x` and `y`. Calls out to libm.                                  |

The scalar constants and functions in Nim retain the same prefixes, `f32` and
the like. I *would* overload them, but the names already exist with the same
type signature in Nim's math library, so it seems like more headache to try to
be clean with naming here.

##### Vectors

| Name                      | Description                                            |
| ------------------------- | ------------------------------------------------------ |
| TxW TxW_set(...)          | Takes `W` arguments of type `T` to construct a vector. |
| TxW TxW_setf(T f)         | Fill all `W` lanes with `f` to construct a vector.     |
| TxW TxW_add(TxW a, TxW b) | Does a lane-wise addition of `a` and `b`.              |
| TxW TxW_addf(TxW v, T f)  | Shorthand for `TxW_add(v, TxW_setf(f)`.                |
| TxW TxW_sub(TxW a, TxW b) | Subtract each lane of `b` from the same lane of `a`.   |
| TxW TxW_subf(TxW v, T f)  | Shorthand for `TxW_sub(v, TxW_setf(f))`.               |
| TxW TxW_fsub(T f, TxW v)  | Shorthand for `TxW_sub(TxW_setf(f), v)`.               |
| TxW TxW_mul(TxW a, TxW b) | Does a lane-wise multiplication of `a` and `b`.        |
| TxW TxW_mulf(TxW v, T f)  | Shorthand for `TxW_mul(v, TxW_setf(f))`.               |
| TxW TxW_div(TxW a, TxW b) | Divide each lane in `a` by the same lane of `b`.       |
| TxW TxW_divf(TxW v, T f)  | Shorthand for `TxW_div(v, TxW_setf(f))`.               |
| TxW TxW_fdiv(T f, TxW v)  | Shorthand for `TxW_div(TxW_setf(f), v)`.               |
| T TxW_sum(TxW v)          | Find the sum of all lanes in `v`.                      |
| TxW TxW_sq(TxW v)         | Square each lane in `v`.                               |

The nim names are a bit different:

- `TxW_set` is now written just `TxW`, where `T` is named as if it were in C. `f32x2_set` becomes `f32x2`, for instance.
- `TxW_setf` is not available in Nim.
- `TxW_add`, `TxW_addf`, `TxW_sub`, `TxW_subf`, `TxW_fsub`, `TxW_mul`, `TxW_mulf`, `TxW_div`, `TxW_divf`, and `TxW_fdiv` are all just their symbolic operators now. `f32x2_add(a, b)` becomes `a + b`, for instance. As operators, `mulf` and `addf` may also be called "backwards" now, like `2 * v`.
- `TxW_sum` and `TxW_sq` drop their prefix and are simply overloaded. For instance, `f32x2_sum(f32x2_set(1, 0))` is instead `sum(f32x2(1, 0))` or `f32x2(1, 0).sum`.
- Simple `op=` operators are supported, so you may do `+=` and the like.
- All vectors have `$` defined, so they may be converted to a string.
- Vector lane set is now written `v.x = 5` rather `x(v) = 5`.
- Thanks to Nim UFCS, vector lane get can be written `v.x` now rather than `x(v)`-- but you can do either.

##### Floating 2D Vectors

`T` here is either `f32` or `f64`.

| Name                       | Description
| -------------------------- | ---------------------------------------------------------------------------- |
| Tx2 Tx2_rot(Tx2 v, T rad)  | Rotate `v` by `rad` radians.                                                 |
| Tx2 Tx2_scale(Tx2 v, T f)  | Shorthand for `Tx2_mulf(Tx2_norm(v), f)`.                                    |
| Tx2 Tx2_norm(Tx2 v)        | Normalize `v` so that its magnitude is 1.                                    |
| T Tx2_mag(Tx2 v)           | Find the magnitude of `v`.                                                   |
| Tx2 Tx2_proj(Tx2 a, Tx2 b) | Find the projection of `a` onto `b`.                                         |
| Tx2 Tx2_rej(Tx2 a, Tx2 b)  | Find the rejection of `a` from `b`.                                          |
| T Tx2_angle(Tx2 a, Tx2 b)  | Find the angle between `a` and `b` in radians.                               |
| T Tx2_cross(Tx2 a, Tx2 b)  | Find the "scalar cross product" of `a` and `b`. `x(a) * y(b) - x(b) * y(a)`. |
| T Tx2_dot(Tx2 a, Tx2 b)    | Find the dot product of `a` and `b`.                                         |

In Nim, the prefixes for all of these functions are dropped and they are simply overloaded.

##### Floating 3D Vectors

| Name                        | Description
| -------------------------   | -------------
| Tx3 Tx3_rot(Tx3 v, Tx4 q)   | Rotate `v` by the quaternion `q`.
| Tx3 Tx3_scale(Tx3 v, T f)   | Shorthand for `Tx3_mulf(Tx3_norm(v), f)`.
| Tx3 Tx3_norm(Tx3 v)         | Normalize `v` so that its magnitude is 1.
| T Tx3_mag(Tx3 v)            | Find the magnitude of `v`.
| Tx3 Tx3_proj(Tx3 a, Tx3 b)  | Find the projection of `a` onto `b`.
| Tx3 Tx3_rej(Tx3 a, Tx3 b)   | Find the rejection of `a` from `b`.
| T Tx3_angle(Tx3 a, Tx3 b)   | Find the angle between `a` and `b`.
| Tx3 Tx3_cross(Tx3 a, Tx3 b) | Find the cross product of `a` and `b`.
| T Tx3_dot(Tx3 a, Tx3 b)     | Find the dot product of `a` and `b`.

In Nim, the prefixes for all of these functions are dropped and they are simply overloaded.

##### Floating 4D Vectors

| Name                 | Description                               |
| -------------------- | ----------------------------------------- |
| Tx4 Tx4_scale(Tx4 v) | Shorthand for `Tx4_mulf(Tx4_norm(v), f)`. |
| Tx4 Tx4_norm(Tx4 v)  | Normalize `v` so that its magnitude is 1. |
| T Tx4_mag(Tx4 v)     | Find the magnitude of `v`.                |

In Nim, the prefixes for all of these functions are dropped and they are simply overloaded.
