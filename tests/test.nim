import
  unittest,
  ../src/sol

suite "float32x2":
  var a, b, c: float32x2
  test ".x":
    a.x = 1
    require a.x == 1
  test ".y":
    a.y = 1
    require a.y == 1
  test "f32x2":
    a = f32x2(0, 1)
    require a.x == 0
    require a.y == 1

suite "float64x2":
  var a, b, c: float64x2
  test ".x":
    a.x = 1
    require a.x == 1
  test ".y":
    a.y = 1
    require a.y == 1
  test "f64x2":
    a = f64x2(0, 1)
    require a.x == 0
    require a.y == 1

suite "float32x3":
  var a, b, c: float32x3
  test ".x":
    a.x = 1
    require a.x == 1
  test ".y":
    a.y = 1
    require a.y == 1
  test ".z":
    a.z = 1
    require a.z == 1
  test "f32x3":
    a = f32x3(0, 1, 2)
    require a.x == 0
    require a.y == 1
    require a.z == 2

suite "float64x3":
  var a, b, c: float64x3
  test ".x":
    a.x = 1
    require a.x == 1
  test ".y":
    a.y = 1
    require a.y == 1
  test ".z":
    a.z = 1
    require a.z == 1
  test "f64x3":
    a = f64x3(0, 1, 2)
    require a.x == 0
    require a.y == 1
    require a.z == 2

suite "float32x4":
  var a, b, c: float32x4
  test ".x":
    a.x = 1
    require a.x == 1
  test ".y":
    a.y = 1
    require a.y == 1
  test ".z":
    a.z = 1
    require a.z == 1
  test "f32x4":
    a = f32x4(0, 1, 2, 3)
    require a.x == 0
    require a.y == 1
    require a.z == 2
    require a.w == 3

suite "float64x4":
  var a, b, c: float64x4
  test ".x":
    a.x = 1
    require a.x == 1
  test ".y":
    a.y = 1
    require a.y == 1
  test ".z":
    a.z = 1
    require a.z == 1
  test "f64x4":
    a = f64x4(0, 1, 2, 3)
    require a.x == 0
    require a.y == 1
    require a.z == 2
    require a.w == 3
