#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

#include <stdint.h>

uint32_t binarySearch(uint32_t *arr, uint32_t start, uint32_t end, uint32_t target);

void zeroOutArray(uint32_t *arr, uint32_t length);

void printArray(uint32_t *arr, uint32_t length);

void mergeArrays(uint32_t *arr1, uint32_t *arr2, uint32_t *res, uint32_t length1, uint32_t length2);

uint32_t existsCommonElementInSortedArrays(uint32_t *arr1, uint32_t *arr2, uint32_t from1, uint32_t to1, uint32_t from2, uint32_t to2);

void cscMatrixVectorMultiplication(uint32_t *row, uint32_t *col, uint32_t *vector, uint32_t *res, uint32_t nc);

uint32_t cmp(const void *a, const void *b);

void createArray(uint32_t nc, uint32_t nr, uint32_t targetNnz, char *name);

#endif //ARRAYUTILS_H
