##################################################################
## sol.nim #######################################################
## Description: Nim bindings for the Sol vector library. #########
## Author: David Garland (https://github.com/davidgarland/sol) ###
##################################################################

{.
  passc: "-I."
  compile: "src/sol_flt.c"
  compile: "src/sol_conv.c"
  compile: "src/sol_vec2.c"
  compile: "src/sol_vec3.c"
  compile: "src/sol_vec4.c"
  compile: "src/sol_ray2.c"
  compile: "src/sol_ray3.c"
  compile: "src/sol_seg2.c"
  compile: "src/sol_seg3.c"
  compile: "src/sol_mat2.c"
  compile: "src/sol_mat3.c"
  compile: "src/sol_mat4.c"
  passl: "-lm"
  passc: "-DSOL_NO_FAM"
.}

################################################################################
# Command-Line Options #########################################################
################################################################################

when defined(avx):
    {.passc: "-mavx -mfma -DSOL_AVX".}
elif defined(avx2):
    {.passc: "-mavx2 -mfma -DSOL_AVX -DSOL_AVX2"}
elif defined(neon):
    {.passc: "-mfpu=neon -DSOL_NEON".}
else:
    {.passc: "-DSOL_NO_SIMD".}

################################################################################
# Type Definitions #############################################################
################################################################################

type Float* {.importc: "Float", header: "sol.h".} = cfloat

type Vec2* {.importc: "Vec2", header: "sol.h".} = object
    x*, y*: Float

type Vec3* {.importc: "Vec3", header: "sol.h".} = object
    x*, y*, z*: Float

type Vec4* {.importc: "Vec4", header: "sol.h".} = object
    x*, y*, z*, w*: Float

type Ray2* {.importc: "Ray2", header: "sol.h".} = object
    pos*, vec*: Vec2

type Ray3* {.importc: "Ray3", header: "sol.h".} = object
    pos*, vec*: Vec3

type Seg2* {.importc: "Seg2", header: "sol.h".} = object
    orig*, dest*: Vec2

type Seg3* {.importc: "Seg3", header: "sol.h".} = object
    orig*, dest*: Vec3

type Mat2* {.importc: "Mat2", header: "sol.h".} = object

type Mat3* {.importc: "Mat3", header: "sol.h".} = object

type Mat4* {.importc: "Mat4", header: "sol.h".} = object

type Box2* {.importc: "Box2", header: "sol.h".} = object
  lower*, upper*: Vec2

type Box3* {.importc: "Box3", header: "sol.h".} = object
    lower*, upper*: Vec3

type Sph2* {.importc: "Sph2", header: "sol.h".} = object
    pos*: Vec2
    rad*: Float

type Sph3* {.importc: "Sph3", header: "sol.h".} = object
    pos*: Vec3
    rad*: Float

################################################################################
# Constants ####################################################################
################################################################################

const sol_pi:  Float = 3.14159265358979323846
const sol_tau: Float = 6.28318530717958647692
const sol_g:   Float = 9.80665
const sol_c:   Float = 299792000

################################################################################
# Module Functions #############################################################
################################################################################

proc sol_prefetch*[T](p: ptr[T]; rw, locality: cint) {.importc: "sol_prefetch", header: "sol.h".}

################################################################################
# Float Functions ##############################################################
################################################################################

proc flt_clamp*(f, lower, upper: Float): Float {.importc: "flt_clamp", header: "sol.h".}
proc flt_abs*(f: Float): Float                 {.importc: "flt_abs",   header: "sol.h".}
proc flt_pow*(a, b: Float): Float              {.importc: "flt_pow",   header: "sol.h".}
proc flt_sqrt*(f: Float): Float                {.importc: "flt_sqrt",  header: "sol.h".}
proc flt_sin*(f: Float): Float                 {.importc: "flt_sin",   header: "sol.h".}
proc flt_cos*(f: Float): Float                 {.importc: "flt_cos",   header: "sol.h".}
proc flt_acos*(f: Float): Float                {.importc: "flt_acos",  header: "sol.h".}

################################################################################
# Float Operators ##############################################################
################################################################################

template `+=`*(a: var Float; b: Float) = a = a + b
template `-=`*(a: var Float; b: Float) = a = a - b
template `*=`*(a: var Float; b: Float) = a = a * b
template `/=`*(a: var Float; b: Float) = a = a / b

################################################################################
# Conversion Functions #########################################################
################################################################################

proc cv_axis_quat*(axis: Vec4): Vec4 {.importc: "cv_axis_quat", header: "sol.h".}
proc cv_quat_axis*(quat: Vec4): Vec4 {.importc: "cv_quat_axis", header: "sol.h".}

proc cv_vec3_vec2*(v: Vec3): Vec2              {.importc: "cv_vec3_vec2", header: "sol.h".}
proc cv_vec4_vec2*(v: Vec4): Vec2              {.importc: "cv_vec4_vec2", header: "sol.h".}
proc cv_vec2_vec3*(v: Vec2; z: Float): Vec3    {.importc: "cv_vec2_vec3", header: "sol.h".}
proc cv_vec4_vec3*(v: Vec4): Vec3              {.importc: "cv_vec4_vec3", header: "sol.h".}
proc cv_vec2_vec4*(v: Vec2; z, w: Float): Vec4 {.importc: "cv_vec2_vec4", header: "sol.h".}
proc cv_vec3_vec4*(v: Vec3; w: Float): Vec4    {.importc: "cv_vec3_vec4", header: "sol.h".}

proc cv_deg_rad*(deg: Float): Float {.importc: "cv_deg_rad", header: "sol.h".}
proc cv_rad_deg*(rad: Float): Float {.importc: "cv_rad_deg", header: "sol.h".}

################################################################################
# Vec2 Functions ###############################################################
################################################################################

proc vec2_init*(x, y: Float): Vec2 {.importc: "vec2_init",  header: "sol.h".}
proc vec2_initf*(f: Float): Vec2   {.importc: "vec2_initf", header: "sol.h".}
proc vec2_zero*(): Vec2            {.importc: "vec2_zero",  header: "sol.h".}

proc vec2_norm*(v: Vec2): Vec2             {.importc: "vec2_norm", header: "sol.h".}
proc vec2_mag*(v: Vec2): Float             {.importc: "vec2_mag",  header: "sol.h".}
proc vec2_eq*(a, b: Vec2; ep: Float): bool {.importc: "vec2_eq",   header: "sol.h".}

proc vec2_rot*(v: Vec2; deg: Float): Vec2  {.importc: "vec2_rot",  header: "sol.h".}
proc vec2_rotr*(v: Vec2; rad: Float): Vec2 {.importc: "vec2_rotr", header: "sol.h".}

proc vec2_proj*(a, b: Vec2): Vec2   {.importc: "vec2_proj",  header: "sol.h".}
proc vec2_rej*(a, b: Vec2): Vec2    {.importc: "vec2_rej",   header: "sol.h".}
proc vec2_angle*(a, b: Vec2): Float {.importc: "vec2_angle", header: "sol.h".}
proc vec2_cross*(a, b: Vec2): Float {.importc: "vec2_cross", header: "sol.h".}
proc vec2_dot*(a, b: Vec2): Float   {.importc: "vec2_dot",   header: "sol.h".}

proc vec2_sum*(v: Vec2): Float           {.importc: "vec2_sum",  header: "sol.h".}
proc vec2_fma*(a, b, c: Vec2): Vec2      {.importc: "vec2_fma",  header: "sol.h".}
proc vec2_add*(a, b: Vec2): Vec2         {.importc: "vec2_add",  header: "sol.h".}
proc vec2_addf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_addf", header: "sol.h".}
proc vec2_sub*(a, b: Vec2): Vec2         {.importc: "vec2_sub",  header: "sol.h".}
proc vec2_subf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_subf", header: "sol.h".}
proc vec2_fsub*(f: Float, v: Vec2): Vec2 {.importc: "vec2_fsub", header: "sol.h".}
proc vec2_mul*(a, b: Vec2): Vec2         {.importc: "vec2_mul",  header: "sol.h".}
proc vec2_mulf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_mulf", header: "sol.h".}
proc vec2_div*(a, b: Vec2): Vec2         {.importc: "vec2_div",  header: "sol.h".}
proc vec2_divf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_divf", header: "sol.h".}
proc vec2_fdiv*(f: Float, v: Vec2): Vec2 {.importc: "vec2_fdiv", header: "sol.h".}
proc vec2_pow*(a, b: Vec2): Vec2         {.importc: "vec2_pow",  header: "sol.h".}
proc vec2_powf*(v: Vec2; f: Float): Vec2 {.importc: "vec2_powf", header: "sol.h".}
proc vec2_fpow*(f: Float; v: Vec2): Vec2 {.importc: "vec2_fpow", header: "sol.h".}
proc vec2_avg*(a, b: Vec2): Vec2         {.importc: "vec2_avg",  header: "sol.h".}
proc vec2_avgf*(v: Vec2, f: Float): Vec2 {.importc: "vec2_avgf", header: "sol.h".}

proc vec2_print*(v: Vec2): void {.importc: "vec2_print", header: "sol.h".}

################################################################################
# Vec2 Operators ###############################################################
################################################################################

template vec*(x, y: Float): Vec3 = vec2_init(x, y)

template norm*(v: Vec2): Vec2    = vec2_norm(v)
template mag*(v: Vec2): Float    = vec2_mag(v)
template `==`*(a, b: Vec2): bool = vec2_eq(a, b)

template `rot`*(v: Vec2; deg: Float): Vec2 = vec2_rot(v, deg)
template `rotr`*(v: Vec2; rad: Float): Vec2 = vec2_rotr(v, rad)

template `proj`*(a, b: Vec2): Vec2   = vec2_proj(a, b)
template `rej`*(a, b: Vec2): Vec2    = vec2_rej(a, b)
template `cross`*(a, b: Vec2): Float = vec2_cross(a, b)
template `dot`*(a, b: Vec2): Float   = vec2_dot(a, b)

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

################################################################################
# Vec3 Functions ###############################################################
################################################################################

proc vec3_init*(x, y, z: Float): Vec3 {.importc: "vec3_init",  header: "sol.h".}
proc vec3_initf*(f: Float): Vec3      {.importc: "vec3_initf", header: "sol.h".}
proc vec3_zero*(): Vec3               {.importc: "vec3_zero",  header: "sol.h".}

proc vec3_norm*(v: Vec3): Vec3            {.importc: "vec3_norm", header: "sol.h".}
proc vec3_mag*(v: Vec3): Float            {.importc: "vec3_mag",  header: "sol.h".}
proc vec3_eq*(a, b: Vec3; f: Float): bool {.importc: "vec3_eq",   header: "sol.h".}
proc vec3_yzx*(v: Vec3): Vec3             {.importc: "vec3_yzx",  header: "sol.h".}

proc vec3_rot*(v: Vec3, aa: Vec4): Vec3 {.importc: "vec3_rot",  header: "sol.h".}
proc vec3_rotq*(v: Vec3, q: Vec4): Vec3 {.importc: "vec3_rotq", header: "sol.h".}

proc vec3_proj*(a, b: Vec3): Vec3   {.importc: "vec3_proj",  header: "sol.h".}
proc vec3_rej*(a, b: Vec3): Vec3    {.importc: "vec3_rej",   header: "sol.h".}
proc vec3_angle*(a, b: Vec3): Float {.importc: "vec3_angle", header: "sol.h".}
proc vec3_cross*(a, b: Vec3): Vec3  {.importc: "vec3_cross", header: "sol.h".}
proc vec3_dot*(a, b: Vec3): Float   {.importc: "vec3_dot",   header: "sol.h".}

proc vec3_sum*(v: Vec3): Float           {.importc: "vec3_sum",  header: "sol.h".}
proc vec3_fma*(a, b, c: Vec3): Vec3      {.importc: "vec3_fma",  header: "sol.h".}
proc vec3_add*(a, b: Vec3): Vec3         {.importc: "vec3_add",  header: "sol.h".}
proc vec3_addf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_addf", header: "sol.h".}
proc vec3_sub*(a, b: Vec3): Vec3         {.importc: "vec3_sub",  header: "sol.h".}
proc vec3_subf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_subf", header: "sol.h".}
proc vec3_fsub*(f: Float, v: Vec3): Vec3 {.importc: "vec3_fsub", header: "sol.h".}
proc vec3_mul*(a, b: Vec3): Vec3         {.importc: "vec3_mul",  header: "sol.h".}
proc vec3_mulf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_mulf", header: "sol.h".}
proc vec3_div*(a, b: Vec3): Vec3         {.importc: "vec3_div",  header: "sol.h".}
proc vec3_divf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_divf", header: "sol.h".}
proc vec3_fdiv*(f: Float, v: Vec3): Vec3 {.importc: "vec3_fdiv", header: "sol.h".}
proc vec3_pow*(a, b: Vec3): Vec3         {.importc: "vec3_pow",  header: "sol.h".}
proc vec3_powf*(v: Vec3; f: Float): Vec3 {.importc: "vec3_powf", header: "sol.h".}
proc vec3_fpow*(f: Float; v: Vec3): Vec3 {.importc: "vec3_fpow", header: "sol.h".}
proc vec3_avg*(a, b: Vec3): Vec3         {.importc: "vec3_avg",  header: "sol.h".}
proc vec3_avgf*(v: Vec3, f: Float): Vec3 {.importc: "vec3_avgf", header: "sol.h".}

proc vec3_print*(v: Vec3): void {.importc: "vec3_print", header: "sol.h".}

################################################################################
# Vec3 Operators ###############################################################
################################################################################

template vec*(x, y, z: Float): Vec3 = vec3_init(x, y, z)

template norm*(v: Vec3): Vec3    = vec3_norm(v)
template mag*(v: Vec3): Float    = vec3_mag(v)
template `==`*(a, b: Vec3): bool = vec3_eq(a, b)

template `rot`*(v: Vec3; aa: Vec4): Vec3 = vec3_rot(v, aa)
template `rotq`*(v: Vec3; q: Vec4): Vec3 = vec3_rotq(v, q)

template `proj`*(a, b: Vec3): Vec3  = vec3_proj(a, b)
template `rej`*(a, b: Vec3): Vec3   = vec3_rej(a, b)
template `cross`*(a, b: Vec3): Vec3 = vec3_cross(a, b)
template `dot`*(a, b: Vec3): Float  = vec3_dot(a, b)

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

################################################################################
# Vec4 Functions ###############################################################
################################################################################

proc vec4_init*(x, y, z, w: Float): Vec4 {.importc: "vec4_init",  header: "sol.h".}
proc vec4_initf*(f: Float): Vec4         {.importc: "vec4_initf", header: "sol.h".}
proc vec4_zero*(): Vec4                  {.importc: "vec4_zero",  header: "sol.h".}

proc vec4_norm*(v: Vec4): Vec4             {.importc: "vec4_norm", header: "sol.h".}
proc vec4_mag*(v: Vec4): Float             {.importc: "vec4_mag",  header: "sol.h".}
proc vec4_eq*(a, b: Vec4; ep: Float): bool {.importc: "vec4_eq",   header: "sol.h".}

proc vec4_sum*(v: Vec4): Float           {.importc: "vec4_sum",  header: "sol.h".}
proc vec4_fma*(a, b, c: Vec4): Vec4      {.importc: "vec4_fma",  header: "sol.h".}
proc vec4_add*(a, b: Vec4): Vec4         {.importc: "vec4_add",  header: "sol.h".}
proc vec4_addf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_addf", header: "sol.h".}
proc vec4_sub*(a, b: Vec4): Vec4         {.importc: "vec4_sub",  header: "sol.h".}
proc vec4_subf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_subf", header: "sol.h".}
proc vec4_fsub*(f: Float; v: Vec4): Vec4 {.importc: "vec4_fsub", header: "sol.h".}
proc vec4_mul*(a, b: Vec4): Vec4         {.importc: "vec4_mul",  header: "sol.h".}
proc vec4_mulf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_mulf", header: "sol.h".}
proc vec4_div*(a, b: Vec4): Vec4         {.importc: "vec4_div",  header: "sol.h".}
proc vec4_divf*(v: Vec4; f: Float): Vec4 {.importc: "vec4_divf", header: "sol.h".}
proc vec4_fdiv*(f: Float; v: Vec4): Vec4 {.importc: "vec4_fdiv", header: "sol.h".}
proc vec4_avg*(a, b: Vec4): Vec4         {.importc: "vec4_avg",  header: "sol.h".}
proc vec4_avgf*(v: Vec4, f: Float): Vec4 {.importc: "vec4_avgf", header: "sol.h".}

proc vec4_print*(v: Vec4): void {.importc: "vec4_print", header: "sol.h".}

################################################################################
# Vec4 Operators ###############################################################
################################################################################

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

################################################################################
# Ray2 Functions ###############################################################
################################################################################

proc ray2_init*(pos, vec: Vec2): Ray2 {.importc: "ray2_init",  header: "sol.h".}
proc ray2_initv*(v: Vec2): Ray2       {.importc: "ray2_initv", header: "sol.h".}
proc ray2_initf*(f: Float): Ray2      {.importc: "ray2_initf", header: "sol.h".}
proc ray2_zero*(): Ray2               {.importc: "ray2_zero",  header: "sol.h".}

proc ray2_norm*(r: Ray2): Ray2             {.importc: "ray2_norm", header: "sol.h".}
proc ray2_mag*(r: Ray2): Float             {.importc: "ray2_mag",  header: "sol.h".}
proc ray2_eq*(a, b: Ray2; ep: Float): bool {.importc: "ray2_eq",   header: "sol.h".}

proc ray2_rot*(r: Ray2; deg: Float): Ray2  {.importc: "ray2_rot",  header: "sol.h".}
proc ray2_rotr*(r: Ray2; rad: Float): Ray2 {.importc: "ray2_rotr", header: "sol.h".}

proc ray2_addp*(r: Ray2; p: Vec2): Ray2   {.importc: "ray2_addp",  header: "sol.h".}
proc ray2_addpf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_addpf", header: "sol.h".}
proc ray2_addv*(r: Ray2; v: Vec2): Ray2   {.importc: "ray2_addv",  header: "sol.h".}
proc ray2_addvf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_addvf", header: "sol.h".}
proc ray2_subp*(r: Ray2; p: Vec2): Ray2   {.importc: "ray2_subp",  header: "sol.h".}
proc ray2_subpf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_subpf", header: "sol.h".}
proc ray2_psub*(p: Vec2; r: Ray2): Ray2   {.importc: "ray2_psub",  header: "sol.h".}
proc ray2_pfsub*(f: Float; r: Ray2): Ray2 {.importc: "ray2_pfsub", header: "sol.h".}
proc ray2_subv*(r: Ray2; v: Vec2): Ray2   {.importc: "ray2_subv",  header: "sol.h".}
proc ray2_subvf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_subvf", header: "sol.h".}
proc ray2_vsub*(v: Vec2; r: Ray2): Ray2   {.importc: "ray2_vsub",  header: "sol.h".}
proc ray2_vfsub*(f: Float; r: Ray2): Ray2 {.importc: "ray2_vfsub", header: "sol.h".}
proc ray2_mulp*(r: Ray2; p: Vec2): Ray2   {.importc: "ray2_mulp",  header: "sol.h".}
proc ray2_mulpf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_mulpf", header: "sol.h".}
proc ray2_mulv*(r: Ray2; v: Vec2): Ray2   {.importc: "ray2_mulv",  header: "sol.h".}
proc ray2_mulvf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_mulvf", header: "sol.h".}
proc ray2_divp*(r: Ray2; p: Vec2): Ray2   {.importc: "ray2_divp",  header: "sol.h".}
proc ray2_divpf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_divpf", header: "sol.h".}
proc ray2_pdiv*(p: Vec2; r: Ray2): Ray2   {.importc: "ray2_pdiv",  header: "sol.h".}
proc ray2_pfdiv*(f: Float; r: Ray2): Ray2 {.importc: "ray2_pfdiv", header: "sol.h".}
proc ray2_divv*(r: Ray2; v: Vec2): Ray2   {.importc: "ray2_divv",  header: "sol.h".}
proc ray2_divvf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_divvf", header: "sol.h".}
proc ray2_vdiv*(v: Vec2; r: Ray2): Ray2   {.importc: "ray2_vdiv",  header: "sol.h".}
proc ray2_vfdiv*(f: Float; r: Ray2): Ray2 {.importc: "ray2_vfdiv", header: "sol.h".}

proc ray2_avgp*(r: Ray2; p: Vec2): Ray2   {.importc: "ray2_avgp",  header: "sol.h".}
proc ray2_avgpf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_avgpf", header: "sol.h".}
proc ray2_avgv*(r: Ray2; v: Vec2): Ray2   {.importc: "ray2_avgv",  header: "sol.h".}
proc ray2_avgvf*(r: Ray2; f: Float): Ray2 {.importc: "ray2_avgvf", header: "sol.h".}

################################################################################
# Ray3 Functions ###############################################################
################################################################################

proc ray3_init*(pos, vec: Vec3): Ray3 {.importc: "ray3_init",  header: "sol.h".}
proc ray3_initv*(v: Vec3): Ray3       {.importc: "ray3_initv", header: "sol.h".}
proc ray3_initf*(f: Float): Ray3      {.importc: "ray3_initf", header: "sol.h".}
proc ray3_zero*(): Ray3               {.importc: "ray3_zero",  header: "sol.h".}

proc ray3_norm*(r: Ray3): Ray3             {.importc: "ray3_norm", header: "sol.h".}
proc ray3_mag*(r: Ray3): Float             {.importc: "ray3_mag",  header: "sol.h".}
proc ray3_eq*(a, b: Ray3; ep: Float): bool {.importc: "ray3_eq",   header: "sol.h".}

proc ray3_rot*(r: Ray3; aa: Vec4): Ray3 {.importc: "ray3_rot",  header: "sol.h".}
proc ray3_rotq*(r: Ray3; q: Vec4): Ray3 {.importc: "ray3_rotq", header: "sol.h".}

proc ray3_addp*(r: Ray3; p: Vec3): Ray3   {.importc: "ray3_addp",  header: "sol.h".}
proc ray3_addpf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_addpf", header: "sol.h".}
proc ray3_addv*(r: Ray3; v: Vec3): Ray3   {.importc: "ray3_addv",  header: "sol.h".}
proc ray3_addvf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_addvf", header: "sol.h".}
proc ray3_subp*(r: Ray3; p: Vec3): Ray3   {.importc: "ray3_subp",  header: "sol.h".}
proc ray3_subpf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_subpf", header: "sol.h".}
proc ray3_psub*(p: Vec3; r: Ray3): Ray3   {.importc: "ray3_psub",  header: "sol.h".}
proc ray3_pfsub*(f: Float; r: Ray3): Ray3 {.importc: "ray3_pfsub", header: "sol.h".}
proc ray3_subv*(r: Ray3; v: Vec3): Ray3   {.importc: "ray3_subv",  header: "sol.h".}
proc ray3_subvf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_subvf", header: "sol.h".}
proc ray3_vsub*(v: Vec3; r: Ray3): Ray3   {.importc: "ray3_vsub",  header: "sol.h".}
proc ray3_vfsub*(f: Float; r: Ray3): Ray3 {.importc: "ray3_vfsub", header: "sol.h".}
proc ray3_mulp*(r: Ray3; p: Vec3): Ray3   {.importc: "ray3_mulp",  header: "sol.h".}
proc ray3_mulpf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_mulpf", header: "sol.h".}
proc ray3_mulv*(r: Ray3; v: Vec3): Ray3   {.importc: "ray3_mulv",  header: "sol.h".}
proc ray3_mulvf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_mulvf", header: "sol.h".}
proc ray3_divp*(r: Ray3; p: Vec3): Ray3   {.importc: "ray3_divp",  header: "sol.h".}
proc ray3_divpf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_divpf", header: "sol.h".}
proc ray3_pdiv*(p: Vec3; r: Ray3): Ray3   {.importc: "ray3_pdiv",  header: "sol.h".}
proc ray3_pfdiv*(f: Float; r: Ray3): Ray3 {.importc: "ray3_pfdiv", header: "sol.h".}
proc ray3_divv*(r: Ray3; v: Vec3): Ray3   {.importc: "ray3_divv",  header: "sol.h".}
proc ray3_divvf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_divvf", header: "sol.h".}
proc ray3_vdiv*(v: Vec3; r: Ray3): Ray3   {.importc: "ray3_vdiv",  header: "sol.h".}
proc ray3_vfdiv*(f: Float; r: Ray3): Ray3 {.importc: "ray3_vfdiv", header: "sol.h".}
proc ray3_avgp*(r: Ray3; p: Vec3): Ray3   {.importc: "ray3_avgp",  header: "sol.h".}
proc ray3_avgpf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_avgpf", header: "sol.h".}
proc ray3_avgv*(r: Ray3; v: Vec3): Ray3   {.importc: "ray3_avgv",  header: "sol.h".}
proc ray3_avgvf*(r: Ray3; f: Float): Ray3 {.importc: "ray3_avgvf", header: "sol.h".}

################################################################################
# Seg2 Functions ###############################################################
################################################################################

proc seg2_init*(orig, dest: Vec2): Seg2 {.importc: "seg2_init",  header: "sol.h".}
proc seg2_initv*(v: Vec2): Seg2         {.importc: "seg2_initv", header: "sol.h".}
proc seg2_initf*(f: Float): Seg2        {.importc: "seg2_initf", header: "sol.h".}
proc seg2_zero*(): Seg2                 {.importc: "seg2_zero",  header: "sol.h".}

proc seg2_add*(a, b: Seg2): Seg2         {.importc: "seg2_add",  header: "sol.h".}
proc seg2_addv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_addv", header: "sol.h".}
proc seg2_addf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_addf", header: "sol.h".}
proc seg2_sub*(a, b: Seg2): Seg2         {.importc: "seg2_sub",  header: "sol.h".}
proc seg2_subv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_subv", header: "sol.h".}
proc seg2_vsub*(v: Vec2; s: Seg2): Seg2  {.importc: "seg2_vsub", header: "sol.h".}
proc seg2_subf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_subf", header: "sol.h".}
proc seg2_fsub*(f: Float; s: Seg2): Seg2 {.importc: "seg2_fsub", header: "sol.h".}
proc seg2_mul*(a, b: Seg2): Seg2         {.importc: "seg2_mul",  header: "sol.h".}
proc seg2_mulv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_mulv", header: "sol.h".}
proc seg2_mulf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_mulf", header: "sol.h".}
proc seg2_div*(a, b: Seg2): Seg2         {.importc: "seg2_div",  header: "sol.h".}
proc seg2_divv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_divv", header: "sol.h".}
proc seg2_vdiv*(v: Vec2; s: Seg2): Seg2  {.importc: "seg2_vdiv", header: "sol.h".}
proc seg2_divf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_divf", header: "sol.h".}
proc seg2_fdiv*(f: Float; s: Seg2): Seg2 {.importc: "seg2_fdiv", header: "sol.h".}
proc seg2_avg*(a, b: Seg2): Seg2         {.importc: "seg2_avg",  header: "sol.h".}
proc seg2_avgv*(s: Seg2; v: Vec2): Seg2  {.importc: "seg2_avgv", header: "sol.h".}
proc seg2_avgf*(s: Seg2; f: Float): Seg2 {.importc: "seg2_avgf", header: "sol.h".}

################################################################################
# Seg2 Operators ###############################################################
################################################################################

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

################################################################################
# Seg3 Functions ###############################################################
################################################################################

proc seg3_init*(orig, dest: Vec3): Seg3 {.importc: "seg3_init",  header: "sol.h".}
proc seg3_initv*(v: Vec3): Seg3         {.importc: "seg3_initv", header: "sol.h".}
proc seg3_initf*(f: Float): Seg3        {.importc: "seg3_initf", header: "sol.h".}
proc seg3_zero*(): Seg3                 {.importc: "seg3_zero",  header: "sol.h".}

proc seg3_add*(a, b: Seg3): Seg3         {.importc: "seg3_add",  header: "sol.h".}
proc seg3_addv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_addv", header: "sol.h".}
proc seg3_addf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_addf", header: "sol.h".}
proc seg3_sub*(a, b: Seg3): Seg3         {.importc: "seg3_sub",  header: "sol.h".}
proc seg3_subv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_subv", header: "sol.h".}
proc seg3_vsub*(v: Vec3; s: Seg3): Seg3  {.importc: "seg3_vsub", header: "sol.h".}
proc seg3_subf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_subf", header: "sol.h".}
proc seg3_fsub*(f: Float; s: Seg3): Seg3 {.importc: "seg3_fsub", header: "sol.h".}
proc seg3_mul*(a, b: Seg3): Seg3         {.importc: "seg3_mul",  header: "sol.h".}
proc seg3_mulv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_mulv", header: "sol.h".}
proc seg3_mulf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_mulf", header: "sol.h".}
proc seg3_div*(a, b: Seg3): Seg3         {.importc: "seg3_div",  header: "sol.h".}
proc seg3_divv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_divv", header: "sol.h".}
proc seg3_vdiv*(v: Vec3; s: Seg3): Seg3  {.importc: "seg3_vdiv", header: "sol.h".}
proc seg3_divf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_divf", header: "sol.h".}
proc seg3_fdiv*(f: Float; s: Seg3): Seg3 {.importc: "seg3_fdiv", header: "sol.h".}
proc seg3_avg*(a, b: Seg3): Seg3         {.importc: "seg3_avg",  header: "sol.h".}
proc seg3_avgv*(s: Seg3; v: Vec3): Seg3  {.importc: "seg3_avgv", header: "sol.h".}
proc seg3_avgf*(s: Seg3; f: Float): Seg3 {.importc: "seg3_avgf", header: "sol.h".}

################################################################################
# Seg3 Operators ###############################################################
################################################################################

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

################################################################################
# Mat2 Functions ###############################################################
################################################################################

proc mat2_init*(f11, f12, f21, f22: Float): Mat2 {.importc: "mat2_init",  header: "sol.h".}
proc mat2_initv*(v1, v2: Vec2): Mat2             {.importc: "mat2_initv", header: "sol.h".}
proc mat2_initf*(f: Float): Mat2                 {.importc: "mat2_initf", header: "sol.h".}
proc mat2_zero*(): Mat2                          {.importc: "mat2_zero",  header: "sol.h".}

proc mat2_add*(a, b: Mat2): Mat2         {.importc: "mat2_add",  header: "sol.h".}
proc mat2_addf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_addf", header: "sol.h".}
proc mat2_sub*(a, b: Mat2): Mat2         {.importc: "mat2_sub",  header: "sol.h".}
proc mat2_subf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_subf", header: "sol.h".}
proc mat2_fsub*(f: Float; m: Mat2): Mat2 {.importc: "mat2_fsub", header: "sol.h".}
proc mat2_mul*(a, b: Mat2): Mat2         {.importc: "mat2_mul",  header: "sol.h".}
proc mat2_mulf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_mulf", header: "sol.h".}
proc mat2_div*(a, b: Mat2): Mat2         {.importc: "mat2_div",  header: "sol.h".}
proc mat2_divf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_divf", header: "sol.h".}
proc mat2_fdiv*(f: Float; m: Mat2): Mat2 {.importc: "mat2_fdiv", header: "sol.h".}
proc mat2_avg*(a, b: Mat2): Mat2         {.importc: "mat2_avg",  header: "sol.h".}
proc mat2_avgf*(m: Mat2; f: Float): Mat2 {.importc: "mat2_avgf", header: "sol.h".}

proc mat2_print*(m: Mat2): void {.importc: "mat2_print", header: "sol.h".}

################################################################################
# Mat2 Operators ###############################################################
################################################################################

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

################################################################################
# Mat3 Functions ###############################################################
################################################################################

proc mat3_init*(f11, f12, f13, f21, f22, f23, f31, f32, f33: Float): Mat3 {.importc: "mat3_init", header: "sol.h".}
proc mat3_initv*(v1, v2, v3: Vec3): Mat3                                  {.importc: "mat3_initv", header: "sol.h".}
proc mat3_initf*(f: Float): Mat3                                          {.importc: "mat3_initf", header: "sol.h".}
proc mat3_zero*(): Mat3                                                   {.importc: "mat3_zero", header: "sol.h".}

proc mat3_add*(a, b: Mat3): Mat3         {.importc: "mat3_add",  header: "sol.h".}
proc mat3_addf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_addf", header: "sol.h".}
proc mat3_sub*(a, b: Mat3): Mat3         {.importc: "mat3_sub",  header: "sol.h".}
proc mat3_subf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_subf", header: "sol.h".}
proc mat3_fsub*(f: Float; m: Mat3): Mat3 {.importc: "mat3_fsub", header: "sol.h".}
proc mat3_mul*(a, b: Mat3): Mat3         {.importc: "mat3_mul",  header: "sol.h".}
proc mat3_mulf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_mulf", header: "sol.h".}
proc mat3_div*(a, b: Mat3): Mat3         {.importc: "mat3_div",  header: "sol.h".}
proc mat3_divf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_divf", header: "sol.h".}
proc mat3_fdiv*(f: Float; m: Mat3): Mat3 {.importc: "mat3_fdiv", header: "sol.h".}
proc mat3_avg*(a, b: Mat3): Mat3         {.importc: "mat3_avg",  header: "sol.h".}
proc mat3_avgf*(m: Mat3; f: Float): Mat3 {.importc: "mat3_avgf", header: "sol.h".}

proc mat3_print*(m: Mat3): void {.importc: "mat3_print", header: "sol.h".}

################################################################################
# Mat3 Operators ###############################################################
################################################################################

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

################################################################################
# Mat4 Functions ###############################################################
################################################################################

proc mat4_init*(f11, f12, f13, f14, f21, f22, f23, f24, f31, f32, f33, f34, f41, f42, f43, f44: Float): Mat4 {.importc: "mat4_init",  header: "sol.h".}
proc mat4_initv*(v1, v2, v3, v4: Vec4): Mat4                                                                 {.importc: "mat4_initv", header: "sol.h".}
proc mat4_initf*(f: Float): Mat4                                                                             {.importc: "mat4_initf", header: "sol.h".}
proc mat4_zero*(): Mat4                                                                                      {.importc: "mat4_zero",  header: "sol.h".}

proc mat4_add*(a, b: Mat4): Mat4         {.importc: "mat4_add",  header: "sol.h".}
proc mat4_addf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_addf", header: "sol.h".}
proc mat4_sub*(a, b: Mat4): Mat4         {.importc: "mat4_sub",  header: "sol.h".}
proc mat4_subf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_subf", header: "sol.h".}
proc mat4_fsub*(f: Float; m: Mat4): Mat4 {.importc: "mat4_fsub", header: "sol.h".}
proc mat4_mul*(a, b: Mat4): Mat4         {.importc: "mat4_mul",  header: "sol.h".}
proc mat4_mulf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_mulf", header: "sol.h".}
proc mat4_div*(a, b: Mat4): Mat4         {.importc: "mat4_div",  header: "sol.h".}
proc mat4_divf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_divf", header: "sol.h".}
proc mat4_fdiv*(f: Float; m: Mat4): Mat4 {.importc: "mat4_fdiv", header: "sol.h".}
proc mat4_avg*(a, b: Mat4): Mat4         {.importc: "mat4_avg",  header: "sol.h".}
proc mat4_avgf*(m: Mat4; f: Float): Mat4 {.importc: "mat4_avgf", header: "sol.h".}

proc mat4_print*(m: Mat4): Mat4 {.importc: "mat4_print", header: "sol.h".}

################################################################################
# Mat4 Operators ###############################################################
################################################################################

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

################################################################################
# Box2 Functions ###############################################################
################################################################################

proc box2_init*(lower, upper: Vec2): Box2 {.importc: "box2_init",  header: "sol.h".}
proc box2_initv*(v: Vec2): Box2           {.importc: "box2_initv", header: "sol.h".}
proc box2_initf*(f: Float): Box2          {.importc: "box2_initf", header: "sol.h".}
proc box2_zero*(): Box2                   {.importc: "box2_zero",  header: "sol.h".}

proc box2_pos*(b: Box2): Vec2 {.importc: "box2_pos", header: "sol.h".}
proc box2_x*(b: Box2): Float  {.importc: "box2_x",   header: "sol.h".}
proc box2_y*(b: Box2): Float  {.importc: "box2_y",   header: "sol.h".}

proc box2_aabb*(a, b: Box2): bool      {.importc: "box2_aabb", header: "sol.h".}
proc box2_pip*(b: Box2; v: Vec2): bool {.importc: "box2_pip",  header: "sol.h".}

proc box2_add*(a, b: Box2): Box2         {.importc: "box2_add",  header: "sol.h".}
proc box2_addv*(b: Box2; v: Vec2): Box2  {.importc: "box2_addv", header: "sol.h".}
proc box2_addf*(b: Box2; f: Float): Box2 {.importc: "box2_addf", header: "sol.h".}
proc box2_sub*(a, b: Box2): Box2         {.importc: "box2_sub",  header: "sol.h".}
proc box2_subv*(b: Box2; v: Vec2): Box2  {.importc: "box2_subv", header: "sol.h".}
proc box2_vsub*(v: Vec2; b: Box2): Box2  {.importc: "box2_vsub", header: "sol.h".}
proc box2_subf*(b: Box2; f: Float): Box2 {.importc: "box2_subf", header: "sol.h".}
proc box2_fsub*(f: Float; b: Box2): Box2 {.importc: "box2_fsub", header: "sol.h".}
proc box2_mul*(a, b: Box2): Box2         {.importc: "box2_mul",  header: "sol.h".}
proc box2_mulv*(b: Box2; v: Vec2): Box2  {.importc: "box2_mulv", header: "sol.h".}
proc box2_mulf*(b: Box2; f: Float): Box2 {.importc: "box2_mulf", header: "sol.h".}
proc box2_div*(a, b: Box2): Box2         {.importc: "box2_div",  header: "sol.h".}
proc box2_divv*(b: Box2; v: Vec2): Box2  {.importc: "box2_divv", header: "sol.h".}
proc box2_vdiv*(v: Vec2; b: Box2): Box2  {.importc: "box2_vdiv", header: "sol.h".}
proc box2_divf*(b: Box2; f: Float): Box2 {.importc: "box2_divf", header: "sol.h".}
proc box2_fdiv*(f: Float; b: Box2): Box2 {.importc: "box2_fdiv", header: "sol.h".}

################################################################################
# Box2 Operators ###############################################################
################################################################################

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

################################################################################
# Box3 Functions ###############################################################
################################################################################

proc box3_init*(lower, upper: Vec3): Box3 {.importc: "box3_init",  header: "sol.h".}
proc box3_initv*(v: Vec3): Box3           {.importc: "box3_initv", header: "sol.h".}
proc box3_initf*(f: Float): Box3          {.importc: "box3_initf", header: "sol.h".}
proc box3_zero*(): Box3                   {.importc: "box3_zero",  header: "sol.h".}

proc box3_pos*(b: Box3): Vec3 {.importc: "box3_pos", header: "sol.h".}
proc box3_x*(b: Box3): Float  {.importc: "box3_x",   header: "sol.h".}
proc box3_y*(b: Box3): Float  {.importc: "box3_y",   header: "sol.h".}
proc box3_z*(b: Box3): Float  {.importc: "box3_z",   header: "sol.h".}

proc box3_aabb*(a, b: Box3): bool      {.importc: "box3_aabb", header: "sol.h".}
proc box3_pip*(b: Box3; v: Vec3): bool {.importc: "box3_pip",  header: "sol.h".}

proc box3_add*(a, b: Box3): Box3         {.importc: "box3_add",  header: "sol.h".}
proc box3_addv*(b: Box3; v: Vec3): Box3  {.importc: "box3_addv", header: "sol.h".}
proc box3_addf*(b: Box3; f: Float): Box3 {.importc: "box3_addf", header: "sol.h".}
proc box3_sub*(a, b: Box3): Box3         {.importc: "box3_sub",  header: "sol.h".}
proc box3_subv*(b: Box3; v: Vec3): Box3  {.importc: "box3_subv", header: "sol.h".}
proc box3_vsub*(v: Vec3; b: Box3): Box3  {.importc: "box3_vsub", header: "sol.h".}
proc box3_subf*(b: Box3; f: Float): Box3 {.importc: "box3_subf", header: "sol.h".}
proc box3_fsub*(f: Float; b: Box3): Box3 {.importc: "box3_fsub", header: "sol.h".}
proc box3_mul*(a, b: Box3): Box3         {.importc: "box3_mul",  header: "sol.h".}
proc box3_mulv*(b: Box3; v: Vec3): Box3  {.importc: "box3_mulv", header: "sol.h".}
proc box3_mulf*(b: Box3; f: Float): Box3 {.importc: "box3_mulf", header: "sol.h".}
proc box3_div*(a, b: Box3): Box3         {.importc: "box3_div",  header: "sol.h".}
proc box3_divv*(b: Box3; v: Vec3): Box3  {.importc: "box3_divv", header: "sol.h".}
proc box3_vdiv*(v: Vec3; b: Box3): Box3  {.importc: "box3_vdiv", header: "sol.h".}
proc box3_divf*(b: Box3; f: Float): Box3 {.importc: "box3_divf", header: "sol.h".}
proc box3_fdiv*(f: Float; b: Box3): Box3 {.importc: "box3_fdiv", header: "sol.h".}

################################################################################
# Box3 Operators ###############################################################
################################################################################

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
