// Copyright 2019 Kolesova Kristina

#include <vector>
#include <random>
#include <mpi.h>
#include <../../../modules/task_2/kolesova_k_rib_vert_sch/rib_vert_sch.h>

std::vector<int> randVec(int n) {
  std::vector<int> vec(n);
  std::mt19937 engine;
  for (int i = 0; i < n; i++) {
    vec[i] = engine() % 10;
  }
  return vec;
}

std::vector<int> randMatr(int m, int n) {
  std::vector<int> matr(m*n);
  std::mt19937 engine;
  for (int i = 0; i < m*n; i++) {
    matr[i] = engine() % 10;
  }
  return matr;
}

std::vector<int> calcMatrOneProc(std::vector<int> matr, std::vector<int> vec, int n, int m) {
  if (n != vec.size()) {
    throw - 1;
  }

  std::vector<int> resVec(m);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      resVec[i] += matr[i*n + j] * vec[j];
    }
  }
  return resVec;
}

std::vector<int> calcMatr(std::vector<int> matr, std::vector<int> vec, int n, int m) {
  if (n != vec.size()) {
    throw - 1;
  }

  int size, rank;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Status status;

  int modf = m * n / size;
  int res = m * n % size;

  std::vector<int> resVec(m);
  std::vector<int> transpMatr(m*n);
  std::vector<int> multMatr(m*n);
  std::vector<int> tmpResVec(modf);

  int id = 0;


  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      transpMatr[id] = matr[j*n + i]
    }
  }

  if (rank == 0) {
    for (int i = 0; i < r; i++) {
      multMatr[i] = transpMatr[i] * vec[i / m];
    }
  }

  MPI_Scatter(&transpMatr[res], modf, MPI_INT, &tmpResVec[0], modf, MPI_INT, 0, MPI_COMM_WORLD);

  for (int i = 0; i < modf; i++) {
    tmpResVec[i] *= vec[rank*modf + i + res];
  }

  MPI_Gather(&tmpResVec[0], modf, MPI_INT, &multMatr[r], modf, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < m*n; i++) {
      resVec[i%m] += multMatr[i];
    }

    return resVec;
  }
}
