// Copyright 2019 Antipin Alexander
#include <time.h>
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include <random>
#include <vector>
#include "./gauss_method.h"

TEST(gauss_method, can_calculate_matrix_correct_using_sequential_method) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<double>> vec{ {1.0, 2.0, 3.0}, {2.0, 3.0, 4.0}, {2.0, 7.0, 7.0} };
    Matrix mat(vec);
    std::vector<double> res(mat.getMatrixSize());
    if (rank == 0) {
        res = mat.getSequentialSolution({ 1, 1, 1 });
        EXPECT_NEAR(res[0], -0.2, 0.00001);
        EXPECT_NEAR(res[1], -0.6, 0.00001);
        EXPECT_NEAR(res[2], 0.8, 0.00001);

        double first = 1 * res[0] + 2 * res[1] + 3 * res[2];
        double second = 2 * res[0] + 3 * res[1] + 4 * res[2];
        double third = 2 * res[0] + 7 * res[1] + 7 * res[2];

        EXPECT_NEAR(first, 1, 0.00001);
        EXPECT_NEAR(second, 1, 0.00001);
        EXPECT_NEAR(third, 1, 0.00001);
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

        double first = 1 * res[0] + 2 * res[1] + 3 * res[2];
        double second = 2 * res[0] + 3 * res[1] + 4 * res[2];
        double third = 2 * res[0] + 7 * res[1] + 7 * res[2];

        EXPECT_NEAR(first, 1, 0.00001);
        EXPECT_NEAR(second, 1, 0.00001);
        EXPECT_NEAR(third, 1, 0.00001);
    }
}

TEST(gauss_method, can_calculate_matrix_if_there_is_zero_element) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<double>> vec{ {0, 2, 3}, {2, 3, 4}, {2, 7, 7} };
    Matrix mat(vec);
    std::vector<double> resM(mat.getMatrixSize());
    resM = mat.getParallelSolution({ 1, 2, 1 });
    if (rank == 0) {
        std::vector<double> res = mat.getSequentialSolution({ 1, 2, 1 });
        EXPECT_NEAR(res[0], resM[0], 0.00001);
        EXPECT_NEAR(res[1], resM[1], 0.00001);
        EXPECT_NEAR(res[2], resM[2], 0.00001);

        double first = 0 * res[0] + 2 * res[1] + 3 * res[2];
        double second = 2 * res[0] + 3 * res[1] + 4 * res[2];
        double third = 2 * res[0] + 7 * res[1] + 7 * res[2];

        EXPECT_NEAR(first, 1, 0.00001);
        EXPECT_NEAR(second, 2, 0.00001);
        EXPECT_NEAR(third, 1, 0.00001);
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

        double first = 1 * res[0] + 2 * res[1] + 2 * res[2] + 3 * res[3] + 5 * res[4];
        double second = 8 * res[0] + 7 * res[1] + 2 * res[2] + 2 * res[3] + 6 * res[4];
        double third = 5 * res[0] + 3 * res[1] + 3 * res[2] + 1 * res[3] + 2 * res[4];
        double fourth = 2 * res[0] + 5 * res[1] + 8 * res[2] + 4 * res[3] + 6 * res[4];
        double fifth = 3 * res[0] + 2 * res[1] + 1 * res[2] + 7 * res[3] + 5 * res[4];
        EXPECT_NEAR(first, 5, 0.001);
        EXPECT_NEAR(second, 3, 0.001);
        EXPECT_NEAR(third, 7, 0.001);
        EXPECT_NEAR(fourth, 4, 0.001);
        EXPECT_NEAR(fifth, 6, 0.001);
    }
}

TEST(gauss_method, can_calculate_matrix_with_size_in_5_elements_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<double>> vec{ {1, 2, 2, 3, 5}, {8, 7, 2, 2, 6}, {5, 3, 3, 1, 2},
        {2, 5, 8, 4, 6}, {3, 2, 1, 7, 5} };
    Matrix mat(vec);
    std::vector<double> res(mat.getMatrixSize());
    res = mat.getParallelSolution({ 5, 3, 7, 4, 6 });
    if (rank == 0) {
        double first = 1 * res[0] + 2 * res[1] + 2 * res[2] + 3 * res[3] + 5 * res[4];
        double second = 8 * res[0] + 7 * res[1] + 2 * res[2] + 2 * res[3] + 6 * res[4];
        double third = 5 * res[0] + 3 * res[1] + 3 * res[2] + 1 * res[3] + 2 * res[4];
        double fourth = 2 * res[0] + 5 * res[1] + 8 * res[2] + 4 * res[3] + 6 * res[4];
        double fifth = 3 * res[0] + 2 * res[1] + 1 * res[2] + 7 * res[3] + 5 * res[4];
        EXPECT_NEAR(first, 5, 0.001);
        EXPECT_NEAR(second, 3, 0.001);
        EXPECT_NEAR(third, 7, 0.001);
        EXPECT_NEAR(fourth, 4, 0.001);
        EXPECT_NEAR(fifth, 6, 0.001);
    }
}

TEST(gauss_method, can_calculate_big_random_matrix_without_throws) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Matrix matrix(100);
    std::vector<double> res(100);
        getRandomVector(matrix.getMemOfMatrix());
        getRandomVector(&res);
    ASSERT_NO_THROW(matrix.getParallelSolution(res));
}

TEST(gauss_method, can_calculate_big_random_matrix_correct) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Matrix matrix(10);
    std::vector<double> b(10);
    std::vector<double> res(10);
    getRandomVector(matrix.getMemOfMatrix());
    getRandomVector(&b);
    if (rank == 0) {
        res = matrix.getSequentialSolution(b);
    }
    std::vector<double> resM = matrix.getParallelSolution(b);
    if (rank == 0) {
        EXPECT_NEAR(res[0], resM[0], 0.001);
        EXPECT_NEAR(res[2], resM[2], 0.001);
        EXPECT_NEAR(res[4], resM[4], 0.001);
        EXPECT_NEAR(res[6], resM[6], 0.001);
        EXPECT_NEAR(res[8], resM[8], 0.001);

        double first = 0;
        double second = 0;
        double third = 0;
        double fourth = 0;
        double fifth = 0;

        for (int i = 0; i < 10; ++i) {
            first += matrix.getElem(0, i) * res[i];
            second += matrix.getElem(2, i) * res[i];
            third += matrix.getElem(4, i) * res[i];
            fourth += matrix.getElem(6, i) * res[i];
            fifth += matrix.getElem(8, i) * res[i];
        }
        EXPECT_NEAR(first, b[0], 0.001);
        EXPECT_NEAR(second, b[2], 0.001);
        EXPECT_NEAR(third, b[4], 0.001);
        EXPECT_NEAR(fourth, b[6], 0.001);
        EXPECT_NEAR(fifth, b[8], 0.001);
    }
}

/*TEST(gauss_method, can_calculate_big_random_matrix_correct_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Matrix matrix(100);
    std::vector<double> mat(10000);
    std::vector<double> b(100);
    std::vector<double> res(100);
    if (rank == 0) {
        getRandomVector(&mat);
        getRandomVector(&b);
    }
    MPI_Bcast(&mat[0], 10000, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b[0], 100, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    *matrix.getMemOfMatrix() = mat;
    std::vector<double> resM = matrix.getParallelSolution(b);
    if (rank == 0) {
        res = matrix.getSequentialSolution(b);
        EXPECT_NEAR(res[0], resM[0], 0.001);
        EXPECT_NEAR(res[15], resM[15], 0.001);
        EXPECT_NEAR(res[37], resM[37], 0.001);
        EXPECT_NEAR(res[68], resM[68], 0.001);
        EXPECT_NEAR(res[95], resM[95], 0.001);
    }
}*/

/*TEST(gauss_method, testing_time) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Matrix matrix(1000);
    std::vector<double> mat(1000000);
    std::vector<double> b(1000);
    std::vector<double> res(1000);
    if (rank == 0) {
        getRandomVector(&mat);
        getRandomVector(&b);
    }
    MPI_Bcast(&mat[0], 1000000, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b[0], 1000, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    *matrix.getMemOfMatrix() = mat;
    double startTime = 0, endTime = 0;
    startTime = MPI_Wtime();
    if (rank == 0) {
        matrix.getSequentialSolution(b);
    }
    endTime = MPI_Wtime();
    if (rank == 0) {
        printf("Time of parallel method - %f\n", startTime - endTime);
    }
    startTime = MPI_Wtime();
    matrix.getParallelSolution(b);
    endTime = MPI_Wtime();
    if (rank == 0) {
        printf("Time of parallel method - %f\n", startTime - endTime);
    }
}*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    srand(time(NULL));
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
