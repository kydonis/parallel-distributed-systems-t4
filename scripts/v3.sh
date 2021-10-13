#!/bin/bash
#SBATCH --job-name=v3
#SBATCH --time=00:10:00
#SBATCH --partition=batch
#SBATCH --nodes=2
#SBATCH --ntasks=10
#SBATCH --cpus-per-task=4

cd ../

module load gcc/9.2.0 openmpi/3.1.4

make v3

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

echo "v3 results" > ./results/v3.txt
	
echo "" >> ./results/v3.txt
for file in ./data/*; do
	echo "" >> ./results/v3.txt
	echo "Running v3 for matrix: "$file >> ./results/v3.txt
	for i in 4 16; do
       	srun -n $i ./v3 $file  >> ./results/v3.txt
	done
	echo "" >> ./results/v3.txt
done
echo "" >> ./results/v3.txt

rm v3
