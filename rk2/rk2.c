// Variant 1

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#define N 5
#define STRLEN 5

#define OK 0
#define INPUT_ERROR -1

#define EQUAL_LEN 1
#define NOT_EQUAL_LEN 0

struct matrix
{
    char matr[N][N][STRLEN + 1];
    int len;
};

int read(struct matrix *matr);
int read_str(char *str);
int count(struct matrix *matr);
void print(struct matrix *matr);

int main(void)
{
    struct matrix matr;
    int rc = read(&matr);
    if (rc == OK)
    {
        print(&matr);
        int ans = count(&matr);
        printf("%d\n", ans);
    }
    return rc;
}

int read(struct matrix *matr)
{
    int rc = OK;
    if (scanf("%d", &matr->len) != 1)
        rc = INPUT_ERROR;
    for (size_t i = 0; (int)i < matr->len && rc == OK; ++i)
        for (size_t j = 0; (int)j < matr->len && rc == OK; ++j)
            rc = read_str(matr->matr[i][j]);
    return rc;
}

int read_str(char *str)
{
    int rc = OK;
    char tmp = getchar();
    size_t i = 0;
    while (isspace(tmp))
        tmp = getchar();
    while (rc == OK && tmp != EOF && !(isspace(tmp)))
    {
        if (i == 5)
            rc = INPUT_ERROR;
        else
        {
            str[i] = tmp;
            tmp = getchar();
        }
        ++i;
    }
    if (i < 6)
        str[i] = '\0';
    return rc;
}

int count(struct matrix *matr)
{
    int ans = 0;
    for (size_t j = 0; (int)j < matr->len; ++j)
    {
        int res = EQUAL_LEN;
        for (size_t i = 1; (int)i < matr->len && res == EQUAL_LEN; ++i)
            if (strlen(matr->matr[i][j]) != strlen(matr->matr[i - 1][j]))
                res = NOT_EQUAL_LEN;
        ans += res;
    }
    return ans;
}

void print(struct matrix *matr)
{
    for (size_t i = 0; (int)i < matr->len; ++i)
    {
        for (size_t j = 0; (int)j < matr->len; ++j)
            printf("%5s ", matr->matr[i][j]);
        printf("\n");
    }
        
}
