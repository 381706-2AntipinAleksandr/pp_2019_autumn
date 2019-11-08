// Copyright 2019 Antipin Alexander
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include <vector>
#include "./gauss_method.h"

TEST(gauss_method, can_calculate_matrix_correct_using_sequential_method) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<double>> vec{ {1, 2, 3}, {2, 3, 4}, {2, 7, 7} };
    Matrix mat(vec);
    std::vector<double> res(mat.getMatrixSize());
    if (rank == 0) {
        res = mat.getSequentialSolution({ 1, 1, 1 });
        EXPECT_NEAR(res[0], -0.2, 0.00001);
        EXPECT_NEAR(res[1], -0.6, 0.00001);
        EXPECT_NEAR(res[2], 0.8, 0.00001);
    }
}

TEST(gauss_method, can_calculate_matrix_correct_using_parallel_method) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<double>> vec{ {1, 2, 3}, {2, 3, 4}, {2, 7, 7} };
    Matrix mat(vec);
    std::vector<double> res(mat.getMatrixSize());
    res = mat.getParallelSolution({ 1, 1, 1 });
    if (rank == 0) {
        EXPECT_NEAR(res[0], -0.2, 0.00001);
        EXPECT_NEAR(res[1], -0.6, 0.00001);
        EXPECT_NEAR(res[2], 0.8, 0.00001);
    }
}

TEST(gauss_method, can_throw_if_matrix_size_less_then_process_count) {
    Matrix mat;
    ASSERT_ANY_THROW(mat.getParallelSolution({ 1, 1, 1 }));
}

TEST(gauss_method, can_throw_if_matrix_size_not_equal_result_vector_size) {
    std::vector<std::vector<double>> vec{ {1, 2, 3}, {2, 3, 4}, {2, 7, 7} };
    Matrix mat(vec);
    std::vector<double> res(mat.getMatrixSize());
    ASSERT_ANY_THROW(mat.getParallelSolution({1, 1, 1, 1}));
}

TEST(gauss_method, can_calculate_matrix_with_size_in_5_elements) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<double>> vec{ {1, 2, 2, 3, 5}, {8, 7, 2, 2, 6}, {5, 3, 3, 1, 2},
        {2, 5, 8, 4, 6}, {3, 2, 1, 7, 5} };
    Matrix mat(vec);
    std::vector<double> res(mat.getMatrixSize());
    res = mat.getParallelSolution({ 5, 3, 7, 4, 6 });
    if (rank == 0) {
        EXPECT_NEAR(res[0], 2.533, 0.001);
        EXPECT_NEAR(res[1], -4.504, 0.001);
        EXPECT_NEAR(res[2], 1.419, 0.001);
        EXPECT_NEAR(res[3], -0.661, 0.001);
        EXPECT_NEAR(res[4], 2.124, 0.001);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
