#ifndef __MY_SORT_H__

#define __MY_SORT_H__

#include <stdio.h>
#include <stddef.h>

int get_number_by_pos(FILE *bin, size_t pos, int *val);
int put_number_by_pos(FILE *bin, size_t pos, int *val);
int quick_sort(FILE *bin, size_t left, size_t right);
int swap(FILE *bin, size_t pos_l, size_t pos_r);
int sort(const char *name);

#endif
