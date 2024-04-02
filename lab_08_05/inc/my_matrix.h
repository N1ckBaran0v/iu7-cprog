#ifndef __MY_MATRIX_H__

#define __MY_MATRIX_H__

#include <stddef.h>
#include <stdint.h>

typedef struct matrix matrix;

struct matrix
{
    int64_t **buf;
    size_t n, m;
};

matrix *create_matrix(size_t n, size_t m);
void free_matrix(matrix *matr);
matrix *resize_matrix(matrix *matr, size_t n);
void find_min(matrix *matr, size_t *i0, size_t *j0);
void del_row(matrix *matr, size_t i0);
void del_col(matrix *matr, size_t j0);

#endif //__MY_MATRIX_H__