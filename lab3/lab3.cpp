#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void fillmatrix(int *arr, int n, int m)
{
    for (int i = 0; i < m * n; i++)
    {
        arr[i] = rand() % 19 - 9;
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int m = 4;
    const int n = m * size;
    const int rows_per_proc = n / size;
    const int local_size = rows_per_proc * m;
    const int global_size = n * m;
    int *A_global = nullptr;
    int *B_global = nullptr;
    int *A_local = new int[local_size];
    int *B_local = new int[local_size];
    int *C_local = new int[local_size];
    int *C_global = new int[global_size];

    if (rank == 0)
    {
        srand(time(NULL));
        A_global = new int[global_size];
        B_global = new int[global_size];
        fillmatrix(A_global, n, m);
        fillmatrix(B_global, n, m);
    }

    MPI_Scatter(A_global, local_size, MPI_INT, A_local, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B_global, local_size, MPI_INT, B_local, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_size; i++)
    {
        C_local[i] = A_local[i] + B_local[i];
    }
    MPI_Allgather(C_local, local_size, MPI_INT, C_global, local_size, MPI_INT, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "A:" << endl;
        for (int i = 0; i < global_size; i++)
        {
            cout << A_global[i] << " ";
            if ((i + 1) % m == 0)
                cout << endl;
        }
        cout << "B:" << endl;
        for (int i = 0; i < global_size; i++)
        {
            cout << B_global[i] << " ";
            if ((i + 1) % m == 0)
                cout << endl;
        }
        cout << "C = A + B:" << endl;
        for (int i = 0; i < global_size; i++)
        {
            cout << C_global[i] << " ";
            if ((i + 1) % m == 0)
                cout << endl;
        }

        delete[] A_global;
        delete[] B_global;
    }

    delete[] A_local;
    delete[] B_local;
    delete[] C_local;
    delete[] C_global;

    MPI_Finalize();
    return 0;
}
