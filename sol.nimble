# Package

version       = "0.3.0"
author        = "davidgarland"
description   = "A portable SIMD-accelerated vector library written in C99 with Nim bindings."
license       = "MIT"
srcDir        = "src"

# Dependencies

requires "nim >= 1.2.0"

# Tasks

task clean, "Cleans up files.":
  exec "rm -rf tests/test"
