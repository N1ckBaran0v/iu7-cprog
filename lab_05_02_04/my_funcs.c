#include <stdio.h>
#include <math.h>

#include "my_errors.h"
#include "my_funcs.h"

#define MY_NULL NULL

int find(const char *name, int *min_pos, int *max_pos)
{
    FILE *fin = fopen(name, "r");
    int rc = OK;
    if (fin == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        int cnt = 0, max_cnt, min_cnt;
        double curr, max_val, min_val;
        double eps = 5e-7;
        while (fscanf(fin, "%lf", &curr) == 1)
        {
            if (cnt == 0)
            {
                max_val = min_val = curr;
                min_cnt = max_cnt = 1;
                *min_pos = *max_pos = 0;
            }
            else
            {
                if (fabs(curr - max_val) < eps)
                    ++max_cnt;
                if (fabs(curr - min_val) < eps)
                    ++min_cnt;
                if (curr > max_val)
                {
                    max_val = curr;
                    *max_pos = cnt;
                    max_cnt = 1;
                }
                if (curr < min_val)
                {
                    min_val = curr;
                    *min_pos = cnt;
                    min_cnt = 1;
                }
            }
            ++cnt;
        }
        if (cnt == 0)
            rc = EMPTY_FILE_ERROR;
        else if (min_cnt + max_cnt > 2)
            rc = VAL_COUNT_ERROR;
    }
    if (rc != FILE_OPEN_ERROR)
        fclose(fin);
    return rc;
}

int average(const char *name, int min_pos, int max_pos, double *ans)
{
    FILE *fin = fopen(name, "r");
    int rc = OK;
    if (fin == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        int diff = min_pos - max_pos;
        if (diff < 0)
            diff ^= ~0;
        else
            --diff;
        if (diff > 0) 
        {
            int stop = min_pos;
            if (stop > max_pos)
                stop = max_pos;
            int i = 0;
            double curr;
            for (; fscanf(fin, "%lf", &curr) == 1 && i < stop; ++i);
            stop += diff;
            for (; fscanf(fin, "%lf", &curr) == 1 && i < stop; ++i)
                *ans += curr;
            *ans /= diff;
        }
        else
            rc = RANGE_ERROR;
    }
    if (rc != FILE_OPEN_ERROR)
        fclose(fin);
    return rc;
}
