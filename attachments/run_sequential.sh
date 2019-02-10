#!/bin/sh

g++ -o seq main_sequential.c lab1_io.c lab1_sequential.cpp
./seq $1 $2 $3 $4

