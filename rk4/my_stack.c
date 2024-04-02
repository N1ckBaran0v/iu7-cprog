#include <stdio.h>
#include <stdlib.h>

#include "my_stack.h"

typedef struct list_t list_t;

struct stack_t
{
    list_t *head;
};

struct list_t
{
    list_t *next;
    int value;
};

list_t *free_list(list_t*);

stack_t *init(void)
{
    stack_t *ret = malloc(sizeof(stack_t));
    if (ret)
        ret->head = NULL;
    return ret;
}

int push(stack_t *stack, int value)
{
    int rc = ERR_OK;
    if (stack)
    {
        list_t *list = malloc(sizeof(list_t));
        if (list)
        {
            list->next = stack->head;
            list->value = value;
            stack->head = list;
        }
        else
            rc = ERR_MEM;
    }
    else
        rc = ERR_PTR;
    return rc;
}
 
int print(stack_t *stack)
{
    int rc = ERR_OK;
    if (stack)
        for (list_t *list = stack->head; list; list = list->next)
            for (int i = 1; i <= list->value; ++i)
                printf((i < list->value) ? "*" : "*\n");
    else
        rc = ERR_PTR;
    return rc;
}

int pop(stack_t *stack, int *ret)
{
    int rc = ERR_OK;
    if (stack && ret)
    {
        if (stack->head)
        {
            *ret = stack->head->value;
            stack->head = free_list(stack->head);
        }
        else
            rc = ERR_EMPTY;
    }
    else
        rc = ERR_PTR;
    return rc;
}

stack_t *clear(stack_t *stack)
{
    if (stack)
        while (stack->head)
            stack->head = free_list(stack->head);
    free(stack);
    return NULL;
}

list_t *free_list(list_t *list)
{
    list_t *ret = NULL;
    if (list)
    {
        ret = list->next;
        free(list);
    }
    return ret;
}


