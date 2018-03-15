#!/bin/bash
#SBATCH --job-name=mulMatrix
#SBATCH --output=output_%j.txt
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100


num_for_repeat=3

echo "Threads,Dimension,InitTime,MultTime,RunTime"
for omp_threads in 2 4
do

export OMP_NUM_THREADS=$omp_threads

for dim in 10 50 100
do
	for ((i=0; i < $num_for_repeat; i++))
	do
	./main $dim
	done
done

done