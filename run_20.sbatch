#!/bin/bash
#SBATCH --job-name=mulMatrix
#SBATCH --output=output_%j.txt
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100

for var in 20
do 

omp_threads=$var
export OMP_NUM_THREADS=$omp_threads

echo "threads:" $omp_threads
echo "╔═══════════════════════════════════════════════════════╗"
echo "║ dim   init            mul             runtime         ║"
echo "╟───────────────────────────────────────────────────────╢"
./main 1000
./main 2000
./main 4000
echo "╚═══════════════════════════════════════════════════════╝"

done
