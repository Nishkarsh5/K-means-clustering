- Perform and plot speed up and efficiency: By changing the input size: Number of threads and size of the dataset.

part-a
- Graphs:
For OpenMP and Pthreads
	Speedup (Ts/Tp) - Number of threads
	Speedup (Ts/Tp) - Size of the dataset
	Efficiency (S/p) - Number of threads
	Efficiency (S/p) - Size of the dataset

part-b
- Design Choices
- Parallelization Strategy
- Load-balancing
---------------

How to do - 
- Make 10 datasets (done)
- Run sequential model and note values
- Run pthread for all: for different no of threads and note values
- Do same for OMP
- Plot graphs


- Write part-b


Report Values::
-------------

Making dataset: For 10k data point variation from 10k to 100k

For Sequential: (in order)
0.074011
0.198905
0.075754
0.129651
0.791337
0.240360
0.278003
0.314614
1.480295
0.253048

For Pthreads: (for 1 thread)
0.097583
0.252150
0.088947
0.158268
0.955417
0.287437
0.329367
0.384122
1.791196
0.294869

For Pthreads: (for 2 thread)
0.056764
0.159762
0.061940
0.097284
0.573494
0.193705
0.223541
0.244760
1.075174
0.212145
