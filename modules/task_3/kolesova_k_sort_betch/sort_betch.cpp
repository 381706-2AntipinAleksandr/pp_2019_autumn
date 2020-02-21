// Copyright 2019 Kolesova Kristina
#include <mpi.h>
#include <vector>
#include <ctime>
#include <random>
#include <utility>
#include <algorithm>
#include "../../../modules/task_3/kolesova_k_sort_betch/sort_betch.h"

std::vector<double> randVec(int size) {
  std::mt19937 gen(time(0));
  std::uniform_real_distribution<> urd(1, 100);

  std::vector<double> vec(size);

  for (int i = 0; i < size; ++i) {
    vec[i] = urd(gen);
  }

  return vec;
}

std::vector<int> separation(std::vector<int> vec) {
  size_loc = vec.size();
  int sep;
  sep = size_loc / 2 + size_loc % 2;
  std::vector<int> tmp(size_loc);

  for (int i = 0; i < sep; i++) {
    tmp[i] = vec[2 * i];
  }
  for (int i = 0; i < size_loc; i ++) {
    tmp[sep + i] = vec[2 * i + 1];
  }
  for (int i = 0; i < size_loc; i++) {
    vec[i] = tmp[i];
  }
  return vec;
}

std::vector<int> merge_even(const std::vector<int>& vec1, const std::vector<int>& vec2) {
  int size_loc1;
  size_loc1 = vec1.size();
  int size_loc2;
  size_loc2 = vec2.size();
  int sep1;
  sep1 = size_loc1 / 2 + size_loc1 % 2;

  std::vector<int> res(sep1 + size_loc2);
  int j = 0, k = 0;
  int l = 0;

  while ((j < sep1) && (k < (size_loc2))) {
    if (vec1[j] > vec2[k]) {
      res[l] = vec2[k];
      l++;
      k++;
    }else {
      res[l] = vec1[j];
      l++;
      j++;
    }
  }

  if (k < size_loc2) {
    for (k; k < size_loc2; k++) {
      res[l] = vec2[k];
      l++;
    }
  }

  if (j < sep1) {
    for (j; j < sep1; j++) {
      res[l] = vec1[j];
      l++;
    }
  }

  return res;
}

std::vector<int> merge_odd(const std::vector<int>& vec1, const std::vector<int>& vec2) {
  int size_loc1;
  size_loc1 = vec1.size();
  int size_loc2;
  size_loc2 = vec2.size();
  int sep1;
  sep1 = size_loc1 / 2 + size_loc1 % 2;

  std::vector<int> res(size_loc1 / 2 + size_loc2);
  int j = sep1, k = 0;
  int l = 0;

  while ((j < sep1) && (k < (size_loc2))) {
    if (vec1[j] > vec2[k]) {
      res[l] = vec2[k];
      l++;
      k++;
    }else {
      res[l] = vec1[j];
      l++;
      j++;
    }
  }

  if (k < size_loc2) {
    for (k; k < size_loc2; k++) {
      res[l] = vec2[k];
      l++;
    }
  }

  if (j < size_loc1) {
    for (j; j < sep1; j++) {
      res[l] = vec1[j];
      l++;
    }
  }

  return res;
}

std::vector<int>  merger(std::vector<int> vec, int even_size, int odd_size) {
  int size_loc;
  size_loc = vec.size();
  int sep;
  sep = size_loc / 2 + size_loc % 2;
  std::vector<int> res(size_loc);
  int j = 0, k = 0, l = 0;

  for(j; (j < even_size && k < odd_size); j++) {
    res[l] = vec[j];
    l++;
    res[l] = vec[even_size + k];
    k++; l++;
  }

  if (j < even_size) {
    for (j; j < even_size; j++) {
      res[l] = vec[j];
      l++;
    }
  }

  for (int i = 0; i < res.size(); i++) {
    if (res[i] > res[i + 1]) {
      t = res[i];
      res[i] = res[i + 1];
      res[i + 1] = t;
    }
  }

  return res;
}

std::vector<double> razr(std::vector<double> vec1, std::vector<double> vec2, int size, int byte) {
  unsigned char *tmp = (unsigned char *)vec1.data();
  int tmp_dat;
  int index;
  int couter;
  int count[256];

  tmp_dat = 0;
  for (int i = 0; i < 256; i++)
    count[i] = 0;

  for (int i = 0; i < size; i++) {
    index = tmp[8 * i + byte];
    count[index]++;
  }

  for (int i = 0; i < 256; i++) {
    int tm = count[i];
    count[i] = tmp_dat;
    tmp_dat = tmp_dat + tm;
  }

  for (int i = 0; i < size; i++) {
    index = tmp[8 * i + byte];
    count = count[index];
    vec2[count] = vec1[i];
    count[index]++;
  }
  return vec2;
}

std::vector<double> last_razr(std::vector<double> vec1, std::vector<double> vec2, int byte, int size) {
  unsigned char *tmp = (unsigned char *)vec1.data();
  int tmp_dat;
  int index;
  int couter;
  int count[256];

  tmp_dar = 0;
  for (int i = 0; i < 256; i++)
    count[i] = 0;

  for (int i = 0; i < size; i++) {
    index = tmp[8 * i + byte];
    count[index]++;
  }

  for (int i = 255; i >= 128; i--) {
    count[i] = count[i] + tmp_dat;
    tmp_dat = count[i];
  }
  for (int i = 0; i < 128; i++) {
    int tm = count[i];
    count[i] = tmp_dat;
    tmp_dat = tmp_dat + tm;
  }

  for (int i = 0; i < size; i++) {
    index = tmp[8 * i + byte];
    counter = count[index];
    if (index < 128) {
      vec2[counter] = vec1[i];
      count[index]++;
    }else {
      count[index]--;
      vec2[counter] = vec1[i];
    }
  }
  return vec2;
}

void sort(std::vector<int> vec, int size) {
  std::vector<int> tmp;
  std::vector<int> res (size);
  for (int i = 0; i < 8; i++) {
    razr(vec, res, size, i);
    tmp = vec;
    vec = res;
    res = tmp;
  }
  last_razr(vec, res, size, 7);
}

std::vector<int> merge_batcher(std::vector<int> global_vec, int size_vec) {
  std::vector<int> local_vec;
  std::vector<int> res;
  std::vector<int> even;
  std::vector<int> odd;
  int merged_proc;
  int displs_proc;
  int size_del;
  int length_recv;
  int* countsend = new int[size];
  int* dis = new int[size];
  int size;
  int rank;
  int sep;
  const int del;
  const int res;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  del = size_vec / size;
  res = size_vec % size;

  if (rank == 0) {
    local_vec.resize(delta + residue);
  }else {
    local_vec.resize(delta);
  }

  for (int i = 0; i < size; i++) {
    dis[i] = 0;
    if (i != 0) {
      countsend[i] = delta;
    }else {
      countsend[i] = delta + residue;
    }
    if (i > 0) {
      dis[i] = dis[i - 1] + countsend[i - 1];
    }
  }

  MPI_Scatterv(global_vec.data(), countsend, dis, MPI_INT, 
    &local_vec.front(), countsend[rank], MPI_INT, 0, MPI_COMM_WORLD);

 
  int numder = (int)round(log2(size);

  local_vec = sort(local_vec);
  local_vec = separation(local_vec);
  merged_proc = 2;
  displs_proc = 1;
  sep = length_recv / 2 + length_recv % 2;

  MPI_Status status;

  for (int i = 0; i < numder; i++) {
    if ((rank % merged_proc == 0) && (rank + displs_proc < size)) {
      size_del = local_vec.size() / 2;

      MPI_Isend(&size_del, 1, MPI_INT, rank + displs_proc, 0, MPI_COMM_WORLD, &status);
      MPI_Irecv(&length_recv, 1, MPI_INT, rank + displs_proc, 0, MPI_COMM_WORLD, &status);

      res.resize(sep);

      MPI_Isend(&local_vec[sep], size_del, MPI_INT, rank + displs_proc, 0, MPI_COMM_WORLD, &status);
      MPI_Irecv(&res.front(), sep, MPI_INT, rank + displs_proc, 0, MPI_COMM_WORLD, &status);

      even = merge_even(local_vec, res);

      odd.resize(length_recv / 2 + local_vec.size() / 2);

      MPI_Recv(&odd.front(), length_recv / 2 + local_vec.size() / 2, MPI_INT, rank + displs_proc, 
        0, MPI_COMM_WORLD, &status);

      local_vec.resize(even.size() + odd.size());

      std::copy(even.begin(), even.end(), local_vec.begin());
      std::copy(odd.begin(), odd.end(), local_vec.begin() + even.size());

      if (numder - i == 1 )
        local_vec = transpos(local_vec, even.size(), odd.size());
      else
        local_vec = merge(local_vec, even.size(), odd.size());
    }

    if (rank - displs_proc >= 0 && (rank - displs_proc) % merged_proc == 0) {
      size_del = local_vec.size();

      MPI_Isend(&size_del, 1, MPI_INT, rank - displs_proc, 0, MPI_COMM_WORLD, &status);
      MPI_Irecv(&length_recv, 1, MPI_INT, rank - displs_proc, 0, MPI_COMM_WORLD, &status);

      res.resize(length_recv);

      MPI_Isend(local_vec.data(), size_del / 2 + size_del % 2, MPI_INT, rank - displs_proc, 0, MPI_COMM_WORLD, &status);
      MPI_Irecv(&res.front(), length_recv, MPI_INT, rank - displs_proc, 0, MPI_COMM_WORLD, &status);

      odd = merge_odd(local_vec, res);
      MPI_Send(odd.data(), odd.size(), MPI_INT, rank - displs_proc, 0, MPI_COMM_WORLD);
    }
    merged_proc *= 2;
    displs_proc *= 2;
  }
  return local_vec;
}
