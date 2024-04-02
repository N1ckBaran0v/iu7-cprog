#ifndef __MY_STACK_H__
#define __MY_STACK_H__

#define ERR_OK     0
#define ERR_MEM   -1
#define ERR_PTR   -2
#define ERR_EMPTY -3

typedef struct stack_t stack_t;

stack_t *init(void);
int push(stack_t*, int);
int print(stack_t*);
int pop(stack_t*, int*);
stack_t *clear(stack_t*);


#endif // __MY_STACK_H__
