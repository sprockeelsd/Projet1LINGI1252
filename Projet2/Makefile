.PHONY: all val
.DEFAULT_GOAL := all
CFLAGS=-g -Wall -Werror

all: tests lib_tar.o
	
a.out: lib_tar.h lib_tar.c tests.c
	gcc -g $^
	gdb a.out

lib_tar.o: lib_tar.c lib_tar.h

tests: tests.c lib_tar.o

val: tests
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests archive.tar
	#valgrind --xml=yes --xml-file="valgrind.xml" --leak-check=yes ./tests archive.tar

clean:
	rm -f lib_tar.o tests soumission.tar
	rm -f lib_tar.h.gch

submit: all
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c *.h *.c Makefile > soumission.tar
