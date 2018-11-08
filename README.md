# Sol
## A vector library for C and Nim.

## NOTE: This project is currently undergoing a rewrite, available in the devel branch. I wouldn't reccomend using this for anything important at the moment.

Sol is an experimental vector math library written in C99, with a goal of being fast, simple, and portable without compromise.

# Simple Examples
## C
```C
#include <sol/sol.h>
#include <stdio.h>

int main() {
  Vec3 a = vec3_init(0, 1, 2);
  Vec3 b = vec3_init(2, 1, 0);
  a[X] = 1; // This is how scalar access is done in C Sol.
  Vec3 c = vec3_add(a, b);
  vec3_print(c); // {3, 2, 2}
  Float f = c[X];
  printf("%f", f); // 3
}
```
## Nim
```Nim
import sol

var a: Vec3 = vec3_init(0, 1, 2)
var b = vec3_init(2, 1, 0) # You can omit types in Nim; they are inferred.
a.x = 1 # The Nim bindings have UFCS scalar accessors.
var c = a + b # The Nim bindings have operator overloading.
echo $c # The Nim bindings have a "stringify" operator $ for vectors.
var f = c.x
echo f # Nim has a type-generic echo proc.
```

# How Sol Works
Sol takes advantage of the [vector extensions](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html) present in modern C compilers such as GCC and Clang.
This enables the use of [SIMD instructions](https://en.wikipedia.org/wiki/SIMD) in simple C or Nim programs without the use of intrinsics, and also works on platforms which don't support SIMD. ([GCC will complain](https://stackoverflow.com/a/39392154/6411165), but it will work as you would expect; you simply need to use fastcall instead of vectorcall if you're not using Sol directly via C or Nim. This shouldn't be a problem since this is the default calling convention.)

This may seem like an odd design decision because it forsakes the use of the rather pretty `.x`, `.y`, `.z`, etc. scalar accessors that could be provided by using a union with these floats in a structure along with SIMD intrinsic types to provide explicit use of instructions and costless scalar access.
However, all of that is false. GNU vector extensions produce just as fast of code as intrinsics, and [using a union with intrinsics actually make it *slower*](https://t0rakka.silvrback.com/simd-scalar-accessor), suprisingly enough.

Therefore, although somewhat unique, using `[X]`, `[Y]`, `[Z]`, etc. to access vector elements *actually* generates faster vectorized code. (The solution given in the earlier linked article only applies to C++, and the goal is to keep everything in C for easier binding to other languages.) The reason the lowercase `[x]`, `[y]`, `[z]`, etc. aren't used is because those are common variable names.

## Documentation
Documentation is currently WIP. It will be linked here as soon as it is no longer misleading and outdated.

# Installation
## C
Installation is fairly simplistic for C:
```Bash
git clone https://github.com/davidgarland/sol && cd sol
sudo make install
```
Note that you may also do `install_avx2`, `install_avx`, or `install_neon` to generate libraries with SIMD instructions instead of scalar ones.

This will allow you to include Sol as `<sol/sol.h>` and link it via either `-lsol-a` for a static library or `-lsol-so` for a shared library.

It should also be noted that installation is not a necessity to use Sol-- it could be bundled into another project easily using git submodules or subtrees. 
This may be preferable to requiring the user to install it on their machine.
Simply have your Makefile compile `sol/src/*.c` as well and it should work properly.

## Nim
Installation for Nim is done via the Nimble package manager, like so:
```Bash
nimble refresh
nimble install sol
```
This will install Sol to your ~/.nimble file and allow it to be included from anywhere.
Note that the C version of Sol must be installed to make use of the Nim bindings, at present. This may be changed later if possible.

Additionally, you can use a .nimble file in your project to require Sol as a dependency:
```nimble
# .nimble
foreignDep "sol"
```
