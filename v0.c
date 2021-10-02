#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "readmtx.h"
#include "coo2csc.h"
#include "arrayutils.h"
#include "controller.h"
#include "stack.h"

void cscSequentialV0(uint32_t *row1, uint32_t *col1, uint32_t *row2, uint32_t *col2, struct Stack *res, uint32_t nc) {
    uint32_t *colSizes = (uint32_t *)malloc(nc * sizeof(uint32_t));
    zeroOutArray(colSizes, nc);
    for (uint32_t i = 0; i < nc; i++) {
        for (uint32_t j = col2[i]; j < col2[i + 1]; j++) {
            colSizes[row2[j]]++;
        }
    }

    // Calculate symmetric csc values
    uint32_t *colIndexes = (uint32_t *)malloc(nc * sizeof(uint32_t));
    zeroOutArray(colIndexes, nc);
    uint32_t **symmetricRowItems = (uint32_t **)malloc(nc * sizeof(uint32_t *));
    for (uint32_t i = 0; i < nc; i++)
        symmetricRowItems[i] = (uint32_t *) malloc(colSizes[i] * sizeof(uint32_t));
    for (uint32_t i = 0; i < nc; i++) {
        for (uint32_t j = col2[i]; j < col2[i + 1]; j++) {
            symmetricRowItems[row2[j]][colIndexes[row2[j]]] = i;
            colIndexes[row2[j]]++;
        }
    }

    // Merge original with calculated symmetric csc values to form full rows and columns
    uint32_t **fullRows = (uint32_t **) malloc(nc * sizeof(uint32_t *));
    uint32_t **fullCols = (uint32_t **) malloc(nc * sizeof(uint32_t *));
    for (uint32_t curRow = 0; curRow < nc; curRow++) {
        uint32_t fullRowSize = col1[curRow + 1] - col1[curRow] + colSizes[curRow];
        uint32_t *fullRow = (uint32_t *) malloc(fullRowSize * sizeof(uint32_t));
        mergeArrays(row1 + col1[curRow], symmetricRowItems[curRow], fullRow, col1[curRow + 1] - col1[curRow], colSizes[curRow]);
        fullRows[curRow] = fullRow;
    }
    for (uint32_t curCol = 0; curCol < nc; curCol++) {
        uint32_t fullColSize = col1[curCol + 1] - col1[curCol] + colSizes[curCol];
        uint32_t *fullCol = (uint32_t *)malloc(fullColSize * sizeof(uint32_t));
        mergeArrays(row1 + col1[curCol], symmetricRowItems[curCol], fullCol, col1[curCol + 1] - col1[curCol], colSizes[curCol]);
        fullCols[curCol] = fullCol;
    }

    // Multiply
    for (uint32_t curRow = 0; curRow < nc; curRow++) {
        for (uint32_t curCol = 0; curCol < nc; curCol++) {
            uint32_t fullRowSize = col1[curRow + 1] - col1[curRow] + colSizes[curRow];
            uint32_t fullColSize = col1[curCol + 1] - col1[curCol] + colSizes[curCol];
            uint32_t *fullRow = fullRows[curRow];
            uint32_t *fullCol = fullCols[curCol];
            uint32_t sum = existsCommonElementInSortedArrays(fullRow, fullCol, fullRowSize, fullColSize);
            if (sum > 0) {
                struct Pair *pair = (struct Pair *) malloc(sizeof(struct Pair));
                pair->x = curCol;
                pair->y = curRow;
                push(res, pair);
            }
        }
    }

    for (uint32_t i = 0; i < nc; i++) {
        free(fullRows[i]);
        free(fullCols[i]);
    }
    free(fullRows);
    free(fullCols);
    for (uint32_t i = 0; i < nc; i++)
        free(symmetricRowItems[i]);
    free(symmetricRowItems);
    free(colIndexes);
    free(colSizes);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [matrix-market-filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Starting...\n");

    uint32_t *rowsCoo, *colsCoo, nr, nc, nnz;

    readMtxFile(argv[1], &rowsCoo, &colsCoo, &nr, &nc, &nnz);

    uint32_t *rowsCsc = (uint32_t *)malloc(nnz * sizeof(uint32_t));
    uint32_t *colsCsc = (uint32_t *)malloc((nc + 1) * sizeof(uint32_t));
    coo2csc(rowsCsc, colsCsc, rowsCoo, colsCoo, nnz, nc, 0);

    runAndPresentResult(rowsCsc, colsCsc, rowsCsc, colsCsc, nc, cscSequentialV0, "V0 Sequential", "./v0-seq.txt", "./v0-seq-results.txt");

    free(rowsCoo);
    free(colsCoo);
    free(rowsCsc);
    free(colsCsc);

    return EXIT_SUCCESS;
}
