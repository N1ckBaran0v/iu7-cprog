#include <stdio.h>
#include <stddef.h>

#define N 10
#define M 10
#define OK 0
#define ERROR -1

void transform(int **matr, int *buf);
int read(int **matr, int *rows, int *columns);
int reverse_simples(int **matr, int rows, int columns);
void print(int **matr, int rows, int columns);
int is_simple(int a);
void reverse(int *arr, int size);
void swap(int *a, int *b);

int main(void)
{
    int buff[N][M], *matr[N], n, m;
    transform(matr, buff[0]);
    int rc = read(matr, &n, &m);
    
    if (rc == OK)
    {
        rc = reverse_simples(matr, n, m);
    }
    
    if (rc == OK)
    {
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

int reverse_simples(int **matr, int rows, int columns)
{
    int simples[N * M], size = 0, rc = OK;
    for (size_t i = 0; (int)i < rows; ++i)
    {
        for (size_t j = 0; (int)j < columns; ++j)
        {
            if (is_simple(matr[i][j]) == OK)
            {
                simples[size] = matr[i][j];
                ++size;
            }
        }
    }
    if (size == 0)
    {
        rc = ERROR;
    }
    else
    {
        reverse(simples, size);
        size = 0;
        for (size_t i = 0; (int)i < rows; ++i)
        {
            for (size_t j = 0; (int)j < columns; ++j)
            {
                if (is_simple(matr[i][j]) == OK)
                {
                    matr[i][j] = simples[size];
                    ++size;
                }
            }
        }
    }
    return rc;
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

int is_simple(int a)
{
    int rc = OK;
    if (a < 2)
    {
        rc = ERROR;
    }
    else
    {
        for (int i = 2; rc == OK && (long long)i * i <= (long long)a; ++i)
        {
            if (a % i == 0)
            {
                rc = ERROR;
            }
        }
    }
    return rc;
}

void reverse(int *arr, int size)
{
    for (size_t i = 0; (int)i < size / 2; ++i)
    {
        swap(arr + i, arr + (size - i - 1));
    }
}

void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
