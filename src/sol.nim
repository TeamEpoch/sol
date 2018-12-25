#
# sol.nim | The Sol Vector Library | Nim Bindings
# https://github.com/davidgarland/sol
#

import
  strformat,
  macros,
  math

#
# Ugly Workaround To Actually Make The Bindings Work Why Does This Exist This Is Not Okay
#

from os import splitPath
{.passC:"-I" & currentSourcePath().splitPath.head.}

#
# Pragmas
#

{.passc: "-I.".}
{.pragma: solh, header: "sol.h".}
{.pragma: sol, solh, importc.}

#
# Vector Types
#

type float32x2* {.solh, importc: "f32x2".} = object
type float32x3* {.solh, importc: "f32x3".} = object
type float32x4* {.solh, importc: "f32x4".} = object

type float64x2* {.solh, importc: "f64x2".} = object
type float64x3* {.solh, importc: "f64x3".} = object
type float64x4* {.solh, importc: "f64x4".} = object

type uint32x2* {.solh, importc: "u32x2".} = object
type uint32x3* {.solh, importc: "u32x3".} = object
type uint32x4* {.solh, importc: "u32x4".} = object

type uint64x2* {.solh, importc: "u64x2".} = object
type uint64x3* {.solh, importc: "u64x3".} = object
type uint64x4* {.solh, importc: "u64x4".} = object

#
# Concept Types
#

type
  Vec = concept v
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
  Vec2 = concept v
    v is Vec
    type T = v.x.type
    v.y is T
  Vec3 = concept v
    v is Vec2
    type T = v.x.type
    v.z is T
  Vec4 = concept v
    v is Vec3
    type T = v.x.type
    v.w is T

template  SOL_FNAME*(T: untyped; F: string): string =
  astToStr(T) & "_" & F

#
# FX2
#

template SOL_FX2*(N, T, V: untyped) =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}

  func `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  func `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ")" 

  func `N`*(x, y: T): V    {.solh, importc: SOL_FNAME(N, "set").}
  
  func `+`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: SOL_FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: SOL_FNAME(N, "fdiv").}

SOL_FX2(f32x2, float32, float32x2)
SOL_FX2(f64x2, float64, float64x2)

template SOL_FX3*(N, T, V: untyped) =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}

  func `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  func `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  func `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & "," & $v.z & ")"

  func `N`*(x, y, z: T): V {.solh, importc: SOL_FNAME(N, "set").}
  
  func `+`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: SOL_FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: SOL_FNAME(N, "fdiv").}

SOL_FX3(f32x3, float32, float32x3)
SOL_FX3(f64x3, float64, float64x3)

template SOL_FX4*(N, T, V: untyped) =
  func x*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func y*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func z*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}
  func w*(v: V): T {.inline.} = {.emit: [result, " = w(", v, ");"].}

  func `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  func `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  func `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}
  func `w=`*(v: var V; f: T) {.inline.} = {.emit: ["w(", v, "[0]) = ", f, ";"].}

  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ", " & $v.z & ", " & $v.w & ")"

  func `N`*(x, y, z, w: T): V {.solh, importc: SOL_FNAME(N, "set").}

  func `+`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "add").}
  func `+`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "addf").}
  func `+`*(f: T; v: V): V {.inline.} = v + f
  func `-`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "sub").}
  func `-`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "subf").}
  func `-`*(f: T; v: V): V {.solh, importc: SOL_FNAME(N, "fsub").}
  func `*`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "mul").}
  func `*`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "mulf").}
  func `*`*(f: T; v: V): V {.inline.} = v * f
  func `/`*(a, b: V): V    {.solh, importc: SOL_FNAME(N, "div").}
  func `/`*(v: V; f: T): V {.solh, importc: SOL_FNAME(N, "divf").}
  func `/`*(f: T; v: V): V {.solh, importc: SOL_FNAME(N, "fdiv").}

SOL_FX4(f32x4, float32, float32x4)
SOL_FX4(f64x4, float64, float64x4)
