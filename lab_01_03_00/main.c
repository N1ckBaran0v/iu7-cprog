#include <stdio.h>

double mnormal(double, double);

double bmi(double, double);

int main(void)
{
	double h, t, m;
	scanf("%lf%lf%lf", &h, &t, &m);
	double mn = mnormal(h, t);
	double bmi0 = bmi(m, h);
	printf("%.6lf\n%.6lf\n", mn, bmi0);
	return 0;
}

double mnormal(double h, double t)
{
	return h * t / 240;
}

double bmi(double m, double h)
{
	h /= 100.0;
	return m / (h * h);
}
