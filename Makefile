CC=cc
CFLAGS=
LDFLAGS=-lm

default: build

update:
	git remote add -f snow https://github.com/mortie/snow
	git fetch snow master
	git subtree pull --prefix lib/snow snow master

build:
	$(CC) src/sol.h
	$(CC) -DSOL_N_GNU src/sol.h

clean:
	-@rm -rf *.gch *.o src/*.gch src/*.o
