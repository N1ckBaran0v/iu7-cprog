#include <stdio.h>
#include <stddef.h>

#define N 10
#define OK 0
#define ERROR -1

int read(int *begin, int *end);
int solve(int *begin, int *end);

int main(void)
{
    int arr[N], n;
    int return_code = OK;
    
    if (scanf("%d", &n) != 1)
    {
        return_code = ERROR;
    }
    
    if (return_code == OK && n > 0 && n <= N) 
    {
        int *begin = arr, *end = begin + n;
        return_code = read(begin, end);
        if (return_code == OK)
        {
            int answer = solve(begin, end);
            printf("%d\n", answer);
        }
    }
    else
    {
        return_code = ERROR;
    }
    
    return return_code;
}

int read(int *begin, int *end)
{
    int rc = OK;
    
    for (int *ptr = begin; ptr < end && rc == OK; ptr++)
    {
        if (scanf("%d", ptr) != 1)
        {
            rc = ERROR;
        }
    }
    
    return rc;
}

int solve(int *begin, int *end)
{
    int answer = 0;
    int first = *begin;
    for (int *ptr = begin; ptr < end; ptr++)
    {
        if (*ptr != first || ptr == begin)
        {
            answer++;
            for (int *next = ptr + 1; next < end; next++)
            {
                if (*next == first || *next == *ptr)
                {
                    *next = first;
                }
            }
        }
    }
    
    return answer;
}
