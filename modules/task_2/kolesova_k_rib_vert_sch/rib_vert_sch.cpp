#include <vector>
#include <random>
#include <mpi.h>


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
  std::vector<int> resVec(m);
  std::vector<int> transpMatr(m*n);
  

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Status status;

  int modf = n / size;
  int res = n % size;
  int id = 0;

  std::vector<int> tmpResVec(modf);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      transpMatr[id]=matr[j*n+i]
    }
  }

  MPI_Scatter()