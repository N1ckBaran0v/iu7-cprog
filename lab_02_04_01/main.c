#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 10
#define OK 0
#define ERROR -1
#define OVERFLOW 100

int read(int *arr, int *size);
void solve(int *arr, int size);
void print(int *arr, int size);
void swap(int *a, int *b);

int main(void)
{
    int arr[N], n = 0;
    int return_code = read(arr, &n);
    
    if (return_code != ERROR)
    {
        solve(arr, n);
        print(arr, n);
    }
    
    return return_code;
}

int read(int *arr, int *size)
{
    int temp;
    int read_code = scanf("%d", &temp);
    int return_code = OK;
    while (read_code == 1 && *size < N)
    {
        arr[(size_t)*size] = temp;
        (*size)++;
        read_code = scanf("%d", &temp);
    }
    if (read_code == 1)
    {
        return_code = OVERFLOW;
    }
    else if (*size == 0)
    {
        return_code = ERROR;
    }
    return return_code;
}

void solve(int *arr, int size)
{
    for (size_t i = 1; (int)i < size; ++i)
    {
        size_t j = i;
        while (j > 0 && arr[j] < arr[j - 1])
        {
            swap(&arr[j], &arr[j - 1]);
            --j;
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

void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
