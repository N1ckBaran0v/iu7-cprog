#include <stddef.h>
#include <string.h>

#include "my_struct.h"
#include "my_errors.h"
#include "my_find.h"

int find(const char *pattern, struct subject *list, const size_t size, size_t *out_index, size_t *sizeind)
{
    int rc = ERR_OK;
    if (strcmp(pattern, "ALL")) 
    {
        for (size_t i = 0; i < size; ++i) 
        {
            if (is_starts_with(list[i].name, pattern))
            {
                out_index[*sizeind] = i;
                ++(*sizeind);
            }
        }
    }
    else
    {
        *sizeind = size;
        for (size_t i = 0; i < size; ++i)
        {
            out_index[i] = i;
        }
    }
    return rc;
}

int is_starts_with(const char *str, const char *substr)
{
    size_t i = 0;
    int ret = TRUE;
    for (; substr[i]; ++i)
    {
        ret = str[i] == substr[i];
    }
    return ret;
}

void sort(struct subject *list, const size_t size)
{
    for (size_t i = 0; i < size - 1; ++i) 
    {
        size_t ind = i;
        for (size_t j = ind + 1; j < size; ++j)
        {
            if (list[j].r < list[ind].r)
            {
                ind = j;
            }
        }
        struct subject tmp = list[ind];
        for (size_t j = ind; j > i; --j)
        {
            list[j] = list[j - 1];
        }
        list[i] = tmp;
    }
}
