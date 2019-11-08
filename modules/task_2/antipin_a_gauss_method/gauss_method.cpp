// Copyright 2019 Antipin Alexander

#include "../../../modules/task_2/antipin_a_gauss_method/gauss_method.h"

Matrix::Matrix() {
    mem = std::vector<double>(0);
    n = 0;
}

Matrix::Matrix(const std::vector<double>& vec) {
    mem = std::vector<double>(vec);
    n = static_cast<int>(sqrt(vec.size()));
}

Matrix::Matrix(const std::vector<std::vector<double>>& mat) {
    for (size_t i = 0; i < mat.size(); ++i) {
        for (size_t j = 0; j < mat[i].size(); ++j) {
            mem.push_back(mat[i][j]);
        }
    }
    n = mat.size();
}

Matrix::Matrix(const Matrix& mat) {
    mem = mat.mem;
    n = mat.n;
}

Matrix::~Matrix() {
    mem.~vector();
}

int Matrix::getMatrixSize() {
    return n;
}

double & Matrix::getElem(const int row, const int col) {
    return mem[row * col + col];
}

std::vector<double> Matrix::getSequentialSolution(const std::vector<double>& coefVec) {
    std::vector<double> result(n);
    std::vector<double> additionalMat(mem);
    std::vector<double> copyCoefVec(coefVec);
    for (int k = 0; k < n - 1; ++k) {
        double leaderElem = additionalMat[k*n + k];
        bool moreElem = leaderElem >= 0.0 ? true : false;
        for (int rows = k + 1; rows < n; ++rows) {
            double leaderRow = additionalMat[rows*n + k];
            bool moreRow = leaderRow >= 0.0 ? true : false;
            if ((moreElem && moreRow) || (!moreElem && !moreRow)) {
                for (int cols = k; cols < n; ++cols) {
                    additionalMat[rows*n + cols] -= additionalMat[k*n + cols] * abs(leaderRow / leaderElem);
                }
                copyCoefVec[rows] -= copyCoefVec[k] * abs(leaderRow / leaderElem);
            } else {
                for (int cols = k; cols < n; ++cols) {
                    additionalMat[rows*n + cols] += additionalMat[k*n + cols] * abs(leaderRow / leaderElem);
                }
                copyCoefVec[rows] += copyCoefVec[k] * abs(leaderRow / leaderElem);
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        double res = 0.0;
        for (int j = n - 1; j >= i + 1; --j) {
            res += additionalMat[i*n + j] * result[j];
        }
        res = (copyCoefVec[i] - res) / additionalMat[i*n + i];
        result[i] = res;
    }
    return result;
}

std::vector<double> Matrix::getParallelSolution(const std::vector<double>& coefVec) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (coefVec.size() != n) {
        throw(1);
    }
    if (size > n) {
        throw(2);
    }
    double leaderElem = 0;
    int colsCount = n / size;
    (n % size) / (rank + 1) < 1 ? colsCount: ++colsCount;
    int additionalMatSize = colsCount * n;
    std::vector<double> additionalMat(additionalMatSize);
    size_t k = 0;
    for (int i = rank; i < n; i += size) {
        for (int j = 0; j < n; ++j) {
            additionalMat[k] = mem[i + j * n];
            k++;
        }
    }
    std::vector<double> recvVec;
    std::vector<double> copyCoefVec(coefVec);
    for (int i = 0; i < n; ++i) {
        recvVec.resize(n);
        if (i % size == rank) {
            recvVec = std::vector<double>(additionalMat.begin()+ n * (i / size),
                additionalMat.begin() + n * (i / size) + n);
        }
        MPI_Bcast(&recvVec[0], n, MPI_DOUBLE, i % size, MPI_COMM_WORLD);
        leaderElem = recvVec[i];
        for (int j = i / size; j < colsCount; ++j) {
            double leaderCol = additionalMat[j*n + i];
            for (int k = 0; k < n; ++k) {
                if (k == i) {
                    additionalMat[j*n + k] /= leaderElem;
                } else {
                    additionalMat[j*n + k] -= round((leaderCol * recvVec[k] / leaderElem) * 100000.0) / 100000.0;
                }
            }
        }
        if (rank == 0) {
            double leaderCol = copyCoefVec[i];
            for (int k = 0; k < n; ++k) {
                if (k == i) {
                    copyCoefVec[k] /= leaderElem;
                } else {
                    copyCoefVec[k] -= round((leaderCol * recvVec[k] / leaderElem) * 100000.0) / 100000.0;
                }
            }
        }
    }
    return copyCoefVec;
}
