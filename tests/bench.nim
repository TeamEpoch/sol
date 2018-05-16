#################
# Sol Benchmark #
#################

import strutils
import terminal
import times
import os

import ../src/sol

############
# Settings #
############

const solRuns = 1_000_000 # How many runs to average.
const solPrecision = 10 # Benchmark float accuracy.
const solSpaces = 15

#############
# Templates #
#############

var start: float64 = 0
var benches: array[solRuns + 1, float64]
var average: float64 = 0

proc bfmt(flt: float64): string =
  var str = flt.formatFloat(format = ffDecimal, precision = solPrecision)
  return spaces(max(0, solSpaces - str.len - 3)) & str

proc headerEcho(s: string) =
  styledEcho(fgYellow, "[sol] ", resetStyle, s)

proc fieldEcho(a, b: string) =
  styledEcho(fgYellow, styleDim, a, resetStyle, b)

template bench(name: string; code: untyped) =
  for i in 0..solRuns:
    start = cpuTime()
    code
    benches[i] = cpuTime() - start
  average = 0
  for i  in 0..solRuns:
    average += benches[i]
  average /= solRuns.float64
  echo ""
  headerEcho("Benchmark for: " & name)
  fieldEcho("-> Seconds:         ", average.bfmt)
  fieldEcho("-> Runs Per Second: ", (1 / average).bfmt)

###################
# Main Benchmarks #
###################

echo ""
headerEcho("Starting benchmark @" & $solRuns & " runs per test.")
echo ""
headerEcho("Initializing test values...")
var b: bool = false

var fa {.volatile.}: Float = 16.0
var fb {.volatile.}: Float = 8.0
var fc {.volatile.}: Float = 0.0

var v2a {.volatile.}: Vec2 = vec2_initf(16)
var v2b {.volatile.}: Vec2 = vec2_initf(8)
var v2c {.volatile.}: Vec2 = vec2_zero()
var deg {.volatile.}: Float = 90

var v3a {.volatile.}: Vec3 = vec3_initf(16)
var v3b {.volatile.}: Vec3 = vec3_initf(8)
var v3c {.volatile.}: Vec3 = vec3_zero()
var axis {.volatile.}: Vec4 = vec4_init(0, 1, 0, 90)
var quat {.volatile.}: Vec4 = cv_axis_quat(axis)

var v4a {.volatile.}: Vec4 = vec4_initf(16)
var v4b {.volatile.}: Vec4 = vec4_initf(8)
var v4c {.volatile.}: Vec4 = vec4_zero()

var m2a: Mat2 = mat2_initf(16)
var m2b: Mat2 = mat2_initf(8)
var m2c: Mat2 = mat2_zero()

var m3a: Mat3 = mat3_initf(16)
var m3b: Mat3 = mat3_initf(8)
var m3c: Mat3 = mat3_zero()

var m4a: Mat4 = mat4_initf(16)
var m4b: Mat4 = mat4_initf(8)
var m4c: Mat4 = mat4_zero()

echo ""
headerEcho "Blank Benchmark"

bench "Blank":
  discard

echo ""
headerEcho "Float Benchmarks"

bench "+":
  fc = fa + fb

bench "-":
  fc = fa - fb

bench "*":
  fc = fa * fb

bench "/":
  fc = fa / fb

bench "flt_pow":
  fc = flt_pow(fa, fb)

bench "flt_sqrt":
  fc = flt_sqrt(fa)

bench "flt_sin":
  fc = flt_sin(fa)

bench "flt_cos":
  fc = flt_cos(fa)

bench "flt_acos":
  fc = flt_acos(fa)

echo ""
headerEcho "Vec2 Benchmarks"

bench "vec2_norm":
  v2c = norm(v2c)

bench "vec2_mag":
  fc = mag(v2c)

bench "vec2_rot":
  v2c = vec2_rot(v2a, deg)

bench "vec2_cross":
  fc = cross(v2a, v2b)

bench "vec2_dot":
  fc = dot(v2a, v2b)

bench "vec2_sum":
  fc = sum(v2c)

bench "vec2_fma":
  v2c = v2a * v2b + v2c

bench "vec2_fms":
  v2c = v2a * v2b - v2c

bench "vec2_add":
  v2c = v2a + v2b

bench "vec2_sub":
  v2c = v2a - v2b

bench "vec2_mul":
  v2c = v2a * v2b

bench "vec2_div":
  v2c = v2a / v2b

echo ""
headerEcho "Vec3 Benchmarks"

bench "vec3_norm":
  v3c = norm(v3c)

bench "vec3_mag":
  fc = mag(v3c)

bench "vec3_rot":
  v3c = vec3_rot(v3a, axis)

bench "vec3_rotq":
  v3c = vec3_rotq(v3a, quat)

bench "vec3_cross":
  v3c = cross(v3a, v3b)

bench "vec3_dot":
  fc = dot(v3a, v3b)

bench "vec3_sum":
  fc = sum(v3c)

bench "vec3_fma":
  v3c = v3a * v3b + v3c

bench "vec3_fms":
  v3c = v3a * v3b - v3c

bench "vec3_add":
  v3c = v3a + v3b

bench "vec3_sub":
  v3c = v3a - v3b

bench "vec3_mul":
  v3c = v3a * v3b

bench "vec3_div":
  v3c = v3a / v3b

echo ""
headerEcho "Vec4 Benchmarks"

bench "vec4_norm":
  v4c = norm(v4c)

bench "vec4_mag":
  fc = mag(v4c)

bench "vec4_eq":
  b = eq(v4a, v4b, 0.1)

bench "vec4_sum":
  fc = sum(v4c)

bench "vec4_fma":
  v4c = v4a * v4b + v4c

bench "vec4_fms":
  v4c = v4a * v4b - v4c

bench "vec4_add":
  v4c = v4a + v4b

bench "vec4_sub":
  v4c = v4a - v4b

bench "vec4_mul":
  v4c = v4a * v4b

bench "vec4_div":
  v4c = v4a / v4b

echo ""
headerEcho "Mat2 Benchmarks"

bench "mat2_dot":
  m2c = mat2_dot(m2a, m2b)

bench "mat2_fma":
  m2c = m2a * m2b + m2c

bench "mat2_fms":
  m2c = m2a * m2b - m2c

bench "mat2_add":
  m2c = m2a + m2b

bench "mat2_sub":
  m2c = m2a - m2b

bench "mat2_mul":
  m2c = m2a * m2b

bench "mat2_div":
  m2c = m2a / m2b

bench "mat2_avg":
  m2c = mat2_avg(m2a, m2b)

echo ""
headerEcho "Mat3 Benchmarks"

bench "mat3_dot":
  m3c = mat3_dot(m3a, m3b)

bench "mat3_fma":
  m3c = m3a * m3b + m3c

bench "mat3_fms":
  m3c = m3a * m3b - m3c

bench "mat3_add":
  m3c = m3a + m3b

bench "mat3_sub":
  m3c= m3a - m3b

bench "mat3_mul":
  m3c = m3a * m3b

bench "mat3_div":
  m3c = m3a / m3b

bench "mat3_avg":
  m3c = mat3_avg(m3a, m3b)

echo ""
headerEcho "Mat4 Benchmarks"

bench "mat4_dot":
  m4c = mat4_dot(m4a, m4b)

bench "mat4_fma":
  m4c = m4a * m4b + m4c

bench "mat4_fms":
  m4c = m4a * m4b - m4c

bench "mat4_add":
  m4c = m4a + m4b

bench "mat4_sub":
  m4c = m4a - m4b

bench "mat4_mul":
  m4c = m4a * m4b

bench "mat4_div":
  m4c = m4a / m4b

bench "mat4_avg":
  m4c = mat4_avg(m4a, m4b)

echo ""
