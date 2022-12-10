#include <time.h>
#include <stdio.h>
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

    clock_t start, end;

    int THREAD_NUM = 4;

    omp_set_num_threads(THREAD_NUM);

    int i;
    start = clock();
#pragma omp parallel shared(sum, ones, negativeOnes) private(i)
    {

#pragma omp for

        for (i = 0; i < (N); i++)
        {
            sum[i] = ones[i] + negativeOnes[i];
        }
    }

    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken to execute in seconds : %f\n", duration);

    for (int i = 0; i < N; i++)
    {
        if (sum[i] != zeros[i])
        {
            printf("Not Summed Correctly");
        }
    }

    return 0;
}