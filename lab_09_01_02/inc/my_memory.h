#ifndef __MY_MEMORY_H__

#define __MY_MEMORY_H__

#include <stddef.h>

#include "my_struct.h"

#define INCREASE 2

struct subject *init(size_t size);
struct subject *resize(struct subject *sub, size_t old_size);
void struct_free(struct subject *sub, size_t size);

#endif // __MY_MEMORY_H__