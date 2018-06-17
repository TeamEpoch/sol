#                                                    ###########################
# sol.nim | Nim bindings for the Sol vector library. ###########################
# https://github.com/davidgarland/sol                ###########################
#                                                    ###########################

{.
  compile: "c/sol_flt.c"
  compile: "c/sol_conv.c"
  compile: "c/sol_vec2.c"
  compile: "c/sol_vec3.c"
  compile: "c/sol_vec4.c"
  compile: "c/sol_ray2.c"
  compile: "c/sol_ray3.c"
  compile: "c/sol_seg2.c"
  compile: "c/sol_seg3.c"
  compile: "c/sol_mat2.c"
  compile: "c/sol_mat3.c"
  compile: "c/sol_mat4.c"
  passl: "-lm"
  passc: "-DSOL_NO_FAM"
.}

#              #################################################################
# Dependencies #################################################################
#              #################################################################

import strutils

#        #######################################################################
# Config #######################################################################
#        #######################################################################

const sol_epsilon* = 0.000001

when not defined(sol_fsize):
  const sol_fsize*   = 64

#                 ##############################################################
# Config Handling ##############################################################
#                 ##############################################################

when defined(sol_bundled):
  {.passc: "-I.".}
  {.pragma: sol, header: "sol.h".}
else:
  when defined(sol_shared):
    {.passl: "-lsol-so".}
  else:
    {.passl: "-lsol-a".}
  {.pragma: sol, header: "<sol/sol.h>".}

when defined(avx):
    {.passc: "-mavx -mfma -DSOL_AVX".}
elif defined(avx2):
    {.passc: "-mavx2 -mfma -DSOL_AVX -DSOL_AVX2"}
elif defined(neon):
    {.passc: "-mfpu=neon -DSOL_NEON".}
else:
    {.passc: "-DSOL_NO_SIMD".}

#                  #############################################################
# Type Definitions #############################################################
#                  #############################################################

when sol_fsize > 32:
  type Float* {.importc: "Float", sol.} = cdouble
  {.passc: "-DSOL_FSIZE=64".}
else:
  type Float* {.importc: "Float", sol.} = cfloat
  {.passc: "-DSOL_FSIZE=32".}

type Vec2* {.importc: "Vec2", sol, packed, noDecl.} = object

type Vec3* {.importc: "Vec3", sol, packed, noDecl.} = object

type Vec4* {.importc: "Vec4", sol, packed, noDecl.} = object

type Ray2* {.importc: "Ray2", sol.} = object
    pos*, vec*: Vec2

type Ray3* {.importc: "Ray3", sol.} = object
    pos*, vec*: Vec3

type Seg2* {.importc: "Seg2", sol.} = object
    orig*, dest*: Vec2

type Seg3* {.importc: "Seg3", sol.} = object
    orig*, dest*: Vec3

type Mat2* {.importc: "Mat2", sol, union, packed.} = object
    v*: array[2, Vec2]

type Mat3* {.importc: "Mat3", sol, union, packed.} = object
    v*: array[4, Vec3]

type Mat4* {.importc: "Mat4", sol, union, packed.} = object
    v*: array[4, Vec4]

type Box2* {.importc: "Box2", sol.} = object
    lower*, upper*: Vec2

type Box3* {.importc: "Box3", sol.} = object
    lower*, upper*: Vec3

type Sph2* {.importc: "Sph2", sol.} = object
    pos*: Vec2
    rad*: Float

type Sph3* {.importc: "Sph3", sol.} = object
    pos*: Vec3
    rad*: Float

#           ####################################################################
# Constants ####################################################################
#           ####################################################################

const X*: int = 0
const Y*: int = 1
const Z*: int = 3
const W*: int = 4

const sol_pi*:  Float = 3.14159265358979323846
const sol_tau*: Float = 6.28318530717958647692
const sol_g*:   Float = 9.80665
const sol_c*:   Float = 299792000

#                  #############################################################
# Module Functions #############################################################
#                  #############################################################

proc sol_prefetch*[T](p: ptr[T]; rw, locality: cint) {.importc: "sol_prefetch", sol.}

#                 ##############################################################
# Float Functions ##############################################################
#                 ##############################################################

proc flt_clamp*(f, lower, upper: Float): Float {.importc: "flt_clamp", sol.}
proc flt_abs*(f: Float): Float                 {.importc: "flt_abs",   sol.}
proc flt_pow*(a, b: Float): Float              {.importc: "flt_pow",   sol.}
proc flt_sqrt*(f: Float): Float                {.importc: "flt_sqrt",  sol.}
proc flt_sin*(f: Float): Float                 {.importc: "flt_sin",   sol.}
proc flt_cos*(f: Float): Float                 {.importc: "flt_cos",   sol.}
proc flt_acos*(f: Float): Float                {.importc: "flt_acos",  sol.}

#                      #########################################################
# Conversion Functions #########################################################
#                      #########################################################

proc cv_axis_quat*(axis: Vec4): Vec4 {.importc: "cv_axis_quat", sol.}
proc cv_quat_axis*(quat: Vec4): Vec4 {.importc: "cv_quat_axis", sol.}

proc cv_vec3_vec2*(v: Vec3): Vec2              {.importc: "cv_vec3_vec2", sol.}
proc cv_vec4_vec2*(v: Vec4): Vec2              {.importc: "cv_vec4_vec2", sol.}
proc cv_vec2_vec3*(v: Vec2; z: Float): Vec3    {.importc: "cv_vec2_vec3", sol.}
proc cv_vec4_vec3*(v: Vec4): Vec3              {.importc: "cv_vec4_vec3", sol.}
proc cv_vec2_vec4*(v: Vec2; z, w: Float): Vec4 {.importc: "cv_vec2_vec4", sol.}
proc cv_vec3_vec4*(v: Vec3; w: Float): Vec4    {.importc: "cv_vec3_vec4", sol.}

proc cv_deg_rad*(deg: Float): Float {.importc: "cv_deg_rad", sol.}
proc cv_rad_deg*(rad: Float): Float {.importc: "cv_rad_deg", sol.}

#                ###############################################################
# Vec2 Functions ###############################################################
#                ###############################################################

proc `[]`*(v: Vec2; i: int): Float {.inline.} =
  {.emit: [result, " =  ", v, "[", i, "];"].}

proc `[]=`*(v: var Vec2; i: int; f: Float) {.inline.} =
  {.emit: [v, "[0][", i, "] = ", f, ";"].}

proc `$`*(v: Vec2): string {.inline.} =
  result = "(" & v[0].formatFloat & ", " & v[1].formatFloat & ")"

proc x*(v: Vec2): Float {.inline.} =
  {.emit: [result, " = ", v, "[0];"].}

proc y*(v: Vec2): Float {.inline.} =
  {.emit: [result, " = ", v, "[1];"].}

proc `x=`*(v: var Vec2; f: Float) {.inline.} =
  {.emit: [v, "[0][0] = ", f, ";"].}

proc `y=`*(v: var Vec2; f: Float) {.inline.} =
  {.emit: [v, "[0][1] = ", f, ";"].}

proc vec2_init*(x, y: Float): Vec2 {.importc: "vec2_init",  sol.}
proc vec2_initf*(f: Float): Vec2   {.importc: "vec2_initf", sol.}
proc vec2_zero*(): Vec2            {.importc: "vec2_zero",  sol.}

proc vec2_norm*(v: Vec2): Vec2             {.importc: "vec2_norm", sol.}
proc vec2_mag*(v: Vec2): Float             {.importc: "vec2_mag",  sol.}
proc vec2_eq*(a, b: Vec2; ep: Float): bool {.importc: "vec2_eq",   sol.}

proc vec2_rot*(v: Vec2; deg: Float): Vec2  {.importc: "vec2_rot",  sol.}
proc vec2_rotr*(v: Vec2; rad: Float): Vec2 {.importc: "vec2_rotr", sol.}

proc vec2_proj*(a, b: Vec2): Vec2   {.importc: "vec2_proj",  sol.}
proc vec2_rej*(a, b: Vec2): Vec2    {.importc: "vec2_rej",   sol.}
proc vec2_angle*(a, b: Vec2): Float {.importc: "vec2_angle", sol.}
proc vec2_cross*(a, b: Vec2): Float {.importc: "vec2_cross", sol.}
proc vec2_dot*(a, b: Vec2): Float   {.importc: "vec2_dot",   sol.}

proc vec2_sum*(v: Vec2): Float      {.importc: "vec2_sum", sol.}
proc vec2_fma*(a, b, c: Vec2): Vec2 {.importc: "vec2_fma", sol.}
proc vec2_fms*(a, b, c: Vec2): Vec2 {.importc: "vec2_fms", sol.}

proc vec2_add*(a, b: Vec2): Vec2 {.inline.} =
  {.emit: [result, " = ", a, " + ", b, ";"].}

proc vec2_addf*(v: Vec2, f: Float): Vec2 {.inline.} =
  {.emit: [result, " = ", v, " + ", f, ";"].}

proc vec2_sub*(a, b: Vec2): Vec2 {.inline.} =
  {.emit: [result, " = ", a, " - ", b, ";"].}

proc vec2_subf*(v: Vec2, f: Float): Vec2 {.inline.} =
  {.emit: [result, " = ", v, " - ", f, ";"].}

proc vec2_fsub*(f: Float, v: Vec2): Vec2 {.inline.} =
  {.emit: [result, " = ", f, " - ", v, ";"].}

proc vec2_mul*(a, b: Vec2): Vec2 {.inline.} =
  {.emit: [result, " = ", a, " * ", b, ";"].}

proc vec2_mulf*(v: Vec2, f: Float): Vec2 {.inline.} =
  {.emit: [result, " = ", v, " * ", f, ";"].}

proc vec2_div*(a, b: Vec2): Vec2 {.inline.} =
  {.emit: [result, " = ", a, " / ", b, ";"].}

proc vec2_divf*(v: Vec2, f: Float): Vec2 {.inline.} =
  {.emit: [result, " = ", v, " / ", f, ";"].}

proc vec2_fdiv*(f: Float, v: Vec2): Vec2 {.inline.} =
  {.emit: [result, " = ", f, " / ", v, ";"].}

proc vec2_avg*(a, b: Vec2): Vec2         {.importc: "vec2_avg",  sol.}

proc vec2_avgf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_avgf", sol.}

proc vec2_print*(v: Vec2): void          {.importc: "vec2_print", sol.}

#                ###############################################################
# Vec2 Operators ###############################################################
#                ###############################################################

template vec*(x, y: Float): Vec3 = vec2_init(x, y)

template norm*(v: Vec2): Vec2             = vec2_norm(v)
template mag*(v: Vec2): Float             = vec2_mag(v)
template eq*(a, b: Vec2; ep: Float): bool = vec2_eq(a, b, ep)

template proj*(a, b: Vec2): Vec2   = vec2_proj(a, b)
template rej*(a, b: Vec2): Vec2    = vec2_rej(a, b)
template angle*(a, b: Vec2): Float = vec2_angle(a, b)
template cross*(a, b: Vec2): Float = vec2_cross(a, b)
template dot*(a, b: Vec2): Float   = vec2_dot(a, b)

template sum*(v: Vec2): Float = vec2_sum(v)

template `==`*(a, b: Vec2): bool = vec2_eq(a, b, sol_epsilon)

template `+`*(a, b: Vec2): Vec2        = vec2_add(a, b)
template `+`*(v: Vec2; f: Float): Vec2 = vec2_addf(v, f)
template `+`*(f: Float; v: Vec2): Vec2 = vec2_addf(v, f)
template `-`*(a, b: Vec2): Vec2        = vec2_sub(a, b)
template `-`*(v: Vec2; f: Float): Vec2 = vec2_subf(v, f)
template `-`*(f: Float; v: Vec2): Vec2 = vec2_fsub(f, v)
template `*`*(a, b: Vec2): Vec2        = vec2_mul(a, b)
template `*`*(v: Vec2; f: Float): Vec2 = vec2_mulf(v, f)
template `*`*(f: Float; v: Vec2): Vec2 = vec2_mulf(v, f)
template `/`*(a, b: Vec2): Vec2        = vec2_div(a, b)
template `/`*(v: Vec2; f: Float): Vec2 = vec2_divf(v, f)
template `/`*(f: Float; v: Vec2): Vec2 = vec2_fdiv(f, v)

template `+=`*(a: var Vec2; b: Vec2)  = a = vec2_add(a, b)
template `+=`*(v: var Vec2; f: Float) = v = vec2_addf(v, f)
template `-=`*(a: var Vec2; b: Vec2)  = a = vec2_sub(a, b)
template `-=`*(v: var Vec2; f: Float) = v = vec2_subf(v, f)
template `*=`*(a: var Vec2; b: Vec2)  = a = vec2_mul(a, b)
template `*=`*(v: var Vec2; f: Float) = v = vec2_mulf(v, f)
template `/=`*(a: var Vec2; b: Vec2)  = a = vec2_div(a, b)
template `/=`*(v: var Vec2; f: Float) = v = vec2_divf(v, f)

#                   ############################################################
# Vec2 Optimization ############################################################
#                   ############################################################

template vec2_opt_fma*{vec2_add(vec2_mul(a, b), c)}(a, b, c: Vec2): Vec2 =
  vec2_fma(a, b, c)

template vec2_opt_fms*{vec2_sub(vec2_mul(a, b), c)}(a, b, c: Vec2): Vec2 =
  vec2_fms(a, b, c)

#                ###############################################################
# Vec3 Functions ###############################################################
#                ###############################################################

proc `[]`*(v: Vec3; i: int): Float {.inline.} =
  {.emit: [result, " = ", v, "[", i, "];"].}

proc `[]=`*(v: var Vec3; i: int; f: Float) {.inline.} =
  {.emit: [v, "[0][", i, "] = ", f, ";"].}

proc `$`*(v: Vec3): string {.inline.} =
  result = "(" & v[0].formatFloat & ", " & v[1].formatFloat & ", " & v[2].formatFloat & ")"

proc x*(v: Vec3): Float {.inline.} =
  {.emit: [result, " = ", v, "[0];"].}

proc y*(v: Vec3): Float {.inline.} =
  {.emit: [result, " = ", v, "[1];"].}

proc z*(v: Vec3): Float {.inline.} =
  {.emit: [result, " = ", v, "[2];"].}

proc `x=`*(v: var Vec3; f: Float) {.inline.} =
  {.emit: [v, "[0][0] = ", f, ";"].}

proc `y=`*(v: var Vec3; f: Float) {.inline.} =
  {.emit: [v, "[0][1] = ", f, ";"].}

proc `z=`*(v: var Vec3; f: Float) {.inline.} =
  {.emit: [v, "[0][2] = ", f, ";"].}

proc vec3_init*(x, y, z: Float): Vec3 {.importc: "vec3_init",  sol.}
proc vec3_initf*(f: Float): Vec3      {.importc: "vec3_initf", sol.}
proc vec3_zero*(): Vec3               {.importc: "vec3_zero",  sol.}

proc vec3_norm*(v: Vec3): Vec3            {.importc: "vec3_norm", sol.}
proc vec3_mag*(v: Vec3): Float            {.importc: "vec3_mag",  sol.}
proc vec3_eq*(a, b: Vec3; f: Float): bool {.importc: "vec3_eq",   sol.}
proc vec3_yzx*(v: Vec3): Vec3             {.importc: "vec3_yzx",  sol.}

proc vec3_rot*(v: Vec3, aa: Vec4): Vec3 {.importc: "vec3_rot",  sol.}
proc vec3_rotq*(v: Vec3, q: Vec4): Vec3 {.importc: "vec3_rotq", sol.}

proc vec3_proj*(a, b: Vec3): Vec3   {.importc: "vec3_proj",  sol.}
proc vec3_rej*(a, b: Vec3): Vec3    {.importc: "vec3_rej",   sol.}
proc vec3_angle*(a, b: Vec3): Float {.importc: "vec3_angle", sol.}
proc vec3_cross*(a, b: Vec3): Vec3  {.importc: "vec3_cross", sol.}
proc vec3_dot*(a, b: Vec3): Float   {.importc: "vec3_dot",   sol.}

proc vec3_sum*(v: Vec3): Float      {.importc: "vec3_sum", sol.}
proc vec3_fma*(a, b, c: Vec3): Vec3 {.importc: "vec3_fma", sol.}
proc vec3_fms*(a, b, c: Vec3): Vec3 {.importc: "vec3_fms", sol.}


proc vec3_add*(a, b: Vec3): Vec3 {.inline.} =
  {.emit: [result, " = ", a, " + ", b, ";"].}

proc vec3_addf*(v: Vec3, f: Float): Vec3 {.inline.} =
  {.emit: [result, " = ", v, " + ", f, ";"].}

proc vec3_sub*(a, b: Vec3): Vec3 {.inline.} =
  {.emit: [result, " = ", a, " - ", b, ";"].}

proc vec3_subf*(v: Vec3, f: Float): Vec3 {.inline.} =
  {.emit: [result, " = ", v, " - ", f, ";"].}

proc vec3_fsub*(f: Float, v: Vec3): Vec3 {.inline.} =
  {.emit: [result, " = ", f, " - ", v, ";"].}

proc vec3_mul*(a, b: Vec3): Vec3 {.inline.} =
  {.emit: [result, " = ", a, " * ", b, ";"].}

proc vec3_mulf*(v: Vec3, f: Float): Vec3 {.inline.} =
  {.emit: [result, " = ", v, " * ", f, ";"].}

proc vec3_div*(a, b: Vec3): Vec3 {.inline.} =
  {.emit: [result, " = ", a, " / ", b, ";"].}

proc vec3_divf*(v: Vec3, f: Float): Vec3 {.inline.} =
  {.emit: [result, " = ", v, " / ", f, ";"].}

proc vec3_fdiv*(f: Float, v: Vec3): Vec3 {.inline.} =
  {.emit: [result, " = ", f, " / ", v, ";"].}

proc vec3_avg*(a, b: Vec3): Vec3 {.importc: "vec3_avg",  sol.}

proc vec3_avgf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_avgf", sol.}

proc vec3_print*(v: Vec3): void {.importc: "vec3_print", sol.}

#                ###############################################################
# Vec3 Operators ###############################################################
#                ###############################################################

template vec*(x, y, z: Float): Vec3 = vec3_init(x, y, z)

template norm*(v: Vec3): Vec3             = vec3_norm(v)
template mag*(v: Vec3): Float             = vec3_mag(v)
template eq*(a, b: Vec3; ep: Float): bool = vec3_eq(a, b, ep)

template proj*(a, b: Vec3): Vec3   = vec3_proj(a, b)
template rej*(a, b: Vec3): Vec3    = vec3_rej(a, b)
template angle*(a, b: Vec3): Float = vec3_angle(a, b)
template cross*(a, b: Vec3): Vec3  = vec3_cross(a, b)
template dot*(a, b: Vec3): Float   = vec3_dot(a, b)

template sum*(v: Vec3): Float = vec3_sum(v)

template `==`*(a, b: Vec3): bool = vec3_eq(a, b, sol_epsilon)

template `+`*(a, b: Vec3): Vec3        = vec3_add(a, b)
template `+`*(v: Vec3; f: Float): Vec3 = vec3_addf(v, f)
template `+`*(f: Float; v: Vec3): Vec3 = vec3_addf(v, f)
template `-`*(a, b: Vec3): Vec3        = vec3_sub(a, b)
template `-`*(v: Vec3; f: Float): Vec3 = vec3_subf(v, f)
template `-`*(f: Float; v: Vec3): Vec3 = vec3_fsub(f, v)
template `*`*(a, b: Vec3): Vec3        = vec3_mul(a, b)
template `*`*(v: Vec3; f: Float): Vec3 = vec3_mulf(v, f)
template `*`*(f: Float; v: Vec3): Vec3 = vec3_mulf(v, f)
template `/`*(a, b: Vec3): Vec3        = vec3_div(a, b)
template `/`*(v: Vec3; f: Float): Vec3 = vec3_divf(v, f)
template `/`*(f: Float; v: Vec3): Vec3 = vec3_fdiv(f, v)

template `+=`*(a: var Vec3; b: Vec3)  = a = vec3_add(a, b)
template `+=`*(v: var Vec3; f: Float) = v = vec3_addf(v, f)
template `-=`*(a: var Vec3; b: Vec3)  = a = vec3_sub(a, b)
template `-=`*(v: var Vec3; f: Float) = v = vec3_subf(v, f)
template `*=`*(a: var Vec3; b: Vec3)  = a = vec3_mul(a, b)
template `*=`*(v: var Vec3; f: Float) = v = vec3_mulf(v, f)
template `/=`*(a: var Vec3; b: Vec3)  = a = vec3_div(a, b)
template `/=`*(v: var Vec3; f: Float) = v = vec3_divf(v, f)

#                   ############################################################
# Vec3 Optimization ############################################################
#                   ############################################################

template vec3_opt_fma*{vec3_add(vec3_mul(a, b), c)}(a, b, c: Vec3): Vec3 =
  vec3_fma(a, b, c)

template vec3_opt_fms*{vec3_sub(vec3_mul(a, b), c)}(a, b, c: Vec3): Vec3 =
  vec3_fms(a, b, c)

#                ###############################################################
# Vec4 Functions ###############################################################
#                ###############################################################

proc `[]`*(v: Vec4; i: int): Float {.inline.} =
  {.emit: [result, " = ", v, "[", i, "];"].}

proc `[]=`*(v: var Vec4; i: int; f: Float) {.inline.} =
  {.emit: [v, "[0][", i, "] = ", f, ";"].}

proc `$`*(v: Vec4): string {.inline.} =
  result = "(" & v[0].formatFloat & ", " & v[1].formatFloat & ", " & v[2].formatFloat & ", " & v[3].formatFloat & ")"

proc x*(v: Vec4): Float {.inline.} =
  {.emit: [result, " = ", v, "[0];"].}

proc y*(v: Vec4): Float {.inline.} =
  {.emit: [result, " = ", v, "[1];"].}

proc z*(v: Vec4): Float {.inline.} =
  {.emit: [result, " = ", v, "[2];"].}

proc w*(v: Vec4): Float {.inline.} =
  {.emit: [result, " = ", v, "[3];"].}

proc `x=`*(v: var Vec4; f: Float) {.inline.} =
  {.emit: [v, "[0][0] = ", f, ";"].}

proc `y=`*(v: var Vec4; f: Float) {.inline.} =
  {.emit: [v, "[0][1] = ", f, ";"].}

proc `z=`*(v: var Vec4; f: Float) {.inline.} =
  {.emit: [v, "[0][2] = ", f, ";"].}

proc `w=`*(v: var Vec4; f: Float) {.inline.} =
  {.emit: [v, "[0][3] = ", f, ";"].}

proc vec4_init*(x, y, z, w: Float): Vec4 {.importc: "vec4_init",  sol.}
proc vec4_initf*(f: Float): Vec4         {.importc: "vec4_initf", sol.}
proc vec4_zero*(): Vec4                  {.importc: "vec4_zero",  sol.}

proc vec4_norm*(v: Vec4): Vec4             {.importc: "vec4_norm", sol.}
proc vec4_mag*(v: Vec4): Float             {.importc: "vec4_mag",  sol.}
proc vec4_eq*(a, b: Vec4; ep: Float): bool {.importc: "vec4_eq",   sol.}

proc vec4_dot*(a, b: Vec4): Float {.importc: "vec4_dot", sol.}

proc vec4_sum*(v: Vec4): Float      {.importc: "vec4_sum", sol.}
proc vec4_fma*(a, b, c: Vec4): Vec4 {.importc: "vec4_fma", sol.}
proc vec4_fms*(a, b, c: Vec4): Vec4 {.importc: "vec4_fms", sol.}

proc vec4_add*(a, b: Vec4): Vec4 {.inline.} =
  {.emit: [result, " = ", a, " + ", b, ";"].}

proc vec4_addf*(v: Vec4; f: Float): Vec4 {.inline.} =
  {.emit: [result, " = ", v, " + ", f, ";"].}

proc vec4_sub*(a, b: Vec4): Vec4 {.inline.} =
  {.emit: [result, " = ", a, " - ", b, ";"].}

proc vec4_subf*(v: Vec4; f: Float): Vec4 {.inline.}
  = {.emit: [result, " = ", v, " - ", f, ";"].}

proc vec4_fsub*(f: Float; v: Vec4): Vec4 {.inline.} =
  {.emit: [result, " = ", f, " - ", v, ";"].}

proc vec4_mul*(a, b: Vec4): Vec4 {.inline.} =
  {.emit: [result, " = ", a, " * ", b, ";"].}

proc vec4_mulf*(v: Vec4; f: Float): Vec4 {.inline.} =
  {.emit: [result, " = ", v, " * ", f, ";"].}

proc vec4_div*(a, b: Vec4): Vec4 {.inline.} =
  {.emit: [result, " = ", a, " / ", b, ";"].}

proc vec4_divf*(v: Vec4; f: Float): Vec4 {.inline.} =
  {.emit: [result, " = ", v, " / ", f, ";"].}

proc vec4_fdiv*(f: Float; v: Vec4): Vec4 {.inline.} =
  {.emit: [result, " = ", f, " / ", v, ";"].}

proc vec4_avg*(a, b: Vec4): Vec4 {.importc: "vec4_avg",  sol.}

proc vec4_avgf*(v: Vec4, f: Float): Vec4 {.importc: "vec4_avgf", sol.}

proc vec4_print*(v: Vec4): void {.importc: "vec4_print", sol.}

#                ###############################################################
# Vec4 Operators ###############################################################
#                ###############################################################

template vec*(x, y, z, w: Float): Vec4 = vec4_init(x, y, z, w)

template norm*(v: Vec4): Vec4 = vec4_norm(v)
template mag*(v: Vec4): Float = vec4_mag(v)
template eq*(a, b: Vec4; ep: Float): bool = vec4_eq(a, b, ep)

template sum*(v: Vec4): Float = vec4_sum(v)

template `==`*(a, b: Vec4): bool = vec4_eq(a, b, sol_epsilon)

template `+`*(a, b: Vec4): Vec4        = vec4_add(a, b)
template `+`*(v: Vec4; f: Float): Vec4 = vec4_addf(v, f)
template `+`*(f: Float; v: Vec4): Vec4 = vec4_addf(v, f)
template `-`*(a, b: Vec4): Vec4        = vec4_sub(a, b)
template `-`*(v: Vec4; f: Float): Vec4 = vec4_subf(v, f)
template `-`*(f: Float; v: Vec4): Vec4 = vec4_fsub(f, v)
template `*`*(a, b: Vec4): Vec4        = vec4_mul(a, b)
template `*`*(v: Vec4; f: Float): Vec4 = vec4_mulf(v, f)
template `*`*(f: Float; v: Vec4): Vec4 = vec4_mulf(v, f)
template `/`*(a, b: Vec4): Vec4        = vec4_div(a, b)
template `/`*(v: Vec4; f: Float): Vec4 = vec4_divf(v, f)
template `/`*(f: Float; v: Vec4): Vec4 = vec4_fdiv(f, v)

template `+=`*(a: var Vec4; b: Vec4)  = a = vec4_add(a, b)
template `+=`*(v: var Vec4; f: Float) = v = vec4_addf(v, f)
template `-=`*(a: var Vec4; b: Vec4)  = a = vec4_sub(a, b)
template `-=`*(v: var Vec4; f: Float) = v = vec4_subf(v, f)
template `*=`*(a: var Vec4; b: Vec4)  = a = vec4_mul(a, b)
template `*=`*(v: var Vec4; f: Float) = v = vec4_mulf(v, f)
template `/=`*(a: var Vec4; b: Vec4)  = a = vec4_div(a, b)
template `/=`*(v: var Vec4; f: Float) = v = vec4_divf(v, f)

#                   ############################################################
# Vec4 Optimization ############################################################
#                   ############################################################

template vec4_opt_fma*{vec4_add(vec4_mul(a, b), c)}(a, b, c: Vec4): Vec4 =
  vec4_fma(a, b, c)

template vec4_opt_fms*{vec4_sub(vec4_mul(a, b), c)}(a, b, c: Vec4): Vec4 =
  vec4_fms(a, b, c)

#                ###############################################################
# Ray2 Functions ###############################################################
#                ###############################################################

proc ray2_init*(pos, vec: Vec2): Ray2 {.importc: "ray2_init",  sol.}
proc ray2_initv*(v: Vec2): Ray2       {.importc: "ray2_initv", sol.}
proc ray2_initf*(f: Float): Ray2      {.importc: "ray2_initf", sol.}
proc ray2_zero*(): Ray2               {.importc: "ray2_zero",  sol.}

proc ray2_norm*(r: Ray2): Ray2             {.importc: "ray2_norm", sol.}
proc ray2_mag*(r: Ray2): Float             {.importc: "ray2_mag",  sol.}
proc ray2_eq*(a, b: Ray2; ep: Float): bool {.importc: "ray2_eq",   sol.}

proc ray2_rot*(r: Ray2; deg: Float): Ray2  {.importc: "ray2_rot",  sol.}
proc ray2_rotr*(r: Ray2; rad: Float): Ray2 {.importc: "ray2_rotr", sol.}

proc ray2_add*(a, b: Ray2): Ray2         {.importc: "ray2_add",  sol.}
proc ray2_addv*(r: Ray2; v: Vec2): Ray2  {.importc: "ray2_addv", sol.}
proc ray2_addf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_addf", sol.}
proc ray2_sub*(a, b: Ray2): Ray2         {.importc: "ray2_sub",  sol.}
proc ray2_subv*(r: Ray2; v: Vec2): Ray2  {.importc: "ray2_subv", sol.}
proc ray2_vsub*(v: Vec2; r: Ray2): Ray2  {.importc: "ray2_vsub", sol.}
proc ray2_subf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_subf", sol.}
proc ray2_fsub*(f: Float; r: Ray2): Ray2 {.importc: "ray2_fsub", sol.}
proc ray2_mul*(a, b: Ray2): Ray2         {.importc: "ray2_mul",  sol.}
proc ray2_mulv*(r: Ray2; v: Vec2): Ray2  {.importc: "ray2_mulv", sol.}
proc ray2_mulf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_mulf", sol.}
proc ray2_div*(a, b: Ray2): Ray2         {.importc: "ray2_div",  sol.}
proc ray2_divv*(r: Ray2; v: Vec2): Ray2  {.importc: "ray2_divv", sol.}
proc ray2_vdiv*(v: Vec2; r: Ray2): Ray2  {.importc: "ray2_vdiv", sol.}
proc ray2_divf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_divf", sol.}
proc ray2_fdiv*(f: Float; r: Ray2): Ray2 {.importc: "ray2_fdiv", sol.}
proc ray2_avg*(a, b: Ray2): Ray2         {.importc: "ray2_avg",  sol.}
proc ray2_avgv*(r: Ray2; v: Vec2): Ray2  {.importc: "ray2_avgv", sol.}
proc ray2_avgf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_avgf", sol.}

proc ray2_print*(r: Ray2) {.importc: "ray2_print", sol.}

#                ###############################################################
# Ray2 Operators ###############################################################
#                ###############################################################

template `+`*(a, b: Ray2): Ray2        = ray2_add(a, b)
template `+`*(r: Ray2; v: Vec2): Ray2  = ray2_addv(r, v)
template `+`*(v: Vec2; r: Ray2): Ray2  = ray2_addv(r, v)
template `+`*(r: Ray2; f: Float): Ray2 = ray2_addf(r, f)
template `+`*(f: Float; r: Ray2): Ray2 = ray2_addf(r, f)
template `-`*(a, b: Ray2): Ray2        = ray2_sub(a, b)
template `-`*(r: Ray2; v: Vec2): Ray2  = ray2_subv(r, v)
template `-`*(v: Vec2; r: Ray2): Ray2  = ray2_vsub(v, r)
template `-`*(r: Ray2; f: Float): Ray2 = ray2_subf(r, f)
template `-`*(f: Float; r: Ray2): Ray2 = ray2_fsub(f, r)
template `*`*(a, b: Ray2): Ray2        = ray2_mul(a, b)
template `*`*(r: Ray2; v: Vec2): Ray2  = ray2_mulv(r, v)
template `*`*(v: Vec2; r: Ray2): Ray2  = ray2_mulv(r, v)
template `*`*(r: Ray2; f: Float): Ray2 = ray2_mulf(r, f)
template `*`*(f: Float; r: Ray2): Ray2 = ray2_mulf(r, f)
template `/`*(a, b: Ray2): Ray2        = ray2_div(a, b)
template `/`*(r: Ray2; v: Vec2): Ray2  = ray2_divv(r, v)
template `/`*(v: Vec2; r: Ray2): Ray2  = ray2_vdiv(v, r)
template `/`*(r: Ray2; f: Float): Ray2 = ray2_divf(r, f)
template `/`*(f; Float; r: Ray2): Ray2 = ray2_fdiv(f, r)

template `+=`*(a: var Ray2; b: Ray2)  = a = ray2_add(a, b)
template `+=`*(r: var Ray2; v: Vec2)  = r = ray2_addv(r, v)
template `+=`*(r: var Ray2; f: Float) = r = ray2_addf(r, f)
template `-=`*(a: var Ray2; b: Ray2)  = a = ray2_sub(a, b)
template `-=`*(r: var Ray2; v: Vec2)  = r = ray2_subv(r, v)
template `-=`*(r: var Ray2; f: Float) = r = ray2_subf(r, f)
template `*=`*(a: var Ray2; b: Ray2)  = a = ray2_mul(a, b)
template `*=`*(r: var Ray2; v: Vec2)  = r = ray2_mulv(r, v)
template `*=`*(r: var Ray2; f: Float) = r = ray2_mulf(r, f)
template `/=`*(a: var Ray2; b: Ray2)  = a = ray2_div(a, b)
template `/=`*(r: var Ray2; v: Vec2)  = r = ray2_divv(r, v)
template `/=`*(r: var Ray2; f: Float) = r = ray2_divf(r, f)

#                ###############################################################
# Ray3 Functions ###############################################################
#                ###############################################################

proc ray3_init*(pos, vec: Vec3): Ray3 {.importc: "ray3_init",  sol.}
proc ray3_initv*(v: Vec3): Ray3       {.importc: "ray3_initv", sol.}
proc ray3_initf*(f: Float): Ray3      {.importc: "ray3_initf", sol.}
proc ray3_zero*(): Ray3               {.importc: "ray3_zero",  sol.}

proc ray3_norm*(r: Ray3): Ray3             {.importc: "ray3_norm", sol.}
proc ray3_mag*(r: Ray3): Float             {.importc: "ray3_mag",  sol.}
proc ray3_eq*(a, b: Ray3; ep: Float): bool {.importc: "ray3_eq",   sol.}

proc ray3_rot*(r: Ray3; aa: Vec4): Ray3 {.importc: "ray3_rot",  sol.}
proc ray3_rotq*(r: Ray3; q: Vec4): Ray3 {.importc: "ray3_rotq", sol.}

proc ray3_add*(a, b: Ray3): Ray3         {.importc: "ray3_add",  sol.}
proc ray3_addv*(r: Ray3; v: Vec3): Ray3  {.importc: "ray3_addv", sol.}
proc ray3_addf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_addf", sol.}
proc ray3_sub*(a, b: Ray3): Ray3         {.importc: "ray3_sub",  sol.}
proc ray3_subv*(r: Ray3; v: Vec3): Ray3  {.importc: "ray3_subv", sol.}
proc ray3_vsub*(v: Vec3; r: Ray3): Ray3  {.importc: "ray3_vsub", sol.}
proc ray3_subf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_subf", sol.}
proc ray3_fsub*(f: Float; r: Ray3): Ray3 {.importc: "ray3_fsub", sol.}
proc ray3_mul*(a, b: Ray3): Ray3         {.importc: "ray3_mul",  sol.}
proc ray3_mulv*(r: Ray3; v: Vec3): Ray3  {.importc: "ray3_mulv", sol.}
proc ray3_mulf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_mulf", sol.}
proc ray3_div*(a, b: Ray3): Ray3         {.importc: "ray3_div",  sol.}
proc ray3_divv*(r: Ray3; v: Vec3): Ray3  {.importc: "ray3_divv", sol.}
proc ray3_vdiv*(v: Vec3; r: Ray3): Ray3  {.importc: "ray3_vdiv", sol.}
proc ray3_divf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_divf", sol.}
proc ray3_fdiv*(f: Float; r: Ray3): Ray3 {.importc: "ray3_fdiv", sol.}
proc ray3_avg*(a, b: Ray3): Ray3         {.importc: "ray3_avg",  sol.}
proc ray3_avgv*(r: Ray3; v: Vec3): Ray3  {.importc: "ray3_avgv", sol.}
proc ray3_avgf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_avgf", sol.}

proc ray3_print*(r: Ray3) {.importc: "ray3_print", sol.}

#                ###############################################################
# Ray3 Operators ###############################################################
#                ###############################################################

template `+`*(a, b: Ray3): Ray3        = ray3_add(a, b)
template `+`*(r: Ray3; v: Vec3): Ray3  = ray3_addv(r, v)
template `+`*(v: Vec3; r: Ray3): Ray3  = ray3_addv(r, v)
template `+`*(r: Ray3; f: Float): Ray3 = ray3_addf(r, f)
template `+`*(f: Float; r: Ray3): Ray3 = ray3_addf(r, f)
template `-`*(a, b: Ray3): Ray3        = ray3_sub(a, b)
template `-`*(r: Ray3; v: Vec3): Ray3  = ray3_subv(r, v)
template `-`*(v: Vec3; r: Ray3): Ray3  = ray3_vsub(v, r)
template `-`*(r: Ray3; f: Float): Ray3 = ray3_subf(r, f)
template `-`*(f: Float; r: Ray3): Ray3 = ray3_fsub(f, r)
template `*`*(a, b: Ray3): Ray3        = ray3_mul(a, b)
template `*`*(r: Ray3; v: Vec3): Ray3  = ray3_mulv(r, v)
template `*`*(v: Vec3; r: Ray3): Ray3  = ray3_mulv(r, v)
template `*`*(r: Ray3; f: Float): Ray3 = ray3_mulf(r, f)
template `*`*(f: Float; r: Ray3): Ray3 = ray3_mulf(r, f)
template `/`*(a, b: Ray3): Ray3        = ray3_div(a, b)
template `/`*(r: Ray3; v: Vec3): Ray3  = ray3_divv(r, v)
template `/`*(v: Vec3; r: Ray3): Ray3  = ray3_vdiv(v, r)
template `/`*(r: Ray3; f: Float): Ray3 = ray3_divf(r, f)
template `/`*(f: Float; r: Ray3): Ray3 = ray3_fdiv(f, r)

template `+=`*(a: var Ray3; b: Ray3)  = a = ray3_add(a, b)
template `+=`*(r: var Ray3; v: Vec3)  = r = ray3_addv(r, v)
template `+=`*(r: var Ray3; f: Float) = r = ray3_addf(r, f)
template `-=`*(a: var Ray3; b: Ray3)  = a = ray3_sub(a, b)
template `-=`*(r: var Ray3; v: Vec3)  = r = ray2_subv(r, v)
template `-=`*(r: var Ray3; f: Float) = r = ray2_subf(r, f)
template `*=`*(a: var Ray3; b: Ray3)  = a = ray3_mul(a, b)
template `*=`*(r: var Ray3; v: Vec3)  = r = ray3_mulv(r, v)
template `*=`*(r: var Ray3; f: Float) = r = ray3_mulf(r, f)
template `/=`*(a: var Ray3; b: Ray3)  = a = ray3_div(a, b)
template `/=`*(r: var Ray3; v: Vec3)  = r = ray3_divv(r, v)
template `/=`*(r: var Ray3; f: Float) = r = ray3_divf(r, f)

#                ###############################################################
# Seg2 Functions ###############################################################
#                ###############################################################

proc seg2_init*(orig, dest: Vec2): Seg2 {.importc: "seg2_init",  sol.}
proc seg2_initv*(v: Vec2): Seg2         {.importc: "seg2_initv", sol.}
proc seg2_initf*(f: Float): Seg2        {.importc: "seg2_initf", sol.}
proc seg2_zero*(): Seg2                 {.importc: "seg2_zero",  sol.}

proc seg2_add*(a, b: Seg2): Seg2         {.importc: "seg2_add",  sol.}
proc seg2_addv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_addv", sol.}
proc seg2_addf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_addf", sol.}
proc seg2_sub*(a, b: Seg2): Seg2         {.importc: "seg2_sub",  sol.}
proc seg2_subv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_subv", sol.}
proc seg2_vsub*(v: Vec2; s: Seg2): Seg2  {.importc: "seg2_vsub", sol.}
proc seg2_subf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_subf", sol.}
proc seg2_fsub*(f: Float; s: Seg2): Seg2 {.importc: "seg2_fsub", sol.}
proc seg2_mul*(a, b: Seg2): Seg2         {.importc: "seg2_mul",  sol.}
proc seg2_mulv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_mulv", sol.}
proc seg2_mulf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_mulf", sol.}
proc seg2_div*(a, b: Seg2): Seg2         {.importc: "seg2_div",  sol.}
proc seg2_divv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_divv", sol.}
proc seg2_vdiv*(v: Vec2; s: Seg2): Seg2  {.importc: "seg2_vdiv", sol.}
proc seg2_divf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_divf", sol.}
proc seg2_fdiv*(f: Float; s: Seg2): Seg2 {.importc: "seg2_fdiv", sol.}
proc seg2_avg*(a, b: Seg2): Seg2         {.importc: "seg2_avg",  sol.}
proc seg2_avgv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_avgv", sol.}
proc seg2_avgf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_avgf", sol.}

#                ###############################################################
# Seg2 Operators ###############################################################
#                ###############################################################

template `+`*(a, b: Seg2): Seg2        = seg2_add(a, b)
template `+`*(s: Seg2; v: Vec2): Seg2  = seg2_addv(s, v)
template `+`*(v: Vec2; s: Seg2): Seg2  = seg2_addv(s, v)
template `+`*(s: Seg2; f: Float): Seg2 = seg2_addf(s, f)
template `+`*(f: Float; s: Seg2): Seg2 = seg2_addf(s, f)
template `-`*(a, b: Seg2): Seg2        = seg2_sub(a, b)
template `-`*(s: Seg2; v: Vec2): Seg2  = seg2_subv(s, v)
template `-`*(v: Vec2; s: Seg2): Seg2  = seg2_vsub(v, s)
template `-`*(s: Seg2; f: Float): Seg2 = seg2_subf(s, f)
template `-`*(f: Float; s: Seg2): Seg2 = seg2_fsub(f, s)
template `*`*(a, b: Seg2): Seg2        = seg2_mul(a, b)
template `*`*(s: Seg2; v: Vec2): Seg2  = seg2_mulv(s, v)
template `*`*(v: Vec2; s: Seg2): Seg2  = seg2_mulv(s, v)
template `*`*(s: Seg2; f: Float): Seg2 = seg2_mulf(s, f)
template `*`*(f: Float; s: Seg2): Seg2 = seg2_mulf(s, f)
template `/`*(a, b: Seg2): Seg2        = seg2_div(a, b)
template `/`*(s: Seg2; v: Vec2): Seg2  = seg2_divv(s, v)
template `/`*(v: Vec2; s: Seg2): Seg2  = seg2_vdiv(v, s)
template `/`*(s: Seg2; f: Float): Seg2 = seg2_divf(s, f)
template `/`*(f: Float; s: Seg2): Seg2 = seg2_fdiv(f, s)

template `+=`*(a: var Seg2; b: Seg2)  = a = seg2_add(a, b)
template `+=`*(s: var Seg2; v: Vec2)  = s = seg2_addv(s, v)
template `+=`*(s: var Seg2; f: Float) = s = seg2_addf(s, f)
template `-=`*(a: var Seg2; b: Seg2)  = a = seg2_sub(a, b)
template `-=`*(s: var Seg2; v: Vec2)  = s = seg2_subv(s, v)
template `-=`*(s: var Seg2; f: Float) = s = seg2_subf(s, f)
template `*=`*(a: var Seg2; b: Seg2)  = a = seg2_mul(a, b)
template `*=`*(s: var Seg2; v: Vec2)  = s = seg2_mulv(s, v)
template `*=`*(s: var Seg2; f: Float) = s = seg2_mulf(s, f)
template `/=`*(a: var Seg2; b: Seg2)  = a = seg2_div(a, b)
template `/=`*(s: var Seg2; v: Vec2)  = s = seg2_divv(s, v)
template `/=`*(s: var Seg2; f: Float) = s = seg2_divf(s, f)

#                ###############################################################
# Seg3 Functions ###############################################################
#                ###############################################################

proc seg3_init*(orig, dest: Vec3): Seg3 {.importc: "seg3_init",  sol.}
proc seg3_initv*(v: Vec3): Seg3         {.importc: "seg3_initv", sol.}
proc seg3_initf*(f: Float): Seg3        {.importc: "seg3_initf", sol.}
proc seg3_zero*(): Seg3                 {.importc: "seg3_zero",  sol.}

proc seg3_add*(a, b: Seg3): Seg3         {.importc: "seg3_add",  sol.}
proc seg3_addv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_addv", sol.}
proc seg3_addf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_addf", sol.}
proc seg3_sub*(a, b: Seg3): Seg3         {.importc: "seg3_sub",  sol.}
proc seg3_subv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_subv", sol.}
proc seg3_vsub*(v: Vec3; s: Seg3): Seg3  {.importc: "seg3_vsub", sol.}
proc seg3_subf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_subf", sol.}
proc seg3_fsub*(f: Float; s: Seg3): Seg3 {.importc: "seg3_fsub", sol.}
proc seg3_mul*(a, b: Seg3): Seg3         {.importc: "seg3_mul",  sol.}
proc seg3_mulv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_mulv", sol.}
proc seg3_mulf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_mulf", sol.}
proc seg3_div*(a, b: Seg3): Seg3         {.importc: "seg3_div",  sol.}
proc seg3_divv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_divv", sol.}
proc seg3_vdiv*(v: Vec3; s: Seg3): Seg3  {.importc: "seg3_vdiv", sol.}
proc seg3_divf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_divf", sol.}
proc seg3_fdiv*(f: Float; s: Seg3): Seg3 {.importc: "seg3_fdiv", sol.}
proc seg3_avg*(a, b: Seg3): Seg3         {.importc: "seg3_avg",  sol.}
proc seg3_avgv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_avgv", sol.}
proc seg3_avgf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_avgf", sol.}

#                ###############################################################
# Seg3 Operators ###############################################################
#                ###############################################################

template `+`*(a, b: Seg3): Seg3        = seg3_add(a, b)
template `+`*(s: Seg3; v: Vec3): Seg3  = seg3_addv(s, v)
template `+`*(v: Vec3; s: Seg3): Seg3  = seg3_addv(s, v)
template `+`*(s: Seg3; f: Float): Seg3 = seg3_addf(s, f)
template `+`*(f: Float; s: Seg3): Seg3 = seg3_addf(s, f)
template `-`*(a, b: Seg2): Seg3        = seg3_sub(a, b)
template `-`*(s: Seg3; v: Vec3): Seg3  = seg3_subv(s, v)
template `-`*(v: Vec3; s: Seg3): Seg3  = seg3_vsub(v, s)
template `-`*(s: Seg3; f: Float): Seg3 = seg3_subf(s, f)
template `-`*(f: Float; s: Seg3): Seg3 = seg3_fsub(f, s)
template `*`*(a, b: Seg3): Seg3        = seg3_mul(a, b)
template `*`*(s: Seg3; v: Vec3): Seg3  = seg3_mulv(s, v)
template `*`*(v: Vec3; s: Seg3): Seg3  = seg3_mulv(s, v)
template `*`*(s: Seg3; f: Float): Seg3 = seg3_mulf(s, f)
template `*`*(f: Float; s: Seg3): Seg3 = seg3_mulf(s, f)
template `/`*(a, b: Seg3): Seg3        = seg3_div(a, b)
template `/`*(s: Seg3; v: Vec3): Seg3  = seg3_divv(s, v)
template `/`*(v: Vec3; s: Seg3): Seg3  = seg3_vdiv(v, s)
template `/`*(s: Seg3; f: Float): Seg3 = seg3_divf(s, f)
template `/`*(f: Float; s: Seg3): Seg3 = seg3_fdiv(f, s)

template `+=`*(a: var Seg3; b: Seg3)  = a = seg3_add(a, b)
template `+=`*(s: var Seg3; v: Vec3)  = s = seg3_addv(s, v)
template `+=`*(s: var Seg3; f: Float) = s = seg3_addf(s, f)
template `-=`*(a: var Seg3; b: Seg3)  = a = seg3_sub(a, b)
template `-=`*(s: var Seg3; v: Vec3)  = s = seg3_subv(s, v)
template `-=`*(s: var Seg3; f: Float) = s = seg3_subf(s, f)
template `*=`*(a: var Seg3; b: Seg3)  = a = seg3_mul(a, b)
template `*=`*(s: var Seg3; v: Vec3)  = s = seg3_mulv(s, v)
template `*=`*(s: var Seg3; f: Float) = s = seg3_mulf(s, f)
template `/=`*(a: var Seg3; b: Seg3)  = a = seg3_div(a, b)
template `/=`*(s: var Seg3; v: Vec3)  = s = seg3_divv(s, v)
template `/=`*(s: var Seg3; f: Float) = s = seg3_divf(s, f)

#                ###############################################################
# Mat2 Functions ###############################################################
#                ###############################################################

proc `[]`*(m: var Mat2; row, col: int): Float {.inline.} = m.v[row][col]

proc `[]=`*(m: var Mat2; row, col: int; f: Float) {.inline.} = m.v[row][col] = f

proc mat2_init*(f11, f12, f21, f22: Float): Mat2 {.importc: "mat2_init",  sol.}
proc mat2_initv*(v1, v2: Vec2): Mat2             {.importc: "mat2_initv", sol.}
proc mat2_initf*(f: Float): Mat2                 {.importc: "mat2_initf", sol.}
proc mat2_iden*(): Mat2                          {.importc: "mat2_iden",  sol.}
proc mat2_zero*(): Mat2                          {.importc: "mat2_zero",  sol.}

proc mat2_row*(m: Mat2; row: csize): Vec2     {.importc: "mat2_row", sol.}
proc mat2_col*(m: Mat2; col: csize): Vec2     {.importc: "mat2_col", sol.}
proc mat2_f*(m: Mat2; row, col: csize): Float {.importc: "mat2_f",   sol.}

proc mat2_dot*(a, b: Mat2): Mat2 {.importc: "mat2_dot", sol.}

proc mat2_fma*(a, b, c: Mat2): Mat2      {.importc: "mat2_fma",  sol.}
proc mat2_fms*(a, b, c: Mat2): Mat2      {.importc: "mat2_fms",  sol.}
proc mat2_add*(a, b: Mat2): Mat2         {.importc: "mat2_add",  sol.}
proc mat2_addf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_addf", sol.}
proc mat2_sub*(a, b: Mat2): Mat2         {.importc: "mat2_sub",  sol.}
proc mat2_subf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_subf", sol.}
proc mat2_fsub*(f: Float; m: Mat2): Mat2 {.importc: "mat2_fsub", sol.}
proc mat2_mul*(a, b: Mat2): Mat2         {.importc: "mat2_mul",  sol.}
proc mat2_mulf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_mulf", sol.}
proc mat2_div*(a, b: Mat2): Mat2         {.importc: "mat2_div",  sol.}
proc mat2_divf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_divf", sol.}
proc mat2_fdiv*(f: Float; m: Mat2): Mat2 {.importc: "mat2_fdiv", sol.}
proc mat2_avg*(a, b: Mat2): Mat2         {.importc: "mat2_avg",  sol.}
proc mat2_avgf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_avgf", sol.}

proc mat2_print*(m: Mat2): void {.importc: "mat2_print", sol.}

#                ###############################################################
# Mat2 Operators ###############################################################
#                ###############################################################

template mat*(f11, f12, f21, f22: Float): Mat2 =
  mat2_init(f11, f12, f21, f22)

template row*(m: Mat2; row: csize): Vec2     = mat2_row(m, row)
template col*(m: Mat2; col: csize): Vec2     = mat2_col(m, col)
template f*(m: Mat2; row, col: csize): Float = mat2_f(m, row, col)

template dot*(a, b: Mat2): Mat2 = mat2_dot(a, b)

template `+`*(a, b: Mat2): Mat2        = mat2_add(a, b)
template `+`*(m: Mat2; f: Float): Mat2 = mat2_addf(m, f)
template `+`*(f: Float; m: Mat2): Mat2 = mat2_addf(m, f)
template `-`*(a, b: Mat2): Mat2        = mat2_sub(a, b)
template `-`*(m: Mat2; f: Float): Mat2 = mat2_subf(m, f)
template `-`*(f: Float; m: Mat2): Mat2 = mat2_fsub(f, m)
template `*`*(a, b: Mat2): Mat2        = mat2_mul(a, b)
template `*`*(m: Mat2; f: Float): Mat2 = mat2_mulf(m, f)
template `*`*(f: Float; m: Mat2): Mat2 = mat2_mulf(m, f)
template `/`*(a, b: Mat2): Mat2        = mat2_div(a, b)
template `/`*(m: Mat2; f: Float): Mat2 = mat2_divf(m, f)
template `/`*(f: Float; m: Mat2): Mat2 = mat2_fdiv(f, m)

template `+=`*(a: var Mat2; b: Mat2) =  a = mat2_add(a, b)
template `+=`*(v: var Mat2; f: Float) = v = mat2_addf(v, f)
template `-=`*(a: var Mat2; b: Mat2) =  a = mat2_sub(a, b)
template `-=`*(v: var Mat2; f: Float) = v = mat2_subf(v, f)
template `*=`*(a: var Mat2; b: Mat2) =  a = mat2_mul(a, b)
template `*=`*(v: var Mat2; f: Float) = v = mat2_mulf(v, f)
template `/=`*(a: var Mat2; b: Mat2) =  a = mat2_div(a, b)
template `/=`*(v: var Mat2; f: Float) = v = mat2_divf(v, f)

#                    ###########################################################
# Mat2 Optimizations ###########################################################
#                    ###########################################################

template mat2_opt_fma*{mat2_add(mat2_mul(a, b), c)}(a, b, c: Mat2): Mat2 =
  mat2_fma(a, b, c)

template mat2_opt_fms*{mat2_sub(mat2_mul(a, b), c)}(a, b, c: Mat2): Mat2 =
  mat2_fms(a, b, c)

#                ###############################################################
# Mat3 Functions ###############################################################
#                ###############################################################

proc `[]`*(m: Mat3; row, col: int): Float {.inline.} = m.v[row][col]

proc `[]=`*(m: var Mat3; row, col: int; f: Float) {.inline.} = m.v[row][col] = f

proc mat3_init*(f11, f12, f13, f21, f22, f23, f31, f32, f33: Float): Mat3 {.importc: "mat3_init",  sol.}
proc mat3_initv*(v1, v2, v3: Vec3): Mat3                                  {.importc: "mat3_initv", sol.}
proc mat3_initf*(f: Float): Mat3                                          {.importc: "mat3_initf", sol.}
proc mat3_iden*(): Mat3                                                   {.importc: "mat3_iden",  sol.}
proc mat3_zero*(): Mat3                                                   {.importc: "mat3_zero",  sol.}

proc mat3_row*(m: Mat3; row: csize): Vec3     {.importc: "mat3_row", sol.}
proc mat3_col*(m: Mat3; col: csize): Vec3     {.importc: "mat3_col", sol.}
proc mat3_f*(m: Mat3; row, col: csize): Float {.importc: "mat3_f",   sol.}

proc mat3_dot*(a, b: Mat3): Mat3 {.importc: "mat3_dot", sol.}

proc mat3_fma*(a, b, c: Mat3): Mat3      {.importc: "mat3_fma",  sol.}
proc mat3_fms*(a, b, c: Mat3): Mat3      {.importc: "mat3_fms",  sol.}
proc mat3_add*(a, b: Mat3): Mat3         {.importc: "mat3_add",  sol.}
proc mat3_addf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_addf", sol.}
proc mat3_sub*(a, b: Mat3): Mat3         {.importc: "mat3_sub",  sol.}
proc mat3_subf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_subf", sol.}
proc mat3_fsub*(f: Float; m: Mat3): Mat3 {.importc: "mat3_fsub", sol.}
proc mat3_mul*(a, b: Mat3): Mat3         {.importc: "mat3_mul",  sol.}
proc mat3_mulf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_mulf", sol.}
proc mat3_div*(a, b: Mat3): Mat3         {.importc: "mat3_div",  sol.}
proc mat3_divf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_divf", sol.}
proc mat3_fdiv*(f: Float; m: Mat3): Mat3 {.importc: "mat3_fdiv", sol.}
proc mat3_avg*(a, b: Mat3): Mat3         {.importc: "mat3_avg",  sol.}
proc mat3_avgf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_avgf", sol.}

proc mat3_print*(m: Mat3): void {.importc: "mat3_print", sol.}

#                ###############################################################
# Mat3 Operators ###############################################################
#                ###############################################################

template mat*(f11, f12, f13, f21, f22, f23, f31, f32, f33: Float): Mat3 =
  mat3_init(f11, f12, f13, f21, f22, f23, f31, f32, f33)

template row*(m: Mat3; row: csize): Vec3     = mat3_row(m, row)
template col*(m: Mat3; col: csize): Vec3     = mat3_col(m, col)
template f*(m: Mat3; row, col: csize): Float = mat3_f(m, row, col)

template dot*(a, b: Mat3): Mat3 = mat3_dot(a, b)

template `+`*(a, b: Mat3): Mat3        = mat3_add(a, b)
template `+`*(m: Mat3; f: Float): Mat3 = mat3_addf(m, f)
template `+`*(f: Float; m: Mat3): Mat3 = mat3_addf(m, f)
template `-`*(a, b: Mat3): Mat3        = mat3_sub(a, b)
template `-`*(m: Mat3; f: Float): Mat3 = mat3_subf(m, f)
template `-`*(f: Float; m: Mat3): Mat3 = mat3_fsub(f, m)
template `*`*(a, b: Mat3): Mat3        = mat3_mul(a, b)
template `*`*(m: Mat3; f: Float): Mat3 = mat3_mulf(m, f)
template `*`*(f: Float; m: Mat3): Mat3 = mat3_mulf(m, f)
template `/`*(a, b: Mat3): Mat3        = mat3_div(a, b)
template `/`*(m: Mat3; f: Float): Mat3 = mat3_divf(m, f)
template `/`*(f: Float; m: Mat3): Mat3 = mat3_fdiv(f, m)

template `+=`*(a: var Mat3; b: Mat3)  = a = mat3_add(a, b)
template `+=`*(m: var Mat3; f: Float) = m = mat3_addf(m, f)
template `-=`*(a: var Mat3; b: Mat3)  = a = mat3_sub(a, b)
template `-=`*(m: var Mat3; f: Float) = m = mat3_subf(m, f)
template `*=`*(a: var Mat3; b: Mat3)  = a = mat3_mul(a, b)
template `*=`*(m: var Mat3; f: Float) = m = mat3_mulf(m, f)
template `/=`*(a: var Mat3; b: Mat3)  = a = mat3_div(a, b)
template `/=`*(m: var Mat3; f: Float) = m = mat3_divf(m, f)

#                    ###########################################################
# Mat3 Optimizations ###########################################################
#                    ###########################################################

template mat3_opt_fma*{mat3_add(mat3_mul(a, b), c)}(a, b, c: Mat3): Mat3 =
  mat3_fma(a, b, c)

template mat3_opt_fms*{mat3_sub(mat3_mul(a, b), c)}(a, b, c: Mat3): Mat3 =
  mat3_fms(a, b, c)

#                ###############################################################
# Mat4 Functions ###############################################################
#                ###############################################################

proc `[]`*(m: Mat4; row, col: int): Float {.inline.} = m.v[row][col]

proc `[]=`*(m: var Mat4; row, col: int; f: Float) {.inline.} = m.v[row][col] = f

proc mat4_init*(f11, f12, f13, f14, f21, f22, f23, f24, f31, f32, f33, f34, f41, f42, f43, f44: Float): Mat4 {.importc: "mat4_init",  sol.}
proc mat4_initv*(v1, v2, v3, v4: Vec4): Mat4                                                                 {.importc: "mat4_initv", sol.}
proc mat4_initf*(f: Float): Mat4                                                                             {.importc: "mat4_initf", sol.}
proc mat4_iden*(): Mat4                                                                                      {.importc: "mat4_iden",  sol.}
proc mat4_zero*(): Mat4                                                                                      {.importc: "mat4_zero",  sol.}

proc mat4_row*(m: Mat4; row: csize): Vec4     {.importc: "mat4_row", sol.}
proc mat4_col*(m: Mat4; col: csize): Vec4     {.importc: "mat4_col", sol.}
proc mat4_f*(m: Mat4; row, col: csize): Float {.importc: "mat4_f", sol.}

proc mat4_dot*(a, b: Mat4): Mat4 {.importc: "mat4_dot", sol.}

proc mat4_fma*(a, b, c: Mat4): Mat4      {.importc: "mat4_fma",  sol.}
proc mat4_fms*(a, b, c: Mat4): Mat4      {.importc: "mat4_fms",  sol.}
proc mat4_add*(a, b: Mat4): Mat4         {.importc: "mat4_add",  sol.}
proc mat4_addf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_addf", sol.}
proc mat4_sub*(a, b: Mat4): Mat4         {.importc: "mat4_sub",  sol.}
proc mat4_subf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_subf", sol.}
proc mat4_fsub*(f: Float; m: Mat4): Mat4 {.importc: "mat4_fsub", sol.}
proc mat4_mul*(a, b: Mat4): Mat4         {.importc: "mat4_mul",  sol.}
proc mat4_mulf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_mulf", sol.}
proc mat4_div*(a, b: Mat4): Mat4         {.importc: "mat4_div",  sol.}
proc mat4_divf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_divf", sol.}
proc mat4_fdiv*(f: Float; m: Mat4): Mat4 {.importc: "mat4_fdiv", sol.}
proc mat4_avg*(a, b: Mat4): Mat4         {.importc: "mat4_avg",  sol.}
proc mat4_avgf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_avgf", sol.}

proc mat4_print*(m: Mat4): Mat4 {.importc: "mat4_print", sol.}

#                ###############################################################
# Mat4 Operators ###############################################################
#                ###############################################################

template mat*(f11, f12, f13, f14, f21, f22, f23, f24, f31, f32, f33, f34, f41, f42, f43, f44: Float): Mat4 =
  mat4_init(f11, f12, f13, f14, f21, f22, f23, f24, f31, f32, f33, f34, f41, f42, f43, f44)

template row*(m: Mat4; row; csize): Vec4     = mat4_row(m, row)
template col*(m: Mat4; col: csize): Vec4     = mat4_col(m, col)
template f*(m: Mat4; row, col: csize): Float = mat4_f(m, row, col)

template dot*(a, b: Mat4): Mat4 = mat4_dot(a, b)

template `+`*(a, b: Mat4): Mat4        = mat4_add(a, b)
template `+`*(m: Mat4; f: Float): Mat4 = mat4_addf(m, f)
template `+`*(f: Float; m: Mat4): Mat4 = mat4_addf(m, f)
template `-`*(a, b: Mat4): Mat4        = mat4_sub(a, b)
template `-`*(m: Mat4; f: Float): Mat4 = mat4_subf(m, f)
template `-`*(f: Float; m: Mat4): Mat4 = mat4_fsub(f, m)
template `*`*(a, b: Mat4): Mat4        = mat4_mul(a, b)
template `*`*(m: Mat4; f: Float): Mat4 = mat4_mulf(m, f)
template `*`*(f: Float; m: Mat4): Mat4 = mat4_mulf(m, f)
template `/`*(a, b: Mat4): Mat4        = mat4_div(a, b)
template `/`*(m: Mat4; f: Float): Mat4 = mat4_divf(m, f)
template `/`*(f: Float; m: Mat4): Mat4 = mat4_fdiv(f, m)

template `+=`*(a: var Mat4; b: Mat4)  = a = mat4_add(a, b)
template `+=`*(m: var Mat4; f: Float) = m = mat4_addf(m, f)
template `-=`*(a: var Mat4; b: Mat4)  = a = mat4_sub(a, b)
template `-=`*(m: var Mat4; f: Float) = m = mat4_subf(m, f)
template `*=`*(a: var Mat4; b: Mat4)  = a = mat4_mul(a, b)
template `*=`*(m: var Mat4; f: Float) = m = mat4_mulf(m, f)
template `/=`*(a: var Mat4; b: Mat4)  = a = mat4_div(a, b)
template `/=`*(m: var Mat4; f: Float) = m = mat4_divf(m, f)

#                    ###########################################################
# Mat4 Optimizations ###########################################################
#                    ###########################################################

template mat4_opt_fma*{mat4_add(mat4_mul(a, b), c)}(a, b, c: Mat4): Mat4 =
  mat4_fma(a, b, c)

template mat4_opt_fms*{mat4_sub(mat4_mul(a, b), c)}(a, b, c: Mat4): Mat4 =
  mat4_fms(a, b, c)

#                ###############################################################
# Box2 Functions ###############################################################
#                ###############################################################

proc box2_init*(lower, upper: Vec2): Box2 {.importc: "box2_init",  sol.}
proc box2_initv*(v: Vec2): Box2           {.importc: "box2_initv", sol.}
proc box2_initf*(f: Float): Box2          {.importc: "box2_initf", sol.}
proc box2_zero*(): Box2                   {.importc: "box2_zero",  sol.}

proc box2_pos*(b: Box2): Vec2 {.importc: "box2_pos", sol.}
proc box2_x*(b: Box2): Float  {.importc: "box2_x",   sol.}
proc box2_y*(b: Box2): Float  {.importc: "box2_y",   sol.}

proc box2_aabb*(a, b: Box2): bool      {.importc: "box2_aabb", sol.}
proc box2_pip*(b: Box2; v: Vec2): bool {.importc: "box2_pip",  sol.}

proc box2_add*(a, b: Box2): Box2         {.importc: "box2_add",  sol.}
proc box2_addv*(b: Box2; v: Vec2): Box2  {.importc: "box2_addv", sol.}
proc box2_addf*(b: Box2; f: Float): Box2 {.importc: "box2_addf", sol.}
proc box2_sub*(a, b: Box2): Box2         {.importc: "box2_sub",  sol.}
proc box2_subv*(b: Box2; v: Vec2): Box2  {.importc: "box2_subv", sol.}
proc box2_vsub*(v: Vec2; b: Box2): Box2  {.importc: "box2_vsub", sol.}
proc box2_subf*(b: Box2; f: Float): Box2 {.importc: "box2_subf", sol.}
proc box2_fsub*(f: Float; b: Box2): Box2 {.importc: "box2_fsub", sol.}
proc box2_mul*(a, b: Box2): Box2         {.importc: "box2_mul",  sol.}
proc box2_mulv*(b: Box2; v: Vec2): Box2  {.importc: "box2_mulv", sol.}
proc box2_mulf*(b: Box2; f: Float): Box2 {.importc: "box2_mulf", sol.}
proc box2_div*(a, b: Box2): Box2         {.importc: "box2_div",  sol.}
proc box2_divv*(b: Box2; v: Vec2): Box2  {.importc: "box2_divv", sol.}
proc box2_vdiv*(v: Vec2; b: Box2): Box2  {.importc: "box2_vdiv", sol.}
proc box2_divf*(b: Box2; f: Float): Box2 {.importc: "box2_divf", sol.}
proc box2_fdiv*(f: Float; b: Box2): Box2 {.importc: "box2_fdiv", sol.}

#                ###############################################################
# Box2 Operators ###############################################################
#                ###############################################################

template `+`*(a, b: Box2): Box2         = box2_add(a, b)
template `+`*(b: Box2; v: Vec2): Box2   = box2_addv(b, v)
template `+`*(v: Vec2; b: Box2): Box2   = box2_addv(b, v)
template `+`*(b: Box2; f: Float): Box2  = box2_addf(b, f)
template `+`*(f: Float; b: Box2): Box2  = box2_addf(b, f)
template `-`*(a, b: Box2): Box2         = box2_sub(a, b)
template `-`*(b: Box2; v: Vec2): Box2   = box2_subv(b, v)
template `-`*(v: Vec2; b: Box2): Box2   = box2_vsub(v, b)
template `-`*(b: Box2; f: Float): Box2  = box2_subf(b, f)
template `-`*(f: Float; b: Box2): Box2  = box2_fsub(f, b)
template `*`*(a, b: Box2): Box2         = box2_mul(a, b)
template `*`*(b: Box2; v: Vec2): Box2   = box2_mulv(b, v)
template `*`*(v: Vec2; b: Box2): Box2   = box2_mulv(b, v)
template `*`*(b: Box2; f: Float): Box2  = box2_mulf(b, f)
template `*`*(f: Float; b: Box2): Box2  = box2_mulf(b, f)
template `/`*(a, b: Box2): Box2         = box2_div(a, b)
template `/`*(b: Box2; v: Vec2): Box2   = box2_divv(b, v)
template `/`*(v: Vec2; b: Box2): Box2   = box2_vdiv(v, b)
template `/`*(b: Box2; f: Float): Box2  = box2_divf(b, f)
template `/`*(f: Float; b: Box2): Box2  = box2_fdiv(f, b)

template `+=`*(a: var Box2; b: Box2)  = a = box2_add(a, b)
template `+=`*(b: var Box2; v: Vec2)  = b = box2_addv(b, v)
template `+=`*(b: var Box2; f: Float) = b = box2_addf(b, f)
template `-=`*(a: var Box2; b: Box2)  = a = box2_sub(a, b)
template `-=`*(b: var Box2; v: Vec2)  = b = box2_subv(b, v)
template `-=`*(b: var Box2; f: Float) = b = box2_subf(b, f)
template `*=`*(a: var Box2; b: Box2)  = a = box2_mul(a, b)
template `*=`*(b: var Box2; v: Vec2)  = b = box2_mulv(b, v)
template `*=`*(b: var Box2; f: Float) = b = box2_mulf(b, f)
template `/=`*(a: var Box2; b: Box2)  = a = box2_div(a, b)
template `/=`*(b: var Box2; v: Vec2)  = b = box2_divv(b, v)
template `/=`*(a: var Box2; f: Float) = b = box2_divf(b, f)

#                ###############################################################
# Box3 Functions ###############################################################
#                ###############################################################

proc box3_init*(lower, upper: Vec3): Box3 {.importc: "box3_init",  sol.}
proc box3_initv*(v: Vec3): Box3           {.importc: "box3_initv", sol.}
proc box3_initf*(f: Float): Box3          {.importc: "box3_initf", sol.}
proc box3_zero*(): Box3                   {.importc: "box3_zero",  sol.}

proc box3_pos*(b: Box3): Vec3 {.importc: "box3_pos", sol.}
proc box3_x*(b: Box3): Float  {.importc: "box3_x",   sol.}
proc box3_y*(b: Box3): Float  {.importc: "box3_y",   sol.}
proc box3_z*(b: Box3): Float  {.importc: "box3_z",   sol.}

proc box3_aabb*(a, b: Box3): bool      {.importc: "box3_aabb", sol.}
proc box3_pip*(b: Box3; v: Vec3): bool {.importc: "box3_pip",  sol.}

proc box3_add*(a, b: Box3): Box3         {.importc: "box3_add",  sol.}
proc box3_addv*(b: Box3; v: Vec3): Box3  {.importc: "box3_addv", sol.}
proc box3_addf*(b: Box3; f: Float): Box3 {.importc: "box3_addf", sol.}
proc box3_sub*(a, b: Box3): Box3         {.importc: "box3_sub",  sol.}
proc box3_subv*(b: Box3; v: Vec3): Box3  {.importc: "box3_subv", sol.}
proc box3_vsub*(v: Vec3; b: Box3): Box3  {.importc: "box3_vsub", sol.}
proc box3_subf*(b: Box3; f: Float): Box3 {.importc: "box3_subf", sol.}
proc box3_fsub*(f: Float; b: Box3): Box3 {.importc: "box3_fsub", sol.}
proc box3_mul*(a, b: Box3): Box3         {.importc: "box3_mul",  sol.}
proc box3_mulv*(b: Box3; v: Vec3): Box3  {.importc: "box3_mulv", sol.}
proc box3_mulf*(b: Box3; f: Float): Box3 {.importc: "box3_mulf", sol.}
proc box3_div*(a, b: Box3): Box3         {.importc: "box3_div",  sol.}
proc box3_divv*(b: Box3; v: Vec3): Box3  {.importc: "box3_divv", sol.}
proc box3_vdiv*(v: Vec3; b: Box3): Box3  {.importc: "box3_vdiv", sol.}
proc box3_divf*(b: Box3; f: Float): Box3 {.importc: "box3_divf", sol.}
proc box3_fdiv*(f: Float; b: Box3): Box3 {.importc: "box3_fdiv", sol.}

#                ###############################################################
# Box3 Operators ###############################################################
#                ###############################################################

template `+`*(a, b: Box3): Box3        = box3_add(a, b)
template `+`*(b: Box3; v: Vec3): Box3  = box3_addv(b, v)
template `+`*(v: Vec3; b: Box3): Box3  = box3_addv(b, v)
template `+`*(b: Box3; f: Float): Box3 = box3_addf(b, f)
template `+`*(f: Float; b: Box3): Box3 = box3_addf(b, f)
template `-`*(a, b: Box3): Box3        = box3_sub(a, b)
template `-`*(b: Box3; v: Vec3): Box3  = box3_subv(b, v)
template `-`*(v: Vec3; b: Box3): Box3  = box3_vsub(v, b)
template `-`*(b: Box3; f: Float): Box3 = box3_subf(b, f)
template `-`*(f: Float; b: Box3): Box3 = box3_fsub(f, b)
template `*`*(a, b: Box3): Box3        = box3_mul(a, b)
template `*`*(b: Box3; v: Vec3): Box3  = box3_mulv(b, v)
template `*`*(v: Vec3; b: Box3): Box3  = box3_mulv(b, v)
template `*`*(b: Box3; f: Float): Box3 = box3_mulf(b, f)
template `*`*(f: Float; b: Box3): Box3 = box3_mulf(b, f)
template `/`*(a, b: Box3): Box3        = box3_div(a, b)
template `/`*(b: Box3; v: Vec3): Box3  = box3_divv(b, v)
template `/`*(v: Vec3; b: Box3): Box3  = box3_vdiv(v, b)
template `/`*(b: Box3; f: Float): Box3 = box3_divf(b, f)
template `/`*(f: Float; b: Box3): Box3 = box3_fdiv(f, b)

template `+=`*(a: var Box3; b: Box3)  = a = box3_add(a, b)
template `+=`*(b: var Box3; v: Vec3)  = b = box3_addv(b, v)
template `+=`*(b: var Box3; f: Float) = b = box3_addf(b, f)
template `-=`*(a: var Box3; b: Box3)  = a = box3_sub(a, b)
template `-=`*(b: var Box3; v: Vec3)  = b = box3_subv(b, v)
template `-=`*(b: var Box3; f: Float) = b = box3_subf(b, f)
template `*=`*(a: var Box3; b: Box3)  = a = box3_mul(a, b)
template `*=`*(b: var Box3; v: Vec3)  = b = box3_mulv(b, v)
template `*=`*(b: var Box3; f: Float) = b = box3_mulf(b, f)
template `/=`*(a: var Box3; b: Box3)  = a = box3_div(a, b)
template `/=`*(b: var Box3; v: Vec3)  = b = box3_divv(b, v)
template `/=`*(b: var Box3; f: Float) = b = box3_divf(b, f)

#                ###############################################################
# Sph2 Functions ###############################################################
#                ###############################################################

proc sph2_init*(pos: Vec2; rad: Float): Sph2 {.importc: "sph2_init", sol.}
proc sph2_zero*(): Sph2                      {.importc: "sph2_zero", sol.}

proc sph2_pip*(s: Sph2; p: Vec2): bool {.importc: "sph2_pip", sol.}

#                ###############################################################
# Sph3 Functions ###############################################################
#                ###############################################################

proc sph3_init*(pos: Vec3; rad: Float): Sph3 {.importc: "sph3_init", sol.}
proc sph3_zero*(): Sph3                      {.importc: "sph3_zero", sol.}

proc sph3_pip*(s: Sph2; p: Vec2): bool {.importc: "sph3_pip", sol.}
