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

type float32x2* {.sol, noDecl.} = object
type float32x3* {.sol, noDecl.} = object
type float32x4* {.sol, noDecl.} = object

type float64x2* {.sol, noDecl.} = object
type float64x3* {.sol, noDecl.} = object
type float64x4* {.sol, noDecl.} = object

type uint32x2* {.sol.} = object
type uint32x3* {.sol.} = object
type uint32x4* {.sol.} = object

type uint64x2* {.sol.} = object
type uint64x3* {.sol.} = object
type uint64x4* {.sol.} = object

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

FX1(float32)
FX1(float64)

