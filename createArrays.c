#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "arrayutils.h"



int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s [nr] [nc] [density] [array-name]\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t nr = atoi(argv[1]);
    uint32_t nc = atoi(argv[2]);
    double density = atof(argv[3]);
    char *name = argv[4];

    createArray(nr, nc, density, name);


}