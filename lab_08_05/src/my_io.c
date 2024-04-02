#include <stdio.h>
#include <stdlib.h>

#include "../inc/my_io.h"
#include "../inc/my_errors.h"

int read_matrix(matrix **this);

int read(matrix **first, matrix **second, size_t *ro, size_t *phi)
{
    int rc = read_matrix(first);
    if (rc == ERR_OK)
        rc = read_matrix(second);
    if (rc == ERR_OK)
    {
        long long tmp1, tmp2;
        if (scanf("%lld %lld", &tmp1, &tmp2) != 2)
            rc = ERR_INPUT_ERROR;
        else if (tmp1 < 0 || tmp2 < 0)
            rc = ERR_SIZE_INVALID;
        else
        {
            *ro = (size_t)tmp1;
            *phi = (size_t)tmp2;
        }
    }
    return rc;
}

void write(matrix *this)
{
    for (size_t i = 0; i < this->n; ++i)
    {
        for (size_t j = 0; j < this->m; ++j)
            printf("%lld ", (long long)this->buf[i][j]);
        printf("\n");
    }
}

int read_matrix(matrix **this)
{
    int rc = ERR_OK;
    long long rows, columns, tmp;
    if (scanf("%lld %lld", &rows, &columns) != 2)
        rc = ERR_INPUT_ERROR;
    else if (rows < 1 || columns < 1)
        rc = ERR_SIZE_INVALID;
    else
    {
        *this = create_matrix((size_t)rows, (size_t)columns);
        if (!(*this))
            rc = ERR_ALLOC_MEM;
    }
    if (rc == ERR_OK)
    {
        for (size_t i = 0; rc == ERR_OK && i < (*this)->n; ++i)
        {
            for (size_t j = 0; rc == ERR_OK && j < (*this)->m; ++j)
            {
                if (scanf("%lld", &tmp) != 1)
                    rc = ERR_INPUT_ERROR;
                else
                    (*this)->buf[i][j] = (size_t)tmp;
            }
        }
    }
    if (*this && rc)
    {
        free_matrix(*this);
        *this = NULL;
    }
    return rc;
}