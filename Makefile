CC=gcc
#MPICC=mpicc
CFLAGS=-O3

default: all

all: v0

v0: v0.c readmtx.c mmio.c coo2csc.c timer.c arrayutils.c controller.c stack.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f v0
