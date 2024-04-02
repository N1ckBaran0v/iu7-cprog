#ifndef __MY_ACTIONS_H__

#define __MY_ACTIONS_H__

#include <stdio.h>
#include <stddef.h>

#include "my_product.h"

int get_by_pos(FILE *bin, size_t pos, product *prod);
int put_by_pos(FILE *bin, size_t pos, product *prod);
int up(FILE *bin, size_t pos);
int swap(FILE *bin, size_t pos_l, size_t pos_r);
int sorted(FILE *bin, product *prod);
int spec_sort(const char *fin, const char *fout);
int spec_out(const char *file, const char *pattern);
int spec_add(const char *file);

#endif
