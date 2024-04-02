#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/my_errors.h"
#include "../inc/my_matrix.h"
#include "../inc/my_resize.h"
#include "../inc/my_multiple.h"
#include "../inc/my_io.h"

int main(void)
{
    int rc = ERR_OK;
    matrix *first = NULL, *second = NULL;
    size_t ro = 0, phi = 0;
    rc = read(&first, &second, &ro, &phi);
    if (rc == ERR_OK)
    {
        to_square(first);
        to_square(second);
        rc = increase(&first, &second);
    }
    if (rc == ERR_OK)
    {
        rc = mult(&first, second, ro, phi);
    }
    if (rc == ERR_OK)
    {
        write(first);
    }
    free_matrix(first);
    free_matrix(second);
    return rc;
}
