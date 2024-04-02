#ifndef __MY_SORT_H__

#define __MY_SORT_H__

#include <stddef.h>

typedef int (*compar_f)(const void*, const void*);

void mysort(void *my__base, size_t my__nmemb, size_t my__size, compar_f my__compar);

int intcmp(const void *first, const void *second);

#endif //__MY_SORT_H__