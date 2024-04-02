#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "my_struct.h"
#include "my_io.h"
#include "my_errors.h"

#define MY_NULL NULL
#define END_OF_FILE EOF

int read(const char *filename, struct subject *list, size_t *size)
{
    FILE *fin = fopen(filename, "r");
    int rc = ERR_OK;

    if (fin == MY_NULL)
    {
        rc = ERR_FILE_OPEN;
    }

    if (rc == ERR_OK)
    {
        while (rc == ERR_OK && !feof(fin) && *size < ARR_SIZE + 1)
        {
            if (!feof(fin)) 
            {
                rc = input(list + *size, fin);
            }
            if (rc == ERR_OK)
            {
                ++(*size);
            }
        }
        if (*size == 0 || *size > ARR_SIZE)
        {
            rc = ERR_FILE_INVALID;
        }
    }

    return rc;
}

int input(struct subject *elem, FILE *const fin)
{
    char buf[STR_SIZE + 3];
    int rc = ERR_OK;
    char *link = fgets(buf, STR_SIZE + 1, fin);

    if (link == MY_NULL || strlen(buf) > STR_SIZE + 1) 
    {
        rc = ERR_FILE_INVALID;
    }
    else
    {
        strcpy(elem->name, buf);
    }

    if (rc == ERR_OK)
    {
        if (fscanf(fin, "%lf\n%lf\n", &(elem->m), &(elem->v)) == 2) 
        {
            if (elem->m >= 0 && elem->v > 0) 
            {
                elem->r = elem->m / elem->v;
            }
            else
            {
                rc = ERR_FILE_INVALID;
            }
        }
        else 
        {
            rc = ERR_FILE_INVALID;
        }
    }
    return rc;
}

void write(struct subject *list, const size_t *out_index, const size_t size)
{
    for (size_t i = 0; i < size; ++i) 
    {
        print(list + out_index[i]);
    }
}

void print(struct subject const *elem)
{
    printf("%s%.6lf\n%.6lf\n", elem->name, elem->m, elem->v);
}
