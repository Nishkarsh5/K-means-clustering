# Sequential----------------
# g++ main_sequential.c lab1_sequential.cpp lab1_io.c -std=c++11 -fopenmp
# ./a.out 3 sample_dataset_5000_3.txt out1.txt out2.txt

# Pthreads--------------
# g++ main_pthread.c lab1_pthread.cpp lab1_io.c -std=c++11 -lpthread -fopenmp
# ./a.out 3 $1 sample_dataset_5000_3.txt out1.txt out2.txt


# OMP---------------------
# g++ main_omp.c lab1_omp.cpp lab1_io.c -std=c++11 -fopenmp
# ./a.out 3 $1 sample_dataset_5000_3.txt out1.txt out2.txt

