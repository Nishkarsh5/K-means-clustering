import yaml
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

with open("values.yml", 'r') as stream:
    try:
        values = (yaml.load(stream))
    except yaml.YAMLError as exc:
        print(exc)


# --------------------------Plotting Graphs-----------------------------
# For both openMP and Pthreads: Each plot


# -----------SpeedUp vs. Size of dataset
# threads = [1, 2, 4, 6, 8, 10, 12, 14, 16] 

# size = []
# j=0
# for i in range(10):
# 	j = j+10000
# 	size.append(j)

# Ts = values['seq']
# TsdivTp = []

# for i in threads:
# 	temp = []
# 	Tp = values['pthr'][i]
# 	for j in range(len(Tp)):
# 		temp.append(Ts[j]/Tp[j])
# 	TsdivTp.append(temp)

# fig = plt.figure(figsize=(14, 6))
# plt.xlabel("Size of the Dataset")
# plt.ylabel("Speed Up")
# plt.title("Speed Up vs Size of the Dataset")
# for i in range(len(threads)):
#     plt.plot(size, TsdivTp[i],label = 'threads %s'%threads[i])

# plt.ylim(bottom=0)  # this line
# plt.legend()
# plt.tight_layout()

# # plt.show()
# fig.savefig('temp2.png')


# ------------Efficiency vs Size of the data
threads = [1, 2, 4, 6, 8, 10, 12, 14, 16] 

size = []
j=0
for i in range(10):
	j = j+10000
	size.append(j)

Ts = values['seq']
TsdivTp = []

for i in threads:
	temp = []
	Tp = values['omp'][i]
	for j in range(len(Tp)):
		temp.append(Ts[j]/(Tp[j]*i))
	TsdivTp.append(temp)

fig = plt.figure(figsize=(14, 6))
plt.xlabel("Size of the Dataset")
plt.ylabel("Efficiency")
plt.title("Efficiency vs Size of the Dataset")
for i in range(len(threads)):
    plt.plot(size, TsdivTp[i],label = 'threads %s'%threads[i])

plt.ylim(bottom=0)  # this line
plt.legend()
plt.tight_layout()

# plt.show()
fig.savefig('temp4.png') 