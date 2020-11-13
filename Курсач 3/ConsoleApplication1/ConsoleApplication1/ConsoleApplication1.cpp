#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//mpiexec -n 2 ConsoleApplication1.exe
#define comm MPI_COMM_WORLD
#define n 10
#define m 2

union
{
	int a;
	double b;
} un[n];

int main(int argc, char** argv)
{
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
	{
		return 1;
	}
	int size, rank;
	if (MPI_Comm_size(comm, &size) != MPI_SUCCESS)
	{
		MPI_Finalize();
		return 2;
	}
	if (MPI_Comm_rank(comm, &rank) != MPI_SUCCESS)
	{
		MPI_Finalize();
		return 3;
	}

	int msgtag = 12;
	MPI_Status status;
	
	double tn0 = 0.0, tk0 = 0.0, tn1 = 0.0, tk1 = 0.0;
	int mass = (n * sizeof(double)), pos; //
	int mass2 = (n * sizeof(int)), pos2; //

	if (!rank)
	{
		void* buf = malloc(mass);
		void* buf2 = malloc(mass2);
		for (int i = 0; i < n; i++)
		{
			un[i].b = rand() % 9;
		}

		for (int i = 0; i < n; i++)
		{
			un[i].a = rand() % 9;
		}

		FILE* f;
		fopen_s(&f, "results1.dat", "w");
		fprintf(f, "Печать исходного объединения\n");
		for (int i = 0; i < n; i++)
		{
			fprintf(f, "un[%d].a = %i\n", i, un[i].a);
			fprintf(f, "un[%d].b = %f\n", i, un[i].b);
		}

		fclose(f);

		pos = 0;
		pos2= 0;
		tn0 = MPI_Wtime();
		for (int i = 0; i < n; i++)
		{
			MPI_Pack(&un[i].a, 1, MPI_INT, buf2, mass2, &pos2, comm); //
			MPI_Pack(&un[i].b, 1, MPI_DOUBLE, buf, mass, &pos, comm); //
			
		}
		
		MPI_Send(&pos, 1, MPI_INT, 1, msgtag, comm);
		MPI_Send(&pos2, 1, MPI_INT, 1, msgtag, comm);
		MPI_Send(buf, mass, MPI_PACKED, 1, msgtag, comm);
		MPI_Send(buf2, mass2, MPI_PACKED, 1, msgtag, comm);
		tk0 = MPI_Wtime();
	}
	else
	{
		pos = 0;
		pos2 = 0;
		int p = 0;
		int p2 = 0;
		tn1 = MPI_Wtime();
		MPI_Recv(&pos, 1, MPI_INT, 0, msgtag, comm, &status);
		MPI_Recv(&pos2, 1, MPI_INT, 0, msgtag, comm, &status);
		void* mybuf2 = malloc(mass2);
		void* mybuf = malloc(mass);
		MPI_Recv(mybuf, pos, MPI_PACKED, 0, msgtag, comm, &status);
		MPI_Recv(mybuf2, pos2, MPI_PACKED, 0, msgtag, comm, &status);
		
		for (int i = 0; i < n; i++)
		{
			MPI_Unpack(mybuf2, pos2, &p2, &un[i].a, 1, MPI_INT, comm);
			MPI_Unpack(mybuf, pos, &p, &un[i].b, 1, MPI_DOUBLE, comm);
		}
		
		tk1 = MPI_Wtime();
		FILE* z;
		fopen_s(&z, "results.dat", "w");
		fprintf(z, "Печать распакованного объединения\n");
		for (int i = 0; i < n; i++)
		{
			fprintf(z, "un[%d].a = %i\n", i, un[i].a);
			fprintf(z, "un[%d].b = %f\n", i, un[i].b);
		}
			
		fclose(z);
	}

	if (!rank)
	{
		double tn = tn0 + tn1;
		double tk = tk0 + tk1;
		FILE* o;
		fopen_s(&o, "time.dat", "w");
		fprintf(o, "\ntime = %f\n", tk - tn);
		fclose(o);
	}

	MPI_Finalize();
	return 0;
}