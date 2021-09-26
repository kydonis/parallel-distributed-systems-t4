CC=gcc
#MPICC=mpicc
CFLAGS=-O3
CBLAS=-lopenblas -lpthread -lm
N=2
COMMON_INCLUDED_FILES=readmtx.c mmio.c coo2csc.c timer.c arrayutils.c controller.c stack.c

default: all

all: main

main: v0

#v0: v0.c utilities.c timer.c controller.c
#	$(CC) $(CFLAGS) $(CBLAS) -o $@ $^
#
#v1: v1.c utilities.c timer.c controller.c read.c
#	$(MPICC) $(CFLAGS) $(CBLAS) -o $@ $^
#
#v2: v2.c utilities.c timer.c controller.c read.c
#	$(MPICC) $(CFLAGS) $(CBLAS) -o $@ $^

v0: main.c
	$(CC) $(CFLAGS) -o $@ $^ $(COMMON_INCLUDED_FILES)

clean:
	rm -f v0




