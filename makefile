#makefile for project 1

all : wsh

run : all
	@./wsh

clean :
	@rm -f *.o

execution.o : execution.c execution.h
	gcc -pedantic -Wall -c execution.c

util.o : util.c util.h
	gcc -pedantic -Wall -c util.c

wsh.o : wsh.c
	gcc -pedantic -Wall -c wsh.c

wsh : wsh.o util.o execution.o
	gcc -pedantic -Wall -o wsh wsh.o util.o execution.o
	@rm *.o
	@echo "\nDone Compiling wsh\n\n"
