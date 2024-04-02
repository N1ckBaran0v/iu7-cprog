#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define N 20
#define M 10
#define OK 0
#define ERROR -1
#define ONE_DIGIT 9

void transform(int **matr, int *buf);
int read(int **matr, int *rows, int *columns, int *digit);
void check(int **matr, int *rows, int columns, int digit);
void shift(int **matr, int *rows, int columns, size_t *i);
void add(int **matr, int columns, size_t i);
void print(int **arr, int rows, int columns);

int main(void)
{
    int buff[N][M], *matr[N], n, m, digit;
    transform(matr, buff[0]);
    int rc = read(matr, &n, &m, &digit);
    
    if (rc == OK)
    {
        check(matr, &n, m, digit);
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

int read(int **matr, int *rows, int *columns, int *digit)
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
    
    if (rc == OK)
    {
        if (scanf("%d", digit) == 1)
        {
            if (*digit < 0 || *digit > ONE_DIGIT)
            {
                rc = ERROR;
            }
        }
        else
        {
            rc = ERROR;
        }
    }
    
    return rc;
}

void check(int **matr, int *rows, int columns, int digit)
{
    for (size_t i = 0; (int)i < *rows; ++i)
    {
        int start = 0, end = 0;
        for (size_t j = 0; (int)j < columns; ++j)
        {
            int temp = abs(matr[i][j]);
            end += temp % 10 == digit;
            while (temp > ONE_DIGIT)
            {
                temp /= 10;
            }
            start += temp == digit;
        }
        if (start == end && start > 0)
        {
            shift(matr, rows, columns, &i);
        }
    }
}

void shift(int **matr, int *rows, int columns, size_t *i)
{
    int *temp = matr[*rows];
    for (size_t it = *rows - 1; it > *i; --it)
    {
        matr[it + 1] = matr[it];
    }
    ++(*i);
    ++(*rows);
    matr[*i] = temp;
    add(matr, columns, *i);
}

void add(int **matr, int columns, size_t i)
{
    for (size_t j = 0; (int)j < columns; ++j)
        matr[i][j] = 100;
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
