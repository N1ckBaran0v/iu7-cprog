#include <stdio.h>

#define OK 0
#define ERROR 1

void print_simples(int);

int main(void)
{
    int n, rc = OK;
    
    if (scanf("%d", &n) == 1 && n > 0)
    {
        print_simples(n);
    } 
    else
    {
        rc = ERROR;
    }
    
    return rc;
}

void print_simples(int n)
{
    for (int i = 2; i <= n; i++)
    {
        while (n % i == 0)
        {
            n /= i;
            printf("%d\n", i);
        }
    }
}
