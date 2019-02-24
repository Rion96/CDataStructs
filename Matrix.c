#include "Matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct Matrix *matrix_init(size_t rows, size_t cols)
{
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    if (matrix == NULL)
    {
        fprintf(stderr, "Error: Could not initialize Matrix struct!\n");
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->array = calloc(rows * cols, sizeof(void *));
    if (matrix->array == NULL)
    {
        free(matrix);
        fprintf(stderr, "Error: Could not allocate Matrix array!\n");
        return NULL;
    }
    return matrix;
}

void matrix_destroy(struct Matrix *matrix)
{
    if (matrix == NULL)
    {
        return;
    }
    free(matrix->array);
    free(matrix);
}

void *matrix_get(struct Matrix *matrix, size_t row, size_t col)
{
    if (matrix == NULL)
    {
        return NULL;
    }
    if (row >= matrix->rows || col >= matrix->cols)
    {
        return NULL;
    }
    return matrix->array[row * matrix->rows + col];
}

void matrix_free(struct Matrix *matrix, size_t row, size_t col)
{
    free(matrix_get(matrix, row, col));
}

void matrix_put(struct Matrix *matrix, size_t row, size_t col, void *elem)
{
    if (matrix == NULL)
    {
        return;
    }
    if (row >= matrix->rows || col >= matrix->cols)
    {
        return;
    }
    matrix->array[row * matrix->rows + col] = elem;
}

void matrix_replace(struct Matrix *matrix, size_t row, size_t col, void *elem)
{
    matrix_free(matrix, row, col);
    matrix_put(matrix, row, col, elem);
}

void matrix_foreach(struct Matrix *matrix, void (*f)(void *elem))
{
    if (matrix == NULL)
    {
        return;
    }
    size_t total = matrix->rows * matrix->cols;
    for(int i = 0; i < total; i++)
    {
        (*f)(matrix->array[i]);
    }
}