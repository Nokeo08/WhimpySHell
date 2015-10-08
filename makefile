#makefile for project 1

all : wsh

run : all
	@./wsh

clean :
	@rm -f *.o

wsh.o : wsh.c
	gcc -pedantic -Wall -c wsh.c

wsh : wsh.o
	gcc -pedantic -Wall -o wsh wsh.o
	@rm *.o
	@echo "\nDone Compiling wsh\n\n"
