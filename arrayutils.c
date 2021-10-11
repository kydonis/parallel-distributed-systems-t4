#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "mmio.h"

uint32_t binarySearch(uint32_t *arr, uint32_t start, uint32_t end, uint32_t target) {
    while (start <= end) {
        uint32_t middle = (start + end) / 2;
        if (arr[middle] < target)
            start = middle + 1;
        else if (arr[middle] > target)
            end = middle - 1;
        else
            return 1;
    }
    return 0;
}

void zeroOutArray(uint32_t *arr, uint32_t length) {
    for (uint32_t i = 0; i < length; i++)
        arr[i] = 0;
}

void printArray(uint32_t *arr, uint32_t length) {
    for (uint32_t i = 0; i < length; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void mergeArrays(uint32_t *arr1, uint32_t *arr2, uint32_t *res, uint32_t length1, uint32_t length2) {
    uint32_t index1 = 0;
    uint32_t index2 = 0;
    while (index1 < length1 && index2 < length2) {
        if (arr1[index1] < arr2[index2]) {
            res[index1 + index2] = arr1[index1];
            index1++;
        } else {
            res[index1 + index2] = arr2[index2];
            index2++;
        }
    }
    while (index1 < length1) {
        res[index1 + index2] = arr1[index1];
        index1++;
    }
    while (index2 < length2) {
        res[index1 + index2] = arr2[index2];
        index2++;
    }
}

uint32_t existsCommonElementInSortedArrays(uint32_t *arr1, uint32_t *arr2, uint32_t from1, uint32_t to1, uint32_t from2, uint32_t to2) {
    uint32_t index1 = from1;
    uint32_t index2 = from2;
    while (index1 < to1 && index2 < to2) {
        if (arr1[index1] < arr2[index2]) {
            index1++;
        } else if (arr1[index1] > arr2[index2]) {
            index2++;
        } else {
            return 1;
        }
    }
    return 0;
}

void cscMatrixVectorMultiplication(uint32_t *row, uint32_t *col, uint32_t *vector, uint32_t *res, uint32_t nc) {
    for (uint32_t i = 0; i < nc; i++) {
        res[i] = 0;
        for (uint32_t j = col[i]; j < col[i + 1]; j++)
            res[i] += vector[row[j]];
    }
}

uint32_t cmp(const void *a, const void *b) {
    return (*(uint32_t *)a - *(uint32_t *)b);
}

void createArray(uint32_t nc, uint32_t nr, double density, char *name) {

    MM_typecode matcode; 
    FILE *outfile;

    int counter = 0;

    outfile = fopen (name, "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_coordinate(&matcode);
    mm_set_real(&matcode);


    // mm_write_banner(outfile, matcode); 
    // mm_write_mtx_crd_size(outfile, nc, nr, counter);

    srand(time(NULL)); 



    // fprintf(outfile, "%%Random generated matrix");

    mm_write_banner(outfile, matcode);
    fprintf(outfile, "                  ");

    for (int j = 1; j < nr; j++){
        double r1 = (double)rand()/RAND_MAX;

        if (r1 < density) {

            for (int i = 1; i < nc; i++) {
                double r2 = (double)rand()/RAND_MAX;

                if (r2 < density && i != j) {
                    // printf("\nx: %d, y: %d", i, j);
                    fprintf(outfile, "%d %d\n", i, j);
                    counter++;
                }
            }
        }
    }

    fseek(outfile, 0, SEEK_SET);
    
    mm_write_banner(outfile, matcode); 
    mm_write_mtx_crd_size(outfile, nc, nr, counter);
    // fprintf(outfile, "%%Random generated matrix");
    // fprintf(outfile, "\n%d %d %d", nr, nc, counter);
    fclose(outfile);

    printf("\nGenerated matrix with nr: %d, d: %d, nnz: %d", nr, nc, counter);
    printf("\nFile name: %s\n", name);

}