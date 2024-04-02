#include <stdio.h>
#include <stdlib.h>

#include "my_list.h"
#include "my_errors.h"

int intcmp(const void*, const void*);

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    if (argc == 3)
    {
        node_t *list = NULL, *tmpl = NULL;
        FILE *fin = fopen(argv[1], "r"), *fout = NULL;
        if (fin) 
        {
            int *tmp = NULL;
            rc = ERR_CONTINUE;
            while (rc == ERR_CONTINUE)
            {
                tmp = malloc(sizeof(int));
                if (tmp)
                {
                    if (fscanf(fin, "%d", tmp) == 1)
                    {
                        tmpl = my_init(tmp, sizeof(int), NULL);
                        if (tmpl)
                            insert(&list, tmpl, NULL);
                        else
                        {
                            rc = ERR_ALLOC_MEMORY;
                            int *val = NULL;
                            while (list)
                            {
                                val = pop_front(&list);
                                free(val);
                            }
                            list = NULL;
                        }
                        tmpl = NULL;
                    }
                    else
                    {
                        rc = ERR_OK;
                        free(tmp);
                    }
                }
                else
                    rc = ERR_ALLOC_MEMORY;
            }
            if (rc == ERR_OK && !(list))
                rc = ERR_FILE_INVALID;
            fclose(fin);
        }
        else
            rc = ERR_FILE_OPEN;
        if (rc == ERR_OK)
        {
            list = sort(list, intcmp);
            list = reverse(list);
            fout = fopen(argv[2], "w");
        }
        if (fout)
        {
            int *val = NULL;
            while (list)
            {
                val = pop_front(&list);
                fprintf(fout, "%d\n", *val);
                free(val);
            }
            fclose(fout);
        }
        else if (rc == ERR_OK)
            rc = ERR_ALLOC_MEMORY;
    }
    else
        rc = ERR_ARGS_COUNT_INVALID;
    return rc;
}

int intcmp(const void *first, const void *second)
{
    return *((const int*)first) - *((const int*)second);
}

