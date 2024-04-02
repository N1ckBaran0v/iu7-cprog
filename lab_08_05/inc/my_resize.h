#ifndef __MY_RESIZE_H__

#define __MY_RESIZE_H__

#include <stddef.h>
#include <stdint.h>

#include "my_matrix.h"

void to_square(matrix *this);
int increase(matrix **first, matrix **second);

#endif //__MY_RESIZE_H__