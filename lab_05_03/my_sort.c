#include <stdio.h>
#include <stddef.h>

#include "my_sort.h"
#include "my_errors.h"

#define MY_NULL NULL
#define FILE_END SEEK_END
#define FILE_START SEEK_SET

int get_number_by_pos(FILE *bin, size_t pos, int *val)
{
    int rc = OK;
    rc = fseek(bin, pos, FILE_START);
    if (rc == OK)
        if (fread((void*)val, sizeof(int), 1, bin) != 1)
            rc = FILE_READ_ERROR;
    return rc;
}

int put_number_by_pos(FILE *bin, size_t pos, int *val)
{
    int rc = OK;
    rc = fseek(bin, pos, FILE_START);
    if (rc == OK)
        if (fwrite((void*)val, sizeof(int), 1, bin) != 1)
            rc = FILE_WRITE_ERROR;
    return rc;
}

int quick_sort(FILE *bin, size_t left, size_t right)
{
    int rc = OK;
    int mid = 0, val = 0;
    rc = get_number_by_pos(bin, (((left + right) >> 1) / sizeof(int)) * sizeof(int), &mid);
    size_t i = left;
    size_t j = right;
    while (rc == OK && i <= j)
    {
        if (rc == OK)
            rc = get_number_by_pos(bin, i, &val);
        while (rc == OK && val < mid)
        {
            i += sizeof(int);
            rc = get_number_by_pos(bin, i, &val);
        }
        if (rc == OK)
            rc = get_number_by_pos(bin, j, &val);
        while (rc == OK && val > mid)
        {
            j -= sizeof(int);
            rc = get_number_by_pos(bin, j, &val);
        }
        if (rc == OK && i <= j)
        {
            rc = swap(bin, i, j);
            i += sizeof(int);
            if (j)
                j -= sizeof(int);
        }
    }
    if (rc == OK && left < j)
        rc = quick_sort(bin, left, j);
    if (rc == OK && right > i)
        rc = quick_sort(bin, i, right);
    return rc;
}

int swap(FILE *bin, size_t pos_l, size_t pos_r)
{
    int first, second;
    int rc = get_number_by_pos(bin, pos_l, &first);
    if (rc == OK)
        get_number_by_pos(bin, pos_r, &second);
    if (rc == OK)
        put_number_by_pos(bin, pos_l, &second);
    if (rc == OK)
        put_number_by_pos(bin, pos_r, &first);
    return rc;
}

int sort(const char *name)
{
    int rc = OK;
    FILE *bin = fopen(name, "r+b");
    if (bin == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        rc = fseek(bin, 0, FILE_END);
        size_t last = ftell(bin);
        if (rc == OK)
            rc = fseek(bin, 0, FILE_START);
        if (last == 0)
            rc = ERROR;
        if (rc == OK && last > 1)
            rc = quick_sort(bin, 0, last -= sizeof(int));
    }
    return rc;
}
