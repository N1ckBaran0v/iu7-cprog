#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "my_errors.h"

#ifdef DYN_LOAD

typedef int (*compar_f)(const void *, const void *);
typedef void (*sort_f)(void *, size_t, size_t, compar_f);
typedef int (*key_f)(const int *, const int *, int **, int **);
typedef int (*read_f)(const char *, int **, int **);
typedef int (*write_f)(const char *, const int *, const int *);

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    void *lib = dlopen("out/libsort.so", RTLD_NOW);

    if (lib)
    {
        compar_f intcmp = dlsym(lib, "intcmp");
        sort_f mysort = dlsym(lib, "mysort");
        key_f key = dlsym(lib, "key");
        read_f read = dlsym(lib, "read");
        write_f write = dlsym(lib, "write");
        if (intcmp && mysort && key && read && write)
        {
            if (argc == 3 || (argc == 4 && strcmp(argv[3], "f") == 0))
            {
                int *start = 0, *end = 0;
                rc = read(argv[1], &start, &end);

                if (rc == ERR_OK && argc > 3)
                {
                    int *t_start = malloc((end - start) * sizeof(int)), *t_end = 0;
                    if (t_start)
                        rc = key(start, end, &t_start, &t_end);
                    else
                        rc = ERR_ALLOC_MEMORY;
                    free(start);
                    start = t_start;
                    end = t_end;
                    if (rc)
                        free(start);
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
        }
        else
            rc = ERR_LOAD_LIB;
    }
    else
        rc = ERR_LOAD_LIB;
    return rc;
}

#else

#include "my_filter.h"
#include "my_sort.h"
#include "my_io.h"

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    if (argc == 3 || (argc == 4 && strcmp(argv[3], "f") == 0))
    {
        int *start = 0, *end = 0;
        rc = read(argv[1], &start, &end);

        if (rc == ERR_OK && argc > 3)
        {
            int *t_start = malloc((end - start) * sizeof(int)), *t_end = 0;
            if (t_start)
                rc = key(start, end, &t_start, &t_end);
            else
                rc = ERR_ALLOC_MEMORY;
            free(start);
            start = t_start;
            end = t_end;
            if (rc)
                free(start);
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

#endif
