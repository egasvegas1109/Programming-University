//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mpi.h"
#define COMM MPI_COMM_WORLD
#define m 25
#define n 20
#define m1 5
#define n1 6

int main(int argc, char** argv)
{
	MPI_Status status;
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
	{
		return 1;
	}
	int size, rank;
	if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS)
	{
		MPI_Finalize();
		return 2;
	}
	if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS)
	{
		MPI_Finalize();
		return 3;
	}

	int i, j, msgtag = 12;
	int buf_size = m1 * n1 * sizeof(int);

	if (rank == 0)
	{
		printf("rank=%d\n", rank);
		int matrix[m][n];//создание массива

		for (i = 0; i < m; i++)//заполнение массива
			for (j = 0; j < n; j++)
				matrix[i][j] = i + j + 1;

		FILE* f;//создание файла
		char name[25];
		sprintf(name, "Ucxodnaya matrica.txt");
		f = fopen(name, "w");
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++)
				fprintf(f, "%d\t", matrix[i][j]);//печать исходной матрицы
			fprintf(f, "\n");
		}
		fclose(f);

		int position = 0;
		int buf[m1][n1];
		for (i = 4; i < m1 + 4; i++)
			for (j = 4; j < n1 + 4; j++)
				MPI_Pack(&matrix[i][j], 1, MPI_INT, &buf, buf_size, &position, COMM);
		MPI_Send(buf, buf_size, MPI_PACKED, 1, msgtag, COMM);
	}
	else
	{
		printf("rank=%d\n", rank);
		int final_matrix[m1][n1];
		int buf[m1][n1];
		int pos = 0;
		MPI_Recv(buf, buf_size, MPI_PACKED, 0, msgtag, COMM, &status);
		for (i = 0; i < m1; i++)
			for (j = 0; j < n1; j++)
				MPI_Unpack(buf, buf_size, &pos, &final_matrix[i][j], 1, MPI_INT, COMM);

		FILE* f;
		char name[25];
		sprintf(name, "Final'na9 matrica.txt");
		f = fopen(name, "w");
		for (i = 0; i < m1; i++) {
			for (j = 0; j < n1; j++)
				fprintf(f, "%d\t", final_matrix[i][j]);
			fprintf(f, "\n");
		}
		fclose(f);
	}
	MPI_Finalize();
	return 0;
}
