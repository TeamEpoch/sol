# Package

version       = "0.2.1"
author        = "davidgarland"
description   = "A SIMD-accelerated vector library written in C99 with Nim bindings."
license       = "MIT"
srcDir        = "src"

# Dependencies

requires "nim >= 0.18.0"

# Tasks

task clean, "Cleans up files.":
  exec "rm -rf tests/test"
