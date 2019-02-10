#!/bin/sh

g++ -o pthrd main_pthread.c lab1_io.c lab1_pthread.cpp -lpthread -fopenmp -std=c++11
./pthrd $1 $2 $3 $4 $5 
