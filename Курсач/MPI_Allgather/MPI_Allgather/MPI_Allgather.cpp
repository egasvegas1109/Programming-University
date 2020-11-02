#include <mpi.h>
#include <stdio.h>
#define n 30//размер массива
#define save 0 //номер процесса, на котором сохраняем результат

template < typename ElementTypeA, typename ElementTypeB>
int MPI_MyAllGather(ElementTypeA* sbuf, int scount, MPI_Datatype stype, ElementTypeB* rbuf, int rcount, MPI_Datatype rtype, MPI_Comm comm)
{
	const int tag = 35;
	int rank;
	int size;

	MPI_Status status;

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	int i;
	int j;

	for (i = 0; i < rank; i++)//отправка всем процессам
	{
		if (rank != save) MPI_Send(sbuf, scount, MPI_INT, i, tag, comm);
	}

	for (j = 0; j < rank; j++)//принимаем от всех процессов
	{
		if (rank == save) MPI_Recv(rbuf, rcount, MPI_INT, j, tag, comm, &status);
	}
	MPI_Barrier(comm);

	return 0;
}

int main(int argc, char** argv)
{
	int size, rank;
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


	double sbuf[n];
	double* rbuf = new double[size * n];

	for (int i = 0; i < n; i++)
		sbuf[i] = rank;

	for (int i = 0; i < n * size; i++)
		rbuf[i] = -1;//"очищаем"

	double tn, tk, dt;

	tn = MPI_Wtime();

	MPI_MyAllGather(sbuf, n, MPI_DOUBLE, rbuf, n, MPI_DOUBLE, MPI_COMM_WORLD);

	tk = MPI_Wtime();
	dt = tk - tn;

	if (rank == save)
	{
		printf("MyAllgather time = %f\n", dt);
	}


	for (int i = 0; i < n * size; i++)
		rbuf[i] = -1;//"очищаем" массив


	//обычный allgather
	MPI_Barrier(MPI_COMM_WORLD);

	tn = MPI_Wtime();

	MPI_Allgather(sbuf, n, MPI_DOUBLE, rbuf, n, MPI_DOUBLE, MPI_COMM_WORLD);

	tk = MPI_Wtime();
	dt = tk - tn;

	if (rank == save)
	{
		printf("Allgather time = %f\n", dt);
	}

	delete[] rbuf;
	MPI_Finalize();
	return 0;
}