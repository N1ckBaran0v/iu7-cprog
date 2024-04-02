// Variant 1

#include <stdio.h>
#include <stddef.h>

#define N 10
#define OK 0
#define ERROR -1

int input(int *arr, int *n);
void solve(int *arr, int n);
void output(int *arr, int n);
void swap(int *a, int *b);

int main(void)
{
    int arr[N], n;
    int rc = input(arr, &n);
    if (rc == OK)
    {
        solve(arr, n);
        output(arr, n);
    }
    
    return rc;
}

int input(int *arr, int *n)
{
    int rc = OK;
    if (scanf("%d", n) != 1)
    {
        rc = ERROR;
    }
    else
    {
        if (*n < 1 || *n > N)
        {
            rc =  ERROR;
        }
        else
        {
            for (size_t i = 0; rc == OK && (int)i < *n; ++i)
            {
                if (scanf("%d", &arr[i]) != 1)
                {
                    rc = ERROR;
                }
            } 
        }
    }
    return rc;
}

void solve(int *arr, int n)
{
    for (size_t i = 1; (int)i < n; ++i)
    {
        for (size_t j = i; (int)j > 0; --j)
        {
            if ((arr[j] == 0 && arr[j - 1] != 0) || (arr[j] < 0 && arr[j - 1] > 0))
            {
                swap(&arr[j - 1], &arr[j]);
            }
        }
    }
}

void output(int *arr, int n)
{
    for (size_t i = 0; (int)i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
}

void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
