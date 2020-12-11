.PHONY: temp all
.DEFAULT_GOAL := temp
CFLAGS=-g -Wall -Werror
OBJ = lib_tar.h lib_tar.c tests.c
CC = gcc

all: tests lib_tar.o

temp: $(OBJ)
	$(CC) $^ -o temp
	
a.out: $(OBJ)
	$(CC) -g $^
	gdb a.out

lib_tar.o: lib_tar.c lib_tar.h

tests: tests.c lib_tar.o

clean:
	rm -f lib_tar.o tests soumission.tar
	rm -f temp

submit: all
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c *.h *.c Makefile > soumission.tar
