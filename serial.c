#include <time.h>
#include <stdio.h>
#define N 10000000
// Set up
static int ones[N];
static int negativeOnes[N];
static int zeros[N];
static int sum[N];

void setUp(int* arr,int val){
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

    start = clock();
    for (int i = 0; i < N; i++)
    {
        sum[i] = ones[i] + negativeOnes[i];
    }
    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken to execute in seconds : %f\n", duration);

    // Check Summation
    for (int i = 0; i < N; i++)
    {
        if (sum[i] != zeros[i])
        {
            printf("Not Summed Correctly");
        }
    }

    return 0;
}