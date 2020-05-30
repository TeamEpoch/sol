#[
## sol.nim | The Sol Vector Library | Nim Bindings
## https://github.com/davidgarland/sol
]#

import
  strformat

#[
## Pragmas
]#

from os import splitPath
{.passC:"-I" & currentSourcePath().splitPath.head.}
{.passc: "-I.".}
{.pragma: solh, header: "sol.h".}
{.pragma: sol, solh, importc.}

#[
## Vector Types
]#

type float32x2* {.solh, importc: "f32x2".} = object
type float32x3* {.solh, importc: "f32x3".} = object
type float32x4* {.solh, importc: "f32x4".} = object

type float64x2* {.solh, importc: "f64x2".} = object
type float64x3* {.solh, importc: "f64x3".} = object
type float64x4* {.solh, importc: "f64x4".} = object

type int8x2* {.solh, importc: "i8x2".} = object
type int8x3* {.solh, importc: "i8x3".} = object
type int8x4* {.solh, importc: "i8x4".} = object

type int16x2* {.solh, importc: "i16x2".} = object
type int16x3* {.solh, importc: "i16x3".} = object
type int16x4* {.solh, importc: "i16x4".} = object

type int32x2*   {.solh, importc: "i32x2".} = object
type int32x3*   {.solh, importc: "i32x3".} = object
type int32x4*   {.solh, importc: "i32x4".} = object

type int64x2*   {.solh, importc: "i64x2".} = object
type int64x3*   {.solh, importc: "i64x3".} = object
type int64x4*   {.solh, importc: "i64x4".} = object

type uint8x2* {.solh, importc: "u8x2".} = object
type uint8x3* {.solh, importc: "u8x3".} = object
type uint8x4* {.solh, importc: "u8x4".} = object

type uint16x2* {.solh, importc: "u16x2".} = object
type uint16x3* {.solh, importc: "u16x3".} = object
type uint16x4* {.solh, importc: "u16x4".} = object

type uint32x2*  {.solh, importc: "u32x2".} = object
type uint32x3*  {.solh, importc: "u32x3".} = object
type uint32x4*  {.solh, importc: "u32x4".} = object

type uint64x2*  {.solh, importc: "u64x2".} = object
type uint64x3*  {.solh, importc: "u64x3".} = object
type uint64x4*  {.solh, importc: "u64x4".} = object

#[
## Constants
]#

const f32_pi*: float32    = 3.14159265358979323846'f32
const f32_pi_sq*: float32 = f32_pi * f32_pi
const f64_pi*: float64    = 3.14159265358979323846'f64
const f64_pi_sq*: float64 = f64_pi * f64_pi

#[
## Concept Types
]#

type
  Vec* = concept v
    type V = v.type
    type T = v.x.type
    var f: T
    v + v is V
    v + f is V
    f + v is V
    v - v is V
    v - f is V
    f - v is V
    v * v is V
    v * f is V
    f * v is V
    v / v is V
    v / f is V
    f / v is V
  Vec2* = concept v
    v is Vec
    type T = v.x.type
    v.y is T
  Vec3* = concept v
    v is Vec2
    type T = v.x.type
    v.z is T
  Vec4* = concept v
    v is Vec3
    type T = v.x.type
    v.w is T

#[
## Implementations
]#

template FNAME(T: untyped; F: string): string =
  astToStr(T) & "_" & F

template FX1(N, T: untyped) {.dirty.} =
  func `N sq`*(f: T): T {.solh, importc: FNAME(N, "sq").}
  func `N sqrt`*(f: T): T {.solh, importc: FNAME(N, "sqrt").}
  func `N abs`*(f: T): T {.solh, importc: FNAME(N, "abs").}
  func `N abs neg`*(f: T) {.solh, importc: FNAME(N, "abs_neg").}
  func `N neg`*(f: T): T {.solh, importc: FNAME(N, "neg").}
  func `N neg if`*(f: T, c: uint64): T {.solh, importc: FNAME(N, "neg_if").}
  func `N mod`*(x, y: T): T {.solh, importc: FNAME(N, "mod").}
  func `N sin`*(f: T): T {.solh, importc: FNAME(N, "sin").}
  func `N cos`*(f: T): T {.solh, importc: FNAME(N, "cos").}
  func `N tan`*(f: T): T {.solh, importc: FNAME(N, "tan").}
  func `N asin`*(f: T): T {.solh, importc: FNAME(N, "asin").}
  func `N acos`*(f: T): T {.solh, importc: FNAME(N, "acos").}
  func `N atan`*(f: T): T {.solh, importc: FNAME(N, "atan").}
  func `N atan2`*(x, y: T): T {.solh, importc: FNAME(N, "atan2").}

FX1(f32, float32)
FX1(f64, float64)

template FX2(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ")" 

  func `N`*(x, y: T): V {.solh, importc: FNAME(N, "set").}

  func rot*(v: V; rad: T): V {.solh, importc: FNAME(N, "rot").}
  func scale*(v: V; f: T): V {.solh, importc: FNAME(N, "scale").}

  func norm*(v: V): V     {.solh, importc: FNAME(N, "norm").}
  func mag*(v: V): T      {.solh, importc: FNAME(N, "mag").}
  func proj*(a, b: V): V  {.solh, importc: FNAME(N, "proj").}
  func rej*(a, b: V): V   {.solh, importc: FNAME(N, "rej").}
  func angle*(a, b: V): T {.solh, importc: FNAME(N, "angle").}
  func cross*(a, b: V): T {.solh, importc: FNAME(N, "cross").}
  func dot*(a, b: V): T   {.solh, importc: FNAME(N, "dot").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V  {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

FX2(f32x2, float32, float32x2)
FX2(f64x2, float64, float64x2)

template FX3(N, T, V, Q: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & "," & $v.z & ")"

  func `N`*(x, y, z: T): V {.solh, importc: FNAME(N, "set").}

  func rot*(v: V; q: Q): V {.solh, importc: FNAME(N, "rot").}
  func scale*(v: V; f: T): V {.solh, importc: FNAME(N, "scale").}

  func norm*(v: V): V     {.solh, importc: FNAME(N, "norm").}
  func mag*(v: V): T      {.solh, importc: FNAME(N, "mag").}
  func proj*(a, b: V): V  {.solh, importc: FNAME(N, "proj").}
  func rej*(a, b: V): V   {.solh, importc: FNAME(N, "rej").}
  func angle*(a, b: V): T {.solh, importc: FNAME(N, "angle").}
  func cross*(a, b: V): V {.solh, importc: FNAME(N, "cross").}
  func dot*(a, b: V): T   {.solh, importc: FNAME(N, "dot").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V  {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

FX3(f32x3, float32, float32x3, float32x4)
FX3(f64x3, float64, float64x3, float32x4)

template FX4(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}
  func w*(v: V): T {.inline.} = {.emit: [result, " = w(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}
  proc `w=`*(v: var V; f: T) {.inline.} = {.emit: ["w(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ", " & $v.z & ", " & $v.w & ")"

  func `N`*(x, y, z, w: T): V {.solh, importc: FNAME(N, "set").}

  func scale*(v: V; f: T): V {.solh, importc: FNAME(N, "scale").}
  
  func norm*(v: V): V {.solh, importc: FNAME(N, "norm").}
  func mag*(v: V): T  {.solh, importc: FNAME(N, "mag").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V  {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

FX4(f32x4, float32, float32x4)
FX4(f64x4, float64, float64x4)

template IX1(N, T: untyped) {.dirty.} =
  discard

IX1(i32, int32)
IX1(i64, int64)

template IX2(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ")"

  func `N`*(x, y: T): V {.solh, importc: FNAME(N, "set").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f


IX2(i8x2,  int8,   int8x2)
IX2(i16x2, int16, int16x2)
IX2(i32x2, int32, int32x2)
IX2(i64x2, int64, int64x2)

template IX3(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ", " & $v.z & ")"

  func `N`*(x, y, z: T): V {.solh, importc: FNAME(N, "set").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

IX3(i8x3,  int8,   int8x3)
IX3(i16x3, int16, int16x3)
IX3(i32x3, int32, int32x3)
IX3(i64x3, int64, int64x3)

template IX4(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}
  func w*(v: V): T {.inline.} = {.emit: [result, " = w(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}
  proc `w=`*(v: var V; f: T) {.inline.} = {.emit: ["w(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ", " & $v.z & ", " & $v.w & ")"

  func `N`*(x, y, z, w: T): V {.solh, importc: FNAME(N, "set").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

IX4(i8x4,  int8,   int8x4)
IX4(i16x4, int16, int16x4)
IX4(i32x4, int32, int32x4)
IX4(i64x4, int64, int64x4)

template UX1(N, T: untyped) {.dirty.} =
  discard

UX1( u8,  uint8)
UX1(u16, uint16)
UX1(u32, uint32)
UX1(u64, uint64)

template UX2(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ")"

  func `N`*(x, y: T): V {.solh, importc: FNAME(N, "set").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V  {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

UX2( u8x2,  uint8,  uint8x2)
UX2(u16x2, uint16, uint16x2)
UX2(u32x2, uint32, uint32x2)
UX2(u64x2, uint64, uint64x2)

template UX3(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}

  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ", " & $v.z & ")"

  func `N`*(x, y, z: T): V {.solh, importc: FNAME(N, "set").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V  {.solh, importc: FNAME(N, "sq").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

UX3( u8x3,  uint8,  uint8x3)
UX3(u16x3, uint16, uint16x3)
UX3(u32x3, uint32, uint32x3)
UX3(u64x3, uint64, uint64x3)

template UX4(N, T, V: untyped) {.dirty.} =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}
  func w*(v: V): T {.inline.} = {.emit: [result, " = w(", v, ");"].}
  
  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}
  proc `w=`*(v: var V; f: T) {.inline.} = {.emit: ["w(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & "," & $v.y & ", " & $v.z & ", " & $v.w & ")"

  func `N`*(x, y, z, w: T): V {.solh, importc: FNAME(N, "set").}

  func sum*(v: V): T {.solh, importc: FNAME(N, "sum").}
  func sq*(v: V): V {.solh, importc: FNAME(N, "sum").}

  func `+`*(a, b: V): V    {.solh, importc: FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: FNAME(N, "fdiv").}

  template `+=`*(a, b: V)    {.dirty.} = a = a + b
  template `+=`*(v: V; f: T) {.dirty.} = v = v + f
  template `-=`*(a, b: V)    {.dirty.} = a = a - b
  template `-=`*(v: V; f: T) {.dirty.} = v = v - f
  template `*=`*(a, b: V)    {.dirty.} = a = a * b
  template `*=`*(v: V; f: T) {.dirty.} = v = v * f
  template `/=`*(a, b: V)    {.dirty.} = a = a / b
  template `/=`*(v: V; f: T) {.dirty.} = v = v / f

UX4( u8x4,  uint8,  uint8x4)
UX4(u16x4, uint16, uint16x4)
UX4(u32x4, uint32, uint32x4)
UX4(u64x4, uint64, uint64x4)
