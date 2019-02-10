#!/bin/sh

g++ -o seq main_sequential.c lab1_io.c lab1_sequential.cpp -std=c++11 -fopenmp
./seq $1 $2 $3 $4

