#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "my_errors.h"
#include "my_memory.h"
#include "my_struct.h"
#include "my_find.h"
#include "my_io.h"

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    size_t size = 0;
    struct subject *list = NULL;
    if (argc == 2 || argc == 3)
        rc = read(argv[1], &list, &size);
    else
        rc = ERR_ARGS_COUNT_INVALID;

    if (rc == ERR_OK)
    {
        size_t *out_index = malloc(size * sizeof(size_t));
        if (out_index)
        {
            size_t sizeind = 0;
            if (argc == 3)
                rc = find(argv[2], list, size, out_index, &sizeind);
            else
            {
                sort(list, size);
                sizeind = size;
                for (size_t i = 0; i < size; ++i)
                    out_index[i] = i;
            }
            if (rc == ERR_OK)
                write(list, out_index, sizeind);
        }
        else
            rc = ERR_ALLOC_MEMORY;
        free(out_index);
        struct_free(list, size);
    }

    return rc;
}
