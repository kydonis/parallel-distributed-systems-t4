#!/bin/bash
#SBATCH --job-name=v1
#SBATCH --time=00:10:00
#SBATCH --partition=batch
#SBATCH --nodes=1
#SBATCH --cpus-per-task=20

cd ../

module load gcc/9.2.0 

make v1

echo "v1 results" > ./results/v1.txt
	
echo "" >> ./results/v1.txt
for file in ./data/*; do
	echo "" >> ./results/v1.txt
	echo "Running v1 for matrix: "$file >> ./results/v1.txt
	for i in 2 4 8 16 20; do
        export OMP_NUM_THREADS=$i
        ./v1 $file >> ./results/v1.txt
	done
	echo "" >> ./results/v1.txt
done
echo "" >> ./results/v1.txt

rm v1