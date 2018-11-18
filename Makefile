# Makefile for MP6
# Heath Gerrald

lab6 : lab6.o graphOperations.o
				gcc -Wall -g graphOperations.o lab6.o -o lab6 -lm

lab6.o : lab6.c
				gcc -Wall -g -c lab6.c

graphOperations.o : graphOperations.c graphOperations.h
	gcc -Wall -g -c graphOperations.c

clean :
				rm -f *.o lab6
