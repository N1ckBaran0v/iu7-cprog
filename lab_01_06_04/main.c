#include <stdio.h>
#include <math.h>

#define OK 0
#define ERROR 1
#define EPS 0.0000005

int readpoint(double*, double*);

int solve(double, double, double, double, double, double);

int main(void)
{
    double xq, yq, xr, yr, xp, yp;
    int rc = readpoint(&xq, &yq);
    
    if (rc == OK)
    {
        rc = readpoint(&xr, &yr);
    }
    
    if (rc == OK)
    {
        rc = readpoint(&xp, &yp);
    }
    
    if (rc == OK && (fabs(xq - xr) > EPS || fabs(yq - yr) > EPS))
    {
        int answer = solve(xq, yq, xr, yr, xp, yp);
        printf("%d\n", answer);
    }
    else
    {
        rc = 1;
    }
    return rc;
}

int readpoint(double *x, double *y)
{
    int rc = OK;
    
    if (scanf("%lf%lf", x, y) != 2)
    {
        rc = ERROR;
    }
    
    return rc;
}

int solve(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double qr = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double qp = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    double pr = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    int rc = fabs(qr - qp - pr) < EPS;
    return rc;
}
