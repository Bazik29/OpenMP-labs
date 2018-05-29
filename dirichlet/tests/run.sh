num_for_repeat=1
max_threds=4
step_treads=1
toFile=1

dims=(100 200 300)

echo "NumThreads,Iterations,Runtime,Dim,Eps" > result.csv

for ((omp_threads=1; omp_threads <= $max_threds; omp_threads+=step_treads)) 
do
	export OMP_NUM_THREADS=$omp_threads
	for dim in ${dims[@]}
	do
		toFile=0
		for ((i=0; i < $num_for_repeat; i++))
		do
			if [[ $toFile == 0 ]]
			then
				 ./../main -n $dim -e 0.001 -o "matrix_$dim.txt" >> result.csv
				toFile=1
			else
				./../main -n $dim -e 0.001 >> result.csv
			fi
		done
	done
done
