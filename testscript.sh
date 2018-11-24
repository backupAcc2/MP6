#!/bin/bash

# Test Script for MP6
# Heath Gerrald

echo Running test script for MP6
echo " "

echo Testing Graph 1 operations
echo Testing Operation 1 with graph 1
./lab6 -g 1 -h 1 -s 2 -d 5

echo Testing Operation 2 with graph 1
./lab6 -g 1 -h 2

echo Testing Operation 1 with no valid paths
./lab6 -g 1 -h 1 -d 2 -s 0

echo Testing Operation 3 with graph 1
./lab6 -g 1 -h 3 -s 4 -d 6

# echo Test verbose mode
# ./lab6 -g 1 -h 1 -s 4 -d 5 -v

echo " "
echo Test for memory leaks
# valgrind --leak-check=yes ./lab6 -g 1 -h 3 -s 2 -d 4
echo " "
# valgrind --leak-check=yes ./lab6 -g 1 -h 2


echo
echo Testing Graph 2 operations
echo Testing Graph 2 Operation 1
./lab6 -g 2 -h 1 -s 3 -d 4 -n 5

echo Testing Graph 2 Operation 2
./lab6 -g 2 -h 2 -n 20

echo Testing Graph 2 Operation 3
./lab6 -g 2 -h 2 -n 200 -s 20 -d 0

echo " "
echo Test for memory leaks
# valgrind --leak-check=yes ./lab6 -g 2 -h 2 -n 25
# valgrind --leak-check=yes ./lab6 -g 2 -h 3 -n 200 -s 50 -d 100

echo " "
echo Testing Graph 3 Operations
echo Testing Graph 3 Operation 1
./lab6 -g 3 -h 1 -n 100 -a 40 -s 4 -d 20

echo " "
echo Testing Graph 3 Operation 2
./lab6 -g 3 -h 2 -n 100 -a 10 -s 0 -d 99
echo Testing for memory leaks with Operation 2
# valgrind --leak-check=yes ./lab6 -g 3 -h 2 -n 100 -s 0 -d 99

echo " "
echo Testing Graph 3 Operation 3 with low adjacency
./lab6 -g 3 -h 3 -n 200 -a 1 -s 20 -d 99

#echo Test memory leaks
#valgrind --leak-check=yes ./lab6 -g 3 -h 3 -n 200 -a 1 -s 20 -d 99

echo " "
echo Testing Graph 3 Operation 3 with high adjacency
./lab6 -g 3 -h 3 -n 200 -a 100 -s 20 -d 99

#echo Test memory leaks
#valgrind --leak-check=yes ./lab6 -g 3 -h 3 -n 200 -a 100 -s 20 -d 99
