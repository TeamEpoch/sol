# Sol
Sol is an experimental vector math library written in C11, with a goal of being fast, simple, and portable without compromise.

Documentation can be found [here](https://davidgarland.gitbooks.io/sol/content/), although it needs a serious rework and doesn't contain up-to-date information yet.

# Examples
```C
// Native C11 Example
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
# Nim Binding Example
import sol/sol

var a: Vec3 = vec3_init(0, 1, 2)
var b = vec3_init(2, 1, 0) # Nim has type inference! No need to note the type.
var c = a + b # An example of the infix operators provided by sol.nim.
var d = vec3_cross(a, b)

# Nim can just print using echo-- no need for vec3_print.
echo c
echo d
```

# Why C?
The use of C over a more modern language as the backend like C++ or Rust may seem odd, but it offers great advantages for Sol's goals.

## Speed
Firstly, C is a very mature language in terms of optimizations; the people making the compilers for it have had over four decades to make it run faster.
This, coupled with the fact that modern C has a wealth of attributes and extensions that are compiler-specific, it is possible to make programs more explicitly optimized; there's less trusting the compiler necessary.
C11 in specific was chosen because it has access to nested anonymous unions and structs, providing an excellent way of doing SIMD operations on vectors without using an OpenMP or awkward dimension-fetching functions.

## Simplicity
Secondly, C is a simple language. C++ has access to all of the things listed above, but more abstraction makes things harder to reason about at a low level--
and all Sol really does is math on structures of varying complexity, so modern features really wouldn't benefit it any.

Rust is also simpler than C++, but it lacks the maturity C has in respect to SIMD, and the lack of simple conditional compilation in Rust makes it less appealing to me.

## Portability
Finally, C is a portable language. Thanks to the powerful -- albeit messy -- preprocessor that C sports, it is possible to detect which SIMD intrinsics are available for the target architecture at compile time and adjust the code accordingly.
Additionally, the use of C means zero overhead bindings can be provided for Nim for those who desperately want high level abstractions but want the speed and portability Sol offers.

# Features

## Types
The following types are supported so far. No hitboxes or raycasting are implemented yet, but are planned for the future. For now it's just the basics.
```
Float: Size-adjustable scalar.

Vec2: 2D Vector
Vec3: 3D Vector
Vec4: 4D Vector

Ray2: 2D Ray
Ray3: 3D Ray

Seg2: 2D Line Segment
Seg3: 3D Line Segment

Mat2: 2x2 Matrix
Mat3: 3x3 Matrix
Mat4: 4x4 Matrix
```
