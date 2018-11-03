#
# sol.nim | The Sol Vector Library | Nim Bindings
# https://github.com/davidgarland/sol
#

{.pragma: sol, importc, header: "sol.h".}

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
