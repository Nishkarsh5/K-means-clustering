#sequential time
import os 
import subprocess
import matplotlib.pyplot as plt

sizes = [10000, 50000, 100000, 200000, 500000, 700000, 1000000]
threads = [1, 2, 4, 6, 8, 10, 12, 14, 16]
# sizes = [10000, 50000]
# threads = [1,2]


try:
    subprocess.call('rm ./time_seq.txt', shell=True)
except:
    print("exception")

for size in sizes:
    syntax = 'sh run_sequential.sh 4 dataset/dataset_' + str(size)+'_10.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
    #syntax = 'sh run_omp.sh 4 dataset_' + str(size)+'_4.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
    print("syntax:", syntax)
    subprocess.call(syntax, shell=True)

try:
    subprocess.call('rm ./time_omp.txt', shell=True)
except:
    print("exception")

for size in sizes:
    for thread in threads:
        #syntax = 'sh run_sequential.sh 4 dataset_' + str(size)+'_4.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
        syntax = 'sh run_omp.sh 4 '+str(thread)+' dataset/dataset_' + str(size)+'_10.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
        print("syntax:", syntax)
        subprocess.call(syntax, shell=True)

file_seq ="time_seq.txt"
file_omp ="time_omp.txt"
file_s_omp = open("speedup_omp.txt", "a")
with open(file_seq) as f:
    sequential = f.readlines()
sequential=[x.strip() for x in sequential]
sequential = list(map(float, sequential))
print('sequential times:', sequential)

with open(file_omp) as f:
    omp = f.readlines()
omp=[x.strip() for x in omp]
omp = list(map(float, omp))
print('omp times:', omp)

i = 0
num_proc = len(threads)
for t_s in sequential:
    print("size:", sizes[i])
    currentlist = omp[i*num_proc:(i+1)*num_proc]
    print("current:", currentlist)
    speedup = [t_s/x for x in currentlist] 
    plt.plot(threads, speedup, label="Size: "+str(sizes[i]))
    print("speedup:", speedup)
    i+=1

plt.show()


