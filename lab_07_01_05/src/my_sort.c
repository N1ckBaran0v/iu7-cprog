#include "../inc/my_sort.h"

void my__swap(void *my__first, void *my__second, size_t my__size);

void mysort(void *my__base, size_t my__nmemb, size_t my__size, int (*my__compar)(const void *, const void *))
{
    size_t end = my__nmemb;
    size_t last;

    while (end > 1)
    {
        last = 1;
        for (size_t i = 1; i < end; ++i)
        {
            if (my__compar((char*)my__base + (i - 1) * my__size, (char*)my__base + i * my__size) > 0)
            {
                my__swap((char*)my__base + (i - 1) * my__size, (char*)my__base + i * my__size, my__size);
                last = i;
            }
        }
        end = last;
    }
}

int intcmp(const void *first, const void *second)
{
    const int *p_first = first;
    const int *p_second = second;
    int rc = 0;
    if (*p_first > *p_second)
        rc = 1;
    if (*p_first < *p_second)
        rc = -1;
    return rc;
}

void my__swap(void *my__first, void *my__second, size_t my__size)
{
    char *first = my__first;
    char *second = my__second;
    char tmp;
    for (size_t i = 0; i < my__size; ++i)
    {
        tmp = *(first + i);
        *(first + i) = *(second + i);
        *(second + i) = tmp;
    }
}