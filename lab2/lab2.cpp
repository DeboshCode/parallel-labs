#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int m = 10;
    const int n = m * size;
    int x_local[m];
    int global_max;
    int *x_global = nullptr;

    if (rank == 0)
    {
        x_global = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; i++)
        {
            x_global[i] = rand() % 10;
        }
    }

    MPI_Scatter(x_global, m, MPI_INT,
                x_local, m, MPI_INT,
                0, MPI_COMM_WORLD);

    cout << "process " << rank << " x_local: ";
    for (int i = 0; i < m; i++)
        cout << x_local[i] << " ";
    cout << endl;

    int local_max = x_local[0];
    for (int i = 1; i < m; i++)
    {
        if (local_max < x_local[i])
        {
            local_max = x_local[i];
        }
    }

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 1, MPI_COMM_WORLD);

    if (rank == 1)
    {
        cout << "global_max: " << global_max << endl;
    }

    if (rank == 0)
    {
        cout << "x_global: ";
        for (int i = 0; i < n; i++)
            cout << x_global[i] << " ";
        cout << endl;
    }
    MPI_Finalize();
    return 0;
}
