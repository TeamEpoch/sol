############
# Sol Test #
############

import ../sol

var a = vec3_init(0, 1, 2)
var b = vec3_init(2, 1, 0)
a += b
vec3_print(a)
