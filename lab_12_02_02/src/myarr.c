#include "myarr.h"

void fill_by_fib(int64_t *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (i < 2)
            arr[i] = i;
        else
            arr[i] = arr[i - 1] + arr[i - 2];
    }
}

void pos_first_found(int64_t *dst, int64_t *arr, size_t size)
{
    size_t j;
    for (size_t i = 0; i < size; ++i)
    {
        for (j = 0; arr[j] != arr[i]; ++j);
        dst[i] = j;
    }
}