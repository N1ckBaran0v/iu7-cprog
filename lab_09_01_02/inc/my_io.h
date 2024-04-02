#ifndef __MY_IO_H__

#define __MY_IO_H__

#include <stddef.h>
#include <stdio.h>

#include "my_struct.h"

int read(const char *filename, struct subject **list, size_t *size);
int input(struct subject *elem, FILE *const fin);
void write(struct subject *list, const size_t *out_index, const size_t size);
void print(struct subject const *elem);

#endif // __MY_IO_H__