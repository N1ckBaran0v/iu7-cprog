#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "my_create.h"
#include "my_errors.h"

#define MY_NULL NULL

long convert(char *size)
{
    long val = 0;
    for (size_t i = 0; size[i] && val != -1; ++i)
    {
        if (isdigit(size[i]));
        else
            val = -1;
    }
    if (val == 0)
        val = atol(size);
    return val;
}


int create(const char *name, char *size)
{
    int rc = OK;
    long num = convert(size);
    if (num > 0)
    {
        srand(time(0));
        FILE *bin = fopen(name, "wb");
        if (bin == MY_NULL)
            rc = FILE_OPEN_ERROR;
        else
        {
            int val;
            for (size_t i = 0; (long)i < num && rc == OK; ++i)
            {
                val = (int)rand();
                if (fwrite((void*)&val, sizeof(int), 1, bin) != 1)
                    rc = FILE_WRITE_ERROR;
            }
            fclose(bin);
        }
    }
    else 
        rc = ERROR;
    return rc;
}
