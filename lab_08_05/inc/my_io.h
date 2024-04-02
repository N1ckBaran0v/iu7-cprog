#ifndef __MY_IO_H__

#define __MY_IO_H__

#include "my_matrix.h"

int read(matrix **first, matrix **second, size_t *ro, size_t *phi);
void write(matrix *this);

#endif //__MY_IO_H__