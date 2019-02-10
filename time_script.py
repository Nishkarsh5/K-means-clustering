#sequential time
import os 
import subprocess
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

sizes = [10000, 50000, 100000, 200000, 500000, 1000000]
threads = [1, 2, 4, 6, 8, 12, 16]
# sizes = [10000, 50000]
# threads = [1,2]


try:
    subprocess.call('rm ./time_seq.txt', shell=True)
except:
    print("exception")

for size in sizes:
    syntax = 'sh run_sequential.sh 4 dataset/dataset_' + str(size)+'_10.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
    #syntax = 'sh run_pthread.sh 4 dataset_' + str(size)+'_4.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
    print("syntax:", syntax)
    subprocess.call(syntax, shell=True)

try:
    subprocess.call('rm ./time_pthread.txt', shell=True)
except:
    print("exception")

for size in sizes:
    for thread in threads:
        #syntax = 'sh run_sequential.sh 4 dataset_' + str(size)+'_4.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
        syntax = 'sh run_pthread.sh 4 '+str(thread)+' dataset/dataset_' + str(size)+'_10.txt out_'+str(size)+'.txt cent_'+str(size)+'.txt'
        print("syntax:", syntax)
        subprocess.call(syntax, shell=True)

file_seq ="time_seq.txt"
file_pthread ="time_pthread.txt"
file_s_pthread = open("speedup_pthread.txt", "a")
with open(file_seq) as f:
    sequential = f.readlines()
sequential=[x.strip() for x in sequential]
sequential = list(map(float, sequential))
print('sequential times:', sequential)

with open(file_pthread) as f:
    pthread = f.readlines()
pthread=[x.strip() for x in pthread]
pthread = list(map(float, pthread))
print('pthread times:', pthread)

i = 0
num_proc = len(threads)

fig = plt.figure(figsize=(14, 6))

plt.ylabel("Speed-Up ->")
plt.xlabel("Number of Threads ->")
plt.title("Speed-Up vs Number of Threads (For `Pthread`)")

for t_s in sequential:
    print("size:", sizes[i])
    currentlist = pthread[i*num_proc:(i+1)*num_proc]
    print("current:", currentlist)
    speedup = [t_s/x for x in currentlist] 
    er = [float(speedup[i])/threads[i] for i in range(len(threads))]

    plt.plot(threads, speedup, label="Size: "+str(sizes[i]))
    print("speedup:", speedup)
    i+=1

plt.ylim(bottom=0)  # this line

plt.legend()
plt.tight_layout()

# plt.show()
fig.savefig('4.png')

