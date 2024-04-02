#include "../inc/my_multiple.h"
#include "../inc/my_errors.h"
#include "../inc/my_matrix.h"

matrix *create_identity_matrix(size_t size);
void matr_mult(matrix *first, matrix *second, matrix *buf);

int mult(matrix **first, matrix *second, size_t ro, size_t phi)
{
    int rc = ERR_OK;
    if (first && *first && second)
    {
        if ((*first)->n == (*first)->m && second->n == second->m && (*first)->n == second->n)
        {
            matrix *dst = create_identity_matrix((*first)->n);
            matrix *tmp = create_matrix((*first)->n, (*first)->n);
            if (dst && tmp)
            {
                for (size_t i = 0; i < ro; ++i)
                    matr_mult(dst, *first, tmp);
                for (size_t i = 0; i < phi; ++i)
                    matr_mult(dst, second, tmp);
                free_matrix(*first);
                *first = dst;
            }
            else
                rc = ERR_ALLOC_MEM;
            free_matrix(tmp);
        }
        else
            rc = ERR_INVALID_ARGS;
    }
    else
        rc = ERR_INVALID_ARGS;

    return rc;
}

matrix *create_identity_matrix(size_t size)
{
    matrix *ret = create_matrix(size, size);
    if (ret)
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
                ret->buf[i][j] = (i == j);
    return ret;
}

void matr_mult(matrix *first, matrix *second, matrix *buf)
{
    int64_t tmp;
    for (size_t i = 0; i < first->n; ++i)
    {
        for (size_t j = 0; j < first->m; ++j)
        {
            tmp = 0;
            for (size_t k = 0; k < second->m; ++k)
            {
                tmp += first->buf[i][k] * second->buf[k][j];
            }
            buf->buf[i][j] = tmp;
        }
    }
    for (size_t i = 0; i < first->n; ++i)
    {
        for (size_t j = 0; j < first->m; ++j)
        {
            first->buf[i][j] = buf->buf[i][j];
        }
    }
}