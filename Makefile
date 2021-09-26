CC=gcc
#MPICC=mpicc
CFLAGS=-O3
CBLAS=-lopenblas -lpthread -lm
N=2
COMMON_INCLUDED_FILES=readmtx.c mmio.c coo2csc.c timer.c arrayutils.c controller.c stack.c

default: all

all: v0

v0: v0.c
	$(CC) $(CFLAGS) -o $@ $^ $(COMMON_INCLUDED_FILES)

clean:
	rm -f v0




