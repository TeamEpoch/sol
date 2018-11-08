CC=cc
CFLAGS=
LDFLAGS=-lm

default: build

build:
	$(CC) src/sol.h
	$(CC) -DSOL_N_GNU src/sol.h

clean:
	-@rm -rf *.gch *.o src/*.gch src/*.o
