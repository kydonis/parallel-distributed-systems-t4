#!/bin/bash
#SBATCH --job-name=v2
#SBATCH --time=00:10:00
#SBATCH --partition=batch
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=10
#SBATCH --qos=small

cd ../

module load gcc/9.2.0 openmpi/3.1.4

make v2

echo "v2 results" > ./results/v2.txt
	
echo "" >> ./results/v2.txt
for file in ./data/*; do
	echo "" >> ./results/v2.txt
	echo "Running v2 for matrix: "$file >> ./results/v2.txt
	for i in 2 4 8 16; do
		srun -n $i ./v2 $file  >> ./results/v2.txt
	done
	echo "" >> ./results/v2.txt
done
echo "" >> ./results/v2.txt

rm v2