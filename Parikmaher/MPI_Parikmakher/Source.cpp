#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

int rank;
void render_vous(int id, int l)
{
	FILE* f;
	int msgtag = 15;
	MPI_Status status;
	char name[256];
	if (!rank) //парикмахер
	{
		int message;
		sprintf_s(name, "report.txt");
		fopen_s(&f, name, "a+");
		MPI_Recv(&message, 1, MPI_INT, id, msgtag, MPI_COMM_WORLD, &status);
		fprintf_s(f, "Принятое сообщение %d Клиент %d На итерации %d\n", message, id, l);
		fclose(f);
	}
	else if (rank) //клиент
	{
		int message = id;
		MPI_Send(&message, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
	}
}

int main(int argc, char** argv)
{
	int size, msgtag = 12;
	MPI_Status status;
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
	//шапочка

	const int n = 3;
	int lmax = 10; int pr;
	int q[n] = { -1,-1,-1 }; //очередь

	for (int l = 0; l < lmax; l++)
	{
		if (!rank) //парикмахер
		{
			int buf;
			int count = 0;
			for (int i = 1; i < size; i++)
			{
				MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, msgtag, MPI_COMM_WORLD, &status);
				if ((buf == 1) && (count < n))
				{
					q[count] = status.MPI_SOURCE; //записываем в очередь
					count++;
				}
				else
				{
					pr = 0;
					MPI_Send(&pr, 1, MPI_INT, status.MPI_SOURCE, msgtag, MPI_COMM_WORLD);
				}
			}
			for (int i = 0; i < n; i++)
			{
				if (q[i] != -1) //если очередь не пустая, то признак заставляет парикхмахера работать
				{
					pr = 1;
					MPI_Send(&pr, 1, MPI_INT, q[i], msgtag, MPI_COMM_WORLD);
					render_vous(q[i], l);
				}
			}
			for (int i = 0; i < n; i++) //обнуляем очередь перед каждой итерацией
				q[i] = -1;

		}

		if (rank)
		{
			srand(time(NULL));
			int zapr = rand() % 2;
			MPI_Send(&zapr, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
			MPI_Recv(&pr, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
			if (pr == 1)
			{
				render_vous(rank, l);
			}
		}

		MPI_Barrier(MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}