//Copyright Gilenkov Alexander 2019
#ifndef MODULES_TASK_1_GILENKOV_A_WRONG_ORDER_WRONG_ORDER_IN_VECTOR_H_
#define MODULES_TASK_1_GILENKOV_A_WRONG_ORDER_WRONG_ORDER_IN_VECTOR_H_
#include "mpi.h"
#include "vector"

std::vector<int> getRandomVector(int size_v); //рандомный вектор
int getWrongOrder(std::vector<int> vector, int count_size_vector); //‘ункци€, вычисл€юща€ количество нарушений последовательности
int getParallelOperations(std::vector<int> global_vec, int count_size_vector);

#endif //MODULES_TASK_1_GILENKOV_A_WRONG_ORDER_WRONG_ORDER_IN_VECTOR_H_