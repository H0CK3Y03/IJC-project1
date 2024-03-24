# CC = gcc
# most CLI flags
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

# Makes sure to run all, clean, run, even if there are files named all, clean, run
.PHONY: all clean run

# all files
all: primes primes-i no-comment
# for running make without arguments/parameters
default_target: all

# -------------------------------primes using macros-------------------------------
primes: primes.o eratosthenes.o error.o
	gcc $(CFLAGS) -o $@ $^ -lm
# $@ -> variable that represents the target (primes)
# $^ -> variable representing all dependendencies (files: primes.o era...)
# $(CFLAGS) -> custom variable that contains all flags
# -lm -> links the math library

# assures that changed files will initiate a recompilation of all necessary files
primes.o: primes.c eratosthenes.h error.h
	gcc $(CFLAGS) -c -o $@ primes.c

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
	gcc $(CFLAGS) -c -o $@ eratosthenes.c

error.o: error.c error.h
	gcc $(CFLAGS) -c -o $@ error.c

# ------------------------------------------primes using inline functions------------------------------------------
primes-i: primes.o eratosthenes.o error.o bitset.c
	gcc $(CFLAGS) -DUSE_INLINE -o $@ $^  -lm
# -DUSE_INLINE -> defines USE_INLINE for header files to know to use inline functions and not macros

primes-i.o: primes.c eratosthenes.h error.h
	gcc $(CFLAGS) -DUSE_INLINE -c -o $@ primes.c

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h error.h
	gcc $(CFLAGS) -DUSE_INLINE -c -o $@ eratosthenes.c

# ----------------------------------------------------no-comment----------------------------------------------------
no-comment: no-comment.c error.c
	gcc $(CFLAGS) -o $@ $^

# removes all binary files
clean:
	rm -f primes primes-i no-comment *.o

# cleans all .o files
clean_o:
	rm -f *.o

# runs all of the binaries
run: all
	ulimit -s 100000 && ./primes
	ulimit -s 100000 && ./primes-i

# zips all .c and .h files into a single .zip archive
zip: *.c *.h
	zip xvesela00.zip *.c *.h Makefile
