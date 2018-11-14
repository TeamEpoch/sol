#
# sol.nim | The Sol Vector Library | Nim Bindings
# https://github.com/davidgarland/sol
#

import
  strformat,
  macros

#
# Pragmas
#

{.passc: "-I.".}
{.pragma: solh, header: "sol.h".}
{.pragma: sol, solh, importc.}

#
# Scalar Types
#

type f32* {.sol.} = float32
type f64* {.sol.} = float64
type u32* {.sol.} = uint32
type u64* {.sol.} = uint64
type i32* {.sol.} = int32
type i64* {.sol.} = int64

#
# Vector Types
#

type f32x2* {.sol, noDecl.} = object
type f32x3* {.sol, noDecl.} = object
type f32x4* {.sol, noDecl.} = object

type f64x2* {.sol, noDecl.} = object
type f64x3* {.sol, noDecl.} = object
type f64x4* {.sol, noDecl.} = object

type u32x2* {.sol.} = object
type u32x3* {.sol.} = object
type u32x4* {.sol.} = object

type u64x2* {.sol.} = object
type u64x3* {.sol.} = object
type u64x4* {.sol.} = object

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
    v.add(v) is V
    v.add(f) is V
    f.add(v) is V
    v.sub(v) is V
    v.sub(f) is V
    f.sub(v) is V
    v.mul(v) is V
    v.mul(f) is V
    f.mul(v) is V
    v.div(v) is V
    v.div(f) is V
    f.div(v) is V
    fma(v, v, v) is V
    fms(v, v, v) is V
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

#
# Prototypes
#

template FNAME(T: untyped; fn: static[string]): untyped =
  astToStr(T) & "_" & fn

template FEMIT(e: static[string]): untyped =
  macro payload: untyped {.gensym.} =
    result = parseStmt(e)
  payload()

template FX1*(T: untyped) {.dirty.} =
  func sqrt*(f: T): T {.solh, importc: FNAME(T, "sqrt").}
  
  func sin*(f: T): T      {.solh, importc: FNAME(T, "sin").}
  func cos*(f: T): T      {.solh, importc: FNAME(T, "cos").}
  func tan*(f: T): T      {.solh, importc: FNAME(T, "tan").}
  func asin*(f: T): T     {.solh, importc: FNAME(T, "asin").}
  func acos*(f: T): T     {.solh, importc: FNAME(T, "acos").}
  func atan*(f: T): T     {.solh, importc: FNAME(T, "atan").}
  func atan2*(y, x: T): T {.solh, importc: FNAME(T, "atan2").}

  template `V sqrt`*(f: T): T = sqrt(f)

  template `V sin`*(f: T): T     = sin(f)
  template `V cos`*(f: T): T     = cos(f)
  template `V tan`*(f: T): T     = tan(f)
  template `V asin`*(f: T): T    = asin(f)
  template `V acos`*(f: T): T    = acos(f)
  template `V atan`*(f: T): T    = atan(f)
  template `V atan2`*(y, x: T): T = atan2(y, x)

FX1(f32)
FX1(f64)

template FX2*(T, V: untyped) {.dirty.} =

  # Scalar Accessors

  func `x`*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func `y`*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ")"

  # Clean Syntax

  func `set`*(x, y: T): V {.solh, importc: FNAME(V, "set").}

  func `add`*(a, b: V): V    {.solh, importc: FNAME(V, "add").}
  func `add`*(v: V; f: T): V {.solh, importc: FNAME(V, "addf").}
  func `sub`*(a, b: V): V    {.solh, importc: FNAME(V, "sub").}
  func `sub`*(v: V; f: T): V {.solh, importc: FNAME(V, "subf").}
  func `sub`*(f: T; v: V): V {.solh, importc: FNAME(V, "fsub").}
  func `mul`*(a, b: V): V    {.solh, importc: FNAME(V, "mul").}
  func `mul`*(v: V; f: T): V {.solh, importc: FNAME(V, "mulf").}
  func `div`*(a, b: V): V    {.solh, importc: FNAME(V, "div").}
  func `div`*(v: V; f: T): V {.solh, importc: FNAME(V, "divf").}
  func `div`*(f: T; v: V): V {.solh, importc: FNAME(V, "fdiv").}
  func `fma`*(a, b, c: V): V {.solh, importc: FNAME(V, "fma").}
  func `fms`*(a, b, c: V): V {.solh, importc: FNAME(V, "fms").}

  template `add`*(f: T; v: V): V = v.add(f)
  template `mul`*(f: T; v: V): V = v.mul(f)

  func `+`*(a, b: V): V    {.inline.} = a.add(b)
  func `+`*(v: V; f: T): V {.inline.} = v.add(f)
  func `+`*(f: T; v: V): V {.inline.} = f.add(v)
  func `-`*(a, b: V): V    {.inline.} = a.sub(b)
  func `-`*(v: V; f: T): V {.inline.} = v.sub(f)
  func `-`*(f: T; v: V): V {.inline.} = f.sub(v)
  func `*`*(a, b: V): V    {.inline.} = a.mul(b)
  func `*`*(v: V; f: T): V {.inline.} = v.mul(f)
  func `*`*(f: T; v: V): V {.inline.} = f.mul(v)
  func `/`*(a, b: V): V    {.inline.} = a.div(b)
  func `/`*(v: V; f: T): V {.inline.} = v.div(f)
  func `/`*(f: T; v: V): V {.inline.} = f.div(v)

  # F Syntax

  template `addf`*(v: V; f: T): V = v.add(f)
  template `subf`*(v: V; f: T): V = v.sub(f)
  template `fsub`*(f: T; v: V): V = f.sub(v)
  template `mulf`*(v: V; f: T): V = v.mul(f)
  template `divf`*(v: V; f: T): V = v.div(f)
  template `fdiv`*(f: T; v: V): V = f.div(v)

  # Original Syntax

  template `V set`*(x, y: T): V = set(x, y)
  proc `V setf`*(f: T): V {.solh, importc: FNAME(V, "setf").}

  template `V add`*(a, b: V): V     = a.add(b)
  template `V addf`*(v: V; f: T): V = v.add(f)
  template `V sub`*(a, b: V): V     = a.sub(b)
  template `V subf`*(v: V; f: T): V = v.sub(f)
  template `V fsub`*(f: T; v: V): V = f.sub(v)
  template `V mul`*(a, b: V): V     = a.mul(b)
  template `V mulf`*(v: V; f: T): V = v.mul(f)
  template `V div`*(a, b: V): V     = a.div(b)
  template `V divf`*(v: V; f: T): V = v.div(f)
  template `V fdiv`*(f: T; v: V): V = f.div(v)
  template `V fma`*(a, b, c: V): V  = a.fma(b, c)
  template `V fms`*(a, b, c: V): V  = a.fms(b, c)

FX2(f32, f32x2)
FX2(f64, f64x2)

template FX3*(T, V: untyped) {.dirty.} =

  # Scalar Accessors

  func `x`*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func `y`*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func `z`*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}
  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(*", v, ") = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(*", v, ") = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(*", v, ") = ", f, ";"].}
  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ", " & $v.z & ")"

  # Clean Syntax

  func `set`*(x, y, z: T): V {.solh, importc: FNAME(V, "set").}

  func `add`*(a, b: V): V    {.solh, importc: FNAME(V, "add").}
  func `add`*(v: V; f: T): V {.solh, importc: FNAME(V, "addf").}
  func `sub`*(a, b: V): V    {.solh, importc: FNAME(V, "sub").}
  func `sub`*(v: V; f: T): V {.solh, importc: FNAME(V, "subf").}
  func `sub`*(f: T; v: V): V {.solh, importc: FNAME(V, "fsub").}
  func `mul`*(a, b: V): V    {.solh, importc: FNAME(V, "mul").}
  func `mul`*(v: V; f: T): V {.solh, importc: FNAME(V, "mulf").}
  func `div`*(a, b: V): V    {.solh, importc: FNAME(V, "div").}
  func `div`*(v: V; f: T): V {.solh, importc: FNAME(V, "divf").}
  func `div`*(f: T; v: V): V {.solh, importc: FNAME(V, "fdiv").}
  func `fma`*(a, b, c: V): V {.solh, importc: FNAME(V, "fma").}
  func `fms`*(a, b, c: V): V {.solh, importc: FNAME(V, "fms").}

  template `add`*(f: T; v: V): V = v.add(f)
  template `mul`*(f: T; v: V): V = v.mul(f)

  func `+`*(a, b: V): V    {.inline.} = a.add(b)
  func `+`*(v: V; f: T): V {.inline.} = v.add(f)
  func `+`*(f: T; v: V): V {.inline.} = f.add(v)
  func `-`*(a, b: V): V    {.inline.} = a.sub(b)
  func `-`*(v: V; f: T): V {.inline.} = v.sub(f)
  func `-`*(f: T; v: V): V {.inline.} = f.sub(v)
  func `*`*(a, b: V): V    {.inline.} = a.mul(b)
  func `*`*(v: V; f: T): V {.inline.} = v.mul(f)
  func `*`*(f: T; v: V): V {.inline.} = f.mul(v)
  func `/`*(a, b: V): V    {.inline.} = a.div(b)
  func `/`*(v: V; f: T): V {.inline.} = v.div(f)
  func `/`*(f: T; v: V): V {.inline.} = f.div(v)

  # F Syntax

  template `addf`*(v: V; f: T): V = v.add(f)
  template `subf`*(v: V; f: T): V = v.sub(f)
  template `fsub`*(f: T; v: V): V = f.sub(v)
  template `mulf`*(v: V; f: T): V = v.mul(f)
  template `divf`*(v: V; f: T): V = v.div(f)
  template `fdiv`*(f: T; v: V): V = f.div(v)

  # Original Syntax

  template `V set`*(x, y, z: T): V = set(x, y, z)
  proc `V setf`*(f: T): V {.solh, importc: FNAME(V, "setf").}

  template `V add`*(a, b: V): V     = a.add(b)
  template `V addf`*(v: V; f: T): V = v.add(f)
  template `V sub`*(a, b: V): V     = a.sub(b)
  template `V subf`*(v: V; f: T): V = v.sub(f)
  template `V fsub`*(f: T; v: V): V = f.sub(v)
  template `V mul`*(a, b: V): V     = a.mul(v)
  template `V mulf`*(v: V; f: T): V = v.mul(f)
  template `V div`*(a, b: V): V     = a.div(b)
  template `V divf`*(v: V; f: T): V = v.div(f)
  template `V fdiv`*(f: T; v: V): V = f.div(v)
  template `V fma`*(a, b, c: V): V  = a.fma(b, c)
  template `V fms`*(a, b, c: V): V  = a.fms(b, c)

FX3(f32, f32x3)
FX3(f64, f64x3)

template FX4*(T, V: untyped) {.dirty.} =

  # Scalar Accessors

  func `x`*(v: V): T {.inline.} = {.emit: [result, " = x(", v, ");"].}
  func `y`*(v: V): T {.inline.} = {.emit: [result, " = y(", v, ");"].}
  func `z`*(v: V): T {.inline.} = {.emit: [result, " = z(", v, ");"].}
  func `w`*(v: V): T {.inline.} = {.emit: [result, " = w(", v, ");"].}
  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(*", v, ") = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(*", v, ") = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(*", v, ") = ", f, ";"].}
  proc `w=`*(v: var V; f: T) {.inline.} = {.emit: ["w(*", v, ") = ", f, ";"].}
  func `$`*(v: V): string {.inline.} = "(" & $v.x & ", " & $v.y & ", " & $v.z & ", " & $v.w & ")"

  # Clean Syntax

  func `set`*(x, y, z, w: T): V {.solh, importc: FNAME(V, "set").}

  func `add`*(a, b: V): V    {.solh, importc: FNAME(V, "add").}
  func `add`*(v: V; f: T): V {.solh, importc: FNAME(V, "addf").}
  func `sub`*(a, b: V): V    {.solh, importc: FNAME(V, "sub").}
  func `sub`*(v: V; f: T): V {.solh, importc: FNAME(V, "subf").}
  func `sub`*(f: T; v: V): V {.solh, importc: FNAME(V, "fsub").}
  func `mul`*(a, b: V): V    {.solh, importc: FNAME(V, "mul").}
  func `mul`*(v: V; f: T): V {.solh, importc: FNAME(V, "mulf").}
  func `div`*(a, b: V): V    {.solh, importc: FNAME(V, "div").}
  func `div`*(v: V; f: T): V {.solh, importc: FNAME(V, "divf").}
  func `div`*(f: T; v: V): V {.solh, importc: FNAME(V, "fdiv").}
  func `fma`*(a, b, c: V): V {.solh, importc: FNAME(V, "fma").}
  func `fms`*(a, b, c: V): V {.solh, importc: FNAME(V, "fms").}

  template `add`*(f: T; v: V): V = v.add(f)
  template `mul`*(f: T; v: V): V = v.mul(f)

  func `+`*(a, b: V): V    {.inline.} = a.add(b)
  func `+`*(v: V; f: T): V {.inline.} = v.add(f)
  func `+`*(f: T; v: V): V {.inline.} = f.add(v)
  func `-`*(a, b: V): V    {.inline.} = a.sub(b)
  func `-`*(v: V; f: T): V {.inline.} = v.sub(f)
  func `-`*(f: T; v: V): V {.inline.} = f.sub(v)
  func `*`*(a, b: V): V    {.inline.} = a.mul(b)
  func `*`*(v: V; f: T): V {.inline.} = v.mul(f)
  func `*`*(f: T; v: V): V {.inline.} = f.mul(v)
  func `/`*(a, b: V): V    {.inline.} = a.div(b)
  func `/`*(v: V; f: T): V {.inline.} = v.div(f)
  func `/`*(f: T; v: V): V {.inline.} = f.div(v)

  # F Syntax

  template `addf`*(v: V; f: T): V = v.add(f)
  template `subf`*(v: V; f: T): V = v.sub(f)
  template `fsub`*(f: T; v: V): V = f.sub(v)
  template `mulf`*(v: V; f: T): V = v.mul(f)
  template `divf`*(v: V; f: T): V = v.div(f)
  template `fdiv`*(f: T; v: V): V = f.div(v)

  # Original Syntax

  template `V set`*(x, y, z, w: T): V = set(x, y, z, w)
  proc `V setf`*(f: T): V {.solh, importc: FNAME(V, "setf").}
  
  template `V add`*(a, b: V): V = a.add(b)
  template `V addf`*(v: V; f: T): V = v.add(f)
  template `V sub`*(a, b: V): V = a.sub(b)
  template `V subf`*(v: V; f: T): V = v.sub(f)
  template `V fsub`*(f: T; v: V): V = f.sub(v)
  template `V mul`*(a, b: V): V = a.mul(b)
  template `V mulf`*(v: V; f: T): V = v.mul(f)
  template `V div`*(a, b: V): V = a.div(b)
  template `V divf`*(v: V; f: T): V = v.div(f)
  template `V fdiv`*(f: T; v: V): V = f.div(v)
  template `V fma`*(a, b, c: V): V = a.fma(b, c)
  template `V fms`*(a, b, c: V): V = a.fms(b, c)

FX4(f32, f32x4)
FX4(f64, f64x4)

template optFma*{`+`(`*`(a, b), c)}(a, b, c: Vec): auto =
  fma(a, b, c)

template optFms*{`-`(`*`(a, b), c)}(a, b, c: Vec): auto =
  fms(a, b, c)
