#include <stdio.h>

#include "my_errors.h"
#include "my_process.h"

int process(FILE *f, int *cnt)
{
    int curr, prev, old;
    int curr_cnt = 0;
    while (fscanf(f, "%d", &curr) == 1)
    {
        ++curr_cnt;
        if (curr_cnt > 2)
            *cnt += (curr < prev && prev > old);
        old = prev;
        prev = curr;
    }
    int rc = OK;
    if (curr_cnt == 0)
        rc = EMPTY_FILE_ERROR;
    else if (curr_cnt < 3)
        rc = NUM_COUNT_ERROR;
    return rc;
}
