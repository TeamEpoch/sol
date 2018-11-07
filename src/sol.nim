#
# sol.nim | The Sol Vector Library | Nim Bindings
# https://github.com/davidgarland/sol
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

type f32x2* {.sol.} = object
type f32x3* {.sol.} = object
type f32x4* {.sol.} = object

type f64x2* {.sol.} = object
type f64x3* {.sol.} = object
type f64x4* {.sol.} = object

type u32x2* {.sol.} = object
type u32x3* {.sol.} = object
type u32x4* {.sol.} = object

type u64x2* {.sol.} = object
type u64x3* {.sol.} = object
type u64x4* {.sol.} = object

#
# Prototypes
#

template FX1*(T: untyped) =
  proc `T sin`*(f: T): T      {.solh, importc: astToStr(T) & "_sin".}
  proc `T cos`*(f: T): T      {.solh, importc: astToStr(T) & "_cos".}
  proc `T tan`*(f: T): T      {.solh, importc: astToStr(T) & "_tan".}
  proc `T asin`*(f: T): T     {.solh, importc: astToStr(T) & "_asin".}
  proc `T acos`*(f: T): T     {.solh, importc: astToStr(T) & "_acos".}
  proc `T atan`*(f: T): T     {.solh, importc: astToStr(T) & "_atan".}
  proc `T atan2`*(y, x: T): T {.solh, importc: astToStr(T) & "_atan2".}

FX1(f32)
FX1(f64)

template FX2*(T, V: untyped) =
  proc `V set`*(x, y: T): V {.solh, importc: astToStr(V) & "_set".}
  proc `V setf`*(f: T): V   {.solh, importc: astToStr(V) & "_setf".}
  proc `V zero`*(): V       {.solh, importc: astToStr(V) & "_zero".}

  proc `V add`*(a, b: V): V     {.solh, importc: astToStr(V) & "_add".}
  proc `V addf`*(v: V; f: T): V {.solh, importc: astToStr(V) & "_addf".}
  proc `V sub`*(a, b: V): V     {.solh, importc: astToStr(V) & "_sub".}
  proc `V subf`*(v: V; f: T): V {.solh, importc: astToStr(V) & "_subf".}
  proc `V fsub`*(f: T; v: V): V {.solh, importc: astToStr(V) & "_fsub".}
  proc `V mul`*(a, b: V): V     {.solh, importc: astToStr(V) & "_mul".}
  proc `V mulf`*(v: V; f: T): V {.solh, importc: astToStr(V) & "_mulf".}
  proc `V div`*(a, b: V): V     {.solh, importc: astToStr(V) & "_div".}
  proc `V divf`*(v: V; f: T): V {.solh, importc: astToStr(V) & "_divf".}
  proc `V fdiv`*(f: T; v: V): V {.solh, importc: astToStr(V) & "_fdiv".}
  proc `V fma`*(a, b, c: V): V  {.solh, importc: astToStr(V) & "_fma".}
  proc `V fms`*(a, b, c: V): V  {.solh, importc: astToStr(V) & "_fms".}

FX2(f32, f32x2)
FX2(f64, f64x4)
