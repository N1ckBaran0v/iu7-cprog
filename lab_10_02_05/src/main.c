#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "my_errors.h"
#include "my_list.h"

int act_out(void);
int act_cat(void);
int act_sps(void);
int act_pos(void);

int main(void)
{
    const char *acts_names[] = 
    {
        "out\n", "cat\n", "sps\n", "pos\n"
    };
    int (*acts_funcs[])(void) =
    {
        act_out, act_cat, act_sps, act_pos
    };
    int rc = ERR_NOT_FOUND;
    char *act_name = NULL;
    size_t buf_size = 0;
    ssize_t size = getline(&act_name, &buf_size, stdin);
    if (size == 4)
        for (size_t i = 0; i < 4; ++i)
            if (strcmp(act_name, acts_names[i]) == 0)
                rc = acts_funcs[i]();
    free(act_name);
    return rc;
}

int act_out(void)
{
    int rc = ERR_OK;
    char *str = NULL;
    size_t buf_size = 0;
    ssize_t size = getline(&str, &buf_size, stdin);
    if (size > 0 && str)
    {
        if (str[0] != '\n')
        {
            list_t *ptr = list_init(str);
            if (ptr)
                list_out(ptr);
            else
                rc = ERR_ALLOC_MEMORY;
            ptr = list_free(ptr);
        }
        else
            rc = ERR_WHILE_READ;
    }
    else
        rc = ERR_WHILE_READ;
    free(str);
    return rc;
}

int act_cat(void)
{
    int rc = ERR_OK;
    char *str = NULL, *next = NULL;
    size_t buf_size = 0;
    ssize_t size = getline(&str, &buf_size, stdin);
    if (size > 1 && str)
    {
        buf_size = 0;
        size = getline(&next, &buf_size, stdin);
    }
    else
        rc = ERR_WHILE_READ;
    if (size > 0 && str && next)
    {
        if (next[0] != '\n')
        {
            list_t *ptr = list_init(str);
            list_t *ptr2 = list_init(next);
            list_t *ptr3 = NULL;
            if (ptr && ptr2)
                ptr3 = list_cat(ptr, ptr2);
            else
                rc = ERR_ALLOC_MEMORY;
            if (ptr3 != ptr)
                rc = ERR_ALLOC_MEMORY;
            if (rc == ERR_OK)
                list_out(ptr3);
            ptr = list_free(ptr);
            ptr2 = list_free(ptr2);
        }
        else
            rc = ERR_WHILE_READ;
    }
    else
        rc = ERR_WHILE_READ;
    free(str);
    free(next);
    return rc;
}

int act_sps(void)
{
    int rc = ERR_OK;
    char *str = NULL;
    size_t buf_size = 0;
    ssize_t size = getline(&str, &buf_size, stdin);
    if (size > 0 && str)
    {
        if (str[0] != '\n')
        {
            list_t *ptr = list_init(str);
            list_t *ptr2 = NULL;
            if (ptr)
                ptr2 = list_sps(ptr);
            else
                rc = ERR_ALLOC_MEMORY;
            if (ptr2 != ptr)
                rc = ERR_ALLOC_MEMORY;
            if (rc == ERR_OK)
                list_out(ptr);
            ptr = list_free(ptr);
        }
        else
            rc = ERR_WHILE_READ;
    }
    else
        rc = ERR_WHILE_READ;
    free(str);
    return rc;
}

int act_pos(void)
{
    int rc = ERR_OK;
    char *str = NULL, *next = NULL;
    size_t buf_size = 0;
    ssize_t size = getline(&str, &buf_size, stdin);
    long ans = -1;
    if (size > 1 && str)
    {
        buf_size = 0;
        size = getline(&next, &buf_size, stdin);
    }
    else
        rc = ERR_WHILE_READ;
    if (size > 0 && str && next)
    {
        list_t *ptr = list_init(str);
        list_t *ptr2 = list_init(next);
        if (ptr && ptr2)
        {
            ans = list_pos(ptr, ptr2);
        }
        else
            rc = ERR_ALLOC_MEMORY;
        ptr = list_free(ptr);
        ptr2 = list_free(ptr2);
    }
    else
        rc = ERR_WHILE_READ;
    free(str);
    free(next);
    if (rc == ERR_OK)
        printf("%ld\n", ans);
    return rc;
}

