#include <stdint.h>
#include "stack.h"

#ifndef PRESENTER_H
#define PRESENTER_H

void runAndPresentResult(uint32_t *rows1Csc, uint32_t *cols1Csc, uint32_t *rows2Csc, uint32_t *cols2Csc, uint32_t nc, void (* runnable) (uint32_t *, uint32_t *, uint32_t *, uint32_t *, struct Stack *, uint32_t), char *name, char *outputFilename, char *resultsFilename);

#endif //PRESENTER_H
