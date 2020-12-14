#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "mpi.h"
//mpiexec -n 2 ConsoleApplication1.exe
#define n 3 
#define m 4 
#define l 11 // Размер массива 
#define k 3 // Количество полей 

using namespace std;

int main(int argc, char** argv) {

	// Шапка
	int size, rank, msgtag = 3;
	MPI_Status status;
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
		return 1;
	if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS) {
		MPI_Finalize();
		return 2;
	}
	if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS) {
		MPI_Finalize();
		return 3;
	}


	union L {
		double a;
		int b;
	} myunion[l], unionType[l];

	// Создаем свой тип
	MPI_Datatype mytype;
	MPI_Datatype r[k] = { MPI_DOUBLE, MPI_INT }; // Массив с описанием типов полей
	int block[k] = { 1, 1 }; // Массив с длинами полей
	MPI_Aint disp[k], tt; // Массив со смещением полей от начала структуры в байтах

	MPI_Get_address(&myunion[0].a, &disp[0]);
	MPI_Get_address(&myunion[0].b, &disp[1]);

	tt = disp[0];
	for (int i = 0; i < k; i++) {
		disp[i] -= tt;
	}
	MPI_Type_create_struct(k, block, disp, r, &mytype);
	MPI_Type_commit(&mytype);

	double tNach = 0.0, tKon = 0.0; // Переменные для время
	//int position = 0;
	//int sizeUnion = l * sizeof(myunion); // Размер

	if (!rank) {

		// Заполнение массива
		for (int i = 0; i < l; i++)
		{
			myunion[i].a = i;
			myunion[i].b = i;
		}
		tNach = MPI_Wtime();
		MPI_Send(&tNach, 1, MPI_DOUBLE, 1, msgtag, MPI_COMM_WORLD);
		MPI_Send(myunion, l, mytype, 1, msgtag, MPI_COMM_WORLD);
		tNach = MPI_Wtime();
		MPI_Send(&tNach, 1, MPI_DOUBLE, 1, msgtag, MPI_COMM_WORLD);

	}
	else {
		int pos = 0;
		double tProm;
		tKon = MPI_Wtime();

		MPI_Recv(&tProm, 1, MPI_DOUBLE, 0, msgtag, MPI_COMM_WORLD, &status);
		MPI_Recv(unionType, l, mytype, 0, msgtag, MPI_COMM_WORLD, &status);

		tKon = MPI_Wtime();
		FILE* z;
		z = fopen("2.dat", "w");
		fprintf(z, "TIME %f\n", tKon - tProm);
		fprintf(z, "\n");
		for (int i = 0; i < l; i++) 
		{
			fprintf(z, "i=%d\n", i);
			fprintf(z, "a=%f\n", unionType[i].a);
			fprintf(z, "\n");
			fprintf(z, "b=%d\n", unionType[i].b);
			fprintf(z, "==============================\n");
		}
		fclose(z);
	}

	MPI_Finalize();
	return 0;
}