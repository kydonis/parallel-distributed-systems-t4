# BMM algorithm
# **Parallel and Distributed Computer Systems**  
## **Exercise 4**
## Kydonis Ioannis      | ikydonis@ece.auth.gr  <br />
## Meta Louis-Kosmas    | louismeta@ece.auth.gr <br />

---
### Contents
   1. [How to build](#1)
   2. [Results from HPC](#2)
   
<a name="1"></a>
### **How to build**  

**File ```Makefile```:**  
   + Use command line ```make all``` to build v0, v1, v2 and v3 immediately.
   + Use command line ```make testv0``` to test v0 sequential with random array (nr = 1000000, nc = 1000000, nnz = 999999). 
   + Use command line ```make testv1``` to test v1 using OpenMP with random array (nr = 1000000, nc = 1000000, nnz = 999999, numOfWorkers = 4).
   + Use command line ```make testv2``` to test v2 using MPI with random array (nr = 1000000, nc = 1000000, nnz = 999999, numOfTasks = 4).
   + Use command line ```make testv3``` to test v3 using both MPI and OpenMp with random array (nr = 1000000, nc = 1000000, nnz = 999999, numOfWorkers = 4 ,numOfTasks = 4).

   
   **Examples:**  
If you want to run a function with one of the given matrices from the data folder, run as shown below:
   + ```./v0 <Matrix Path> ```   
   + ```./v1 <Matrix Path> <Number of workers> ```   
   + ``` mpirun -np <Number of tasks> ./v2 <Matrix Path> ```
   + ``` mpirun -np <Number of tasks> ./v3 <Matrix Path> ```

**Note:** All the functions that we implemented are using a filter F for the product.

---
<a name="2"></a>
### **Results from HPC** 


**Note:** We used the following [Scripts](https://github.com/kydonis/parallel-distributed-systems-t4/tree/master/scripts) in AUTh High Performance Computing (HPC) infrastructure to test our code.  
We used different time durations for these scripts to compute the [results](https://github.com/kydonis/parallel-distributed-systems-t4/tree/master/results) for the tested matrices.  
To build and run these scripts you should contain a subfolder named "data" which will have the tested matrices.  

**Script [```v1.sh```](https://github.com/kydonis/parallel-distributed-systems-t4/blob/master/scripts/v1.sh):**
   + calculates BMM using v1 function for the following combinations of workers
   + number of workers: 2 4 8 16 20
   + creates the directory results and outputs for v1 file

**Script [```v3.sh```](https://github.com/kydonis/parallel-distributed-systems-t4/blob/master/scripts/v3.sh):**
   + calculates BMM using v1 function for the following combinations of tasks with 4 workers
   + number of tasks: 4 16
   + creates the directory results and outputs for v0 file

**Note**: The remaining script files (v0.sh, v2.sh) are in the [script](https://github.com/kydonis/parallel-distributed-systems-t4/tree/master/scripts) folder.

We created 5 arrays using the createArrays.c file in order to run the scripts with the HPC. 
Specifically, we used the following arrays: 
   + array_01.mtx (nr = 10000, nc = 10000, nnz =  926)
   + array_02.mtx (nr = 100000, nc = 100000, nnz =  100370)
   + array_03.mtx (nr = 1000000, nc = 1000000, nnz =  100000)
   + array_04.mtx (nr = 1000000, nc = 1000000, nnz =  999999)
   + array_05.mtx (nr = 1000000, nc = 1000000, nnz =  9999968)



|     |  v0 |
| --- | --- | 
| array_01 | 0.000060 | 
| array_02 | 0.003315 | 
| array_03 | 0.004157 | 
| array_04 | 0.018473 | 
| array_05 | 1.052849 | 

| v1 |  2 | 4 | 8 | 16 | 20 |
| --- | --- | --- | --- | --- | --- |
| array_01 | 0.003175 | 0.002865 | 0.004934 | 0.007313 | 0.011521 |
| array_02 | 0.026070 | 0.024627 | 0.041482 | 0.060982 | 0.069314 |
| array_03 | 0.175552 | 0.168070 | 0.286944 | 0.510560 | 0.560353 |
| array_04 | 0.185006 | 0.169186 | 0.288766 | 0.481752 | 0.565193 |
| array_05 | 0.726218 | 0.503463 | 0.289329 | 0.407794 | 0.525494 |


|  v2  |  4 | 16 |
| --- | --- | --- | 
| array_01 | 0.013536 | 0.017561 |
| array_02 | 0.040261 | 0.055346 |
| array_03 | 0.055406 | 0.047880 |
| array_04 | 0.307301 | 0.458496 |
| array_05 | 3.130619 | 3.343731 |

|  v3  |  4 |
| --- | --- |
| array_01 | 0.026144 | 
| array_02 | 0.085114 | 
| array_03 | 0.399487 |
| array_04 | 0.672515 | 
| array_05 | 3.013410 | 



