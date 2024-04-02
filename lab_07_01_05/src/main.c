#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/my_errors.h"
#include "../inc/my_filter.h"
#include "../inc/my_sort.h"
#include "../inc/my_io.h"

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    if (argc == 3 || (argc == 4 && strcmp(argv[3], "f") == 0))
    {
        int *start = 0, *end = 0;
        rc = read(argv[1], &start, &end);

        if (rc == ERR_OK && argc > 3)
        {
            int *t_start = 0, *t_end = 0;
            rc = key(start, end, &t_start, &t_end);
            free(start);
            start = t_start;
            end = t_end;
        }

        if (rc == ERR_OK)
        {
            mysort(start, end - start, sizeof(int), intcmp);
            rc = write(argv[2], start, end);
            free(start);
        }
    }
    else
    {
        if (argc != 3 && argc != 4)
            rc = ERR_ARGS_COUNT_INVALID;
        else
            rc = ERR_ARGS_INVALID;
    }
    return rc;
}
