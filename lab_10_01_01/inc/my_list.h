#ifndef   __MY_LIST_H__
#define   __MY_LIST_H__

#include <stddef.h>

typedef struct node node_t;

node_t *my_init(void *data, size_t size, node_t *next);
void my_destroy(node_t *head);
void *pop_front(node_t **head);
void insert(node_t **head, node_t *elem, node_t *before);
node_t *reverse(node_t *head);
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif // __MY_LIST_H__

