#include <iostream>
#include "mpi.h"
//mpiexec -n 2 ConsoleApplication1.exe
#define k 2//поля в структуре
#define n 4//числа в 1 массиве
#define m 5//числа в 2 массиве
#define l 2//кол-во структур
#define MSMPI_NO_DEPRECATE_20
FILE* f;
int main(int argc, char** argv)
{

	int size, rank, msgtag = 3;
	MPI_Status status;
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
		return 1;
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
	double tn = MPI_Wtime(); //Узнаем текущее время(начальное)
	struct L {
		int a;
		double b[n];
	} str[l];
	MPI_Datatype mytype; // [l] ;
	MPI_Datatype r[k] = { MPI_INT, MPI_DOUBLE};//r-массив типов
	int block[k] = { 1,n };
	MPI_Aint disp[k], tt;
	for (int i = 0; i < l; i++)
	{
		MPI_Get_address(&str[i], &disp[0]);
		MPI_Get_address(&str[i].b, &disp[1]);

		tt = disp[0];
		for (int i = 0; i < k; i++)
			disp[i] -= tt;
		MPI_Type_create_struct(k, block, disp, r, &mytype);
	}

	//for (int i = 0; i < l; i++)
	MPI_Type_commit(&mytype); // [i] );
	double tp = 0.0, tr;
	int position;
	int ss = l * sizeof(str);
	if (!rank)
	{
		for (int j = 0; j < l; j++)
		{
			str[j].a = 5 + j;
			for (int i = 0; i < n; i++)
			{
				str[j].b[i] = j + i * 1.5;

			}

		}


		fopen_s(&f, "array1.dat", "w");
		for (int i = 0; i < l; i++)
			fprintf(f, "a=%d\n", str[i].a);
		fprintf(f, "\n");
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < n; j++)
				fprintf(f, "b[%d]=%f\n", i, str[i].b[j]);
			fprintf(f, "\n");
		}
		fclose(f);


		//паковка

		void* buf;
		buf = malloc(ss);
		position = 0;

		tp = MPI_Wtime();
		for (int i = 0; i < l; i++)
		{

			MPI_Pack(&str[i].a, 1, r[0], buf, ss, &position, MPI_COMM_WORLD);
			for (int j = 0; j < n; j++)
				MPI_Pack(&str[i].b[j], 1, r[1], buf, ss, &position, MPI_COMM_WORLD);


		}

		MPI_Send(&position, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
		MPI_Send(buf, position, MPI_PACKED, 1, msgtag, MPI_COMM_WORLD);
		MPI_Send(&tp, 1, MPI_DOUBLE, 1, msgtag, MPI_COMM_WORLD);
		////for (int i = 0; i < l; i++)
		MPI_Send(str, l, mytype, 1, msgtag, MPI_COMM_WORLD);
	}
	if (rank)
	{
		position = 0;
		int pos = 0;
		double tp;
		MPI_Recv(&position, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
		void* mybuf = malloc(position);
		MPI_Recv(mybuf, position, MPI_PACKED, 0, msgtag, MPI_COMM_WORLD, &status);
		MPI_Recv(&tp, 1, MPI_DOUBLE, 0, msgtag, MPI_COMM_WORLD, &status);

		for (int i = 0; i < l; i++)
		{

			MPI_Unpack(mybuf, position, &pos, &str[i].a, 1, r[0], MPI_COMM_WORLD);
			for (int j = 0; j < n; j++)
				MPI_Unpack(mybuf, position, &pos, &str[i].b[j], 1, r[1], MPI_COMM_WORLD);


		}
		tr = MPI_Wtime();

		////for (int i = 0; i < l; i++)
		MPI_Recv(str, l, mytype, 0, msgtag, MPI_COMM_WORLD, &status);
		fopen_s(&f, "array2.dat", "w");
		fprintf(f, "timepack=%f\n", tr - tp);
		for (int i = 0; i < l; i++)
			fprintf(f, "a=%d\n", str[i].a);
		fprintf(f, "\n");
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < n; j++)
				fprintf(f, "b[%d]=%f\n", i, str[i].b[j]);
			fprintf(f, "\n");
		}
		fclose(f);
	}
	//for (int i = 0; i < l; i++)
	MPI_Type_free(&mytype);
	MPI_Finalize();
	return 0;
}
