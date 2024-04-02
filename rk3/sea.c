#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

size_t read_field(FILE *fin, int *matr);
size_t my_sqrt(size_t size);
void print(int *matr, size_t size);
void game(int *matr, size_t size);
int check(int *matr, int pos, size_t size);

int main(int argc, char **argv)
{
    FILE *fin = fopen(argv[1], "r");
    if (fin)
    {
        int *matr = malloc(100 * sizeof(int));
        size_t size = 0;
        if (matr)
        {
            size = my_sqrt(read_field(fin, matr));
            print(matr, size);
        }
        if (matr)
            game(matr, size);
        fclose(fin);
        free(matr);
    }
    return 0;
}

size_t read_field(FILE *fin, int *matr)
{
    int tmp = 0;
    size_t size = 0;
    while (fscanf(fin, "%d", &tmp) == 1)
    {
        matr[size] = tmp;
        ++size;
    }
    return size;
}

void print(int *matr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
             printf("%d ", matr[i * size + j]);
        printf("\n");
    }
}

void game(int *matr, size_t size)
{
    char c;
    int i;
    int pos;
    int tmp;
    fprintf(stdout, "Введите координаты: ");
    fscanf(stdin,"%c %d", &c, &i);
    size_t it = 0;
    while (c != 'q' || i != 0)
    {
        ++it;
        if (it % 2 == 1)
        {
        if (i < 1 || i > (int)size || c < 'a' || c >= (char)('a' + size))
            pos = size * size;
        else
            pos = (i - 1) * (int)size + (int)(c - 'a');
        if (pos == size * size)
        {
            fprintf(stdout, "0\n");
        }
        else if (matr[pos] < 1)
        {
            fprintf(stdout, "1\n");
        }
        else
        {
            tmp = matr[pos];
            matr[pos] = -1;
            fprintf(stdout, "%d %d\n", check(matr, pos, size), tmp);
        }
        fprintf(stdout, "Введите координаты: ");
        }
        fscanf(stdin, "%c %d", &c, &i);
    }
}

int check(int *matr, int pos, size_t size)
{
    int rc = 3;
    int tmp = matr[pos];
    matr[pos] = 0;
    if (tmp == -1)
    {
        rc = 3;
        if (rc == 3 && pos >= size)
            rc = check(matr, pos - (int)size, size);
        if (rc == 3 && pos + size < size * size)
            rc = check(matr, pos + (int)size, size);
        if (rc == 3 && pos % (int)size)
            rc = check(matr, pos - 1, size);
        if (rc == 3 && (pos % (int)size) < (int)(size - 1))
            rc = check(matr, pos + 1, size);
    }
    else if (tmp > 0)
        rc = 2;
    matr[pos] = tmp;
    return rc;
}

size_t my_sqrt(size_t size)
{
    size_t ret = 0;
    for (; ret * ret < size; ++ret);
    return ret;
}
