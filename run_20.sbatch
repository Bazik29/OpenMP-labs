#!/bin/bash
#SBATCH --job-name=hello_openmp
#SBATCH --output=output_%j.txt
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100

if [ -n "$SLURM_CPUS_PER_TASK" ]; then
  omp_threads=$SLURM_CPUS_PER_TASK
else
  omp_threads=1
fi
export OMP_NUM_THREADS=$omp_threads