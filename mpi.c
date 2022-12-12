#include <time.h>
#include <stdio.h>
#include "mpi.h"
#include "omp.h"
#define N 10000000
static int ones[N];
static int negativeOnes[N];
static int zeros[N];
static int sum[N];

void setUp(int *arr, int val)
{
    int k;
    for (k = 0; k < N; k++)
    {
        arr[k] = val;
    }
}

int main(int argc, char *argv[])
{
    setUp(ones, 1);
    setUp(negativeOnes, -1);
    setUp(zeros, 0);

    double start, end;

    int rank, size;
    int i;
    int lower = 0;
    int upper = N;

    int local_total = 0;
    int global_total = 0;

    omp_set_num_threads(4);

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start = MPI_Wtime();

    MPI_Bcast(&upper, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (i = lower + rank; i < upper; i = i + size)
    {
        sum[i] = ones[i] + negativeOnes[i];
    }

    MPI_Reduce(&local_total, &global_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    end = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
    if(rank !=0){
        return 0;
    }
    printf("Work took %f seconds\n", end - start);

    int j;
    for (j = 0; j < N; j++)
    {
        if (sum[j] != zeros[j])
        {
            printf("Not Summed Correctly");
        }
    }

    return 0;
}