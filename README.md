# Sol: Rewritten
## A fast, portable vector library for C and Nim.

Sol is a vector library for C aiming to make performant, simple, and portable
SIMD-accelerated code esier to write.

## Comparison

```C
// Old

#define SOL_FSIZE 32
#include <sol.h>

int main() {
  Vec3 a = vec3_init(0, 1, 2);
  Vec3 b = vec3_init(2, 1, 0);
  Vec3 c = vec3_add(a, b);
  printf("%f, %f, %f\n", c[X], c[Y], c[Z]);
  return 0;
}
```

```C
// New

#include <sol.h>

int main() {
  f32x3 a = f32x3_set(0, 1, 2);
  f32x3 b = f32x3_set(2, 1, 0);
  f32x3 c = f32x3_add(a, b);
  printf("%f, %f, %f\n", x(c), y(c), z(c));
  return 0;
}
```

```Nim
# Old Nim

import sol

let a = vec3_init(0, 1, 2)
let b = vec3_init(2, 1, 0)
let c = a + b
echo c
```

```Nim
# New Nim

import sol

let a = f32x3(0, 1, 2)
let b = f32x3(2, 1, 0)
let c = a + b
echo c
```

## Better Types

Types have been changed to more concrete variants that explicitly specify the
size, allowing you to now use 32-bit and 64-bit types interchangably instead of
having to choose only one at compile time via the old `SOL_FSIZE` flag.

Additionally, integer scalar and vector types are now supported for operations
such as masking and more flexible shuffles.

| Scalar | Vec2  | Vec3  | Vec4  |
| ------ | ----- | ----- | ----- |
| f32    | f32x2 | f32x3 | f32x4 |
| f64    | f64x2 | f64x3 | f64x4 |
| i32    | i32x2 | i32x3 | i32x4 |
| i64    | i64x2 | i64x3 | i64x4 |
| u32    | u32x2 | u32x3 | u32x4 |
| u64    | u64x2 | u64x3 | u64x4 |

Note that in Nim the types are instead of the form `float32x3` and such to be
more in-line with the language. The names `f32x3` etc. are used instead as
initializers.

## Portability

Sol no longer relies upon GNU C, removing some syntactic sugar but allowing for
less common compilers like tcc and pcc to be used effectively with Sol.

## Macro Overloading

Sol now uses macro-based overloading internally to make development simpler; for
example `fx2.h` contains a macro which defines both the `f32x2` and `f64x2`
types in one fell swoop. This will hopefully reduce the number of bugs and allow
faster development.

## Less Rigid Commentation

This may sound like a downgrade, but less picky commentation will allow Sol to
be worked on with more frequency as less work has to be done to explain simple
functions. Instead, docs will be done separately, making Sol easier to learn for
people who just want to see how it works on the surface.
