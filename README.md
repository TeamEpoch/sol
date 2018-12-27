# Sol
## 0.2.0

Sol *(not to be confused with [sol](https://github.com/ThePhD/sol2) or [sol](https://github.com/Rapptz/sol)
or [sol](https://github.com/solus-project/sol))* is a fast and portable vector library written in C with first-class Nim bindings.

More details will be put here eventually, and documentation will be put out sometime™.

### Examples

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