#include <iostream>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <windows.h>

using namespace std;

int sem = 0;


void wait()//ожидание
{
	while (!sem)
	{
		int a = 10;
	}
}

void signal(int n) //определяет кто заходит
{
	sem = n;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < 4; i++)
	{
#pragma omp parallel shared (sem) num_threads (11)
		{
			int myid = omp_get_thread_num();
			int pol = (myid % 2) + 1; // определяем пол каждого человека 1 - мужчина 2 - женщина
			if (!myid)
			{
				cout << "\n" << endl;
				signal(i % 2 + 1);//определяем кто будет заходить
			}
			else
			{
				wait(); 
				if (pol == sem)
				{
					if (pol == 1)
					{
						cout << "В душевую вошёл мужчина\n";
					}
					else
					{
						cout << "В душевую вошла женщина\n";
					}
				}
			}
#pragma omp barrier
		}
		signal(0);
	}
} 