import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

data = pd.read_csv('res.txt',header=None, sep=" ")

Z=np.array(data)
print(Z.shape[1])
X = np.arange(0, 1, 1/Z.shape[1])
Y = np.arange(0,1, 1/Z.shape[1])


X2D,Y2D = np.meshgrid(X,Y)

fig = plt.figure()
ax = Axes3D(fig)

ax.plot_surface(X2D,Y2D, Z)
plt.show()
