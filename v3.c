#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include "readmtx.h"
#include "coo2csc.h"
#include "coo2csr.h"
#include "arrayutils.h"
#include "stack.h"
#include "serializationutils.h"

void cscDistributedOmpV3(uint32_t *row1, uint32_t *col1, uint32_t *row2, uint32_t *col2, struct Stack *res, uint32_t nc, uint32_t offsetX, uint32_t offsetY) {
#pragma omp parallel for
    for (uint32_t i = 0; i < nc; i++) {
        struct Stack *localRes = createStack();
        for (uint32_t j = 0; j < nc; j++) {
            uint32_t exists = existsCommonElementInSortedArrays(row1, col2, col1[i], col1[i + 1], row2[j], row2[j + 1]);
            if (exists > 0) {
                struct Pair *pair = (struct Pair *) malloc(sizeof(struct Pair));
                pair->x = i + offsetX;
                pair->y = j + offsetY;
                push(localRes, pair);
            }
        }
#pragma omp critical
        {
            for (int k = 0; k < localRes->top; k++) {
                push(res, localRes->array[k]);
            }
        }
        free(localRes);
    }
}

void saveOutput(struct Stack *results, char *filename) {
    FILE *f = fopen(filename, "wb");
    struct Pair **pairs = getArrayCopy(results);
    for (uint32_t i = 0; i < results->top; i++) {
        fprintf(f, "%d, %d\n", pairs[i]->x, pairs[i]->y);
    }
    fclose(f);
}

void saveStats(char *name, double time, char *filename) {
    FILE *f = fopen(filename, "wb");
    fprintf(f, "Algorithm: %s\n", name);
    fprintf(f, "Time: %lf sec\n", time);
    fclose(f);
}

int main(int argc, char *argv[]) {
    int initialized, finalized, SelfTID, NumTasks;

    uint32_t *rowsCoo, *colsCoo, nr, nc, nnz;

    MPI_Initialized(&initialized);
    if (!initialized){
        MPI_Init(&argc, &argv);
    }
    MPI_Status mpistat;
    MPI_Request mpireq;
    MPI_Comm_size(MPI_COMM_WORLD, &NumTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &SelfTID);

    uint32_t blocksPerRow = sqrt(NumTasks);

    struct timespec ts_start;
    struct timespec ts_end;

    if (SelfTID == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage: mpirun -np [num-of-tasks] %s [matrix-market-filename]\n", argv[0]);
            return EXIT_FAILURE;
        }

        printf("Starting...\n");

        readMtxFile(argv[1], &rowsCoo, &colsCoo, &nr, &nc, &nnz);

        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        uint32_t elementsPerBlock = nc / blocksPerRow;

        struct Stack **blocks = (struct Stack **) malloc(blocksPerRow * blocksPerRow * sizeof(struct Stack *));
        for (uint32_t i = 0; i < blocksPerRow * blocksPerRow; i++) {
            blocks[i] = createStack();
        }

        for (uint32_t i = 0; i < nnz; i++) {
            uint32_t rowIndex = rowsCoo[i] / elementsPerBlock;
            uint32_t colIndex = colsCoo[i] / elementsPerBlock;

            struct Pair *pair = (struct Pair *) malloc(sizeof(struct Pair));
            pair->x = rowsCoo[i] % elementsPerBlock;
            pair->y = colsCoo[i] % elementsPerBlock;

            push(blocks[blocksPerRow * rowIndex + colIndex], pair);
        }

        for (uint32_t step = 0; step < blocksPerRow; step++) {
            for (uint32_t i = 0; i < blocksPerRow * blocksPerRow; i++) {
                uint32_t row = i / blocksPerRow;
                uint32_t col = i % blocksPerRow;

                uint32_t blockAIdx = row * blocksPerRow + step;
                uint32_t blockBIdx = col + step * blocksPerRow;

                uint32_t *blockA = (uint32_t *) malloc((blocks[blockAIdx]->top * 2 + 2) * sizeof(uint32_t));
                serializeStack(blocks[blockAIdx], blockA, nc / blocksPerRow);
                MPI_Isend(&blockA[0], 1, MPI_UINT32_T, i, 55, MPI_COMM_WORLD, &mpireq);
                MPI_Isend(blockA, blockA[0] * 2 + 2, MPI_UINT32_T, i, 55, MPI_COMM_WORLD, &mpireq);

                uint32_t *blockB = (uint32_t *) malloc((blocks[blockBIdx]->top * 2 + 2) * sizeof(uint32_t));
                serializeStack(blocks[blockBIdx], blockB, nc / blocksPerRow);
                MPI_Isend(&blockB[0], 1, MPI_UINT32_T, i, 55, MPI_COMM_WORLD, &mpireq);
                MPI_Isend(blockB, blockB[0] * 2 + 2, MPI_UINT32_T, i, 55, MPI_COMM_WORLD, &mpireq);
            }
        }
    }
    MPI_Bcast(&nc, 1, MPI_UINT32_T, 0, MPI_COMM_WORLD);
    uint32_t elementsPerBlock = nc / blocksPerRow;
    struct Stack *res = createStack();
    for (uint32_t i = 0; i < blocksPerRow; i++) {
        uint32_t cnt;
        MPI_Recv(&cnt, 1, MPI_UINT32_T, 0, 55, MPI_COMM_WORLD, &mpistat);

        uint32_t *blockA = (uint32_t *) malloc((cnt * 2 + 2) * sizeof(uint32_t));
        MPI_Recv(blockA, cnt * 2 + 2, MPI_UINT32_T, 0, 55, MPI_COMM_WORLD, &mpistat);

        uint32_t *rowsCooA = (uint32_t *) malloc(cnt * sizeof(uint32_t));
        uint32_t *colsCooA = (uint32_t *) malloc(cnt * sizeof(uint32_t));

        MPI_Recv(&cnt, 1, MPI_UINT32_T, 0, 55, MPI_COMM_WORLD, &mpistat);

        uint32_t *blockB = (uint32_t *) malloc((cnt * 2 + 2) * sizeof(uint32_t));
        MPI_Recv(blockB, cnt * 2 + 2, MPI_UINT32_T, 0, 55, MPI_COMM_WORLD, &mpistat);

        uint32_t *rowsCooB = (uint32_t *) malloc(cnt * sizeof(uint32_t));
        uint32_t *colsCooB = (uint32_t *) malloc(cnt * sizeof(uint32_t));
        uint32_t ncc;
        deserializeToCoo(blockA, rowsCooA, colsCooA, &ncc);
        deserializeToCoo(blockB, rowsCooB, colsCooB, &ncc);

        uint32_t *rowsCsc = (uint32_t *)malloc(blockA[0] * sizeof(uint32_t));
        uint32_t *colsCsc = (uint32_t *)malloc((ncc + 1) * sizeof(uint32_t));
        uint32_t *rowsCsr = (uint32_t *)malloc((ncc + 1) * sizeof(uint32_t));
        uint32_t *colsCsr = (uint32_t *)malloc(blockB[0] * sizeof(uint32_t));
        coo2csc(rowsCsc, colsCsc, rowsCooA, colsCooA, blockA[0], ncc, 0);
        coo2csr(rowsCsr, colsCsr, rowsCooB, colsCooB, blockB[0], ncc, 0);

        uint32_t row = SelfTID / blocksPerRow;
        uint32_t col = SelfTID % blocksPerRow;
        cscDistributedOmpV3(rowsCsc, colsCsc, rowsCsr, colsCsr, res, ncc, col * elementsPerBlock, row * elementsPerBlock);

        free(rowsCooA);
        free(colsCooA);
        free(rowsCooB);
        free(colsCooB);
        free(rowsCsc);
        free(colsCsc);
        free(rowsCsr);
        free(colsCsr);
        free(blockA);
        free(blockB);
    }

    uint32_t *serializedRes = (uint32_t *) malloc((2 * res->top + 2) * sizeof(uint32_t));
    serializeStack(res, serializedRes, 0);
    uint32_t cnt = res->top;
    MPI_Isend(&cnt, 1, MPI_UINT32_T, 0, 55, MPI_COMM_WORLD, &mpireq);
    MPI_Isend(serializedRes, 2 * res->top + 2, MPI_UINT32_T, 0, 55, MPI_COMM_WORLD, &mpireq);

    if (SelfTID == 0) {
        struct Stack *fullRes = createStack();
        for (uint32_t i = 0; i < blocksPerRow * blocksPerRow; i++) {
            uint32_t recvCnt;
            MPI_Recv(&recvCnt, 1, MPI_UINT32_T, i, 55, MPI_COMM_WORLD, &mpistat);

            uint32_t *recvRes = (uint32_t *) malloc((recvCnt * 2 + 2) * sizeof(uint32_t));
            MPI_Recv(recvRes, recvCnt * 2 + 2, MPI_UINT32_T, i, 55, MPI_COMM_WORLD, &mpistat);

            deserializedIntoStack(recvRes, fullRes);
        }

        clock_gettime(CLOCK_MONOTONIC, &ts_end);
        double time = (ts_end.tv_sec - ts_start.tv_sec) + (ts_end.tv_nsec - ts_start.tv_nsec) / 1000000000.0;
        printf("-----------------------------------\n");
        printf("| Algorithm: %s\n", "V3 MPI + OpenMP");
        printf("| Time: %10.6lf\n", time);
        printf("-----------------------------------\n");
        saveOutput(fullRes, "v3-mpi-omp.txt");
        saveStats("V3 MPI + OpenMP", time, "v3-mpi-omp-results.txt");
        free(fullRes);
    }

    MPI_Finalized(&finalized);
    if (!finalized) {
        MPI_Finalize();
    }
    free(serializedRes);
    free(res);

    return EXIT_SUCCESS;
}
