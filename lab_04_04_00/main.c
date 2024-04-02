#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

#define N 256
#define OK 0
#define ERROR -1
#define MAX_IP 255
#define END_OF_FILE EOF

size_t read(char *str);
int is_ip(char *str, size_t len);
 
int main(void) 
{
    char str[N + 1];
    int rc = OK;
    size_t len = read(str);
    if (len > N) 
        rc = ERROR;
    else
    {
        int flag = is_ip(str, len);
        printf((flag) ? "NO\n" : "YES\n");
    }
    return rc;
}

size_t read(char *str)
{
    char temp = getchar();
    size_t i = 0;
    while (temp != '\n' && temp != END_OF_FILE)
    {
        if (i < N)
        {
            str[i++] = temp;
            temp = getchar();
        }
        else
        {
            temp = END_OF_FILE;
            ++i;
        }
    }
    if (i <= N)
        str[i] = '\0';
    else
        str[N] = '\0';
    return i;
}

int is_ip(char *str, size_t len)
{
    size_t start = 0;
    for (; isspace(str[start]) && str[start]; ++start);
    size_t end = len - (len > 0);
    for (; end > start && isspace(str[end]); --end);
    int str_is_ip = ERROR, was_digit = ERROR, is_correct = OK;
    int num = 0, points = 0, digits = 0;
    for (size_t i = start; i <= end && is_correct == OK; ++i)
    {
        if (isdigit(str[i]))
        {
            int digit = str[i] - '0';
            if (digits == 3)
                is_correct = ERROR;
            was_digit = OK;
            num *= 10;
            num += digit;
            ++digits;
            if (points == 3)
                str_is_ip = OK;
            if (num > MAX_IP)
                is_correct = ERROR;
        }
        else if (str[i] == '.')
        {
            if (was_digit == ERROR || points == 3)
                is_correct = ERROR;
            else
            {
                ++points;
                was_digit = ERROR;
                digits = 0;
                num = 0;
            }
        }
        else
            is_correct = ERROR;
    }
    if (is_correct == ERROR)
        str_is_ip = ERROR;
    return str_is_ip;
}
