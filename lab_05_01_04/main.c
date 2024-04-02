#include <stdio.h>

#include "my_errors.h"
#include "my_process.h"

int main(void)
{
    int cnt = 0;
    int rc = process(stdin, &cnt);
    if (rc == OK)
        fprintf(stdout, "Answer: %d\n", cnt);
    return rc;
}
