import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
import numpy as np

# v = np.random.rand(10,4)
# v[:,3] = np.random.randint(0,2,size=10)
df = pd.read_csv('./eval.csv')
# df = pd.DataFrame(v, columns=['Feature1', 'Feature2','Feature3',"Cluster"])

fig = plt.figure(figsize=(10,10))
ax = fig.add_subplot(111, projection='3d')
x = np.array(df['Feature1'])
y = np.array(df['Feature2'])
z = np.array(df['Feature3'])

ax.scatter(x,y,z, marker="o", c=df["Cluster"])

# plt.show()
fig.savefig('temp.png')
