# Sol's Makefile #

# C Compiler Settings #

CC=clang
CFLAGS=-Weverything -O3 -ffast-math
LDFLAGS=-lm

# Nim Compiler Settings #

NIMC=nim
NIMLANG=c
NIMFLAGS=--cc:$(CC)

# Files #
SOLSRC=*.h src/*.c
SOLOUT=out/*.o out/*.out out/*.exe *.o *.out *.exe bench test
SOLLIB=out/*.a out/*.so out/*.dll out/*.dylib *.a *.so *.dll *.dylib
SOLCACHE=*.gch *~ src/*~ nimcache tests/nimcache

# Build Options #

default:
	-@make -B build >/dev/null || true

build:
	-@$(CC) -c $(CFLAGS) $(SOLSRC) $(LDFLAGS)
	-@mv *.o *.out *.a *.so *.exe *.dll out >/dev/null 2>/dev/null || true

test:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) tests/test.nim
	-@mv tests/test .

bench:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release --opt:speed tests/bench.nim
	-@mv tests/bench .

avx:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:avx --opt:speed tests/bench.nim
	-@mv tests/bench .

avx2:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:avx2 --opt:speed tests/bench.nim
	-@mv tests/bench .

neon:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:neon --opt:speed tests/bench.nim
	-@mv tests/bench .

clean:
	-@rm -rf $(SOLCACHE) >/dev/null || true

reset: clean
	-@rm -rf $(SOLOUT) $(SOLLIB) >/dev/null || true
