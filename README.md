# BMM algorithm
# **Parallel and Distributed Computer Systems**  
## **Exercise 4**
## Kydonis Ioannis     |   <br />
## Meta Louis-Kosmas    | louismeta@ece.auth.gr <br />

---
### Contents
   1. [How to build](#1)
   2. [Results from HPC](#2)
   3. [Graphs](#3)
   
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


---
<a name="3"></a>
### **Graphs** 
