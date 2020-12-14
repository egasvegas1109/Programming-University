#include <iostream>
#include "mpi.h"
#define k 2//поля в структуре
#define n 10
#define MSMPI_NO_DEPRECATE_20

FILE* f;
//mpiexec -n 2 ConsoleApplication1.exe
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
	union
	{
		int a;
		double b;
	} un[n];

	MPI_Datatype mytype; // [l] ;
	MPI_Datatype r[k] = { MPI_INT, MPI_DOUBLE};//r-массив типов
	int block[k] = { 1,1 };
	MPI_Aint disp[k], tt;
	for (int i = 0; i < n; i++)
	{
		MPI_Get_address(&un[i], &disp[0]);
		MPI_Get_address(&un[i], &disp[1]);
		tt = disp[0];
		for (int i = 0; i < k; i++)
			disp[i] -= tt;
		MPI_Type_create_struct(k, block, disp, r, &mytype);
	}

	MPI_Type_commit(&mytype);
	double tp = 0.0, tr;
	int position;
	int ss = n * sizeof(un);
	if (!rank)
	{
		for (int i = 0; i < n; i++)
		{
			un[i].b = rand() % 9;
		}

		for (int i = 0; i < n; i++)
		{
			un[i].a = rand() % 9;
		}
		fopen_s(&f, "array1.dat", "w");

		for (int i = 0; i < n; i++)
		{
			fprintf(f, "a=%i\n", un[i].a);

		}

		for (int i = 0; i < n; i++)
		{
			fprintf(f, "b=%f\n", un[i].b);
		}


		fprintf(f, "\n");

		fclose(f);
		//паковка
		void* buf;
		buf = malloc(ss);
		position = 0;
		tp = MPI_Wtime();
		for (int i = 0; i < n; i++)
		{

			MPI_Pack(&un[i].a, 1, r[0], buf, ss, &position, MPI_COMM_WORLD);
			MPI_Pack(&un[i].b, 1, r[1], buf, ss, &position, MPI_COMM_WORLD);
		}

		MPI_Send(&position, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
		MPI_Send(buf, position, MPI_PACKED, 1, msgtag, MPI_COMM_WORLD);
		MPI_Send(&tp, 1, MPI_DOUBLE, 1, msgtag, MPI_COMM_WORLD);
		MPI_Send(un, n, mytype, 1, msgtag, MPI_COMM_WORLD);
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
		for (int i = 0; i < n; i++)
		{
			MPI_Unpack(mybuf, position, &pos, &un[i].a, 1, r[0], MPI_COMM_WORLD);
			MPI_Unpack(mybuf, position, &pos, &un[i].b, 1, r[1], MPI_COMM_WORLD);
		}
		tr = MPI_Wtime();
		MPI_Recv(un, n, mytype, 0, msgtag, MPI_COMM_WORLD, &status);

		fopen_s(&f, "array2.dat", "w");
		fprintf(f, "timepack=%f\n", tr - tp);
		for (int i = 0; i < n; i++)
		{
			fprintf(f, "a=%i\n", un[i].a);

		}

		for (int i = 0; i < n; i++)
		{
			fprintf(f, "b=%f\n", un[i].b);
		}
		fprintf(f, "\n");

		fclose(f);

	}
	MPI_Type_free(&mytype);
	MPI_Finalize();
	return 0;

}