import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

import sys
import argparse

def surface(data):
	Z = np.array(data)
	X = np.arange(0, 1, 1.0 / Z.shape[1])
	Y = np.arange(0, 1, 1.0 / Z.shape[1])
	X2D, Y2D = np.meshgrid(X,Y)
	fig = plt.figure()
	ax = Axes3D(fig)
	ax.plot_surface(X2D,Y2D, Z)
	plt.show()

def build_efficiency_plots(mean_values, file):
	fig = plt.figure()
	rt_subplt = fig.add_subplot(212)
	Sp_subplt = fig.add_subplot(221)
	Ep_subplt = fig.add_subplot(222)

	rt_subplt.set_title('runtime'); rt_subplt.set_xlabel('threads'); rt_subplt.set_ylabel('time')
	Sp_subplt.set_title('Speedup'); Sp_subplt.set_xlabel('threads'); Sp_subplt.set_ylabel("$S_{p}$")
	Ep_subplt.set_title('Efficiency'); Ep_subplt.set_xlabel('threads'); Ep_subplt.set_ylabel("$E_{p}$")

	for dimension in sorted(set(mean_values['Dim'])):
		sub_df = mean_values.loc[mean_values.Dim == dimension]
		one_thread_t = sub_df[sub_df.NumThreads == 1]['Runtime'].astype(float)
		speedup = np.array(one_thread_t) / np.array(sub_df['Runtime'])
		efficiency = speedup / np.array(sub_df['NumThreads']) 

		rt_subplt.plot(sub_df['NumThreads'], sub_df['Runtime'], marker = "o", label = "{dim}x{dim}".format(dim = dimension))
		Sp_subplt.plot(sub_df['NumThreads'], speedup, marker=".", label="{dim}x{dim}".format(dim = dimension))
		Ep_subplt.plot(sub_df['NumThreads'], efficiency, marker=".", label="{dim}x{dim}".format(dim = dimension))
	rt_subplt.legend()
	plt.subplots_adjust(wspace=0.5, hspace=0.6)
	plt.savefig('{}.pdf'.format(file))


 
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument ('-a', default='grahp')
    action = parser.parse_args(sys.argv[1:])
    if action.n = 'grahp':
		details = pd.read_csv("result.csv").groupby(['NumThreads','Dim'], as_index = False).mean()
		build_efficiency_plots(details, "d_plots")
	if action.n = 'plot':
		data = pd.read_csv("matrix.txt", header=None, sep=' ')
		surface(data)
