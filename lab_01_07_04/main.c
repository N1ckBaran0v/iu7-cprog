#include <stdio.h>
#include <math.h>

#define OK 0
#define ERROR 1

double solve(double, double);

int main(void)
{
    double x, eps;
    int rc = OK;
    
    if (scanf("%lf%lf", &x, &eps) == 2 && eps > 0 && eps <= 1 && fabs(x) < 1)
    {
        double s = solve(x, eps);
        double f = 1 / pow(x + 1, 3);
        double delt = fabs(f - s);
        double sigm = delt / fabs(f);
        printf("%.6lf %.6lf %.6lf %.6lf\n", s, f, delt, sigm);
    }
    else
    {
        rc = ERROR;
    }
    
    return rc;
}

double solve(double x, double eps)
{
    double s = 0.0;
    double next = 1.0;
    long long num = 2;
    while (fabs(next) >= eps)
    {
        s += next;
        next /= (num - 1);
        next *= (num + 1);
        next *= -x;
        num += 1;
    }
    return s;
}
