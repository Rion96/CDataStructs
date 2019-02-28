#ifndef MATRIX_H
#define MATRIX_H
#include <stddef.h>

typedef struct Matrix
{
    size_t rows;
    size_t cols;
    void **array;
} Matrix;

/* Constructor for Matrix structure, 
 * demands amount of rows and columns.
 */
Matrix *matrix_init(size_t rows, size_t cols);

/* Destructor for Matrix structure.
 * Only destroys the struct, not its elements.
 * Use matrix_foreach() with &free to free elements.
 */
void matrix_destroy(Matrix *matrix);

/* Get element from specified place of matrix. */
void *matrix_get(Matrix *matrix, size_t row, size_t col);

/* Free element in matrix. */
void matrix_free(Matrix *matrix, size_t row, size_t col);

/* Put element in specified place of matrix. */
void matrix_put(Matrix *matrix, size_t row, size_t col, void *elem);

/* Free current pointer in matrix and overwrite with specified element.
 * Use matrix_put() to just overwrite the pointers.
 */
void matrix_replace(Matrix *matrix, size_t row, size_t col, void *elem);

/* Apply function to elements of matrix. */
void matrix_foreach(Matrix *matrix, void (*f)(void *elem));

#endif /* MATRIX_H */