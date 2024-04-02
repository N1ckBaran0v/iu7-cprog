#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <memory.h>

#include "my_list.h"

struct my_list
{
    list_t *next;
    char buf[BUF_SIZE];
};

list_t *list_init(char *buf)
{
    list_t *ret = malloc(sizeof(list_t));
    if (ret)
    {
        list_t *it = ret;
        memset(it, 0, sizeof(*it));
        for (size_t i = 0; it; ++i)
        {
            if (i && i % BUF_SIZE == 0)
            {
                it->next = malloc(sizeof(list_t));
                if (it->next)
                {
                    it = it->next;
                    memset(it, 0, sizeof(*it));
                }
                else
                {
                    ret = list_free(ret);
                    it = NULL;
                }
            }
            if (it)
            {
                if (buf[i] == '\n' || buf[i] == '\0')
                {
                    it->buf[i % BUF_SIZE] = '\0';
                    it = NULL;
                }
                else
                    it->buf[i % BUF_SIZE] = buf[i];
            }
        }
    }
    return ret;
}

void list_out(list_t *list)
{
    if (list)
    {
        for (; list->next; list = list->next)
            for (size_t i = 0; i < BUF_SIZE; ++i)
                printf("%c", list->buf[i]);
        printf("%s\n", list->buf);
    }
}

list_t *list_cat(list_t *head, list_t *tail)
{
    list_t *ret = head;
    if (head && tail)
    {
        list_t *end = head;
        for (; end->next; end = end->next);
        size_t nul = BUF_SIZE;
        for (size_t i = 0; i < nul; ++i)
            if (end->buf[i] == '\0')
                nul = i;
        list_t *curr = end;
        for (size_t i = nul, j = 0; curr; ++i, ++j)
        {
            if (j && j % BUF_SIZE == 0)
                tail = tail->next;
            if (curr)
            {
                curr->buf[i % BUF_SIZE] = tail->buf[j % BUF_SIZE];
                if (tail->buf[j % BUF_SIZE] == '\0')
                    curr = NULL;
                else if (i && i % BUF_SIZE == BUF_SIZE - 1)
                {
                    curr->next = malloc(sizeof(list_t));
                    if (curr->next)
                    {
                        curr = curr->next;
                        memset(curr, 0, sizeof(*curr));
                    }
                    else
                    {
                        end = list_free(end);
                        end->buf[nul] = '\0';
                        curr = NULL;
                        ret = NULL;
                    }
                }
            }
        }
    }
    else
        ret = NULL;
    return ret;
}

list_t *list_sps(list_t *list)
{
    list_t *ret = list;
    if (list)
    {
        list_t *run = list;
        bool was_space = false;
        bool need_rot = false;
        for (size_t i = 0, j = 0; list->next && run; ++j)
        {
            if (need_rot && i % BUF_SIZE == 0)
            {
                list = list->next;
                need_rot = false;
            }
            if (isspace(run->buf[j % BUF_SIZE]))
            {
                if (!(was_space))
                {
                    was_space = true;
                    if (i < j)
                        list->buf[i % BUF_SIZE] = run->buf[j % BUF_SIZE];
                    ++i;
                    need_rot = true;
                }
            }
            else
            {
                was_space = false;
                if (i < j)
                    list->buf[i % BUF_SIZE] = run->buf[j % BUF_SIZE];
                ++i;
                need_rot = true;
            }
            if (run && run->buf[j % BUF_SIZE] == '\0')
            {
                list->next = list_free(list->next);
                run = NULL;
            }
            if (run && j % BUF_SIZE == BUF_SIZE - 1)
                run = run->next;
        }
    }
    return ret;
}

long list_pos(list_t *list, list_t *substr)
{
    long ret = -1;
    if (list && substr)
    {
        list_t *tmpl;
        list_t *tmps;
        for (size_t i = 0; ret == -1 && list->buf[i % BUF_SIZE]; ++i)
        {
            tmpl = list;
            tmps = substr;
            for (size_t it = i % BUF_SIZE, j = 0; tmps; ++it, ++j)
            {
                if (it && it % BUF_SIZE == 0)
                    tmpl = tmpl->next;
                if (j && j % BUF_SIZE == 0)
                    tmps = tmps->next;
                if (tmps->buf[j % BUF_SIZE])
                {
                    if (tmps->buf[j % BUF_SIZE] != tmpl->buf[it % BUF_SIZE])
                        tmps = NULL;
                }
                else
                {
                    tmps = NULL;
                    ret = i;
                }
            }
            if (i && i % BUF_SIZE == BUF_SIZE - 1)
                list = list->next;
        }
    }
    return ret;
}

int list_cmp(list_t *first, list_t *second)
{
    int rc = 0;
    for (size_t i = 0; rc == 0 && (first->buf[i % BUF_SIZE] || second->buf[i % BUF_SIZE]); ++i)
    {
        rc = first->buf[i % BUF_SIZE] - second->buf[i % BUF_SIZE];
        if (i % BUF_SIZE == BUF_SIZE - 1)
        {
            first = first->next;
            second = second->next;
        }
    }
    return rc;
}

list_t *list_free(list_t *list)
{
    list_t *tmp;
    while (list)
    {
        tmp = list->next;
        free(list);
        list = tmp;
    }
    return NULL;
}

