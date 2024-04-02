#include <stdio.h>
#include <stdlib.h>

#include "../inc/my_io.h"
#include "../inc/my_errors.h"

int read(const char *filename, int **ptr_begin, int **ptr_end)
{
    int rc = ERR_OK;
    FILE *fin = fopen(filename, "r");
    if (fin)
    {
        size_t size = 0;
        for (int tmp; fscanf(fin, "%d", &tmp) == 1; ++size);
        rewind(fin);
        int *start = 0;
        if (size)
            start = malloc(size * sizeof(int));
        if (start)
        {
            for (size_t i = 0; i < size; ++i)
                fscanf(fin, "%d", start + i);
            *ptr_begin = start;
            *ptr_end = start + size;
        }
        else
            rc = ERR_ALLOC_MEMORY;
        fclose(fin);
    }
    else
        rc = ERR_FILE_OPEN;
    return rc;
}

int write(const char *filename, const int *ptr_begin, const int *ptr_end)
{
    int rc = ERR_OK;
    FILE *fout = fopen(filename, "w");
    if (fout)
    {
        for (int *it = (int*)ptr_begin; it != ptr_end; ++it)
            fprintf(fout, "%d ", *it);
        fclose(fout);
    }
    else
        rc = ERR_FILE_OPEN;
    return rc;
}