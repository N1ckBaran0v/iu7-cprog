#include <stdio.h>
#include <math.h>

double perimeter(double, double, double);

int main(void)
{
	double a, b, h;
	scanf("%lf%lf%lf", &a, &b, &h);
	double p = perimeter(a, b, h);
	printf("%.6lf\n", p);
	return 0;
}

double perimeter(double a, double b, double h)
{
	double difference = fabs(a - b) / 2;
	return 2 * sqrt(pow(difference, 2) + pow(h, 2)) + a + b;
}
