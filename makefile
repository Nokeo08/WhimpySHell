#makefile for project 1

all : wsh

run : all
	@./wsh

clean :
	@rm -f *.o

util.o : util.c util.h
	gcc -pedantic -Wall -c util.c

wsh.o : wsh.c
	gcc -pedantic -Wall -c wsh.c

wsh : wsh.o util.o
	gcc -pedantic -Wall -o wsh wsh.o util.o
	@rm *.o
	@echo "\nDone Compiling wsh\n\n"
