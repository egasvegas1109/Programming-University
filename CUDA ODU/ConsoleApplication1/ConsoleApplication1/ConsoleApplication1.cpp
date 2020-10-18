#include <conio.h>
#include <iostream>
#include <math.h>

#define tau 0.001
#define tmax 0.1
#define t0 0.0
#define n 2

using namespace std;

__device__ float func(float x, float y1, float y2, int i) {
	float tmp = 0;
	switch (i) {
	case 0:
		tmp = y2; //var 8
		break;
	case 1:
		tmp = -0.07f * x * y2 - x * x * y1; //var 8
		break; //obyazat
	}
	return tmp;
}

__global__ void Kernel(float* x, float tt, int t)
{
	int idx = threadIdx.x;
	int i = (t - 1) * n;
	__shared__ float R1[n], R2[n], R3[n], R4[n];

	R1[idx] = tau * func(tt, x[i], x[i + 1], idx);
	__syncthreads();
	R2[idx] = tau * func(tt, x[i] + 0.5 * R1[0], x[i + 1] + 0.5 * R1[1], idx);
	__syncthreads();
	R3[idx] = tau * func(tt, x[i] + 0.5 * R2[0], x[i + 1] + 0.5 * R2[1], idx);
	__syncthreads();
	R4[idx] = tau * func(tt, x[i] + R3[0], x[i + 1] + R3[1], idx);
	__syncthreads();

	/*R1[idx]=tau*func(tt, x[i],x[i+1],idx);
	__syncthreads();
	R2[idx]=tau*func(tt, x[i]+0.5*R1[0],x[i+1]+0.5*R1[1],idx);
	__syncthreads();
	R3[idx]=tau*func(tt, x[i]+0.5*R2[0],x[i+1]+0.5*R2[1],idx);
	__syncthreads();
	R4[idx]=tau*func(tt, x[i]+R3[0],x[i+1]+R3[1],idx);
	__syncthreads(); //синхронизируются треды внутри блока
	*/

	x[idx + i + n] = x[idx + i] + (R1[idx] + 2 * R2[idx] + 2 * R3[idx] + R4[idx]) / 6.0;
}

int main() {
	int M = (int)((tmax - t0) / tau), t;
	int size = M * n * sizeof(float);
	float* xDev = NULL;
	float* x = (float*)malloc(size);
	float time = 0.0;

	cudaEvent_t tn, tk;
	x[0] = 0.0; //var
	x[1] = 0.125; //var
	cudaEventCreate(&tn);
	cudaEventCreate(&tk);
	cudaEventRecord(tn, 0);
	cudaMalloc((void**)&xDev, size);
	cudaMemcpy(xDev, x, size, cudaMemcpyHostToDevice);
	for (int t = 1; t < M; t++, time += tau)
	{
		Kernel << <1, n >> > (xDev, time, t);
	}
	cudaThreadSynchronize(); //хост ожидает выполнения блоков всего девайса
	cudaMemcpy(x, xDev, size, cudaMemcpyDeviceToHost);
	cudaFree(xDev);
	cudaEventRecord(tk, 0);
	cudaEventSynchronize(tk);
	cudaEventElapsedTime(&time, tn, tk);
	//cout <<"time="<< time /1000.0 <<endl;
	cout << "time= " << time / 1000.0 << endl;
	time = 0.0f;
	for (int i = 0;i < M;i++, time += tau)
		//cout <<"x="<< x[i*n] <<" y="<< x[i+1]<< endl;
		cout << "time = " << time << " y1= " << x[i * n] << " y2= " << x[i * n + 1] << endl;
	cudaEventDestroy(tn);
	cudaEventDestroy(tk);
	free(x);
	return 0;
}
