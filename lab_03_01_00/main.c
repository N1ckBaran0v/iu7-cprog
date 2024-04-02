#include <stdio.h>
#include <stddef.h>

#define N 10
#define M 10
#define OK 0
#define ERROR -1
#define GOOD 1
#define BAD 0

void transform(int **matr, int *buf);
int read(int **matr, int *rows, int *columns);
void solve(int **matr, int rows, int columns, int *arr);
void print(int *arr, int size);

int main(void)
{
    int buff[N][M], arr[N], *matr[N], n, m;
    transform(matr, buff[0]);
    int rc = read(matr, &n, &m);
    
    if (rc == OK)
    {
        solve(matr, n, m, arr);
        print(arr, m);
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

void solve(int **matr, int rows, int columns, int *arr)
{
    for (size_t j = 0; (int)j < columns; ++j)
    {
        arr[j] = GOOD;
        for (size_t i = 1; arr[j] == GOOD && (int)i < rows; ++i)
        {
            if (matr[i - 1][j] <= matr[i][j])
            {
                arr[j] = BAD;
            }
        }
        if (rows == 1)
        {
            arr[j] = BAD;
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
