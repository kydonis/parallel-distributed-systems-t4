/**
 *   \file coo2csr.c
 *   \brief An example of COO to CSR matrix conversion
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************************************/
/*                             routine definition                            */
/*****************************************************************************/

/**
 *  \brief COO to CSR conversion
 *
 *  Converts a square matrix from COO to CSR format.
 *
 *  Note: The routine assumes the input COO and the output CSR matrix
 *  to be square.
 *
 */
void coo2csr(
  uint32_t       * const row,       /*!< CSR row start indices */
  uint32_t       * const col,       /*!< CSR column indices */
  uint32_t const * const row_coo,   /*!< COO row indices */
  uint32_t const * const col_coo,   /*!< COO column indices */
  uint32_t const         nnz,       /*!< Number of nonzero elements */
  uint32_t const         n,         /*!< Number of rows/columns */
  uint32_t const         isOneBased /*!< Whether COO is 0- or 1-based */
) {

  // ----- cannot assume that input is already 0!
  for (uint32_t l = 0; l < n+1; l++) row[l] = 0;


  // ----- find the correct column sizes
  for (uint32_t l = 0; l < nnz; l++)
    row[row_coo[l] - isOneBased]++;

  // ----- cumulative sum
  for (uint32_t i = 0, cumsum = 0; i < n; i++) {
    uint32_t temp = row[i];
    row[i] = cumsum;
    cumsum += temp;
  }
  row[n] = nnz;
  // ----- copy the row indices to the correct place
  for (uint32_t l = 0; l < nnz; l++) {
    uint32_t row_l;
    row_l = row_coo[l] - isOneBased;

    uint32_t dst = row[row_l];
    col[dst] = col_coo[l] - isOneBased;

    row[row_l]++;
  }
  // ----- revert the column pointers
  for (uint32_t i = 0, last = 0; i < n; i++) {
    uint32_t temp = row[i];
    row[i] = last;
    last = temp;
  }

}

/*****************************************************************************/
/*                 setup example and assert correct behavior                 */
/*****************************************************************************/

//int main() {
//
//  const int nnz = 7;
//  const int n   = 5;
//
//  int * csc_row = (int *)malloc(nnz     * sizeof(int));
//  int * csc_col = (int *)malloc((n + 1) * sizeof(int));
//
//  // Example from
//  // https://medium.com/swlh/an-in-depth-introduction-to-sparse-matrix-a5972d7e8c86
//
//  int coo_row[7] = {1,2,3,4,5,5,5};
//  int coo_col[7] = {4,1,3,2,3,4,5};
//  int isOneBased = 1;
//
//  int csc_col_gold[6] = {0,1,2,4,6,7};
//  int csc_row_gold[7] = {1,3,2,4,0,4,4};
//
//  // Call coo2csc for isOneBase false
//  coo2csc(csc_row, csc_col,
//          coo_row, coo_col,
//          nnz, n,
//          isOneBased);
//
//  // Verify output
//  int pass = 1;
//  for (int i = 0; i < n + 1; i++) {
//    printf("%d ", csc_col[i]);
//    pass &= (csc_col[i] == csc_col_gold[i]);
//  }
//  printf("\n");
//  for (int i = 0; i < nnz; i++) {
//    printf("%d ", csc_row[i]);
//    pass &= (csc_row[i] == csc_row_gold[i]);
//  }
//  printf("\n");
//  if (pass) printf("Tests: PASSed\n");
//  else      printf("Tests: FAILed\n");
//
//  /* cleanup variables */
//  free( csc_row );
//  free( csc_col );
//
//
//}
