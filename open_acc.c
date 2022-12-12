#include <time.h>
#include <stdio.h>
#include <openacc.h>
#include <cuda.h>
#include <omp.h>
#define N 10000000

static int ones[N];
static int negativeOnes[N];
static int zeros[N];
static int sum[N];

void setUp(int *arr, int val)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = val;
    }
}

int main()
{
    setUp(ones, 1);
    setUp(negativeOnes, -1);
    setUp(zeros, 0);

    double start, end;

    start = omp_get_wtime();
    int i;

#pragma acc kernels
        for (i = 0; i < (N); i++)
        {
            sum[i] = ones[i] + negativeOnes[i];
        }
    end = omp_get_wtime();
    printf("Work took %f seconds\n", end - start);
    for (int i = 0; i < N; i++)
    {
        if (sum[i] != zeros[i])
        {
            printf("Not Summed Correctly");
        }
    }

    return 0;
}