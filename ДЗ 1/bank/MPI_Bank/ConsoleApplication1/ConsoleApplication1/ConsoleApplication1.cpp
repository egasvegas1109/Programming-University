#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <mpi.h>
#include <ctime>
#include <iostream>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;

const int n = 2,
m = 5,
lmax = 15;//жизненный цикл

int main(int argc, char** argv)
{

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int rank, size;// rank -номер процесса, size - количество процессов
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

	int msgtag = 7,
		pr = 1,
		mag[m * n],
		balance,
		z[n],
		* p1,
		* nmag,
		M,
		kmax,
		sum,
		N = 5;
	p1 = nmag = mag;

	srand((unsigned)time(0));

	FILE* f;
	char name[20];
	sprintf(name, "process%d.txt", rank);
	fopen_s(&f, name, "w");

	if (!rank) {
		//процесс-банк
		balance = 200;
		kmax = size - 1;
	}
	else {
		//процессы-клиенты
		z[0] = rand() % 2;
		z[1] = ((rand() % 200) * rank) + 1;

		fprintf(f, "Процесс %d имеет статус z[0] %d и средства z[1] %d\n", rank, z[0], z[1]);
	}

	fclose(f);
	MPI_Barrier(MPI_COMM_WORLD);


	for (int l = 0; l < lmax; l++) //ЖИЗНЕННЫЙ ЦИКЛ ПРОГРАММЫ
	{
		fopen_s(&f, name, "a");
		if (!rank) //банк
		{
			for (int i = 0; i < kmax; i++) //Работаем с клиентами по очереди
			{
				MPI_Recv(z, n, MPI_INT, MPI_ANY_SOURCE, msgtag, MPI_COMM_WORLD, &status);
				if (z[0]) //пополнение СЧЁТА
				{
					balance += z[1];
					pr = 1;
					MPI_Send(&pr, 1, MPI_INT, status.MPI_SOURCE, msgtag, MPI_COMM_WORLD);
					fprintf(f, "Процесс-клиент %d положил сумму = %d$, Текущий СЧЁТ = %d\n", status.MPI_SOURCE, z[1], balance);
				}
				else //снятие со СЧЁТА
				{
					if (z[1] > balance - N) //помещаем в очередь
					{
						fprintf(f, "В очереди: процесс-клиент %d хочет снять сумму z[1] %d\n", status.MPI_SOURCE, z[1]);
						*p1 = status.MPI_SOURCE; //указатель на клиента
						p1++;
						*p1 = z[1];
						p1++;
					}
					else
					{
						balance -= z[1];
						pr = 1;
						MPI_Send(&pr, 1, MPI_INT, status.MPI_SOURCE, msgtag, MPI_COMM_WORLD);
						fprintf(f, "Банк выдает клиенту %d сумму z[1] = %d Текущий СЧЁТ = %d\n", status.MPI_SOURCE, z[1], balance);

					}
				}
			}
			//РАБОТА С ОЧЕРЕДЬЮ идёт в обратном порядке: начинаем с последнего пришедшего клиента
			int flag = 1;
			while ((p1 != nmag) && flag)//пока очередь не пустая
			{
				fprintf(f, "l=%d очередь не пуста, количество клиентов равно %d\n", l, (p1 - nmag) / 2);

				M = *(p1 - 2); //Какому процессу выдаём
				sum = *(p1 - 1);

				if (sum < balance - N) //Если сумма которую хотят снять меньше Текущего СЧЁТА, то можно выдать деньги
				{
					balance -= sum;
					pr = 1;
					MPI_Send(&pr, 1, MPI_INT, M, msgtag, MPI_COMM_WORLD);
					fprintf(f, "l = % d банк выдал процессу % d сумму - % d и клиент выбыл из очереди\n", l, M, sum);
					p1 -= 2; //указатель сдвигаем в конец очереди
				}

				else //Сумма, которую хотят взять больше, чем остаток средств на счёте, следовательно банк не может выдать средства
				{
					flag = 0;
					fprintf(f, "В банке balance = %d, а процесс %d просит %d\n", balance, M, sum);
				}
			}

			//Проверим оставшуюся очередь. Если все процессы-клиенты стоят в очереди, закрываем банк
			kmax = (p1 - nmag) / 2;
			for (int i = 1; i <= kmax; i++) {
				pr = 0;
				M = *(p1 - 2 * i);
				MPI_Send(&pr, 1, MPI_INT, M, msgtag, MPI_COMM_WORLD);
				fprintf(f, "l=%d банк не выдал процессу %d сумму - %d и клиент остался в очереди\n", l, M, *(p1 - 2 * i + 1));
			}

			kmax = (size - 1) - kmax;
			fprintf(f, "kmax = %d\n", kmax);
			if (!kmax) fprintf(f, "В банке нет достаточно денег \n");


		}
		else //клиент
		{
			if (pr)
			{
				MPI_Send(z, n, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
				fprintf(f, "Процесс-клиент %d отправил запрос z[1]=%d на итерации l=%d\n", rank, z[1], l);
			}
			MPI_Recv(&pr, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);

			if (pr)//=1
			{
				z[0] = rand() % 2;
				z[1] = ((rand() % 100) * 1) + 1;
				fprintf(f, "Процесс-клиент %d имеет запрос z[0]=%d и сумму z[1]=%d\n", rank, z[0], z[1]);
			}
		}
		MPI_Barrier(MPI_COMM_WORLD);
		fclose(f);
	}

	MPI_Finalize();
	return 0;

}