#include "cuda_runtime.h"
#include <device_launch_parameters.h>
#include <stdio.h>
#include <cstring>

#define block_size 16
#define kmax 200 //число итраций

__global__ void Kernel(float* uDev, int n, int m) {
	int x = blockIdx.x * blockDim.x + threadIdx.x; //индекс треда по X
	int y = blockIdx.y * blockDim.y + threadIdx.y; //индекс треда по Y

	//»ндексы дл€ массивов
	int i = threadIdx.x + 1;
	int j = threadIdx.y + 1;

	//¬ыдел€ем пам€ть под дополнительные точки
	__shared__ float subPoly[block_size + 2][block_size + 2];

	//≈сли дл€ нас нет точки, то выходим
	if (x<0 || x>n - 1 || y<0 || y>m - 1)
		return;

	//ѕеремещаю свою точку в раздел€емую пам€ть
	subPoly[i][j] = uDev[y * n + x];

	//≈сли мы на границе, то выходим
	if (x == 0 || x == n - 1 || y == 0 || y == m - 1)
		return;

	//≈сли € нахожусь на левой границе блока, то переношу левую приграничную точку в раздел€емую пам€ть
	if (threadIdx.x == 0) subPoly[i - 1][j] = uDev[y * n + x - 1];

	//≈сли € нахожусь на верхней границе блока, то переношу верхнюю приграничную точку в раздел€емую пам€ть
	if (threadIdx.y == 0) subPoly[i][j - 1] = uDev[(y - 1) * n + x];

	//≈сли € нахожусь на правой границе блока, то переношу правую приграничную точку в раздел€емую пам€ть
	if (threadIdx.x == blockDim.x - 1) subPoly[i + 1][j] = uDev[y * n + x + 1];

	//≈сли € нахожусь на нижней границе блока, топереношу нижнюю приграничную точку в раздел€емую пам€ть
	if (threadIdx.y == blockDim.y - 1) subPoly[i][j + 1] = uDev[(y + 1) * n + x];

	//—инхронизируем треды в блоке
	__syncthreads();

	//¬ысчитываем нашу точку и записываем ее в раздел€емую, а потом и в глобальную пам€ть
	subPoly[i][j] = 0.25 * (subPoly[i - 1][j] + subPoly[i + 1][j] + subPoly[i][j - 1] + subPoly[i][j + 1]);
	uDev[y * n + x] = subPoly[i][j];
}

int main(int argc, char** argv) {
	float lx = 1.0, ly = 1.0, h = 0.2;//начальные значени€ по услови€ задачи

	int n = (int)(lx / h) + 1; //„исло точек по X
	int m = (int)(ly / h) + 1; //„исло точек по Y

	float** uHost = new float* [n]; //ƒвумерный динамичесский массив U, который позже будем раскладывать в одномерный, где n - количество строчек
	for (int i = 0; i < n; i++)
		uHost[i] = new float[m];//m - кол-во столбцов

	float* u = new float[n * m]; //массив U на хосте
	float* uDev = NULL; //массив U на девайсе
	int size = n * m * sizeof(float); //размер массива в байтах

	//«аполн€ем двумерный массив нул€ми
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			uHost[i][j] = 0.0;

	//¬ерхн€€ и нижн€€ границы
	for (int i = 0; i < n; i++) {
		float x = (i * h);//просчитываем x в каждой точке

		uHost[i][0] = 60.0 * x * (1.0 - x * x); //AD
		uHost[i][m - 1] = 50.0 * (1.0 - x); //BC
	}

	//ѕрава€ и лева€ границы
	for (int i = 0; i < m; i++) {
		float y = (i * h);

		uHost[0][i] = 50.0 * y * y; //AB
		uHost[n - 1][i] = 0; //CD
	}

	//разложение массива в одномерный
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			u[j * m + i] = uHost[i][j];

	float time = 0.0;
	cudaEvent_t tn, tk;
	cudaEventCreate(&tn);
	cudaEventCreate(&tk);
	cudaEventRecord(tn, 0);

	cudaMalloc((void**)&uDev, size); //выдел€ем пам€ть на девайсе

	cudaMemcpy(uDev, u, size, cudaMemcpyHostToDevice);

	for (int k = 0; k < kmax; k++) {
		Kernel << < dim3(n / block_size + 1, m / block_size + 1), dim3(block_size, block_size) >> > (uDev, n, m);

		//∆дем пока все завершат
		cudaThreadSynchronize();
	}

	cudaMemcpy(u, uDev, size, cudaMemcpyDeviceToHost);

	cudaEventRecord(tk, 0);
	cudaEventSynchronize(tk);
	cudaEventElapsedTime(&time, tn, tk);

	printf("\nCuda time = %f\n", time / 1000.0);

	const char* error = cudaGetErrorString(cudaGetLastError());
	printf("Cuda error = %s\n", error);

	FILE* f;
	f = fopen("Rez.txt", "w");

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++)
			fprintf(f, "%f   ", u[i * m + j]);
		fprintf(f, "\n");
	}

	fclose(f);

	cudaFree(uDev);

	for (int i = 0; i < n; i++)
	{
		delete[] uHost[i];
	}
	delete[] uHost;

	return 0;
}