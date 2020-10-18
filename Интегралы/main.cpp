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



double midrect(int n, double a, double b, double* t)
{
    double I = 0, h = (b - a) / n;

    double tn = omp_get_wtime();

    for (int i = 0; i < n; i++)
    {
        I += f(a + i * h + h / 2);
    }

    I *= h;

    double tk = omp_get_wtime();

    *t = tk - tn;
    return I;
}

double trap(int n, double a, double b, double* t)
{
    double I = (f(a) + f(b)) / 2.0, h = (b - a) / n;

    double tn = omp_get_wtime();

    for (int i = 1; i < n; i++)
    {
        I += f(a + i * h);
    }

    I *= h;

    double tk = omp_get_wtime();

    *t = tk - tn;
    return I;
}



//parallel

double midrectP(int n, double a, double b, double* t)
{
    double I = 0, h = (b - a) / n;

    double tn = omp_get_wtime();

#pragma omp parallel for schedule(static) reduction(+:I)
    for (int i = 0; i < n; i++)
    {
        I += f(a + i * h + h / 2);
    }

    I *= h;

    double tk = omp_get_wtime();

    *t = tk - tn;
    return I;
}

double trapP(int n, double a, double b, double* t)
{
    double I = (f(a) + f(b)) / 2.0, h = (b - a) / n;

    double tn = omp_get_wtime();

#pragma omp parallel for schedule(static) reduction(+:I)
    for (int i = 1; i < n; i++)
    {
        I += f(a + i * h);
    }

    I *= h;

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
    printf("Метод cредних прямоугольников:\n\n   I = %f\n   t = %f\n", midrect(n, a, b, &t), t);
    printf("Метод трапеций:\n\n   I = %f\n   t = %f\n", trap(n, a, b, &t), t);

    printf(" Параллельный\n");
    printf("Метод cредних прямоугольников:\n\n   I = %f\n   t = %f\n", midrectP(n, a, b, &t), t);
    printf("Метод трапеций:\n\n   I = %f\n   t = %f\n", trapP(n, a, b, &t), t);

    getchar();
}