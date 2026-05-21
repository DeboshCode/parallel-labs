#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int m = 4;
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);
    int x_local[m];
    for (int i = 0; i < m; i++)
    {
        x_local[i] = rand() % 19 - 9;
    }

    cout << "process " << rank << ": ";
    for (int j = 0; j < m; j++)
    {
        cout << x_local[j] << " ";
    }
    cout << endl;

    if (rank == size - 1)
    {
        int n = m * size;
        int x_global[n];
        

        for (int i = 0; i < size - 1; i++)
        {
            MPI_Recv(&x_global[i * m], m, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (int j = 0; j < m; j++)
        {
            x_global[(size - 1) * m + j] = x_local[j];
        }

        for (int i = 0; i < n; i++)
        {
            cout << x_global[i] << " ";
        }
    }
    else
    {
        MPI_Send(x_local, m, MPI_INT, size - 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}