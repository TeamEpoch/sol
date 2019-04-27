CC=clang
CFLAGS=
WFLAGS=-std=c99 -Weverything
LDFLAGS=-lm

default: build

build:
	$(CC) $(WFLAGS) -DSOL_N_GNU src/sol.h
	$(CC) $(WFLAGS) -DSOL_GNU src/sol.h
	$(CC) $(WFLAGS) -DSOL_GNU -mavx src/sol.h

disas:
	$(CC) $(CFLAGS) -DSOL_GNU -c -S -mavx2 -mavx -march=native -Ofast tests/disas.c

test:
	$(CC) $(CFLAGS) -Og -fno-omit-frame-pointer -fsanitize=undefined tests/test.c -L. -L./src -I. -Ilib/snow -DSNOW_ENABLED -g -o test.o $(LDFLAGS)
	-@./test.o
	-@rm -rf *.o

clean:
	-@rm -rf *.gch *.o *.s src/*.gch src/*.o
