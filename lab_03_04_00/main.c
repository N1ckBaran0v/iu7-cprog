#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 10
#define OK 0
#define ERROR -1

void transform(int **matr, int *buf);
int read(int **matr, int *rows);
int find(int **matr, int rows);

int main(void)
{
    int buff[N][N], *matr[N], n;
    transform(matr, buff[0]);
    int rc = read(matr, &n);
    
    if (rc == OK)
    {
        int num = find(matr, n);
        if (num != 0)
        {
            printf("%d\n", num);
        }
        else
        {
            rc = ERROR;
        }
    }
    
    return rc;
}

void transform(int **matr, int *buf)
{
    for (size_t i = 0; i < N; ++i)
    {
        matr[i] = buf + i * N;
    }
}

int read(int **matr, int *rows)
{
    int rc = OK, columns;
    
    if (scanf("%d %d", rows, &columns) != 2)
    {
        rc = ERROR;
    }
    
    if (rc == OK)
    {
        if (*rows < 2 || *rows > N || *rows != columns)
        {
            rc = ERROR;
        }
    }
    
    if (rc == OK)
    {
        for (size_t i = 0; rc == OK && (int)i < *rows; ++i)
        {
            for (size_t j = 0; rc == OK && (int)j < *rows; ++j)
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

int find(int **matr, int rows)
{
    int value = 0;
    for (size_t i = 1; (int)i < rows; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            if (matr[i][j] % 2 != 0 && (value == 0 || value > matr[i][j]))
            {
                value = matr[i][j];
            }
        }
    }
    return value;
}


