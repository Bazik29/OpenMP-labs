python3 graph.py -b benchmark.csv

dims=(100 200 300)

for dim in ${dims[@]}
do
	python3 graph.py -s "matrix_$dim.txt"
done
