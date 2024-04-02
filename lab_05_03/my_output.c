#include <stdio.h>
#include <stdint.h>

#include "my_output.h"
#include "my_errors.h"

#define MY_NULL NULL
#define FILE_END SEEK_END
#define FILE_START SEEK_SET

int output(const char *name)
{
    int rc = OK;
    FILE *bin = fopen(name, "rb");
    if (bin == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        rc = fseek(bin, 0, FILE_END);
        long len = ftell(bin) >> 2;
        if (rc == OK)
            rc = fseek(bin, 0, FILE_START);
        int val;
        if (len == 0)
            rc = ERROR;
        for (size_t i = 0; (long)i < len && rc == OK; ++i)
        {
            if (fread((void*)&val, sizeof(int), 1, bin) != 1)
                rc = FILE_READ_ERROR;
            else
                fprintf(stdout, "%d\n", val);
        }
    }
    return rc;
}
