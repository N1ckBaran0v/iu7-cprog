#ifndef __MY_PRODUCT_H__

#define __MY_PRODUCT_H__

#include <stdint.h>

#define NAME_LEN 30
#define PROD_LEN 15

#define EQ 0
#define LT 1
#define GT -1

#define YES 1
#define NO 0

typedef struct product
{
    char name[NAME_LEN + 1];
    char producer[PROD_LEN + 1];
    uint32_t cost;
    uint32_t count;
} product;

int read_prod(product *prod);
int read_str(char *str, size_t maxlen);
void print_prod(product *prod);
int compare(product *first, product *second);
int is_end(product *prod, const char *pattern);

#endif
