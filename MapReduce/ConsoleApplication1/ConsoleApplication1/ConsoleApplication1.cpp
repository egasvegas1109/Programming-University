#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include "mpi.h"
#include <ctime>

#define buf_size 30 //максимальное кол-во элементов в массиве
#define comm MPI_COMM_WORLD


int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	int rank, size;

	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
	{
		return 1;
	}
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

	int msgtag = 12;
	MPI_Status status;
	int buf[buf_size];
	int n = 0, link;// n-номер элемента, link-номер процесса
	double tn, tk, tn2, tk2;

	/* Заполнение файла случайными числами */
	if (!rank)
	{
		FILE* f;
		fopen_s(&f, "number.txt", "w");//файл с макс
		for (int i = 0; i < 5; i++)
		{

			fprintf_s(f, "%d ", rand() % 16);
		}
		fclose(f);


		fopen_s(&f, "number2.txt", "w");//файл с мин
		for (int i = 0; i < 5; i++)
		{

			fprintf_s(f, "%d ", rand() % 30);
		}
		fclose(f);


	}
	MPI_Barrier(comm);



	if (!rank)
	{
		FILE* fin, * fout, * fin2;

		////////////////////////////////////////////////////////////////////
		fopen_s(&fin, "number.txt", "r");

		n = 0; link = 1;// n-номер элемента, link-номер процесса
		tn = MPI_Wtime();
		while (fscanf_s(fin, "%d", buf + n) != EOF)//пока файл не пустой, выполняем
		{
			n++;
			if (n == buf_size)
			{
				MPI_Send(buf, buf_size, MPI_INT, link, msgtag, comm);//записываем всё что внутри файла в массив buf
				link++;
				n = 0;
				if (link == size) link = 1;
			}
		}
		fclose(fin);
		
		// Поиск максимального числа 
		int max = buf[0];//перебираем числа в массиве 
		for (int i = 0; i < n; i++)
		{
			if (max < buf[i])
				max = buf[i];
		}
		////////////////////////////////////////////////////////////////////

		fopen_s(&fin2, "number2.txt", "r");

		n = 0; link = 1;// n-номер элемента, link-номер процесса
		tn2 = MPI_Wtime();
		while (fscanf_s(fin2, "%d", buf + n) != EOF)//пока файл не пустой, выполняем
		{
			n++;
			if (n == buf_size)
			{
				MPI_Send(buf, buf_size, MPI_INT, link, msgtag, comm);
				link++;
				n = 0;
				if (link == size) link = 1;
			}
		}
		fclose(fin2);
		
		// Поиск минимальноого числа 

		int min = buf[0];//перебираем числа в массиве 
		for (int i = 0; i < n; i++)
		{
			if (min > buf[i])
				min = buf[i];
		}
		////////////////////////////////////////////////////////////////////
		//вывод всех данных
		tk = MPI_Wtime();
		tk2 = MPI_Wtime();
		printf("PARALLEL: MAX= %d TIME= %f\n", max, tk - tn);
		printf("PARALLEL: MIN= %d TIME= %f\n", min, tk2 - tn2);
		fopen_s(&fout, "result.txt", "w");
		fprintf_s(fout, "MAX=%d", max);
		fprintf_s(fout, " MIN=%d", min);
		fclose(fout);
		////////////////////////////////////////////////////////////////////
	}
	else//worker node
	{
		int n = 0, max, min;
		while (1)
		{
			MPI_Recv(buf, buf_size, MPI_INT, 0, MPI_ANY_TAG, comm, &status);
			if (status.MPI_TAG == 0)
				break;
			if (!n)
				max = buf[0];
			for (int i = 0; i < buf_size; i++)
			{
				if (max < buf[i])
					max = buf[i];
			}

			n++;
		}
		//
		n = 0;
		while (1)
		{
			MPI_Recv(buf, buf_size, MPI_INT, 0, MPI_ANY_TAG, comm, &status);
			if (status.MPI_TAG == 0)
				break;
			if (!n)
				min = buf[0];
			for (int i = 0; i < buf_size; i++)
			{
				if (min > buf[i])
					min = buf[i];
			}

			n++;
		}
		//
		MPI_Send(&max, 1, MPI_INT, 0, msgtag, comm);
		MPI_Send(&min, 1, MPI_INT, 0, msgtag, comm);
	}
	MPI_Barrier(comm);
	MPI_Finalize();
	return 0;
}