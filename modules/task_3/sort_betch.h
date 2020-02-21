// Copyright 2019 Kolesova Kristina
#ifndef MODULES_TASK_3_KOLESOVA_K_SORT_BETCH_SORT_BETCH_H_
#define MODULES_TASK_3_KOLESOVA_K_SORT_BETCH_SORT_BETCH_H_ 

#include <mpi.h>
#include <vector>

std::vector<double> randVec(int size);
std::vector<int> separation(std::vector<int> vec);
std::vector<int> merge_even(const std::vector<int>& vec1, const std::vector<int>& vec2);
std::vector<int> merge_odd(const std::vector<int>& vec1, const std::vector<int>& vec2);
std::vector<int>  merger(std::vector<int> vec, int even_size, int odd_size);
std::vector<double> razr(std::vector<double> vec1, std::vector<double> vec2, int size, int byte);
std::vector<double> last_razr(std::vector<double> vec1, std::vector<double> vec2, int byte, int size);
void sort(std::vector<int> vec, int size);
std::vector<int> merge_batcher(std::vector<int> global_vec, int size_vec);

# endif   // MODULES_TASK_3_KOLESOVA_K_SORT_BETCH_SORT_BETCH_H_
