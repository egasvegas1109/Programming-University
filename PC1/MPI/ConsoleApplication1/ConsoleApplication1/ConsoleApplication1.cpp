#include <stdio.h>
#include <mpi.h>
#include <math.h>
#define comm MPI_COMM_WORLD
double func(double x[], double t, int i)
{
	double w;
	switch (i)
	{
	case 1:
	{
		w = (-2 + x[1]) * x[0] + 0.1 * x[0] * x[0];
		break;
	}
	case 2:
	{
		w = (4 - 2.5 * x[0]) * x[1] - 0.1 * x[1] * x[1];
		break;
	}
	}
	return w;
}
int main(int arc, char** argv) {
	int i, j;
	int size, rank, msgtag = 1;
	const int m = 4, n = 2;
	double y[n] = { 3.0, 1.0 }, yy[n] = { 0.0 }, time = 0.0, tmax = 0.1, tau = 1*exp(-3), r[m], ff = 0.0;

	//Шапочка
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
	if (!rank) { //Открываем на 0 процессе файл и выводим начальные значения
		printf("time = %f\n", time);
		printf(" NACH ZNACH     x0 = %f\n", y[0]);
		printf(" NACH ZNACH     y0 = %f\n", y[1]);
	}
	double tn = MPI_Wtime(); //Узнаем текущее время(начальное)
	do {
		if (!rank) { //Для 0 процесса принимаем от остальных промеж. знач. и отправляем  их всем
			double tmp;
			for (i = 0;i < m;i++) {
				for (j = 0;j < n;j++) {
					MPI_Recv(&tmp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, msgtag, comm, &status);
					yy[status.MPI_SOURCE - 1] = tmp;
				}
				for (j = 0;j < n;j++)
					MPI_Send(yy, n, MPI_DOUBLE, j+1, msgtag, comm);
			}
		}
		else {
			/*Не 0 процесс, вычисляем значения коэфф. и промежуточных значений и отправляем их на 0 процесс, после принимаем от 0 массив со всеми промежуточными переменными */
			j = rank - 1;
			r[0] = tau * func(y, time, rank);
			ff = y[j] + 0.5 * r[0];
			MPI_Send(&ff, 1, MPI_DOUBLE, 0, msgtag, comm);
			MPI_Recv(yy, n, MPI_DOUBLE, 0, msgtag, comm, &status);

			r[1] = tau * func(yy, time + 0.5 * tau, rank);
			ff = y[j] + 0.5 * r[1];
			MPI_Send(&ff, 1, MPI_DOUBLE, 0, msgtag, comm);
			MPI_Recv(yy, n, MPI_DOUBLE, 0, msgtag, comm, &status);

			r[2] = tau * func(yy, time + 0.5 * tau, rank);
			ff = y[j] + r[2];
			MPI_Send(&ff, 1, MPI_DOUBLE, 0, msgtag, comm);
			MPI_Recv(yy, n, MPI_DOUBLE, 0, msgtag, comm, &status);

			r[3] = tau * func(yy, time + tau, rank);
			y[j] += (r[0] + 2.0 * r[1] + 2.0 * r[2] + r[3]) / 6.0;
			MPI_Send(&y[j], 1, MPI_DOUBLE, 0, msgtag, comm);
			MPI_Recv(y, n, MPI_DOUBLE, 0, msgtag, comm, &status);
		}
		time += tau; //Смещаемся по времени
	//Ждем пока все не закончат считать и записываем текущие значения на 0 процессе
		MPI_Barrier(comm);
		if (!rank) {

			printf("time = %f\n", time);
			printf(" x0 = %f\n", yy[0]);
			printf(" y0 = %f\n", yy[1]);
		}
	} while (time <= tmax);
	double tk = MPI_Wtime(); //Текущее время(конечное)
	if (!rank) {

		printf("\ntime_end = %f\n", tk - tn); //Записываем время выполнения в файл

	}
	//Тапочки
	MPI_Finalize();
	return 0;
}
