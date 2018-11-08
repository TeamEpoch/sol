#
# sol.nim | The Sol Vector Library | Nim Bindings
# https://github.com/davidgarland/sol
#

import
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

template FNAME(T: untyped; fn: static[string]): untyped =
  astToStr(T) & "_" & fn

template FEMIT(e: static[string]): untyped =
  macro payload: untyped {.gensym.} =
    result = parseStmt(e)
  payload()

template FX1(T: untyped) =
  proc `T sqrt`*(f: T): T {.solh, importc: FNAME(T, "sqrt").}

  proc `T sin`*(f: T): T      {.solh, importc: FNAME(T, "sin").}
  proc `T cos`*(f: T): T      {.solh, importc: FNAME(T, "cos").}
  proc `T tan`*(f: T): T      {.solh, importc: FNAME(T, "tan").}
  proc `T asin`*(f: T): T     {.solh, importc: FNAME(T, "asin").}
  proc `T acos`*(f: T): T     {.solh, importc: FNAME(T, "acos").}
  proc `T atan`*(f: T): T     {.solh, importc: FNAME(T, "atan").}
  proc `T atan2`*(y, x: T): T {.solh, importc: FNAME(T, "atan2").}

FX1(f32)
FX1(f64)

template FX2*(T, V: untyped) =
  # Vector Scalar Accessors
  proc `x`*(v: V): T {.inline.} = {.emit: ["result = x(", v, ");"].}
  proc `y`*(v: V): T {.inline.} = {.emit: ["result = y(", v, ");"].}
  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  # Initializers
  proc `V set`*(x, y: T): V {.solh, importc: FNAME(V, "set").}
  proc `V setf`*(f: T): V   {.solh, importc: FNAME(V, "setf").}
  proc `V zero`*(): V       {.solh, importc: FNAME(V, "zero").}
  # Vector Transformations
  proc `V rot`*(v: V; rad: T): V {.solh, importc: FNAME(V, "rot").}
  proc `V scale`*(v: V; f: T): V {.solh, importc: FNAME(V, "scale").}
  # Vector math
  proc `V norm`*(v: V): V     {.solh, importc: FNAME(V, "norm").}
  proc `V mag`*(v: V): T      {.solh, importc: FNAME(V, "mag").}
  proc `V proj`*(a, b: V): V  {.solh, importc: FNAME(V, "proj").}
  proc `V rej`*(a, b: V): V   {.solh, importc: FNAME(V, "rej").}
  proc `V angle`*(a, b: V): T {.solh, importc: FNAME(V, "angle").}
  proc `V cross`*(a, b: V): T {.solh, importc: FNAME(V, "cross").}
  proc `V dot`*(a, b: V): T   {.solh, importc: FNAME(V, "dot").}
  # Basic Math
  proc `V sum`*(v: V): T        {.solh, importc: FNAME(V, "sum").}
  proc `V add`*(a, b: V): V     {.solh, importc: FNAME(V, "add").}
  proc `V addf`*(v: V; f: T): V {.solh, importc: FNAME(V, "addf").}
  proc `V sub`*(a, b: V): V     {.solh, importc: FNAME(V, "sub").}
  proc `V subf`*(v: V; f: T): V {.solh, importc: FNAME(V, "subf").}
  proc `V fsub`*(f: T; v: V): V {.solh, importc: FNAME(V, "fsub").}
  proc `V mul`*(a, b: V): V     {.solh, importc: FNAME(V, "mul").}
  proc `V mulf`*(v: V; f: T): V {.solh, importc: FNAME(V, "mulf").}
  proc `V div`*(a, b: V): V     {.solh, importc: FNAME(V, "div").}
  proc `V divf`*(v: V; f: T): V {.solh, importc: FNAME(V, "divf").}
  proc `V fdiv`*(f: T; v: V): V {.solh, importc: FNAME(V, "fdiv").}
  proc `V fma`*(a, b, c: V): V  {.solh, importc: FNAME(V, "fma").}
  proc `V fms`*(a, b, c: V): V  {.solh, importc: FNAME(V, "fms").}

FX2(f32, f32x2)
FX2(f64, f64x2)

template FX3*(T, V, Q: untyped) =
  # Vector Scalar Accessors
  proc `x`*(v: V): T {.inline.} = {.emit: ["result = x(", v, ");"].}
  proc `y`*(v: V): T {.inline.} = {.emit: ["result = y(", v, ");"].}
  proc `z`*(v: V): T {.inline.} = {.emit: ["result = z(", v, ");"].}
  proc `x=`*(v: var V; f: T) {.inline.} = {.emit: ["x(", v, "[0]) = ", f, ";"].}
  proc `y=`*(v: var V; f: T) {.inline.} = {.emit: ["y(", v, "[0]) = ", f, ";"].}
  proc `z=`*(v: var V; f: T) {.inline.} = {.emit: ["z(", v, "[0]) = ", f, ";"].}
  # Initializers
  proc `V set`*(x, y, z: T): V {.solh, importc: FNAME(V, "set").}
  proc `V setf`*(f: T): V      {.solh, importc: FNAME(V, "setf").}
  proc `V zero`*(): V          {.solh, importc: FNAME(V, "zero").}
  # Vector Transformations
  proc `V rot`*(v: V; q: Q): V   {.solh, importc: FNAME(V, "rot").}
  proc `V scale`*(v: V; f: T): V {.solh, importc: FNAME(V, "scale").}
  # Vector Math
  proc `V norm`*(v: V): V     {.solh, importc: FNAME(V, "norm").}
  proc `V mag`*(v: V): T      {.solh, importc: FNAME(V, "mag").}
  proc `V proj`*(a, b: V): V  {.solh, importc: FNAME(V, "proj").}
  proc `V rej`*(a, b: V): V   {.solh, importc: FNAME(V, "rej").}
  proc `V angle`*(a, b: V): T {.solh, importc: FNAME(V, "angle").}
  proc `V cross`*(a, b: V): V {.solh, importc: FNAME(V, "cross").}
  proc `V dot`*(a, b: V): T   {.solh, importc: FNAME(V, "dot").}
  # Basic Math
  proc `V sum`*(v: V): T        {.solh, importc: FNAME(V, "sum").}
  proc `V add`*(a, b: V): V     {.solh, importc: FNAME(V, "add").}
  proc `V addf`*(v: V; f: T): V {.solh, importc: FNAME(V, "addf").}
  proc `V sub`*(a, b: V): V     {.solh, importc: FNAME(V, "sub").}
  proc `V subf`*(v: V; f: T): V {.solh, importc: FNAME(V, "subf").}
  proc `V fsub`*(f: T; v: V): V {.solh, importc: FNAME(V, "fsub").}
  proc `V mul`*(a, b: V): V     {.solh, importc: FNAME(V, "mul").}
  proc `V mulf`*(v: V; f: T): V {.solh, importc: FNAME(V, "mulf").}
  proc `V div`*(a, b: V): V     {.solh, importc: FNAME(V, "div").}
  proc `V divf`*(v: V; f: T): V {.solh, importc: FNAME(V, "divf").}
  proc `V fdiv`*(f: T; v: V): V {.solh, importc: FNAME(V, "fdiv").}
  proc `V fma`*(a, b, c: V): V  {.solh, importc: FNAME(V, "fma").}
  proc `V fms`*(a, b, c: V): V  {.solh, importc: FNAME(V, "fms").}

FX3(f32, f32x3, f32x4)
FX3(f64, f64x3, f64x4)
