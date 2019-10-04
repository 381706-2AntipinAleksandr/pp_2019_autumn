#include <vector>
#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 2000
#define MIN_NUMBER -1000


std::vector<int> creatRandomVector(const int v_size);

int getSequentialScalarProduct(const std::vector<int>& a, const std::vector<int>& b);

int getParallelScalarProduct(const std::vector<int>& a, const std::vector<int>& b);