#include <mpi.h>
#include <stdio.h>


template < typename ElementTypeA, typename ElementTypeB>
int MPI_MyGather(ElementTypeA* sbuf, int scount, ElementTypeB* rbuf, int rcount, int root, MPI_Comm comm)
{
	const int tag = 35;
	int rank;
	int size;

	MPI_Status status;
	ElementTypeA* barr = new ElementTypeA[scount];

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);


	if (rank != root) MPI_Send(sbuf, scount, MPI_INT, root, tag, comm);

	if (rank == root)
	{
		for (int j = root, k = 0; k < rcount; k++)
		{

			*(rbuf + j * rcount + k) = (ElementTypeB) * (sbuf + k);
		}
		for (int i = 0; i < size - 1; i++)
		{
			MPI_Recv(barr, rcount, MPI_INT, MPI_ANY_SOURCE, tag, comm, &status);
			for (int j = status.MPI_SOURCE, k = 0; k < rcount; k++)
				*(rbuf + j * rcount + k) = (ElementTypeB) * (barr + k);

		}
	}

	MPI_Barrier(comm);

	delete[] barr;
	return 0;
}

int main(int argc, char** argv)
{
	int size, rank;
	MPI_Status status;
	//Шапочка
	{
		if (MPI_Init(&argc, &argv) != MPI_SUCCESS) return 1;
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
	}

	printf("I'm proc #: %d\n", rank);
	MPI_Barrier(MPI_COMM_WORLD);
#define n 5
#define maxiter 100
#define save 0
	int sbuf[n];
	int* rbuf = new int[size * n];

	for (int i = 0; i < n; i++)
		sbuf[i] = rank - 10;
	for (int i = 0; i < n * size; i++)
		rbuf[i] = -1;

	double tn, tk, dt;

	tn = MPI_Wtime();
	for (int t = 0; t < maxiter; t++)
	{
		MPI_MyGather(sbuf, n, rbuf, n, save, MPI_COMM_WORLD);
	}
	tk = MPI_Wtime();
	dt = tk - tn;

	if (rank == save)
	{
		printf("MyGather time = %f\n", dt);
		for (int i = 0; i < size * n; i++)
			printf("rbuf[%d] = %d\n", i, rbuf[i]);
		printf("\n\n\n\n", dt);
	}


	for (int i = 0; i < n * size; i++)
		rbuf[i] = -1;

	if (rank == save)
	{
		for (int i = 0; i < size * n; i++)
			printf("rbuf[%d] = %d\n", i, rbuf[i]);
	}

	tn = MPI_Wtime();
	for (int t = 0; t < maxiter; t++)
	{
		MPI_MyGather(sbuf, n, rbuf, n, save, MPI_COMM_WORLD);
	}
	tk = MPI_Wtime();
	dt = tk - tn;

	if (rank == save)
	{
		printf("Gather time = %f\n", dt);
		for (int i = 0; i < size * n; i++)
			printf("rbuf[%d] = %d\n", i, rbuf[i]);
	}

	delete[] rbuf;
	MPI_Finalize();
	return 0;
}