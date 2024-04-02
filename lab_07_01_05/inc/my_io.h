#ifndef __MY_IO_H__

#define __MY_IO_H__

int read(const char *filename, int **ptr_begin, int **ptr_end);

int write(const char *filename, const int *ptr_begin, const int *ptr_end);

#endif //__MY_IO_H__