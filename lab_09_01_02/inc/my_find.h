#ifndef __MY_FIND_H__

#define __MY_FIND_H__

#include <stddef.h>

#include "my_struct.h"

int find(const char *pattern, struct subject *list, const size_t size, size_t *out_index, size_t *sizeind);
int is_starts_with(const char *str, const char *substr);
void sort(struct subject *list, const size_t size);

#endif // __MY_FIND_H__
