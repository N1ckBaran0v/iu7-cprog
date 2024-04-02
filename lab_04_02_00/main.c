#include <stdio.h>
#include <stddef.h>

#define SIZEOF_STR 256
#define SIZEOF_WORD 16
#define ARR_SIZE 128
#define OK 0
#define ERROR -1
#define END_OF_FILE EOF

void transform(char **arr, char *buf);
size_t read(char *str);
int str_tok(char *str, char **arr, size_t *size);
int in(char *str, char sym);
void count(char **arr, size_t size, int *find);
int str_cmp(char *str1, char *str2);
void print(char **arr, size_t size, int *find);
 
int main(void) 
{
    char str[SIZEOF_STR + 1];
    char *arr[ARR_SIZE], buff[ARR_SIZE][SIZEOF_WORD + 1];
    transform(arr, buff[0]);
    int rc = OK;
    size_t len = read(str);
    size_t size = 0;
    if (len > SIZEOF_STR)
        rc = ERROR;
    else
        rc = str_tok(str, arr, &size);
    if (rc == OK)
    {
        int find[ARR_SIZE];
        count(arr, size, find);
        print(arr, size, find);
    }
    return rc;
}

void transform(char **arr, char *buf)
{
    for (size_t i = 0; i < ARR_SIZE; ++i)
        arr[i] = buf + i * (SIZEOF_WORD + 1);
}

size_t read(char *str)
{
    char temp = getchar();
    size_t i = 0;
    while (temp != '\n' && temp != END_OF_FILE)
    {
        if (i < SIZEOF_STR)
        {
            str[i] = temp;
            temp = getchar();
        }
        else
            temp = '\n';
        ++i;
    }
    str[i] = '\0';
    return i;
}

int str_tok(char *str, char **arr, size_t *size)
{
    char *sep = " ,.:;-!?";
    int rc = OK;
    size_t j = 0;
    for (char *it = str; *it && rc == OK; ++it)
    {
        if (in(sep, *it))
        {
            if (j > 0)
            {
                arr[(*size)++][j] = '\0';
                j = 0;
            }
        }
        else
        {
            if (j == SIZEOF_WORD)
                rc = ERROR;
            else
                arr[*size][j++] = *it;
        }
    }
    if (j > 0)
    {
        arr[(*size)++][j] = '\0';
        j = 0;
    }
    if (*size == 0)
        rc = ERROR;
    return rc;
}

int in(char *str, char sym)
{
    for (; *str && *str != sym; ++str);
    return *str;
}

void count(char **arr, size_t size, int *find)
{
    for (size_t i = 0; i < size; ++i)
    {
        int flag = OK;
        for (size_t j = 0; i - j && flag == OK; ++j)
            if (!(str_cmp(arr[i], arr[j])))
            {
                ++find[j];
                find[i] = 0;
                flag = ERROR;
            }
        if (flag == OK)
            find[i] = 1;
    }
}

int str_cmp(char *str1, char *str2)
{
    size_t i = 0;
    for (; str1[i] == str2[i] && str1[i]; ++i);
    return str1[i] - str2[i];
}

void print(char **arr, size_t size, int *find)
{
    printf("Result: ");
    for (size_t i = 0; i < size; ++i)
        if (find[i])
            printf("%s %d\n", arr[i], find[i]);
}
