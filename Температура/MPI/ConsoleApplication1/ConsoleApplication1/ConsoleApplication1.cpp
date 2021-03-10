#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <mpi.h>
#include <math.h>


double phi(double x) //Вычисляем значение функции в точке х
{
	return cos(2 * x + 0.19);
}

const double psi1 = 0.932; //Значение в левой краевой точке

double psi2(double t) //Значение в правой краевой точке
{
	return 0.1798 * t;
}

int main(int arc, char** argv) {
	//Определение начальных значений переменных
	int size, rank, msgtag = 12;
	double a = 1.0, L = 300.0, x = 0.0, time = 0.0, tmax = 1.0, tau = 0.0001, h = 0.02;
	double r = a * tau / (h * h), upr, uu;
	int N = (int)(L / h) + 1;
	int n, l = 0, i, j;

	//шапочка
	if (MPI_Init(&arc, &argv) != MPI_SUCCESS) return 1;
	if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS) {
		MPI_Finalize();
		return 2;
	}
	if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS) {
		MPI_Finalize();
		return 3;
	}

	MPI_Status status;
	//Распределение отрезков по процессам
	int l1 = N / size;
	int l2 = N % size;

	int* kol = new int[size];
	for (i = 0; i < size; i++) kol[i] = l1;

	if (l2) {
		if (rank == size - 1) l1++;
		l2--;
		kol[size - 1]++;
	}
	if (l2) {
		if (rank < l2) l1++;
		for (i = 0; i < l2; i++) kol[i]++;
	}

	n = l1;
	if ((!rank) || (rank == size - 1)) n++; else n += 2;
	double* u = new double[n];

	if (rank) {
		int sum = 0;
		for (i = 0; i < rank; i++) sum += kol[i];
		l = sum;
		sum--;
		x = h * sum; //Вычисляем смещение для каждого промежутка
	}
	//Присваиваем начальные значения
	for (i = 0; i < n; i++) {
		u[i] = phi(x);
		x += h;
	}

	if (!rank) u[0] = psi1;
	if (rank == size - 1) u[n - 1] = psi2(time);

	double tn = MPI_Wtime(); //Начальное время

	do {
		upr = u[0]; //Запоминаем предыдущее значение
		for (i = 1; i < n - 1; i++) {
			uu = u[i];
			u[i] += r * (upr - 2.0 * u[i] + u[i + 1]); //Вычисление новых значений в точках
			upr = uu; //Запоминаем предыдущее значение
		}
		//Начальные значения в краевых точках
		if (!rank) u[0] = psi1;
		if (rank == size - 1) u[n - 1] = psi2(time + tau);
		//Обмен данными между процессами
		if (rank & 1) {
			MPI_Ssend(&u[1], 1, MPI_DOUBLE, rank - 1, msgtag, MPI_COMM_WORLD);
			MPI_Recv(&u[0], 1, MPI_DOUBLE, rank - 1, msgtag, MPI_COMM_WORLD, &status);
			if (rank != size - 1) {
				MPI_Ssend(&u[n - 2], 1, MPI_DOUBLE, rank + 1, msgtag, MPI_COMM_WORLD);
				MPI_Recv(&u[n - 1], 1, MPI_DOUBLE, rank + 1, msgtag, MPI_COMM_WORLD, &status);
			}
		}
		else {
			if (rank != size - 1) {
				MPI_Recv(&u[n - 1], 1, MPI_DOUBLE, rank + 1, msgtag, MPI_COMM_WORLD, &status);
				MPI_Ssend(&u[n - 2], 1, MPI_DOUBLE, rank + 1, msgtag, MPI_COMM_WORLD);
			}
			if (rank) {
				MPI_Recv(&u[0], 1, MPI_DOUBLE, rank - 1, msgtag, MPI_COMM_WORLD, &status);
				MPI_Ssend(&u[1], 1, MPI_DOUBLE, rank - 1, msgtag, MPI_COMM_WORLD);
			}
		}

		time += tau; //Шаг по времени
	} while (time <= tmax);

	double tk = MPI_Wtime(); //Конечное время

	//вывод
	int in, ik;

	if (!rank) in = 0; else in = 1;
	if (rank == size - 1) ik = n; else ik = n - 1;

	for (int i = 0; i < size; i++)
	{
		if (i == rank)
		{
			FILE* f;
			f = fopen("Temperature.txt", "a");
			for (j = in; j < ik; j++, l++) {
				fprintf(f, "u[%d] = %f\n", l, u[j]);
			}
			fclose(f);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	if (!rank) {
		FILE* f;
		f = fopen("Temperature.txt", "a");
		fprintf(f, "\n¬рем¤ вычислений: %f", tk - tn);
		fclose(f);
	}
	delete[]u;
	delete[]kol;

	//тапочки
	MPI_Finalize();
	return 0;
}
