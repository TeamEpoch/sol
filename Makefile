CC=clang
CFLAGS=
WFLAGS=-Weverything
LDFLAGS=-lm

default: build

update:
	git remote add -f snow https://github.com/mortie/snow
	git fetch snow master
	git subtree pull --prefix lib/snow snow master

build:
	$(CC) $(WFLAGS) -DSOL_N_GNU src/sol.h
	$(CC) $(WFLAGS) -DSOL_GNU src/sol.h
	$(CC) $(WFLAGS) -DSOL_GNU -mavx src/sol.h

clean:
	-@rm -rf *.gch *.o src/*.gch src/*.o
