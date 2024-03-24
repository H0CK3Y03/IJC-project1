CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra






# zips all .c and .h files into a single .zip archive
zip: *.c *.h
	zip xvesela00.zip *.c *.h Makefile
