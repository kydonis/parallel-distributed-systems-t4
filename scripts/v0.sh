#!/bin/bash
#SBATCH --job-name=v0
#SBATCH --time=00:10:00
#SBATCH --partition=batch
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

cd ../

module load gcc/9.2.0 

make v0

echo "v0 results" > ./results/v0.txt
	
echo "" >> ./results/v0.txt
for file in ./data/*; do
	echo "" >> ./results/v0.txt
	echo "Running v0 for matrix: "$file >> ./results/v0.txt
    ./v0 $file >> ./results/v0.txt
	echo "" >> ./results/v0.txt
done
echo "" >> ./results/v0.txt

rm v0 