#include "cuda_runtime.h"
#include <device_launch_parameters.h>
#include <stdio.h>
#include <cstring>

#define block_size 16
#define kmax 200 //����� �������

__global__ void Kernel(float* uDev, int n, int m) {
	int x = blockIdx.x * blockDim.x + threadIdx.x; //������ ����� �� X
	int y = blockIdx.y * blockDim.y + threadIdx.y; //������ ����� �� Y

	//������� ��� ��������
	int i = threadIdx.x + 1;
	int j = threadIdx.y + 1;

	//�������� ������ ��� �������������� �����
	__shared__ float subPoly[block_size + 2][block_size + 2];

	//���� ��� ��� ��� �����, �� �������
	if (x<0 || x>n - 1 || y<0 || y>m - 1)
		return;

	//��������� ���� ����� � ����������� ������
	subPoly[i][j] = uDev[y * n + x];

	//���� �� �� �������, �� �������
	if (x == 0 || x == n - 1 || y == 0 || y == m - 1)
		return;

	//���� � �������� �� ����� ������� �����, �� �������� ����� ������������ ����� � ����������� ������
	if (threadIdx.x == 0) subPoly[i - 1][j] = uDev[y * n + x - 1];

	//���� � �������� �� ������� ������� �����, �� �������� ������� ������������ ����� � ����������� ������
	if (threadIdx.y == 0) subPoly[i][j - 1] = uDev[(y - 1) * n + x];

	//���� � �������� �� ������ ������� �����, �� �������� ������ ������������ ����� � ����������� ������
	if (threadIdx.x == blockDim.x - 1) subPoly[i + 1][j] = uDev[y * n + x + 1];

	//���� � �������� �� ������ ������� �����, ���������� ������ ������������ ����� � ����������� ������
	if (threadIdx.y == blockDim.y - 1) subPoly[i][j + 1] = uDev[(y + 1) * n + x];

	//�������������� ����� � �����
	__syncthreads();

	//����������� ���� ����� � ���������� �� � �����������, � ����� � � ���������� ������
	subPoly[i][j] = 0.25 * (subPoly[i - 1][j] + subPoly[i + 1][j] + subPoly[i][j - 1] + subPoly[i][j + 1]);
	uDev[y * n + x] = subPoly[i][j];
}

int main(int argc, char** argv) {
	float lx = 1.0, ly = 1.0, h = 0.2;//��������� �������� �� ������� ������

	int n = (int)(lx / h) + 1; //����� ����� �� X
	int m = (int)(ly / h) + 1; //����� ����� �� Y

	float** uHost = new float* [n]; //��������� ������������� ������ U, ������� ����� ����� ������������ � ����������, ��� n - ���������� �������
	for (int i = 0; i < n; i++)
		uHost[i] = new float[m];//m - ���-�� ��������

	float* u = new float[n * m]; //������ U �� �����
	float* uDev = NULL; //������ U �� �������
	int size = n * m * sizeof(float); //������ ������� � ������

	//��������� ��������� ������ ������
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			uHost[i][j] = 0.0;

	//������� � ������ �������
	for (int i = 0; i < n; i++) {
		float x = (i * h);//������������ x � ������ �����

		uHost[i][0] = 60.0 * x * (1.0 - x * x); //AD
		uHost[i][m - 1] = 50.0 * (1.0 - x); //BC
	}

	//������ � ����� �������
	for (int i = 0; i < m; i++) {
		float y = (i * h);

		uHost[0][i] = 50.0 * y * y; //AB
		uHost[n - 1][i] = 0; //CD
	}

	//���������� ������� � ����������
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			u[j * m + i] = uHost[i][j];

	float time = 0.0;
	cudaEvent_t tn, tk;
	cudaEventCreate(&tn);
	cudaEventCreate(&tk);
	cudaEventRecord(tn, 0);

	cudaMalloc((void**)&uDev, size); //�������� ������ �� �������

	cudaMemcpy(uDev, u, size, cudaMemcpyHostToDevice);

	for (int k = 0; k < kmax; k++) {
		Kernel << < dim3(n / block_size + 1, m / block_size + 1), dim3(block_size, block_size) >> > (uDev, n, m);

		//���� ���� ��� ��������
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