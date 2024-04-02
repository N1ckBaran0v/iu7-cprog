#ifndef __MY_LIST_H__

#define __MY_LIST_H__

#define BUF_SIZE 4

typedef struct my_list list_t;

list_t *list_init(char *buf);
void list_out(list_t *list);
list_t *list_cat(list_t *head, list_t *tail);
list_t *list_sps(list_t *list);
long list_pos(list_t *list, list_t *substr);
int list_cmp(list_t *first, list_t *second);
list_t *list_free(list_t *list);

#endif //__MY_LIST_H__

