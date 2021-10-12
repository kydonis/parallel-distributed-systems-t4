#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "stack.h"

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

int existsInArray(uint32_t *arr, uint32_t length, uint32_t element) {
    for (uint32_t i = 0; i < length; i++) {
        if (arr[i] == element) {
            return 1;
        }
    }
    return 0;
}

void createArray(uint32_t nc, uint32_t nr, uint32_t targetNnz, char *name) {
    FILE *outfile = fopen (name, "w");
    if (outfile == NULL) {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }
    srand(time(NULL));

    struct Stack *stack = createStack();
    uint32_t *x = (uint32_t *) malloc(targetNnz * sizeof(uint32_t));
    uint32_t *y = (uint32_t *) malloc(targetNnz * sizeof(uint32_t));

    for (uint32_t i = 0; i < targetNnz; i++) {
        x[i] = rand() % nc + 1;
        y[i] = rand() % nc + 1;
    }

    qsort(x, targetNnz, sizeof(uint32_t), cmp);

    uint32_t prevX = -1;
    uint32_t lastIndexInY = -1;

    for (uint32_t i = 0; i < targetNnz; i++) {
        if (prevX != x[i] || lastIndexInY == -1 || !existsInArray(&y[lastIndexInY], i - 1 - lastIndexInY, y[i])) {
            struct Pair *p = (struct Pair *) malloc(sizeof(struct Pair));
            p->x = x[i];
            p->y = y[i];
            push(stack, p);
        }
        if (prevX != x[i]) {
            prevX = x[i];
            lastIndexInY = i;
        }
    }

    fprintf(outfile, "%sMatrixMarket matrix coordinate real general\n", "%%");
    fprintf(outfile, "%d %d %d\n", nr, nc, stack->top);
    for (uint32_t i = 0; i < stack->top; i++) {
        fprintf(outfile, "%d %d %lf\n", stack->array[i]->x, stack->array[i]->y, 1.0);
    }
    fclose(outfile);

    printf("\nGenerated matrix with nr: %d, d: %d, nnz: %d", nr, nc, stack->top);
    printf("\nFile name: %s\n", name);
}