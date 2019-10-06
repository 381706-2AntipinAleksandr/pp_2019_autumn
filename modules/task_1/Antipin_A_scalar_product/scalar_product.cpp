// Copyright 2019 Antipin Alexander
#include "scalar_product.h"


std::vector<int> creatRandomVector(const int v_size)
{
    std::vector<int> vector;
    for (int i = 0; i < v_size; i++)
    {
        vector.push_back(rand() % MAX_NUMBER + MIN_NUMBER);
        // std::cout << vector.back() << ", ";
    }
    // std::cout << std::endl;
    return vector;
}

int getSequentialScalarProduct(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a.size() != b.size()) {
        throw (1);
    }
    int result = 0;
    for (int i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
    }   
    return result;
}

int getParallelScalarProduct(const std::vector<int>& a, const std::vector<int>& b)
{
    int rank, size;
    if (a.size() != b.size()) {
        throw (1);
    }  
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int v_size = a.size() / size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int result = 0, result_other = 0, resive = 0;
    if (rank == 0)
    {
        for (int i = 0; i < v_size; i++) {
            result += a[i] * b[i];
        }
        for (int i = 1; i < size; i++)
        {
            MPI_Status status;
            MPI_Recv(&resive, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            result += resive;
        }
        return result;
    }
    else
    {
        if (size % 2 == 1 && rank == size - 1 || a.size() % 2 == 1 && rank == size - 1) {
            for (int i = v_size * rank; i < a.size(); i++) {
                result_other += a[i] * b[i];
            }
        }    
        else {
            for (int i = v_size * rank; i < v_size * (rank + 1); i++) {
                result_other += a[i] * b[i];
            }
        }
        MPI_Send(&result_other, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
}
