SHELL := /bin/bash


# ============================================
# COMMANDS

CC = gcc-9
MPICC = mpicc
CFLAGS = -O3
OPENMP = -fopenmp
RM = rm -f
OUTPUT = *txt

# ==========================================
# TARGETS

EXECUTABLES = createArrays v0 v1 v2 v3

default: all

all: $(EXECUTABLES)

createArrays: createArrays.c  arrayutils.c mmio.c stack.c
	$(CC) $(CFLAGS) -o $@ $^

v0: v0.c readmtx.c mmio.c coo2csc.c coo2csr.c timer.c arrayutils.c controller.c stack.c serializationutils.c
	$(CC) $(CFLAGS) -o $@ $^

v1: v1.c readmtx.c mmio.c coo2csc.c coo2csr.c timer.c arrayutils.c controller.c stack.c serializationutils.c
	$(CC) $(CFLAGS) -o $@ $^ $(OPENMP)

v2: v2.c readmtx.c mmio.c coo2csc.c coo2csr.c timer.c arrayutils.c stack.c serializationutils.c
	$(MPICC) $(CFLAGS) -o $@ $^ -lm

v3: v3.c readmtx.c mmio.c coo2csc.c coo2csr.c timer.c arrayutils.c stack.c serializationutils.c
	$(MPICC) $(CFLAGS) -o $@ $^ $(OPENMP) -lm

.PHONY: clean

# ==========================================
# TESTS

testCreateArray:
	@printf "\n** Creating a random array\n"
	./createArrays 1000000 1000000 10000000 ./data/newArray.mtx

testv0: 
	@printf "\n** Testing v0 masked with random array "
	@printf "\n** nr: 1000000 nc: 1000000 nnz: 999999 \n"
	./v0 ./data/array_04.mtx

testv1: 
	@printf "\n** Testing v1 using OpenMp masked with random array and 4 workers"
	@printf "\n** nr: 1000000 nc: 1000000 nnz: 999999 \n"
	./v1 ./data/array_04.mtx 4

testv2: 
	@printf "\n** Testing v2 using MPI masked with random array and 4 tasks\n"
	@printf "\n** nr: 1000000 nc: 1000000 nnz: 999999 \n"
	mpirun -np 4 ./v2 ./data/array_04.mtx

testv3: 
	@printf "\n** Testing v3 using MPI and OpenMP with random array and 4 tasks\n"
	@printf "\n** nr: 1000000 nc: 1000000 nnz: 999999 \n"
	mpirun -np 4 ./v3 ./data/array_04.mtx


# ==========================================
# CLEAN 

clean:
	$(RM) *.o *~ $(EXECUTABLES) $(OUTPUT)