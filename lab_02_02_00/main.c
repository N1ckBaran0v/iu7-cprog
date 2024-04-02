#include <stdio.h>
#include <stddef.h>

#define N 10
#define OK 0
#define ERROR -1

int read(int *arr, int *size);
int solve(int *arr, int size, int *new_arr, int *new_size);
void print(int *arr, int size);

int main(void)
{
    int arr[N], n;
    int return_code = read(arr, &n);
    
    if (return_code == OK)
    {
        int new_arr[N], m = 0;
        return_code = solve(arr, n, new_arr, &m);
        
        if (return_code == OK)
        {
            print(new_arr, m);
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
int solve(int *arr, int size, int *new_arr, int *new_size)
{
    int rc = ERROR;
    double mid = 0.0;
    for (size_t i = 0; (int)i < size; ++i)
    {
        mid += arr[i];
    }
    mid /= size;
    for (size_t i = 0; (int)i < size; ++i)
    {
        if ((double)arr[i] > mid)
        {
            new_arr[(size_t)(*new_size)] = arr[i];
            (*new_size)++;
            rc = OK;
        }
    }
    return rc;
}

void print(int *arr, int size)
{
    for (size_t i = 0; (int)i < size; ++i)
    {
        printf("%d\n", arr[i]);
    }
}
