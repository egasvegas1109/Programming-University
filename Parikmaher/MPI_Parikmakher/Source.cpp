#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
int rank;
const int lmax = 15; // Количество итераций

void render_vous(int id, int l)
{
	FILE* f;
	char str[256];
	MPI_Status status;
	int msgtag = 35;
	int message;

	if(!rank ) //парикмахер
	{
		sprintf_s(str, "Barber.txt");
		fopen_s(&f, str, "w");
		MPI_Recv(&message, 1, MPI_INT, id, msgtag, MPI_COMM_WORLD, &status);
		fprintf_s(f, "L = %d, Message = %d\n", l, message);
		fclose(f);
	}
	else if (rank) //клиент
	{
		sprintf_s(str, "customer%d.txt", id);
		fopen_s(&f, str, "w");
		message = id;
		MPI_Send(&message, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
		fprintf_s(f, "Customer L = %d, Message = %d\n", l, message);
		fclose(f);
	}
	
}

int main(int argc, char **argv)
{
	int size;
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

	const int msgtag = 35;
	const int n = 3; // Размер очереди
	int count=0;
	int q[n] = {-1, -1 , -1}; // Очередь
	int pr ;
	int buf;

		for(int l=0; l<lmax; l++)
	{
		if (!rank)// 0
		{
			for(int i=1; i<size; i++)
			{
				MPI_Recv(&buf,1,MPI_INT,MPI_ANY_SOURCE,msgtag,MPI_COMM_WORLD,&status);
				if((buf==1)&&(count<n))
				{
					q[count]=status.MPI_SOURCE;
					count++;
				}
				else
				{
					pr=0;
					MPI_Send(&pr,1,MPI_INT,status.MPI_SOURCE,msgtag,MPI_COMM_WORLD);
				}
			}
			for(int i=1; i<size; i++)
			{
				if(q[i]!=-1)
				{
					pr=1;
					MPI_Send(&pr,1,MPI_INT,q[i],msgtag,MPI_COMM_WORLD);
					render_vous(q[i],l);
				}
			}
			for(int i=0;i<n;i++)
				q[i]=-1;
		//	MPI_Barrier(MPI_COMM_WORLD);
		}
		if(rank)
		{
			srand(time(NULL));
			int zapr=rand()%2;
			MPI_Send(&zapr,1,MPI_INT,0,msgtag,MPI_COMM_WORLD);
			MPI_Recv(&pr,1,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
			if(pr==1)
				render_vous(rank,l);
	//MPI_Barrier(MPI_COMM_WORLD);
		}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}