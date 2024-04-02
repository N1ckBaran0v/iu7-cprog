#include <stdlib.h>

#include "my_memory.h"

struct subject *init(size_t size)
{
    struct subject *ret = calloc(size, sizeof(struct subject));
    return ret;
}

struct subject *resize(struct subject *sub, size_t old_size)
{
    struct subject *tmp = calloc(old_size * INCREASE, sizeof(struct subject));
    if (tmp)
    {
        for (size_t i = 0; i < old_size; ++i)
            tmp[i] = sub[i];
        free(sub);
    }
    else
        struct_free(sub, old_size);
    return tmp;
}

void struct_free(struct subject *sub, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        free(sub[i].name);
    free(sub);
}