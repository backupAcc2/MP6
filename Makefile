# Makefile for MP6
# Heath Gerrald

lab6 : lab6.o graph.o
				gcc -Wall -g graph.o lab6.o -o lab6 -lm

lab6.o : lab6.c
				gcc -Wall -g -c lab6.c

graph.o : graph.c graph.h
	gcc -Wall -g -c graph.c

clean :
				rm -f *.o lab6
