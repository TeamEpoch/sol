###############################################################
# test.nim | The Sol Testing Suite ############################
# Author: David Garland (https://github.com/davidgarland/sol) #
###############################################################

################################################################################
# Dependencies #################################################################
################################################################################

import unittest

import ../src/sol

################################################################################
# Setup ########################################################################
################################################################################

echo "Test Epsilon: " & $sol_epsilon

################################################################################
# Test Suites ##################################################################
################################################################################

##############
# Vec2 Tests #
##############

suite "Vec2":
  var a, b, c: Vec2
  var f, rad, deg: Float
  setup:
    a = vec2_init(1, 2)
    b = vec2_init(3, 4)
    c = vec2_init(5, 6)
    f = 1
    deg = 90
    rad = cv_deg_rad(deg)
  test "Scalar Accessors":
    a.x = 2
    require:
      a == vec2_init(2, 2)
      a.x == 2
    a[0] = 3
    require:
      a == vec2_init(3, 2)
      a[0] == 3
  test "Summation":
    require:
      vec2_sum(a) == a.x + a.y
  test "Fused Multiply Add":
    require:
      a * b + c == vec2_init((a.x * b.x) + c.x,
                             (a.y * b.y) + c.y)
  test "Fused Multiply Subtract":
    require:
      a * b - c == vec2_init((a.x * b.x) - c.x,
                             (a.y * b.y) - c.y)
  test "Addition":
    require:
      a + b == vec2_init(a.x + b.x,
                         a.y + b.y)
      a + f == vec2_init(a.x + f,
                         a.y + f)
  test "Subtraction":
    require:
      a - b == vec2_init(a.x - b.x,
                         a.y - b.y)
      a - f == vec2_init(a.x - f,
                         a.y - f)
      f - a == vec2_init(f - a.x,
                         f - a.y)
  test "Multiplication":
    require:
      a * b == vec2_init(a.x * b.x,
                         a.y * b.y)
      a * f == vec2_init(a.x * f,
                         a.y * f)
  test "Division":
    require:
      a / b == vec2_init(a.x / b.x,
                         a.y / b.y)
      a / f == vec2_init(a.x / f,
                         a.y / f)
      f / a == vec2_init(f / a.x,
                         f / a.y)

##############
# Vec3 Tests #
##############

suite "Vec3":
  var axis, quat: Vec4
  var a, b, c: Vec3
  var f: Float
  setup:
    a = vec3_init(1, 2, 3)
    b = vec3_init(4, 5, 6)
    c = vec3_init(7, 8, 9)
    f = 1
    axis = vec4_init(1, 0, 0, 90)
    quat = cv_axis_quat(axis)
  test "Scalar Accessors":
    a.x = 2
    require:
      a == vec3_init(2, 2, 3)
      a.x == 2
    a[0] = 3
    require:
      a == vec3_init(3, 2, 3)
      a[0] == 3
  test "Summation":
    require:
      vec3_sum(a) == a.x + a.y + a.z
  test "Fused Multiply Add":
    require:
      a * b + c == vec3_init((a.x * b.x) + c.x,
                             (a.y * b.y) + c.y,
                             (a.z * b.z) + c.z)
  test "Fused Multiply Subtract":
    require:
      a * b - c == vec3_init((a.x * b.x) - c.x,
                             (a.y * b.y) - c.y,
                             (a.z * b.z) - c.z)
  test "Addition":
    require:
      a + b == vec3_init(a.x + b.x,
                         a.y + b.y,
                         a.z + b.z)
      a + f == vec3_init(a.x + f,
                         a.y + f,
                         a.z + f)
  test "Subtraction":
    require:
      a - b == vec3_init(a.x - b.x,
                         a.y - b.y,
                         a.z - b.z)
      a - f == vec3_init(a.x - f,
                         a.y - f,
                         a.z - f)
      f - a == vec3_init(f - a.x,
                         f - a.y,
                         f - a.z)
  test "Multiplication":
    require:
      a * b == vec3_init(a.x * b.x,
                         a.y * b.y,
                         a.z * b.z)
      a * f == vec3_init(a.x * f,
                         a.y * f,
                         a.z * f)
  test "Division":
    require:
      a / b == vec3_init(a.x / b.x,
                         a.y / b.y,
                         a.z / b.z)
      a / f == vec3_init(a.x / f,
                         a.y / f,
                         a.z / f)
      f / a == vec3_init(f / a.x,
                         f / a.y,
                         f / a.z)

##############
# Vec4 Tests #
##############

suite "Vec4":
  var a, b, c: Vec4
  var f: Float
  
  setup:
    a = vec4_init(1, 2, 3, 4)
    b = vec4_init(5, 6, 7, 8)
    c = vec4_init(9, 10, 11, 12)
    f = 1
  test "Scalar Accessors":
    a.x = 2
    require:
      a == vec4_init(2, 2, 3, 4)
      a.x == 2
    a[0] = 3
    require:
      a == vec4_init(3, 2, 3, 4)
      a[0] == 3
  test "Summation":
    require:
      vec4_sum(a) == a.x + a.y + a.z + a.w
  test "Fused Multiply Add":
    require:
      a * b + c == vec4_init((a.x * b.x) + c.x,
                             (a.y * b.y) + c.y,
                             (a.z * b.z) + c.z,
                             (a.w * b.w) + c.w)
  test "Fused Multiply Subtract":
    require:
      a * b - c == vec4_init((a.x * b.x) - c.x,
                             (a.y * b.y) - c.y,
                             (a.z * b.z) - c.z,
                             (a.w * b.w) - c.w)
  test "Addition":
    require:
      a + b == vec4_init(a.x + b.x,
                         a.y + b.y,
                         a.z + b.z,
                         a.w + b.w)
      a + f == vec4_init(a.x + f,
                         a.y + f,
                         a.z + f,
                         a.w + f)
  test "Subtraction":
    require:
      a - b == vec4_init(a.x - b.x,
                         a.y - b.y,
                         a.z - b.z,
                         a.w - b.w)
      a - f == vec4_init(a.x - f,
                         a.y - f,
                         a.z - f,
                         a.w - f)
      f - a == vec4_init(f - a.x,
                         f - a.y,
                         f - a.z,
                         f - a.w)
  test "Multiplication":
    require:
      a * b == vec4_init(a.x * b.x,
                         a.y * b.y,
                         a.z * b.z,
                         a.w * b.w)
      a * f == vec4_init(a.x * f,
                         a.y * f,
                         a.z * f,
                         a.w * f)
  test "Division":
    require:
      a / b == vec4_init(a.x / b.x,
                         a.y / b.y,
                         a.z / b.z,
                         a.w / b.w)
      a / f == vec4_init(a.x / f,
                         a.y / f,
                         a.z / f,
                         a.w / f)
      f / a == vec4_init(f / a.x,
                         f / a.y,
                         f / a.z,
                         f / a.w)
