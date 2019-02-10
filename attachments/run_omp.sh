#!/bin/sh

g++ -o omp main_omp.c lab1_io.c lab1_omp.cpp -fopenmp
./omp $1 $2 $3 $4 $5 
