#include <mpi.h>
#include <stdio.h>
#include <fstream>

template < typename ElementTypeA, typename ElementTypeB>
int MPI_MyGather(ElementTypeA* sbuf, int scount, MPI_Datatype stype, ElementTypeB* rbuf, int rcount, MPI_Datatype rtype, int root, MPI_Comm comm)
{
	const int tag = 35;
	int rank;
	int size;

	MPI_Status status;

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	int i;
	int j;
	//mpiexec -n 4 MPI_Allgather.exe
	for (i = 0; i < rank; i++)//отправка всем процессам
	{
		if (rank != root) MPI_Send(sbuf, scount, MPI_INT, i, tag, comm);
	}

	for (j = 0; j < rank; j++)//принимаем от всех процессов
	{
		if (rank == root) MPI_Recv(rbuf, rcount, MPI_INT, j, tag, comm, &status);
	}
	MPI_Barrier(comm);

	return 0;
}

int main(int argc, char** argv)
{
	using namespace std;
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

	
	MPI_Barrier(MPI_COMM_WORLD);
#define n 30//размер массива
#define maxiter 100//кол-во итераций
#define save 0 //номер процесса, на котором сохраняем результат

	double sbuf[n];//создаём массив 
	double* rbuf = new double[size * n];//создаём массив №2
	//создание массивов для передачи и приёма
	for (int i = 0; i < n; i++)
		sbuf[i] = rank;

	for (int i = 0; i < n * size; i++)
		rbuf[i] = -1;//"очищаем"
	 int i;
	ofstream fout;
	fout.open("file.txt");
	for (i = 0; i < size; i++)
	{
		fout << rank;
	}
	
	fout.close();

	printf("I'm proc #: %d\n", rank);
	double tn, tk, dt;

	tn = MPI_Wtime();

	MPI_MyGather(sbuf, n, MPI_DOUBLE, rbuf, n, MPI_DOUBLE, save, MPI_COMM_WORLD);

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