#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <windows.h>
#include <iostream>	

using namespace std;

double phi(double x) //Вычисляем значение функции в точке х
{
	return cos(2 * x + 0.19);
}

const double psi1 = 0.932; //Значение в левой краевой точке

double psi2(double t) //Значение в правой краевой точке
{
	return 0.1798 * t;
}
int main()
{
	setlocale(LC_ALL, "RUS");
	//Объявление начальных значений
	double a = 1.0, L = 300.0, x = 0.0, time = 0.0, tmax = 10.0, tau = 0.0001, h = 0.02;
	double r = a * tau / (h * h); //Постоянный коэффициент
	int n = (int)(L / h) + 1;
	double* u = new double[n];
	double* un = new double[n];
	double tn = omp_get_wtime(); //Начальное время
	u[0] = psi1; //Начальное значение в левой краевой точке
	x += h; //Шаг по координате
	for (int i = 1; i < n - 1; i++) //Задаем начальные значения
	{
		u[i] = phi(x);
		x += h;
	}
	u[n - 1] = psi2(time); //Начальное значение в правой краевой точке
	do {
		printf(" \r Время расчёта %f", time); // Вывод текущего значения переменной time для отладки
#pragma omp parallel //Открываем параллельную секцию
		{
#pragma omp for schedule(dynamic, 1)
			for (int i = 1; i < n - 1; i++) //Вычисляем новые значения в точках
			{
				un[i] = u[i] + r * (u[i - 1] - 2.0 * u[i] + u[i + 1]);
			}
#pragma omp for schedule(dynamic, 1)
			for (int i = 1; i < n - 1; i++) //Переприсваиваем новые значения в массив u
			{
				u[i] = un[i];
			}
		}
		time += tau; //Шаг по времени
		u[0] = psi1;
		u[n - 1] = psi2(time);
	} while (time <= tmax);
	double tk = omp_get_wtime(); //Конечное время
	FILE* f;
	f = fopen("Temp_res_m.dat", "w");
	for (int i = 0; i < n; i++)
		fprintf(f, "u[%d] = %f\n", i, u[i]); //Вывод значений
	fprintf(f, "\nВремя вычислений: %f\n", tk - tn); //Время выполнения
	fclose(f);
	delete[] u;
	delete[] un;
	system("pause");
	return 0;
}
