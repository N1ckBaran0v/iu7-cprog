#include <stddef.h>
#include <stdlib.h>

#include "my_filter.h"
#include "my_errors.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int rc = ERR_OK;
    if (pe_src <= pb_src)
        rc = ERR_OTHER;
    else
    {
        size_t new_size = 0;
        long long sum = 0;
        for (int *it = (int*)pe_src; it != pb_src; --it)
        {
            if (it != (int*)pe_src && *(it - 1) > sum)
                ++new_size;
            sum += *(it - 1);
        }
        int *new_arr = 0;
        if (new_size)
            new_arr = *pb_dst;
        if (new_arr)
        {
            int *new_it = new_arr + new_size;
            sum = 0;
            for (int *it = (int*)pe_src; it > pb_src; --it)
            {
                if (it != (int*)pe_src && *(it - 1) > sum)
                {
                    *(new_it - 1) = *(it - 1);
                    --new_it;
                }
                sum += *(it - 1);
            }
            *pe_dst = new_arr + new_size;
        }
        else
            rc = ERR_OTHER;
    }
    return rc;
}