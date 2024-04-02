#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define N 10
#define MY_NULL NULL
#define TRUE 1
#define FALSE 0

char *my_strchr(char *s, int c);
char *my_strrchr(char *s, int c);
char *my_strpbrk(char *s, char *accept);

int main(void) 
{
    char *tests[] = 
    {
        "Hello, world!",
        "NO SYMBOL HERE",
        "FIRST",
        "LAST",
        "SEARCH '\\0'",
        "qwertyuiop",
        "A lot of symbols o",
        "87418297219831789712831",
        "Why I must write this 3 times for every function?",
        "Goodbye!"
    };
    
    int fail_strchr = 0;
    char sc[N] =
    {
        ',', 'A', 'F', 'T', '\0', 'y', 'o', '2', '3', 'g'
    };
    
    for (size_t i = 0; i < N; ++i)
        fail_strchr += my_strchr(tests[i], sc[i]) != strchr(tests[i], sc[i]);
    
    int fail_strrchr = 0;
    
    for (size_t i = 0; i < N; ++i)
        fail_strrchr += my_strrchr(tests[i], sc[i]) != strrchr(tests[i], sc[i]);
    
    char *ac[] = 
    {
        ", ",
        "KAK",
        "FT",
        "LT",
        "\0\0\0",
        "eyyyo",
        "oooooo",
        "9293",
        "must",
        "bye"
    };
    
    int fail_strpbrk = 0;
    
    for (size_t i = 0; i < N; ++i)
        fail_strpbrk += my_strpbrk(tests[i], ac[i]) != strpbrk(tests[i], ac[i]);
        
    printf("%d %d %d\n", fail_strchr, fail_strrchr, fail_strpbrk);
    
    return 0;
}

char *my_strchr(char *s, int c)
{
    char *result = s;
    for (; *result && *result != c; ++result);
    if (*result != c)
        result = MY_NULL;
    return result;
}

char *my_strrchr(char *s, int c)
{
    char *result = s;
    for (; *result; ++result);
    for (; result != s && *result != c; --result);
    if (*result != c)
        result = MY_NULL;
    return result;
}

char *my_strpbrk(char *s, char *accept)
{
    char *result = s;
    int flag = TRUE;
    for (; *result && flag; ++result)
        for (char *it = accept; *it && flag; ++it)
            if (*it == *result)
                flag = FALSE;
    if (flag)
        result = MY_NULL;
    else
        --result;
    return result;
}
