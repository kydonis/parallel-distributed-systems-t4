#ifndef COO2CSR_H
#define COO2CSR_H

#include <stdint.h>

/* This ifdef allows the header to be used from both C and C++. */
#ifdef __cplusplus
extern "C" {
#endif

void coo2csr(
        uint32_t       * const row,       /*!< CSR row start indices */
        uint32_t       * const col,       /*!< CSR column indices */
        uint32_t const * const row_coo,   /*!< COO row indices */
        uint32_t const * const col_coo,   /*!< COO column indices */
        uint32_t const         nnz,       /*!< Number of nonzero elements */
        uint32_t const         n,         /*!< Number of rows/columns */
        uint32_t const         isOneBased /*!< Whether COO is 0- or 1-based */
);

#ifdef __cplusplus
}
#endif

#endif
