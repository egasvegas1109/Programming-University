#include <stdio.h>
#include <mpi.h>
#include <windows.h>

const int Fmax = 12;
const int lmax = 5;

int main(int arc, char** argv) {

	int size, rank, msgtag = 12, pr = 1, porc = 1;
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


	if (!rank) {
		int F = Fmax, Link=1, tmp, l = 0;

		while (pr) {
			while (F) {
				MPI_Send(&porc, 1, MPI_INT, Link, msgtag, MPI_COMM_WORLD);

				F--; Link++;
				if (Link == size) Link = 2;
			}

			tmp = -1;
			int LL;
			if (Link == 2) LL = size - 1;
			else LL = Link - 1;
			MPI_Send(&tmp, 1, MPI_INT, LL, msgtag, MPI_COMM_WORLD);

			MPI_Recv(&F, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);

			l++;
			if (l == lmax) pr = 0;
		}
		for (int i = 1; i < size; i++) {
			MPI_Send(&pr, 1, MPI_INT, i, msgtag, MPI_COMM_WORLD);
		}

	}


	//тапочки
	MPI_Finalize();
	return 0;
}