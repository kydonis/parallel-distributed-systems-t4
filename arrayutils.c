#include <stdio.h> // fprintf, printf
#include <stdlib.h> // malloc
#include <stdint.h>

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

uint32_t countCommonElementsInSortedArrays(uint32_t *arr1, uint32_t *arr2, uint32_t length1, uint32_t length2) {
    uint32_t sum = 0;
    uint32_t index1 = 0;
    uint32_t index2 = 0;
    while (index1 < length1 && index2 < length2) {
        if (arr1[index1] < arr2[index2]) {
            index1++;
        } else if (arr1[index1] > arr2[index2]) {
            index2++;
        } else {
            sum++;
            index1++;
            index2++;
        }
    }
    return sum;
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
