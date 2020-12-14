#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define lmax 200

int main(int arc, char** argv) {
	double lx = 1.0, ly = 1.0, h = 0.2, x = 0.0, y = 0.0; //начальные значения по условия задачи
	int i, j, n, m;

	n = (int)(lx / h) + 1; //Число точек по горизонтали
	m = (int)(ly / h) + 1; //по вертикали

	double** u = new double* [n]; //массив точек сетки

#pragma omp parallel for schedule(static)
	for (i = 0; i < n; i++)
		u[i] = new double[m];

#pragma omp parallel for schedule(static)
	for (i = 0; i < n; i++) //заполняем начальные значения нулями
		for (j = 0; j < m; j++)
			u[i][j] = 0.0;

	x = 0.0;
#pragma omp parallel for schedule(static)
	for (i = 0; i < n; i++) {
		u[i][0] = 60.0 * x * (1.0 - x * x); //AD
		u[i][m - 1] = 50.0 * (1.0 - x); //BC
		x += h;
	}

	y = 0.0;

#pragma omp parallel for schedule(static)
	for (j = 0; j < m; j++) {
		u[0][j] = 50.0 * y * y; //AB
		u[n - 1][j] = 0.0;//CD
		y += h;
	}

	double tn = omp_get_wtime();
#pragma omp parallel for schedule(static)
	for (int k = 0; k < lmax; k++)
	{
#pragma omp parallel for schedule(static)
		for (i = 1; i < n - 1; i++) //высчитываем основную область
#pragma omp parallel for schedule(static)
			for (j = 1; j < m - 1; j++)
				u[i][j] = 0.25 * (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1]);
	}
	double tk = omp_get_wtime();


	FILE* f;
	f = fopen("Rez.dat", "w");
	fprintf(f, "Time %f\n", tk - tn);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++)
			fprintf(f, "u[%d][%d]=%f   ", j, i, u[j][i]);
		fprintf(f, "\n");
	}
	fclose(f);
	for (i = 0; i < n; i++)
		delete[] u[i];
	delete[] u;

	return 0;
}
