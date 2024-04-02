#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#define SIZEOF_STR 256
#define SIZEOF_WORD 16
#define ARR_SIZE 128
#define OK 0
#define ERROR -1
#define END_OF_FILE EOF
#define MY_NULL NULL

void transform(char **arr, char *buf);
size_t read(char *str);
int str_tok(char *str, char **arr, size_t *size);
void new_string(char **arr, char *new_str, size_t size);
 
int main(void) 
{
    char str[SIZEOF_STR + 1];
    char *arr[ARR_SIZE], buff[ARR_SIZE][SIZEOF_WORD + 1];
    transform(arr, buff[0]);
    int rc = OK;
    size_t len = read(str);
    if (len > SIZEOF_STR || len == 0)
    {
        rc = ERROR;
    }
    else
    {
        size_t size = 0;
        rc = str_tok(str, arr, &size);
        char new_str[SIZEOF_STR + 1];
        if (rc == OK)
        {
            new_string(arr, new_str, size);
            if (strlen(new_str))
                printf("Result: %s\n", new_str);
            else
                rc = ERROR;
        }
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
    char sep[] = " ,.:;-!?";
    char *buf = strtok(str, sep);
    int rc = OK;
    while (buf != MY_NULL && rc == OK)
    {
        if (strlen(buf) > SIZEOF_WORD)
        {
            rc = ERROR;
        }
        else if (strlen(buf) > 0)
        {
            arr[*size] = strcpy(arr[*size], buf);
            ++(*size);
            buf = strtok(MY_NULL, sep);
        }
    }
    return rc;
}

void new_string(char **arr, char *new_str, size_t size)
{
    int last = (int)size - 1;
    size_t it = 0;
    for (int i = last - 1; i >= 0; --i)
        if (strcmp(arr[i], arr[last]))
        {
            if (it != 0)
                new_str[it++] = ' ';
            char first = arr[i][0];
            new_str[it++] = first;
            for (size_t j = 1; j < SIZEOF_WORD && arr[i][j] != '\0'; ++j)
                if (arr[i][j] != first)
                    new_str[it++] = arr[i][j];
        }
    new_str[it] = '\0';
}
