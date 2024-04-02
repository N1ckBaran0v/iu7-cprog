#include <stdio.h>
#include <stddef.h>

#include "my_errors.h"
#include "my_product.h"
#include "my_actions.h"

#define MY_NULL NULL
#define FILE_END SEEK_END
#define FILE_START SEEK_SET

int get_by_pos(FILE *bin, size_t pos, product *prod)
{
    int rc = OK;
    rc = fseek(bin, pos, FILE_START);
    if (rc == OK)
        if (fread((void*)prod, sizeof(product), 1, bin) != 1)
            rc = FILE_READ_ERROR;
    return rc;
}

int put_by_pos(FILE *bin, size_t pos, product *prod)
{
    int rc = OK;
    rc = fseek(bin, pos, FILE_START);
    if (rc == OK)
        if (fwrite((void*)prod, sizeof(product), 1, bin) != 1)
            rc = FILE_WRITE_ERROR;
    return rc;
}

int up(FILE *bin, size_t pos)
{
    size_t flen = pos / sizeof(product);
    product first, second;
    int rc = OK;
    for (size_t i = flen; i > 0 && rc == OK; --i)
    {
        rc = get_by_pos(bin, (i - 1) * sizeof(product), &first);
        if (rc == OK && i < flen)
        {
            if (compare(&first, &second) == LT)
                rc = swap(bin, i * sizeof(product), (i - 1) * sizeof(product));
            else
                i = 1;
        }
        else
            second = first;
    }
    return rc;
}

int swap(FILE *bin, size_t pos_l, size_t pos_r)
{
    product first, second;
    int rc = get_by_pos(bin, pos_l, &first);
    if (rc == OK)
        get_by_pos(bin, pos_r, &second);
    if (rc == OK)
        put_by_pos(bin, pos_l, &second);
    if (rc == OK)
        put_by_pos(bin, pos_r, &first);
    return rc;
}

int sorted(FILE *bin, product *prod)
{
    int rc = fseek(bin, 0, FILE_END);
    size_t flen = ftell(bin) / sizeof(product);
    product first, second;
    if (rc == OK)
    {
        rc = get_by_pos(bin, 0, &first);
        *prod = first;
    }
    for (size_t i = 1; i < flen && rc == OK; ++i)
    {
        rc = get_by_pos(bin, (i - 1) * sizeof(product), &second);
        if (rc == OK)
            if (compare(&first, &second) == LT)
                rc = UNSORTED;
        first = second;
    }
    return rc;
}

int spec_sort(const char *fin, const char *fout)
{
    int rc = OK;
    FILE *bin = fopen(fin, "rb");
    FILE *dest = fopen(fout, "w+b");
    if (bin == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else if (dest == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        rc = fseek(bin, 0, FILE_END);
        size_t flen = ftell(bin);
        if (rc == OK)
            rc = fseek(bin, 0, FILE_START);
        if (flen == 0)
            rc = FILE_IS_EMPTY;
        if (rc == OK)
        {
            if (flen % sizeof(product))
                rc = FILE_SIZE_ERROR;
            else
            {
                flen /= sizeof(product);
                product prod;
                for (size_t i = 0; i < flen && rc == OK; ++i)
                {
                    rc = get_by_pos(bin, i * sizeof(product), &prod);
                    if (rc == OK)
                        rc = put_by_pos(dest, i * sizeof(product), &prod);
                    if (rc == OK)
                        rc = up(dest, (i + 1) * sizeof(product));
                }
            }
        }
    }
    if (bin != MY_NULL)
        fclose(bin);
    else if (dest != MY_NULL)
        fclose(dest);
    return rc;
}

int spec_out(const char *file, const char *pattern)
{
    int rc = OK;
    FILE *bin = fopen(file, "rb");
    if (bin == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        rc = fseek(bin, 0, FILE_END);
        size_t flen = ftell(bin);
        if (rc == OK)
            rc = fseek(bin, 0, FILE_START);
        if (flen == 0)
            rc = FILE_IS_EMPTY;
        if (rc == OK)
        {
            if (flen % sizeof(product))
                rc = FILE_SIZE_ERROR;
            else
            {
                flen /= sizeof(product);
                product prod;
                int out = 0;
                for (size_t i = 0; i < flen && rc == OK; ++i)
                {
                    rc = get_by_pos(bin, i * sizeof(product), &prod);
                    if (rc == OK)
                    {
                        if (is_end(&prod, pattern))
                        {
                            ++out;
                            print_prod(&prod);
                        }
                    }
                }
                if (out == 0)
                    rc = ERROR;
            }
        }
        fclose(bin);
    }
    return rc;
}

int spec_add(const char *file)
{
    int rc = OK;
    FILE *bin = fopen(file, "r+b");
    if (bin == MY_NULL)
        rc = FILE_OPEN_ERROR;
    else
    {
        rc = fseek(bin, 0, FILE_END);
        size_t flen = ftell(bin);
        if (flen == 0)
            rc = FILE_IS_EMPTY;
        if (rc == OK)
        {
            if (flen % sizeof(product))
                rc = FILE_SIZE_ERROR;
            else
            {
                product prod;
                rc = sorted(bin, &prod);
                if (rc == OK)
                    rc = read_prod(&prod);
                if (rc == OK)
                    rc = put_by_pos(bin, flen, &prod);
                if (rc == OK)
                    rc = up(bin, flen + sizeof(product));
            }
        }
        fclose(bin);
    }
    return rc;
}
