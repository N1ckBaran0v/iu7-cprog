#include <stdio.h>
#include <math.h>

#define OK 0
#define ERROR 1

int main(void)
{
    int n = 0;
    double x, result = 0.0;
    int read_code = scanf("%lf", &x), return_code = OK;
    
    while (read_code == 1 && x >= 0.0)
    {
        ++n;
        result += x / n;
        read_code = scanf("%lf", &x);
    }
    
    if (read_code == 1 && n > 0)
    {
        result = sqrt(result);
        printf("%lf\n", result);
    }
    else
    {
        return_code = ERROR;
    }
    
    return return_code;
}
