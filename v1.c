#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "readmtx.h"
#include "coo2csc.h"
#include "coo2csr.h"
#include "arrayutils.h"
#include "controller.h"
#include "stack.h"

void cscOmpV1(uint32_t *row1, uint32_t *col1, uint32_t *row2, uint32_t *col2, struct Stack *res, uint32_t nc) {
#pragma omp parallel for
    for (uint32_t i = 0; i < nc; i++) {
        struct Stack *localRes = createStack();
        for (uint32_t j = col1[i]; j < col1[i + 1]; j++) { // Masking on matrix A
            uint32_t exists = existsCommonElementInSortedArrays(row1, col2, col1[i], col1[i + 1], row2[j], row2[j + 1]);
            if (exists > 0) {
                struct Pair *pair = (struct Pair *) malloc(sizeof(struct Pair));
                pair->x = i;
                pair->y = j;
                push(localRes, pair);
            }
        }
#pragma omp critical
        {
            for (uint32_t k = 0; k < localRes->top; k++) {
                push(res, localRes->array[k]);
            }
        }
        free(localRes);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [matrix-market-filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Starting...\n");

    uint32_t *rowsCoo, *colsCoo, nr, nc, nnz;

    readMtxFile(argv[1], &rowsCoo, &colsCoo, &nr, &nc, &nnz);

    uint32_t *rowsCsc = (uint32_t *) malloc(nnz * sizeof(uint32_t));
    uint32_t *colsCsc = (uint32_t *) malloc((nc + 1) * sizeof(uint32_t));
    uint32_t *rowsCsr = (uint32_t *)malloc((nc + 1) * sizeof(uint32_t));
    uint32_t *colsCsr = (uint32_t *)malloc(nnz * sizeof(uint32_t));
    coo2csc(rowsCsc, colsCsc, rowsCoo, colsCoo, nnz, nc, 0);
    coo2csr(rowsCsr, colsCsr, rowsCoo, colsCoo, nnz, nc, 0);

    runAndPresentResult(rowsCsc, colsCsc, rowsCsr, colsCsr, nc, cscOmpV1, "V1 OpenMP", "./v1-omp.txt","./v1-omp-results.txt");

    free(rowsCoo);
    free(colsCoo);
    free(rowsCsc);
    free(colsCsc);
    free(rowsCsr);
    free(colsCsr);

    return EXIT_SUCCESS;
}
