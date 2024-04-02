#define _GNU_SOURCE

#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "my_io.h"
#include "my_errors.h"
#include "my_memory.h"

#define MY_NULL NULL
#define END_OF_FILE EOF

int read(const char *filename, struct subject **list, size_t *size)
{
    FILE *fin = fopen(filename, "r");
    int rc = ERR_OK;

    if (fin == MY_NULL)
        rc = ERR_FILE_OPEN;

    if (rc == ERR_OK)
    {
        struct subject *tmp = init(1);
        size_t buf_size = 1;
        if (tmp)
        {
            while (tmp && rc == ERR_OK && !feof(fin))
            {
                if (*size == buf_size)
                {
                    tmp = resize(tmp, buf_size);
                    if (tmp)
                        buf_size *= INCREASE;
                }
                if (tmp)
                {
                    if (!feof(fin))
                        rc = input(tmp + *size, fin);
                    if (rc == ERR_OK)
                        ++(*size);
                }
            }
            if (*size == 0)
                rc = ERR_FILE_INVALID;
        }
        if (rc && tmp)
        {
            struct_free(tmp, buf_size);
            tmp = NULL;
        }
        if (tmp)
            *list = tmp;
        else
            rc = ERR_ALLOC_MEMORY;
        fclose(fin);
    }

    return rc;
}

int input(struct subject *elem, FILE *const fin)
{
    int rc = ERR_OK;
    size_t str_len = 0;
    ssize_t ret = getline(&(elem->name), &str_len, fin);

    if (ret == -1 || elem->name == MY_NULL || str_len == 0)
        rc = ERR_FILE_INVALID;

    if (rc == ERR_OK)
    {
        if (fscanf(fin, "%lf\n%lf\n", &(elem->m), &(elem->v)) == 2)
        {
            if (elem->m >= 0 && elem->v > 0)
                elem->r = elem->m / elem->v;
            else
                rc = ERR_FILE_INVALID;
        }
        else
            rc = ERR_FILE_INVALID;
    }
    return rc;
}

void write(struct subject *list, const size_t *out_index, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
        print(list + out_index[i]);
}

void print(struct subject const *elem)
{
    printf("%s%.6lf\n%.6lf\n", elem->name, elem->m, elem->v);
}
