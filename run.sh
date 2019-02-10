# Pthreads--------------
# g++ main_pthread.c lab1_pthread.cpp lab1_io.c -std=c++11 -lpthread -fopenmp
# ./a.out 3 $1 dataset_10000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_20000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_30000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_40000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_50000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_60000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_70000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_80000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_90000_3.txt out1.txt out2.txt
# ./a.out 3 $1 dataset_100000_3.txt out1.txt out2.txt


# OMP---------------------
g++ main_omp.c lab1_omp.cpp lab1_io.c -std=c++11 -fopenmp
./a.out 3 $1 dataset_10000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_20000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_30000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_40000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_50000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_60000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_70000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_80000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_90000_3.txt out1.txt out2.txt
./a.out 3 $1 dataset_100000_3.txt out1.txt out2.txt


# Sequential----------------
# g++ main_sequential.c lab1_sequential.cpp lab1_io.c -std=c++11 -fopenmp
# ./a.out 3 dataset_10000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_20000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_30000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_40000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_50000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_60000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_70000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_80000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_90000_3.txt out1.txt out2.txt
# ./a.out 3 dataset_100000_3.txt out1.txt out2.txt
