CC=gcc-9
MPICC=mpicc
CFLAGS=-O3

default: all

all: v0 v1

v0: v0.c readmtx.c mmio.c coo2csc.c coo2csr.c timer.c arrayutils.c controller.c stack.c serializationutils.c
	$(CC) $(CFLAGS) -o $@ $^

v1: v1.c readmtx.c mmio.c coo2csc.c coo2csr.c timer.c arrayutils.c controller.c stack.c serializationutils.c
	$(CC) $(CFLAGS) -o $@ $^ -fopenmp

v2: v2.c readmtx.c mmio.c coo2csc.c coo2csr.c timer.c arrayutils.c stack.c serializationutils.c
	$(MPICC) $(CFLAGS) -o $@ $^

clean:
	rm -f v0
