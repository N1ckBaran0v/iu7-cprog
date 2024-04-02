#include <stdio.h>
#include <string.h>

#include "my_errors.h"
#include "my_actions.h"

int main(int argc, char **argv)
{
    int rc = OK;
    if (argc < 2)
        rc = ARGS_ERROR;
    else if (strcmp(argv[1], "sb") == 0 && argc == 4)
        rc = spec_sort(argv[2], argv[3]);
    else if (strcmp(argv[1], "fb") == 0 && argc == 4)
        rc = spec_out(argv[2], argv[3]);
    else if (strcmp(argv[1], "ab") == 0 && argc == 3)
        rc = spec_add(argv[2]);
    else
        rc = ARGS_ERROR;
    return rc;
}
