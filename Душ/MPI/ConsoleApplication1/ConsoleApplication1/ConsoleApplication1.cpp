# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <math.h>
# include <ctime>
#include <iostream>
using namespace std;
#define max 3
#define mmax 10
#define size 7



int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "RUSSIA");
	int i, j, m, * priznak, * var;
	priznak = new int[size];
	var = new int[size];
	int queue = 0;
	int flag = 0;
	for (i = 0; i < size; i++) {
		priznak[i] = 0;
	}
# pragma omp parallel shared(var, priznak, flag) private(m) num_threads(size)
	{
		int rank = omp_get_thread_num();
		if (rank == 0) {
			for (i = 1; i < size; i++) {
				var[i] = rand() % 2;
				printf("rank = %d var = %d\n", i, var[i]);
			}
		}
		m = 0;
		do {
#pragma omp barrier
			flag = 0;
			if (rank == 0) {
				int n = 0;
				for (i = 0; i < size; i++)
					priznak[i] = 0;
				printf("iter  = %d\n", m);
				queue = 1 - queue;
				if (queue)
					printf("mens\n");
				else
					printf("womens\n");
				for (i = 1; i < size; i++)
					if ((var[i] == queue) && (n < max)) {
						priznak[i] = 1;
						n++;
					}
				m++;
				flag = 1;
			}
			if (rank) {
				while (!flag) {
					int qwe;
				}
				if (priznak[rank] == 1) {
					printf("wash rank = %d\n", rank);
				}

			}
		} while (m < mmax);
	}
	return 0;
}