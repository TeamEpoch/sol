# Sol
## Changelog

### 0.2.4

Add `u16x#`, `i16x#`, and `i8x#`.

### 0.2.3

Adds basic math operations for integer vector types.

### 0.2.2

Changes the `arc-` trigonometric functions to be the stdlib definition instead.

This is because the previous design did not work accurately enough for the full range.

`sin`/`cos`/`tan` still use the optimized design instead.

### 0.2.1

- Adds `op=` for `FX#` types. Will be done better later.

### 0.2.0

Base version.
