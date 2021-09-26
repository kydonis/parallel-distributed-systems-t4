#ifndef READMTX_H
#define READMTX_H

#include <stdint.h>

/* This ifdef allows the header to be used from both C and C++. */
#ifdef __cplusplus
extern "C" {
#endif

int readMtxFile(char *filename, uint32_t **rows, uint32_t **columns, uint32_t *rowCount, uint32_t *colCount, uint32_t *nnz);

#ifdef __cplusplus
}
#endif

#endif
