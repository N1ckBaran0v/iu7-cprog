#ifndef __MY_SORT_H__

#define __MY_SORT_H__

#include <stddef.h>

void mysort(void *my__base, size_t my__nmemb, size_t my__size, int (*my__compar)(const void *, const void *));

int intcmp(const void *first, const void *second);

#endif //__MY_SORT_H__