#include <stdio.h>
#include <stddef.h>

#define N 10
#define M 10
#define OK 0
#define ERROR -1

void transform(int **matr, int *buf);
int read(int **matr, int *rows, int *columns);
void sort(int **matr, int rows, int columns);
void print(int **arr, int rows, int columns);
void swap(int **first, int **second);
void llswap(long long *first, long long *second);

int main(void)
{
    int buff[N][M], *matr[N], n, m;
    transform(matr, buff[0]);
    int rc = read(matr, &n, &m);
    
    if (rc == OK)
    {
        sort(matr, n, m);
        print(matr, n, m);
    }
    
    return rc;
}

void transform(int **matr, int *buf)
{
    for (size_t i = 0; i < N; ++i)
    {
        matr[i] = buf + i * M;
    }
}

int read(int **matr, int *rows, int *columns)
{
    int rc = OK;
    
    if (scanf("%d", rows) != 1)
    {
        rc = ERROR;
    }
    
    if (scanf("%d", columns) != 1)
    {
        rc = ERROR;
    }
    
    if (rc == OK)
    {
        if (*rows < 1 || *columns < 1 || *rows > N || *columns > M)
        {
            rc = ERROR;
        }
    }
    
    if (rc == OK)
    {
        for (size_t i = 0; rc == OK && (int)i < *rows; ++i)
        {
            for (size_t j = 0; rc == OK && (int)j < *columns; ++j)
            {
                if (scanf("%d", &matr[i][j]) != 1)
                {
                    rc = ERROR;
                }
            }
        }
    }
    
    return rc;
}

void sort(int **matr, int rows, int columns)
{
    long long sum[N];
    for (size_t i = 0; (int)i < rows; ++i)
    {
        sum[i] = 0;
        for (size_t j = 0; (int)j < columns; ++j)
        {
            sum[i] += matr[i][j];
        }
    }
    for (size_t i = 1; (int)i < rows; ++i)
    {
        int flag = 0;
        for (size_t j = i; (int)j > 0 && flag == 0; --j)
        {
            if (sum[j] < sum[j - 1])
            {
                swap(matr + j, matr + j - 1);
                llswap(&sum[j], &sum[j - 1]);
            }
            else
            {
                flag = 1;
            }
        }
    }
}

void print(int **arr, int rows, int columns)
{
    for (size_t i = 0; (int)i < rows; ++i)
    {
        for (size_t j = 0; (int)j < columns; ++j)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void swap(int **first, int **second)
{
    int *temp = *first;
    *first = *second;
    *second = temp;
}

void llswap(long long *first, long long *second)
{
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}
