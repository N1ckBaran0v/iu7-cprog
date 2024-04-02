#include <stdio.h>

#include "my_errors.h"
#include "my_funcs.h"

int main(int argc, char **argv)
{
    int rc = OK;
    int min_pos, max_pos;
    if (argc != 2)
        rc = ARGS_ERROR;
    else
        rc = find(argv[1], &min_pos, &max_pos);
    double ans = 0;
    if (rc == OK)
        rc = average(argv[1], min_pos, max_pos, &ans);
    if (rc == OK)
        fprintf(stdout, "Average: %.6lf\n", ans);
    return rc;
}
