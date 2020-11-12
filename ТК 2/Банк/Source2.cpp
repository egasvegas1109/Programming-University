//#include "pch.h"
#include <iostream>
#include <mpi.h>
#include <stdlib.h>
using namespace std;

int main(int arc, char **argv) {

	int size, rank, msgtag = 12;
	MPI_Status status;

	//шапочка
	if (MPI_Init(&arc, &argv) != MPI_SUCCESS) return 1;

	if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS) {
		MPI_Finalize();
		return 2;
	}

	if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS) {
		MPI_Finalize();
		return 3;
	}
	//	cout << "my rank: " << rank << endl;

#define comm MPI_COMM_WORLD
#define lmax 20 //жизненный цикл
#define omax 10 //
#define n 2

	int pr = 1, mag[omax*n], balance, z[n];
	int *p1, *nmag, m, kmax, sum, nz = 10;
	p1=nmag=mag;
	FILE *fres;
	char name[20];
	sprintf_s(name, "result%d.txt",rank);
	fopen_s(&fres, name, "w");

	if (!rank) //банк
	{
		balance = 100;
		kmax = size - 1;
	}
	if (rank) //клиент
	{
		z[0] = rand() % 2;
		z[1] = (rand() % 100)*rank + 1;
		fprintf(fres, "клиент %d имеет статус z[0] %d и сумму z[1] %d\n", rank, z[0], z[1]);
	}
	fclose(fres);
	MPI_Barrier(MPI_COMM_WORLD);

	for (int l = 0; l < lmax; l++) //жизненный цикл
	{
		fopen_s(&fres, name, "a");
		if (!rank) //банк
		{
			for (int i = 0; i < kmax; i++) //до мах клиента
			{
				MPI_Recv(z, n, MPI_INT, MPI_ANY_SOURCE, msgtag, comm, &status);
				if (z[0]) //=1 если кладем деньги
				{
					balance += z[1];
					pr = 1;
					MPI_Send(&pr, 1, MPI_INT, status.MPI_SOURCE, msgtag, comm);
					fprintf(fres, "клиент %d PUT = %d$, Текущий balance = %d\n", status.MPI_SOURCE,z[1], balance);			
				}
				else //z[0]=0 если снимаем
				{
					if (z[1] > balance - nz) //помещаем в очередь
					{
						fprintf(fres, "в очереди: клиент %d имеет сумму z[1] %d\n", status.MPI_SOURCE,z[1]);
						*p1 = status.MPI_SOURCE; //указатель на клиента
						p1++;
						*p1 = z[1]; 
						p1++;
					}
					else
					{
						balance -= z[1];
						pr = 1;
						MPI_Send(&pr, 1, MPI_INT, status.MPI_SOURCE, msgtag, comm);
						fprintf(fres, "банк выдает клиенту %d сумму z[1] = %d Текущий balance = %d\n", status.MPI_SOURCE, z[1],balance);

					}
				}
			}
			//РАБОТА С ОЧЕРЕДЬЮ without strategy FCFS
			int *p2 = nmag;
			while (p1!=p2) //пока очередь не пустая
			{
				m = *p2; //кому
				sum = *(p2 + 1);

				if (sum < balance - nz) //можно выдать
				{
					balance -= sum;
					pr = 1;
					MPI_Send(&pr, 1, MPI_INT, m, msgtag, comm);
					fprintf(fres,"банк может выдать %d клиенту сумму %d, текущий balance=%d\n",status.MPI_SOURCE,sum,balance);
					for (int i = 0; i < (p1 - p2) / 2; i += 2)
					{
						*(p2 + i) = *(p2 + i + 2);
						*(p2 + i + 1) = *(p2 + i + 3);
					}
					p1 -= 2; //текущий указатель в конец очереди
				} //end if

				else //нельзя выдать, если нет у банка денег
				{
					pr=0;
					MPI_Send(&pr, 1, MPI_INT, m, msgtag, comm);
					fprintf(fres,"банк не может выдать %d $ клиенту  %d, т.к balance=%d\n",sum,m,balance);
					p2+=2; //конец очереди
				}
			}
				kmax = (size-1) - (p1-nmag)/2;
				//fprintf(fres, "balance=%d; клиент %d сумма %d\n", balance, m, sum);
		}
		else //клиент
		{
			if (pr)
			{
				MPI_Send(z, n, MPI_INT, 0, msgtag, comm);
				fprintf(fres, "клиент %d отправил запрос z[1]=%d на итерации l=%d\n",rank,z[1],l);
			}
			MPI_Recv(&pr, 1, MPI_INT, 0, msgtag, comm, &status);

			if (pr)//=1
			{
				z[0] = rand() % 2;
				z[1] = ((rand() % 100)*rank) + 1;
				fprintf(fres, "клиент %d; имеет запрос z[0]=%d и сумму z[1]=%d\n", rank, z[0], z[1]);
			}
		}
		MPI_Barrier(comm);
		fclose(fres);
	}
	MPI_Finalize();
	return 0;
}