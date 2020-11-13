#include <mpi.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <ctime>

int main(int argc, char** argv)
{
	int size, rank;
	MPI_Status status;
	int msgtag = 4;
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

#define lmax 10
#define n 2 // размер массива
#define omax 10 // максимальное число клиентов

	int pr = 1;
	int nz = 100; // несгораемая сумма
	int mag[omax * n], balance, z[n]; // очередь, баланс, запрос
	int* p1, * nmag, kmax, flag, sum, m;
	p1 = nmag = mag;

	FILE* f;
	char str[256];
	sprintf_s(str, "rank%d.txt", rank);
	fopen_s(&f, str, "w");
	if (!rank)
	{
		p1 = nmag = mag;
		balance = 100;
		kmax = size - 1;
	}
	if (rank)
	{
		z[0] = abs((rand() % 1000) - rank) % 2;
		z[1] = (rand() % 100 + 1) * rank;

		fprintf(f, "New query| rank = %d status = %d sum = %d\n", rank, z[0], z[1]);
		//fprintf(f, "rank = %d stat")
	}
	fclose(f);
	MPI_Barrier(MPI_COMM_WORLD);
	fopen_s(&f, str, "a");
	for (int l = 0; l < lmax, pr != -1; l++)
	{

		fprintf(f, "DAY: %d\n", l);
		if (!rank)// Bank
		{
			fprintf(f, "BALANCE  = %d MINIMUM = %d KMAX = %d\n", balance, nz, kmax);
			for (int i = 0; i < kmax; i++)
			{
				MPI_Recv(z, n, MPI_INT, MPI_ANY_SOURCE, msgtag, MPI_COMM_WORLD, &status);
				//fprintf(f, "Get Message| from proc = %d z[0] = %d\n", status.MPI_SOURCE, z[0]);

				if (z[0])
				{
					fprintf(f, "Query(Get money)| proc = %d z[0] = %d z[1] = %d\n", status.MPI_SOURCE, z[0], z[1]);
					balance += z[1];
					pr = 1;
					MPI_Send(&pr, 1, MPI_INT, status.MPI_SOURCE, msgtag, MPI_COMM_WORLD);
				}
				else
				{
					if (z[1] > balance - nz)
					{
						//печать
						fprintf(f, "Query(Give money Fail)| proc = %d z[1] = %d\n", status.MPI_SOURCE, z[1]);
						*p1 = status.MPI_SOURCE;
						p1++;
						*p1 = z[1];
						p1++;
					}
					else
					{
						fprintf(f, "Query(Give money True)| proc = %d z[1] = %d\n", status.MPI_SOURCE, z[1]);
						balance -= z[1];
						pr = 1;
						MPI_Send(&pr, 1, MPI_INT, status.MPI_SOURCE, msgtag, MPI_COMM_WORLD);
					}
				}
			}
			// Работа с очередью

			int flag = 1;
			while ((p1 != nmag) && flag)
			{
				m = *nmag;
				sum = *(nmag + 1);
				if (sum < balance - nz)
				{
					balance -= sum;
					pr = 1;
					MPI_Send(&pr, 1, MPI_INT, m, msgtag, MPI_COMM_WORLD);
					fprintf(f, "Queue (True): proc = %d balance = %d sum = %d\n", m, balance, sum);
					//if (kmax < size - 1)
					//	kmax++;
					for (int i = 0; i <= (p1 - nmag) / n; i += 2)
					{
						*(nmag + i) = *(nmag + i + 2);
						*(nmag + i + 1) = *(nmag + i + 3);
					}
					p1 -= 2;
				}
				else
				{
					flag = 0;
					int count = 0;
					//for (int i = 0; i <= (p1 - nmag) / n; i += 2)
					for (int* i = nmag; i < p1; i += 2)
					{
						count++;
						fprintf(f, "Queue (Fail)| proc = %d WON'T GET MONEY balance = %d sum = %d\n", *i, balance, *(i + 1));
						if (kmax != 0)
						{
							pr = 0;
							MPI_Send(&pr, 1, MPI_INT, *i, msgtag, MPI_COMM_WORLD);
						}
						else
						{
							pr = -1;
							MPI_Send(&pr, 1, MPI_INT, *i, msgtag, MPI_COMM_WORLD);
						}
					}
					kmax = size - 1 - count;
				}
			}
		}
		else
		{
			if (pr == 1)
			{
				MPI_Send(z, n, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
				fprintf(f, "Send: rank = %d status = %d sum = %d l = %d\n", rank, z[0], z[1], l);
			}
			MPI_Recv(&pr, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
			if (pr == -1)
			{
				fprintf(f, "rank = %d EXIT\n", rank);
				break;
			}
			if (pr == 1)
			{
				Sleep(600 + 100 * rank);
				z[0] = ((rand() % 1000) - rank) % 2;
				z[1] = (rand() % 100 + 1) * rank;
				fprintf(f, "New query| rank = %d status = %d sum = %d\n", rank, z[0], z[1]);
			}
		}
		fprintf(f, "\n\n");

		//MPI_Barrier(MPI_COMM_WORLD);
	}
	fclose(f);
	if (!rank) {
		pr = 0;
		for (int ll = 1; ll < size; ll++) MPI_Send(&pr, 1, MPI_INT, ll, msgtag, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}