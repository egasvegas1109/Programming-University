#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <windows.h>
#include <iostream>
#include <ctime>
using namespace std;
double func(double x[], double t, int rank) //Вычисление правых частей системы уравнений
{
	double w;
	switch (rank)
	{
	case 0:
	{
		w = (-2 + x[1]) * x[0] + 0.1 * x[0] * x[0];
		break;
	}
	case 1:
	{
		w = (4 - 2.5 * x[0]) * x[1] - 0.1 * x[1] * x[1];
		break;
	}
	}
	return w;
}
void one() //Однопроцессорный(последовательный)
{
	const int n = 2;//Число неизвестных
	const int m = 4;//Степень метода Рунге-Кутта
	double y[n] = { 1.0, 3.0 }, yy[n] = { 0.0 }, time = 0.0, tmax = 0.1, tau = 0.01, r[m][n];
	/*y – начальные значения, yy – промежуточные значения, time – текущее время, tmax – максимальное время, tau – шаг, r – значения коэффициентов*/
	printf("ONE:\n   time = %f\n", time);

	printf(" NACH ZNACH     x0 = %f\n", y[0]);
	printf(" NACH ZNACH     y0 = %f\n", y[1]);

	do
	{
	#pragma omp parallel //Объявление параллельной секции
		{
		#pragma omp for schedule(static, 1) 
			for (int i = 0; i < n; i++)
			{
				r[0][i] = tau * func(y, time, i);//Вычисление 1 коэфф.
				yy[i] = y[i] + 0.5 * r[0][i];//Подготовка промежут. знач. для 2 коэфф
			}
		#pragma omp for schedule(static, 1) 
			for (int i = 0; i < n; i++)
			{
				r[1][i] = tau * func(yy, time + tau * 0.5, i);//Вычисление 2 коэфф.
			}
		#pragma omp for schedule(static, 1) 
			for (int i = 0; i < n; i++)
			{
				yy[i] = y[i] + 0.5 * r[1][i];//Подготовка промежут. знач. для 3 коэфф
			}
		#pragma omp for schedule(static, 1) 
			for (int i = 0; i < n; i++)
			{
				r[2][i] = tau * func(yy, time + tau * 0.5, i);//Вычисление 3 коэфф.
			}
		#pragma omp for schedule(static, 1) 
			for (int i = 0; i < n; i++)
			{
				yy[i] = y[i] + r[2][i];//Подготовка промежут. знач. для 4 коэфф
			}
		#pragma omp for schedule(static, 1) 
			for (int i = 0; i < n; i++)
			{
				r[3][i] = tau * func(yy, time + tau, i);//Вычисление 4 коэфф.
				y[i] += (r[0][i] + 2.0 * r[1][i] + 2.0 * r[2][i] + r[3][i]) / 6.0;//Конечные знач.
			}
		}
		time += tau;

		printf("   time = %f\n", time);
		printf(" x0 = %f\n", y[0]);
		printf(" y0 = %f\n", y[1]);
	} while (time <= tmax);
	cout << "\ntime_end = " << clock() / 1000.0 << endl; // замеряем время
}
int main()
{
	one();
	system("pause");
	return 0;
}
