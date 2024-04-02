#include <stdlib.h>

#include "../inc/my_resize.h"
#include "../inc/my_io.h"
#include "../inc/my_errors.h"

int64_t multcol(const matrix *matr, size_t col);
int64_t maxval(const matrix *matr, size_t row);
int64_t pow64(int64_t val, size_t cnt);
int64_t mid_geom(int64_t val, size_t cnt);

void to_square(matrix *this)
{
    while (this->n != this->m)
    {
        size_t i0 = 0, j0 = 0;
        find_min(this, &i0, &j0);
        if (this->n > this->m)
        {
            del_row(this, i0);
        }
        else
        {
            del_col(this, j0);
        }
    }
}

int increase(matrix **first, matrix **second)
{
    int rc = ERR_OK;
    matrix *tmp;
    size_t et;
    if ((*first)->n > (*second)->n)
    {
        tmp = resize_matrix(*second, (*first)->n);
        *second = tmp;
        et = (*first)->n;
    }
    else
    {
        tmp = resize_matrix(*first, (*second)->n);
        *first = tmp;
        et = (*second)->n;
    }
    if (tmp)
    {
        for (size_t j = 0; j < tmp->m; ++j)
        {
            int64_t filler = mid_geom(multcol(tmp, j), tmp->n);
            for (size_t i = tmp->n; i < et; ++i)
                tmp->buf[i][j] = filler;
        }
        tmp->n = et;
        for (size_t i = 0; i < tmp->n; ++i)
        {
            int64_t filler = maxval(tmp, i);
            for (size_t j = tmp->m; j < et; ++j)
                tmp->buf[i][j] = filler;
        }
        tmp->m = et;
    }
    else
        rc = ERR_ALLOC_MEM;
    return rc;
}

int64_t multcol(const matrix *matr, size_t col)
{
    int64_t ret = 1;
    for (size_t i = 0; i < matr->n; ++i)
        ret *= abs(matr->buf[i][col]);
    return ret;
}

int64_t maxval(const matrix *matr, size_t row)
{
    int64_t ret = matr->buf[row][0];
    for (size_t j = 1; j < matr->m; ++j)
        if (matr->buf[row][j] > ret)
            ret = matr->buf[row][j];
    return ret;
}

int64_t mid_geom(int64_t val, size_t cnt)
{
    int64_t res = 0;
    for (; pow64(res, cnt) <= val; ++res);
    return res - 1;
}

int64_t pow64(int64_t val, size_t cnt)
{
    int64_t mult = val;
    int64_t res = 1;
    while (cnt)
    {
        if (cnt & 1)
            res *= mult;
        mult *= mult;
        cnt >>= 1;
    }
    return res;
}