// Copyright 2019 Kolesova Kristina

#ifndef MODULES_TASK_2_KOLESOVA_K_RIB_VERT_SCH_RIB_VERT_SCH_H_
#define MODULES_TASK_2_KOLESOVA_K_RIB_VERT_SCH_RIB_VERT_SCH_H_

#include <vector>

std::vector<int> randVec(int n);

std::vector<int> randMatr(int m, int n);

std::vector<int> calcMatrOneProc(std::vector<int> matr, std::vector<int> vec, int n, int m);

std::vector<int> calcMatr(std::vector<int> matr, std::vector<int> vec, int n, int m);

#endif  // MODULES_TASK_2_KOLESOVA_K_RIB_VERT_SCH_RIB_VERT_SCH_H_
