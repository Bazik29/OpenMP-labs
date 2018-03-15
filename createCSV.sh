#!/bin/bash

touch result.csv

num_for_repeat=10

echo "Threads,Dimension,InitTime,MultTime,RunTime" > result.csv

for omp_threads in 1 2 3 4 #5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	export OMP_NUM_THREADS=$omp_threads
	for dim in 100 500 800
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./main $dim >> result.csv
		done
	done
done