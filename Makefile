# Sol's Makefile #

# C Compiler Settings #

CC=clang
CFLAGS=-Weverything -O3 -ffast-math
LDFLAGS=-lm

# Nim Compiler Settings #

NIMC=nim
NIMLANG=c
NIMFLAGS=

# Files #
SOLSRC=*.h src/*.h

# Build Options #

default:
	-@make -B quicktest >/dev/null || true

quicktest:
	-@$(CC) -c $(CFLAGS) $(SOLSRC) $(LDFLAGS)

test:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) unit/test.nim
	-@mv unit/test .

bench:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release --opt:speed unit/bench.nim
	-@mv unit/bench .

avx:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:avx --opt:speed unit/bench.nim
	-@mv unit/bench .

avx2:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:avx2 --opt:speed unit/bench.nim
	-@mv unit/bench .

neon:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:neon --opt:speed unit/bench.nim
	-@mv unit/bench .

clean:
	-@rm -rf *.o *.out *.gch src/*.gch unit/nimcache nimcache sol bench test >/dev/null || true

reset: clean
	-@rm -rf *.a *.so *.dylib *.dll *~ src/*~
