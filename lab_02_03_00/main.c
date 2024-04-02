#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 10
#define OK 0
#define ERROR -1
#define ONE_DIGIT 9

int read(int *arr, int *size);
void solve(int *arr, int *size);
void print(int *arr, int size);
int is_palindrome(int n);

int main(void)
{
    int arr[N], n;
    int return_code = read(arr, &n);
    
    if (return_code == OK)
    {
        solve(arr, &n);
        if (n > 0)
        {
            print(arr, n);
        }
        else
        {
            return_code = ERROR;
        }
    } 
    
    return return_code;
}

int read(int *arr, int *size)
{
    int rc = OK;
    if (scanf("%d", size) != 1)
    {
        rc = ERROR;
    }
    if (rc == OK && *size > 0 && *size <= N)
    {
        for (size_t i = 0; (int)i < *size && rc == OK; ++i)
        {
            if (scanf("%d", &arr[i]) != 1)
            {
                rc = ERROR;
            }
        }
    }
    else
    {
        rc = ERROR;
    }
    return rc;
}

void solve(int *arr, int *size)
{
    size_t i = 0;
    while ((int)i < *size)
    {
        if (is_palindrome(arr[i]) == OK)
        {
            (*size)--;
            for (size_t j = i; (int)j < *size; ++j)
            {
                arr[j] = arr[j + 1];
            }
        }
        else
        {
            ++i;
        }
    }
}

void print(int *arr, int size)
{
    for (size_t i = 0; (int)i < size; ++i)
    {
        printf("%d\n", arr[i]);
    }
}

int is_palindrome(int n)
{
    int rc = OK;
    int module = abs(n);
    int st = 1;
    while (module / st > ONE_DIGIT)
    {
        st *= 10;
    }
    while (st > ONE_DIGIT && rc == OK)
    {
        if (module % 10 != (module / st) % 10)
        {
            rc = ERROR;
        }
        module /= 10;
        st /= 100;
    }
    return rc;
}
