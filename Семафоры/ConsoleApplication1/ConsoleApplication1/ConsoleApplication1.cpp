#include <omp.h>
#include <math.h>
#include <ctime>
#include <iostream>

using namespace std;

#define max 3
#define mmax 10

int sem = 0;

void signal()
{
	sem = 1;
}

void wait()
{
	sem = 0;
}

int main() {
	sem = 1;
	setlocale(LC_ALL, "Russian");
	int i, j, m;
#pragma omp parallel shared(sem,m) num_threads(2)
	{
		int sem = omp_get_thread_num();
		m = 0;

		do {

#pragma omp barrier	
			printf("iter = %d\n", m);

			//---------------------------------
			if (sem) 
			{
				
					printf("mens\n");
				
					wait();
				
			}

			else if (sem == 0)
			{
				printf("womens\n");

				signal();
			}
				
			
			//---------------------------------

			m++;

		} while (m < mmax);
	}
	return 0;
}