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
- Run sequential model and note values (done)
- Run pthread for all: for different no of threads and note values (done)
- Do same for OMP (done)
- Plot graphs 


- Write part-b


Report Values::
-------------

Making dataset: For 10k data point variation from 10k to 100k

For Sequential: (in order)
0.048024
0.138633
0.052133
0.091655
0.572429
0.169416
0.204940
0.224592
1.081538
0.181036


For Pthreads: (for 1 thread)
0.059986
0.166670
0.064542
0.110394
0.701102
0.205052
0.240682
0.275185
1.279875
0.212156

For Pthreads: (for 2 thread)
0.035782
0.101305
0.038856
0.067226
0.406696
0.120170
0.141748
0.158178
0.738413
0.148447

for 3 threads:
0.030351
0.079654
0.033703
0.053060
0.302192
0.093207
0.116409
0.126152
0.573866
0.102628

for 4 threads:
0.029505
0.071444
0.031813
0.055412
0.274841
0.104482
0.122454
0.129371
0.554671
0.108405

for 5 threads:
0.027637
0.074594
0.029640
0.051800
0.294177
0.089038
0.107897
0.122634
0.523972
0.110731

for 6 threads:
0.030046
0.071055
0.027527
0.050469
0.261893
0.088774
0.105375
0.112959
0.478721
0.095022

for 7 threads
0.029752
0.071948
0.030146
0.049026
0.255027
0.098117
0.112398
0.122679
0.482208
0.094476

for 8 threads:
0.031648
0.075542
0.030740
0.050961
0.269410
0.090701
0.112555
0.119689
0.478370
0.097571

for 9 threads:
0.031290
0.075583
0.030632
0.048978
0.280653
0.085077
0.105699
0.120236
0.499752
0.101956

for 10 threads:
0.032149
0.070642
0.028155
0.046450
0.270242
0.085037
0.101364
0.117176
0.491132
0.097263

for 12:
0.036018
0.079373
0.031450
0.051913
0.272089
0.089234
0.098968
0.122926
0.506910
0.095199


for 14:
0.029210
0.083651
0.030637
0.050745
0.273649
0.086048
0.098690
0.116793
0.480727
0.102471

for 16:
0.029959
0.074380
0.031456
0.051070
0.284736
0.087335
0.104593
0.118872
0.476890
0.098783


for openmp:

for 1 thread:
0.057606
0.166744
0.061499
0.108916
0.696837
0.202160
0.239981
0.277739
1.315758
0.227773

for 2:
0.034479
0.097274
0.038809
0.065938
0.403432
0.120267
0.136453
0.157380
0.706993
0.126302

for 3:
0.027026
0.076305
0.030085
0.050167
0.293030
0.090468
0.111349
0.123669
0.532948
0.100607

for 4:
0.023893
0.083000
0.027219
0.045684
0.252262
0.082652
0.110605
0.137016
0.480448
0.089389

for 5:
0.031945
0.076289
0.033609
0.052065
0.290715
0.092061
0.109466
0.126156
0.522657
0.102502


for 6:
0.031505
0.070933
0.029915
0.048586
0.273704
0.085589
0.100358
0.110710
0.483469
0.091607

for 7:
0.028478
0.079053
0.029695
0.051628
0.261832
0.086128
0.096975
0.109848
0.465651
0.089426

for 8:
0.030413
0.083447
0.033021
0.055721
0.268363
0.087673
0.106536
0.112833
0.451785
0.092125

for 10:
0.024458
0.064750
0.028167
0.047474
0.258107
0.081773
0.097554
0.109981
0.460883
0.090837

for 12:
0.026005
0.065054
0.030115
0.044803
0.255945
0.080157
0.096742
0.106294
0.436217
0.084196

for 14:
0.024868
0.064904
0.028338
0.044629
0.250458
0.080373
0.099961
0.105553
0.440270
0.084252

for 16:
0.025749
0.063848
0.027718
0.046672
0.244103
0.081707
0.093503
0.104396
0.438870
0.086359