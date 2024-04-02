#include <stdio.h>
#include <stddef.h>

#define N 10
#define M 10
#define OK 0
#define ERROR -1

void transform(int **matr, int *buf);
int read(int *rows, int *columns);
void generate(int **matr, int rows, int columns);
void print(int **arr, int rows, int columns);

int main(void)
{
    int buff[N][M], *matr[N], n, m;
    transform(matr, buff[0]);
    int rc = read(&n, &m);
    
    if (rc == OK)
    {
        generate(matr, n, m);
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

int read(int *rows, int *columns)
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
    
    return rc;
}

void generate(int **matr, int rows, int columns)
{
    int num = 1;
    for (size_t j = 0; (int)j < columns; ++j)
    {
        for (size_t i = 0; (int)i < rows; ++i)
        {
            matr[i][j] = num;
            num += 1;
        }
        ++j;
        for (size_t i = rows; (int)j < columns && i > 0; --i)
        {
            matr[i - 1][j] = num;
            num += 1;
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
