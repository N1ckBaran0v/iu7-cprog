/**
 * Type: int
 * Sort type: quick sort
 * Sort from smallest to largest
 */


#include <string.h>

#include "my_errors.h"
#include "my_create.h"
#include "my_output.h"
#include "my_sort.h"

int main(int argc, char **argv)
{
    int rc = OK;
    if (argc < 2)
        rc = ARGS_ERROR;
    else if (strcmp(argv[1], "c") == 0 && argc == 4)
        rc = create(argv[3], argv[2]);
    else if (strcmp(argv[1], "p") == 0 && argc == 3)
        rc = output(argv[2]);
    else if (strcmp(argv[1], "s") == 0 && argc == 3)
        rc = sort(argv[2]);
    else
        rc = ARGS_ERROR;
    return rc;
}
