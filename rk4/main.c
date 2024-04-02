#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "my_stack.h"

#define STACKS_CNT 3

int prall(stack_t **stacks);
int game(stack_t **stacks);

int main(void)
{
    int rc = ERR_OK;
    stack_t *stacks[STACKS_CNT] = {NULL};
    for (size_t i = 0; i < STACKS_CNT; ++i)
    {
        stacks[i] = init();
        if (!(stacks[i]))
            rc = ERR_MEM;
    }
    if (rc == ERR_OK)
    {
        for (int i = 4; rc == ERR_OK && i; --i)
            rc = push(stacks[0], i);
        if (rc == ERR_OK)
            rc = prall(stacks);
        if (rc == ERR_OK)
            rc = game(stacks);
        if (rc == ERR_MEM)
            printf("Error mem allocation.\n");
    }
    for (size_t i = 0; i < STACKS_CNT; ++i)
        stacks[i] = clear(stacks[i]);
    return rc;
}

int prall(stack_t **stacks)
{
    int rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && i < STACKS_CNT; ++i)
    {
        printf("%d tower:\n", (int)(i + 1));
        rc = print(stacks[i]);
    }
    return rc;
}

int game(stack_t **stacks)
{
    int rc = ERR_OK;
    int first = 1, second = 1, rread = 2;
    int fval, sval;
    bool win = false;
    while (rc == ERR_OK && !(win))
    {
        do
        {
            if (first != 1 || second != 1 || rread != 2)
                printf("Error. Try again.\n");
            printf("Input 2 numbers: ");
            rread = scanf("%d %d", &first, &second);
        } while (rread != 2 && (first < 1 || first > STACKS_CNT || second < 1 || second > STACKS_CNT));
        first--, second--;
        
        rc = pop(stacks[first], &fval);
        if (rc)
        {
            printf("%d is empty\n", first + 1);
            rc = ERR_OK;
        }
        else
        {
            rc = pop(stacks[second], &sval);
            if (rc)
            {
                rc = ERR_OK;
                rc = push(stacks[second], fval);
            }
            else if (fval > sval)
            {
                printf("Error. First greater then second.\n");
                rc = push(stacks[first], fval);
                if (rc == ERR_OK)
                    rc = push(stacks[second], sval);
            }
            else
            {
                rc = push(stacks[second], sval);
                if (rc == ERR_OK)
                    rc = push(stacks[second], fval);
            }
        }
        
        if (rc == ERR_OK)
            rc = prall(stacks);
            
        win = true;
        for (size_t i = 0; rc == ERR_OK && i < STACKS_CNT - 1 && win; ++i)
        {
            rc = pop(stacks[i], &fval);
            win = rc;
            if (rc == ERR_OK)
                rc = push(stacks[i], fval);
            else
                rc = ERR_OK;
        }
        if (win)
            printf("You win!\n");
        first = 1, second = 1, rread = 2;
    }
    return rc;
}
