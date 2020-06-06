// Copyright 2019 Gilenkov Alexandr

#ifndef MODULES_TASK_2_GILENKOV_A_HORIZONT_GAUSS_GAUSS_H_
#define MODULES_TASK_2_GILENKOV_A_HORIZONT_GAUSS_GAUSS_H_
#include <vector>

std::vector<double> getRandomMatrix(int rows, int cols, double min, double max);
std::vector<double> parallelGauss(const std::vector<double> &a, int rows, int cols);
std::vector<double> Gauss(const std::vector<double> &b, int rows, int cols);

#endif  // MODULES_TASK_2_GILENKOV_A_HORIZONT_GAUSS_H_