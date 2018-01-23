# Sol
## A vector library written in pure C.
Sol is a fast, maintainable, and portable vector library written in C.

Nim bindings are provided "out of the box" for those who prefer higher level languages. Additionally, the Nim bindings come with basic infix operators such as `+` defined for all of the types. (Have a look at the Examples section.)

To learn how to use it, [click here.](https://davidgarland.gitbooks.io/sol/content/)

## Examples
Here are some examples of Sol, using the repo bundled into the current directory.
```C
// C11 Example
#include "sol/sol.h"

int main() {
  Vec3 a = vec3_init(0, 1, 2);
  Vec3 b = vec3_init(2, 1, 0);
  
  Vec3 c = vec3_add(a, b);
  Vec3 d = vec3_cross(a, b);
  
  vec3_print(c);
  vec3_print(d);
  
  return 0;
}
```
```Nim
# Nim Example
import sol/sol

var a = vec3_init(0, 1, 2)
var b = vec3_init(2, 1, 0)

var c = a + b
var d = vec3_cross(a, b)

vec3_print(c)
vec3_print(d)
```

## Goals
### Speed
Sol achieves its speed by taking advantage of the SIMD intrinsics provided by modern compilers. This allows parallelized vector addition but without any of the nuances of multithreading; this improves speed substantially in cases where the compiler wouldn't have automatically vectorized.

Additionally, the use of the C programming language makes the cost of each operation very transparent, unlike most modern languages which revolve around data hiding and more human-friendly abstractions.

### Portability
Although Sol uses intrinsics, feature test macros are used to make sure they're compatible with the target platform. Thanks to this, Sol should be able to run on any C11-compliant compiler, even if they don't have access to SIMD intrinsics; they will just be automatically disabled.

### Maintainability
All functions in Sol are documented thoroughly to make contributing as a newcomer much easier. Organizational comment "headers" are also scattered around the files to make finding sections easier. (Have a look at the Inner-Workings section.)

## Inner-Workings
### How is the code documented?
There is a good amount of documentation before each function, regardless of simplicity. It's not for a docgen, but it's regimented nonetheless.
```C
/// vec2_add ///
// Description
//   Adds the elements of two vectors.
// Arguments
//   a: Vector (Vec2)
//   b: Vector (Vec2)
// Returns
//   Vector (Vec2) = {a.xy + b.xy}

sol
Vec2 vec2_add(Vec2 a, Vec2 b) {
  // etc.
}
```
### How do you detect if the SIMD intrinsic will work?
Using predefined compiler preprocessor macros such as `__AVX__`.
```C
#ifdef SOL_SIMD
      #if defined(__AVX__)
            // AVX intrinsic stuff.
      #elif defined(__ARM_NEON__)
            // NEON intrinsic stuff.
      #endif
#endif
```
### How does each vector have .x, .y, etc. and still use SIMD intrinsics?
Each structure is defined with internal anonymous unions and structs; this is a feature only existing in standard C11 or in GNU C99.

Eventually a preprocessor macro allowing standard C99 to run Sol may be added, but SIMD would be unavailable to it as a result of not having this feature.
```C
typedef struct {
  union { 
    struct {
      Float x, y, z;
    };
    Float f[3];
    #if defined(SOL_AVX_64)
          __m256d avx64;
    #elif defined(SOL_AVX)
          __m128 avx32;
    #elif defined(SOL_NEON_64)
          f64x4_t neon64;
    #elif defined(SOL_NEON)
          f32x4_t neon32;
    #endif
  };
} Vec3;
```
