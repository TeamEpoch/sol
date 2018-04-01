# Sol's Makefile #

# C Compiler Settings #

CC=gcc
CFLAGS=-Ofast -pipe -flto
LDFLAGS=

# Nim Compiler Settings #

NIMC=nim
NIMLANG=c
NIMFLAGS=--cc:$(CC) -d:fsize=32

# Sol Shared Library Settings #


CPATH=/usr/include
NIMPATH=~/.nimble/pkgs
LIBPATH=/usr/lib
SHARED=-fpic -shared

# Sol SIMD Settings #

SOLAVX2=-mavx2 -mavx -mfma
SOLAVX=-mavx
SOLNEON=-mfpu=neon

# Convenience Strings #

SOLSRC=src/*.c
SOLHDR=*.h

SOLCACHE=bench test nimcache *.gch *~ src/*~ tests/*~ tests/nimcache

SOLGEN=*.o *.out *.a *.so *.s
SOLOUT=out/*.o out/*.out out/*.a out/*.so out/*.s

SOLEXE=*.o *.out *.s out/*.o out/*.out out/*.s
SOLLIB=*.a *.so out/*.a out/*.so

MUTE=>/dev/null 2>/dev/null || true

# Compiler Logic #

ifeq ($(CC), gcc)
	SOLSRC += *.h
	CFLAGS+= -Wno-psabi
	LDFLAGS += -pipe -flto=8
else ifeq ($(CC), clang)
	SOLSRC += $(SOLHDR)
	CFLAGS += 
	LDFLAGS += -pipe -Weverything
else
	# ...
endif

# Default #

default:
	-@make -B build >/dev/null

# Build Rules #

build:
	-@$(CC) -c $(CFLAGS) $(SOLSRC) $(LDFLAGS)
	-@mv $(SOLGEN) out $(MUTE)

build_avx2:
	-@$(CC) -c $(CFLAGS) $(SOLAVX2) $(SOLSRC) $(LDFLAGS)
	-@mv $(SOLGEN) out $(MUTE)

build_avx:
	-@$(CC) -c $(CFLAGS) $(SOLAVX) $(SOLSRC) $(LDFLAGS)
	-@mv $(SOLGEN) out $(MUTE)

build_neon:
	-@$(CC) -c $(CFLAGS) $(SOLNEON) $(SOLSRC) $(LDFLAGS)
	-@mv $(SOLGEN) out $(MUTE)

# Static Library Rules #

static: build
	-@ar rcs sol-a.a out/*.o $(MUTE)
	-@mv $(SOLGEN) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

static_avx2: build_avx2
	-@ar rcs sol-a.a out/*.o $(MUTE)
	-@mv $(SOLGEN) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

static_avx: build_avx
	-@ar rcs sol-a.a out/*.o $(MUTE)
	-@mv $(SOLGEN) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

static_neon: build_neon
	-@ar rcs sol-a.a out/*.o $(MUTE)
	-@mv $(SOLGEN) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

# Dynamic Library Rules #

dynamic:
	-@$(CC) $(SHARED) src/*.c -o sol-so.so
	-@mv $(SOLGEN) $(SOLOUT) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

dynamic_avx2:
	-@$(CC) $(SHARED) $(SOLAVX2) src/*.c -o sol-so.so
	-@mv $(SOLGEN) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

dynamic_avx:
	-@$(CC) $(SHARED) $(SOLAVX) src/*.c -o sol-so.so
	-@mv $(SOLGEN) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

dynamic_neon:
	-@$(CC) $(SHARED) $(SOLNEON) src/*.c -o sol-so.so
	-@mv $(SOLGEN) out $(MUTE)
	-@rm $(SOLEXE) $(MUTE)

# Installation Rules #

install: static dynamic
	-@rm -rf $(SOLEXE) $(SOLCACHE) $(MUTE)
	-@mv $(SOLOUT) $(LIBPATH) $(MUTE)
	-@cp -r . $(CPATH)/sol

install_avx2: static_avx2 dynamic_avx2
	-@rm -rf $(SOLEXE) $(SOLCACHE) $(MUTE)
	-@mv $(SOLOUT) $(LIBPATH) $(MUTE)
	-@cp -r . $(CPATH)/sol $(MUTE)

install_avx: static_avx dynamic_avx
	-@rm -rf $(SOLEXE) $(SOLCACHE) $(MUTE)
	-@mv $(SOLOUT) $(LIBPATH) $(MUTE)
	-@cp -r . $(CPATH)/sol $(MUTE)

install_neon: static_neon dynamic_neon
	-@rm -rf $(SOLEXE) $(SOLCACHE) $(MUTE)
	-@mv $(SOLOUT) $(LIBPATH) $(MUTE)
	-@cp -r . $(CPATH)/sol $(MUTE)

# Nim Installation Rules #

install_nim:
	-@echo "This won't work currently. :L"
	#-@cp -r . $(NIMPATH)/sol $(MUTE)

# Uninstallation Rules #

uninstall:
	-@rm -rf $(LIBPATH)/sol-so.so $(MUTE)
	-@rm -rf $(LIBPATH)/sol-a.a $(MUTE)
	-@rm -rf $(CPATH)/sol $(MUTE)

# Nim Uninstallation Rules #

uninstall_nim:
	-@echo "This won't work currently. :L"
	#-@rm -rf $(NIMPATH)/sol $(MUTE)

# Disassembly Rules #

disas:
	-@$(CC) $(CFLAGS) $(SOLSRC) $(LDFLAGS) -S -masm=intel
	-@mv $(SOLGEN) out $(MUTE)

disas_avx2:
	-@$(CC) $(CFLAGS) $(SOLAVX2) $(SOLSRC) $(LDFLAGS) -S -masm=intel
	-@mv $(SOLGEN) out $(MUTE)

disas_avx:
	-@$(CC) $(CFLAGS) $(SOLAVX) $(SOLSRC) $(LDFLAGS) -S -masm=intel
	-@mv $(SOLGEN) out $(MUTE)

disas_neon:
	-@$(CC) $(CFLAGS) $(SOLNEON) $(SOLSRC) $(LDFLAGS) -S masm=intel
	-@mv $(SOLGEN) out $(MUTE)

# Test Rules #

test:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:none tests/test.nim
	-@mv tests/test . $(MUTE)

test_avx2:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:avx2 tests/test.nim
	-@mv tests/test . $(MUTE)

test_avx:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:avx tests/test.nim
	-@mv tests/test . $(MUTE)

test_neon:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:neon tests/test.nim
	-@mv tests/test . $(MUTE)

# Benchmark Rules #

bench:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:none --opt:speed tests/bench.nim
	-@mv tests/bench . $(MUTE)

bench_avx2:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:avx2 --opt:speed tests/bench.nim
	-@mv tests/bench . $(MUTE)

bench_avx:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:avx --opt:speed tests/bench.nim
	-@mv tests/bench . $(MUTE)

bench_neon:
	-@$(NIMC) $(NIMLANG) $(NIMFLAGS) -d:release -d:neon --opt:speed tests/bench.nim
	-@mv tests/bench . $(MUTE)

# Cleanup Rules #

clean:
	-@rm -rf $(SOLCACHE) $(MUTE)

reset: clean
	-@rm -rf $(SOLEXE) $(SOLLIB) $(SOLCACHE) $(MUTE)
