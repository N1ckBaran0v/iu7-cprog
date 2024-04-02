#include <stdio.h>
#include <stddef.h>

#define N 10
#define OK 0
#define ERROR -1

int read(int *arr, int *size);
int solve(int *arr, int size, long long int *result);

int main(void)
{
    int arr[N], n;
    int return_code = read(arr, &n);
    
    if (return_code == OK)
    {
        long long int ans = 0;
        return_code = solve(arr, n, &ans);
        
        if (return_code == OK)
        {
            printf("%lld\n", ans);
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

int solve(int *arr, int size, long long int *result)
{
    int rc = ERROR;
    for (size_t i = 0; (int)i < size; ++i)
    {
        if (arr[i] % 2 == 0)
        {
            rc = OK;
            *result += arr[i];
        }
    }
    return rc;
}
