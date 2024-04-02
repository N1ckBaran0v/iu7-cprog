#include <stdio.h>
#include <math.h>

#define OK 0
#define ERROR 1

void solve(unsigned int*, int);

void output(unsigned int);

int main(void)
{
    unsigned int a;
    signed int n;
    int rc = OK;
    
    if (scanf("%u%d", &a, &n) == 2 && n >= 0)
    {
        solve(&a, n);
        output(a);
    }
    else
    {
        printf("Error: incorrect input\n");
        rc = ERROR;
    }
    
    return rc;
}

void solve(unsigned int *a, int n)
{
    n %= 32;
    unsigned int mask = 0;
    for (int i = 0; i < n; i++)
    {
        mask <<= 1;
        mask |= 1;
    }
    mask &= *a;
    *a >>= n;
    mask <<= 32 - n;
    *a |= mask;
}

void output(unsigned int a)
{
    unsigned int pattern = 1 << 31, out;
    printf("Result: ");
    for (int i = 0; i < 32; i++)
    {
        out = (a & pattern) >> 31;
        printf("%u", out);
        a <<= 1;
    }
    printf("\n");
}
