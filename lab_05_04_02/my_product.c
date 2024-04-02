#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

#include "my_product.h"
#include "my_errors.h"

#define END_OF_FILE EOF
#define MAX_VAL UINT32_MAX

int read_prod(product *prod)
{
    int rc = read_str(prod->name, NAME_LEN);
    if (rc == OK)
        rc = read_str(prod->producer, PROD_LEN);
    long unsigned t1, t2;
    if (rc == OK && scanf("%lu %lu", &t1, &t2) == 2)
    {
        if (t1 <= MAX_VAL && t2 <= MAX_VAL)
        {
            prod->cost = (uint32_t)t1;
            prod->count = (uint32_t)t2;
        }
        else
            rc = OVERFLOW;
    }
    else
        rc = READ_ERROR;
    return rc;
}

int read_str(char *str, size_t maxlen)
{
    int rc = OK;
    char tmp = getchar();
    for (; isspace(tmp); tmp = getchar());
    size_t len = 0;
    while (tmp != END_OF_FILE && !(isspace(tmp)) && rc == OK)
    {
        str[len] = tmp;
        ++len;
        if (len > maxlen + 1)
            rc = OVERFLOW;
        tmp = getchar();
    }
    if (len == 0)
        rc = READ_ERROR;
    else if (rc == OK)
        str[len] = '\0';
    return rc;
}

void print_prod(product *prod)
{
    fprintf(stdout, "%s\n", prod->name);
    fprintf(stdout, "%s\n", prod->producer);
    fprintf(stdout, "%llu\n", (long long unsigned)prod->cost);
    fprintf(stdout, "%llu\n", (long long unsigned)prod->count);
}

int compare(product *first, product *second)
{
    int ret = EQ;
    if (first->cost < second->cost)
        ret = LT;
    else if (first->cost > second->cost)
        ret = GT;
    else if (first->count < second->count)
        ret = LT;
    else if (first->count > second->count)
        ret = GT;
    return ret;
}

int is_end(product *prod, const char *pattern)
{
    size_t i = 0, j = 0;
    for (; prod->name[i]; ++i);
    for (; pattern[j]; ++j);
    int ret = NO;
    for (; i && j && prod->name[i] == pattern[j]; --i, --j);
    if (j == 0 && prod->name[i] == pattern[j])
        ret = YES;
    return ret;
}
