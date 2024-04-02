#include <stdlib.h>
#include <memory.h>

#include "my_list.h"

struct node
{
    void *data;
    node_t *next;
};

node_t *my_init(void *data, size_t size, node_t *next)
{
    node_t *ret = malloc(sizeof(node_t));
    if (ret)
    {
        ret->data = data;
        ret->next = next;
    }
    return ret;
}

void my_destroy(node_t *head)
{
    node_t *tmp;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

void *pop_front(node_t **head)
{
    void *ret = NULL;
    if (head)
    {
        if (*head)
        {
            ret = (*head)->data;
            node_t *del = *head;
            *head = (*head)->next;
            free(del);
        }
    }
    return ret;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (head && elem)
    {
        if (before == *head)
        {
            *head = elem;
            elem->next = before;
        }
        else if (*head)
        {
            node_t *it = *head;
            for (; it->next && it->next != before; it = it->next);
            if (it->next == before)
            {
                it->next = elem;
                elem->next = before;
            }
        }
    }
}

node_t *reverse(node_t *head)
{
    node_t *prev = NULL;
    node_t *curr = head;
    node_t *next = NULL;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void front_back_split(node_t *head, node_t **back)
{
    if (head && back)
    {
        size_t size = 1;
        node_t *it = head;
        for (; it; it = it->next, ++size);
        size >>= 1;
        it = head;
        for (size_t i = 0; i < size - 1; it = it->next, ++i);
        *back = it->next;
        it->next = NULL;
    }
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t *res = NULL, *it = NULL;
    if (head_a && head_b && comparator)
    {
        while (*head_a || *head_b)
        {
            if (!(*head_a))
            {
                if (it)
                {
                    it->next = *head_b;
                    it = it->next;
                }
                else
                    res = it = *head_b;
                *head_b = (*head_b)->next;
            }
            else if (!(*head_b))
            {
                if (it)
                {
                    it->next = *head_a;
                    it = it->next;
                }
                else
                    res = it = *head_a;
                *head_a = (*head_a)->next;
            }
            else if (comparator((*head_a)->data, (*head_b)->data) > 0)
            {
                if (it)
                {
                    it->next = *head_b;
                    it = it->next;
                }
                else
                    res = it = *head_b;
                *head_b = (*head_b)->next;
            }
            else
            {
                if (it)
                {
                    it->next = *head_a;
                    it = it->next;
                }
                else
                    res = it = *head_a;
                *head_a = (*head_a)->next;
            }
        }
        if (it)
            it->next = NULL;
    }
    return res;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *ans = NULL;
    if (head && comparator)
    {
        node_t *second = NULL;
        front_back_split(head, &second);
        if (head->next)
            head = sort(head, comparator);
        if (second)
            second = sort(second, comparator);
        ans = sorted_merge(&head, &second, comparator);
    }
    return ans;
}
