#include <iostream>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <windows.h>

using namespace std;

int sem = 0;


void wait()//��������
{
	while (!sem)
	{
		int a = 10;
	}
}

void signal(int n) //���������� ��� �������
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
			int pol = (myid % 2) + 1; // ���������� ��� ������� �������� 1 - ������� 2 - �������
			if (!myid)
			{
				cout << "\n" << endl;
				signal(i % 2 + 1);//���������� ��� ����� ��������
			}
			else
			{
				wait(); 
				if (pol == sem)
				{
					if (pol == 1)
					{
						cout << "� ������� ����� �������\n";
					}
					else
					{
						cout << "� ������� ����� �������\n";
					}
				}
			}
#pragma omp barrier
		}
		signal(0);
	}
} 