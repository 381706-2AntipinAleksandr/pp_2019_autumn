// Copyright 2019 Kolesova Kristina
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
//#include <algorithm>
#include <random>
#include <cassert>
#include "../../../modules/task_3/kolesova_k_sort_betch/sort_betch.h"

TEST(Sort_Batcher, Vec_Setpoints) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> vec = {  103, 5, 10, 21, 35, 18, 13, 29};
  std::vector<int> res = { 5, 10, 13, 18, 21, 29, 35, 103};

  std::vector<int> parralel = merge_batcher(vec, vec.size());
  if (rank == 0) {
    ASSERT_EQ(parralel, res);
  }
}

TEST(Sort_Batcher, Vec_50_Elem) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int size_vector = 50;
  if (rank == 0) {
    global_vec = getRandomVector(size_vector);
  }

  std::vector<int> parralel = merge_batcher(global_vec, size_vector);
  if (rank == 0) {
    global_vec = radix_sort(global_vec);
    ASSERT_EQ(parralel, global_vec);
  }
}

TEST(Sort_Batcher, Vec_100_Elem) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> global_vec;
  const int size_vector = 100;
  if (rank == 0) {
    global_vec = getRandomVector(size_vector);
  }

  std::vector<int> parralel = merge_batcher(global_vec, size_vector);
  if (rank == 0) {
    global_vec = radix_sort(global_vec);
    ASSERT_EQ(parralel, global_vec);
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
