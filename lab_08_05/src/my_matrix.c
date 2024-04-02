#include <stdlib.h>

#include "../inc/my_matrix.h"

matrix *create_matrix(size_t n, size_t m)
{
    matrix *ret = malloc(sizeof(matrix));
    if (ret)
    {
        ret->buf = malloc(n * sizeof(int64_t *) + n * m * (sizeof(int64_t)));
        if (ret->buf)
        {
            ret->n = n;
            ret->m = m;
            ret->buf[0] = (int64_t *)((char *)ret->buf + n * sizeof(int64_t *));
            for (size_t i = 1; i < n; ++i)
                ret->buf[i] = ret->buf[i - 1] + m;
        }
        else
        {
            free(ret);
            ret = NULL;
        }
    }
    return ret;
}

void free_matrix(matrix *matr)
{
    if (matr)
        free(matr->buf);
    free(matr);
}

matrix *resize_matrix(matrix *matr, size_t n)
{
    matrix *new = create_matrix(n, n);
    if (new)
    {
        for (size_t i = 0; i < matr->n; ++i)
            for (size_t j = 0; j < matr->m; ++j)
                new->buf[i][j] = matr->buf[i][j];
        new->n = matr->n;
        new->m = matr->m;
    }
    free_matrix(matr);
    return new;
}

void find_min(matrix *matr, size_t *i0, size_t *j0)
{
    *i0 = *j0 = 0;
    for (size_t i = 0; i < matr->n; ++i)
    {
        for (size_t j = 0; j < matr->m; ++j)
        {
            if (matr->buf[i][j] < matr->buf[*i0][*j0])
            {
                *i0 = i;
                *j0 = j;
            }
        }
    }
}

void del_row(matrix *matr, size_t i0)
{
    for (size_t i = i0 + 1; i < matr->n; ++i)
        for (size_t j = 0; j < matr->m; ++j)
            matr->buf[i - 1][j] = matr->buf[i][j];
    --(matr->n);
}

void del_col(matrix *matr, size_t j0)
{
    for (size_t j = j0 + 1; j < matr->m; ++j)
        for (size_t i = 0; i < matr->n; ++i)
            matr->buf[i][j - 1] = matr->buf[i][j];
    --(matr->m);
}