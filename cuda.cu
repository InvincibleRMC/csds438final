#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>
#define N 10000000


static int ones[N];
static int negativeOnes[N];
static int zeros[N];
static int sum[N];

__global__ void vector_add(int *sum, int *a, int *b, int n) {
    int index = threadIdx.x;
    int stride = blockDim.x;

    for(int i = index; i < n; i += stride){
        sum[i] = a[i] + b[i];
    }
}

void setUp(int *arr, int val)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = val;
    }
}

int main()
{
    int size = N * sizeof(int);
    setUp(ones, 1);
    setUp(negativeOnes, -1);
    setUp(zeros, 0);

    int *cudaOnes, *cudaNegativeOnes, *cudaSum;
    cudaMalloc((void**)&cudaOnes, size);
    cudaMalloc((void**)&cudaNegativeOnes, size);
    cudaMalloc((void**)&cudaSum, size);

    cudaMemcpy(cudaOnes, ones, size, cudaMemcpyHostToDevice);
    cudaMemcpy(cudaNegativeOnes, negativeOnes, size, cudaMemcpyHostToDevice);

    
    vector_add<<<1, 256>>>(cudaSum, cudaOnes, cudaNegativeOnes,N);
    
    cudaMemcpy(sum, cudaSum, size, cudaMemcpyDeviceToHost);

    cudaFree(cudaNegativeOnes);
    cudaFree(cudaOnes);
    cudaFree(cudaSum);
    
    for (int i = 0; i < N; i++)
    {
        if (sum[i] != zeros[i])
        {
            printf("Not Summed Correctly");
        }
    }

    return 0;
}