#include <stdio.h>
#include <stdint.h>
#include "timer.h"
#include "stack.h"

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

void runAndPresentResult(uint32_t *rows1Csc, uint32_t *cols1Csc, uint32_t *rows2Csc, uint32_t *cols2Csc, uint32_t nc, void (* runnable) (uint32_t *, uint32_t *, uint32_t *, uint32_t *, struct Stack *, uint32_t), char *name, char *outputFilename, char *resultsFilename) {
    struct Stack *res = createStack();
    double time = measureTimeForRunnable(runnable, rows1Csc, cols1Csc, rows2Csc, cols2Csc, res, nc);
    printf("-----------------------------------\n");
    printf("| Algorithm: %s\n", name);
    printf("| Time: %10.6lf\n", time);
    printf("-----------------------------------\n");
    saveOutput(res, outputFilename);
    saveStats(name, time, resultsFilename);
    free(res);
}
