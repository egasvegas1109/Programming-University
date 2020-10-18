#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <clocale>




double f(double x) //функция
{
    return 1 / sqrt(1 + 3 * x + 2 * x * x);
}



double simposon(int n, double a, double b, double* t)
{
    double I = (f(b) - f(a)) / 2.0, h = (b - a) / n;

    double tn = omp_get_wtime();

    for (int i = 0; i < n; i++)
    {
        I += f(a + i * h) + 2.0 * f(a + i * h + h / 2.0);
    }

    I *= h / 3;

    double tk = omp_get_wtime();

    *t = tk - tn;
    return I;
}



//parallel

double simposonP(int n, double a, double b, double* t)
{
    double I = (f(b) - f(a)) / 2.0, h = (b - a) / n;

    double tn = omp_get_wtime();

#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++)
    {
        I += f(a + i * h) + 2.0 * f(a + i * h + h / 2.0);
    }

    I *= h / 3;

    double tk = omp_get_wtime();

    *t = tk - tn;
    return I;
}



int main()
{
    int n = 100;
    double a = 0, b = 2, t = 0.0;

    srand(time(0));

	setlocale(LC_ALL, "RUS");

    printf("Однопроцессорный\n");
    printf("Метод Симпсона:\n\n   I = %f\n   t = %f\n", simposon(n, a, b, &t), t);


	printf("Параллельный\n");
	printf("Метод Симпсона:\n\n   I = %f\n   t = %f\n", simposonP(n, a, b, &t), t);

    getchar();
}