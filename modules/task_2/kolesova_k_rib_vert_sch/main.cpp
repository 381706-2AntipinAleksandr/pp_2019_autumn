// Copyright 2019 Kolesova Kristina

#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <mpi.h>
#include <vector>
#include <../../../modules/task_2/kolesova_k_rib_vert_sch/rib_vert_sch.h>

TEST(Test_Rib_Vert_Sch, Create_Rand_Vector) {
  int n = 5;
  std::vector<int> vec = randVec(n);
  EXPECT_EQ(n, vec.size());
}

TEST(Test_Rib_Vert_Sch, Create_Rand_Martix) {
  int n = 5;
  int m = 3;
  std::vector<int> matr = randMatr(m, n);
  EXPECT_EQ(m*n, matr.size());
}

TEST(Test_Rib_Vert_Sch, One_Proc_Mult_One) {
  int n = 3;
  int m = 3;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> vec = { 1, 2, 3 };
  std::vector<int> matr = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::vector<int> trueVec = { 14, 32, 50 };
  std::vector<int> resVect;

  if (rank == 0) {
    resVect = calcMatrOneProc(matr, vec, n, m);
  }

  EXPECT_EQ(trueVec, resVect);
}

TEST(Test_Rib_Vert_Sch, Mult_One) {
  int n = 3;
  int m = 3;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> vec = { 1, 2, 3 };
  std::vector<int> matr = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::vector<int> trueVec = { 14, 32, 50 };
  std::vector<int> resVect;

  if (rank == 0) {
    resVect = calcMatr(matr, vec, n, m);
  }

  EXPECT_EQ(trueVec, resVect);
}

TEST(Test_Rib_Vert_Sch, One_Proc_Mult_Two) {
  int n = 5;
  int m = 5;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> vec = { 6, 7, 8, 9, 10 };
  std::vector<int> matr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5 };
  std::vector<int> trueVec = { 130, 330, 310, 110, 130 };
  std::vector<int> resVect;

  if (rank == 0) {
    resVect = calcMatr(matr, vec, n, m);
  }

  EXPECT_EQ(trueVec, resVect);
}

TEST(Test_Rib_Vert_Sch, Mult_100Elem) {
  int n = 100;
  int m = 100;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> vec = randVec(n);
  std::vector<int> matr = randMatr(m, n);
  std::vector<int> trueVec = calcMatrOneProc(matr, vec, n, m);
  std::vector<int> resVect;

  if (rank == 0) {
    resVect = calcMatr(matr, vec, n, m);
  }

  EXPECT_EQ(trueVec, resVect);
}

TEST(Test_Rib_Vert_Sch, Mult_1000Elem) {
  int n = 1000;
  int m = 1000;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> vec = randVec(n);
  std::vector<int> matr = randMatr(m, n);
  std::vector<int> trueVec = calcMatrOneProc(matr, vec, n, m);
  std::vector<int> resVect;

  if (rank == 0) {
    resVect = calcMatr(matr, vec, n, m);
  }

  EXPECT_EQ(trueVec, resVect);
}
