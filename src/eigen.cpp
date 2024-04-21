#include <math.h>
#include <Eigen/Core>
#include <cassert>
#include <iostream>

extern "C"
{
    float float_norm(int rows, int cols, float* data)
    {
        Eigen::Map<Eigen::MatrixXf> x(data, rows, cols);
        return x.norm();
    }

    void float_matrix_matrix_mult(int rowsA, int colsA, float* _A, int rowsB, int colsB, float* _B, float* _C)
    {
        assert(colsA == rowsB);
        Eigen::Map<Eigen::MatrixXf> A(_A, rowsA, colsA);
        Eigen::Map<Eigen::MatrixXf> B(_B, rowsB, colsB);
        Eigen::Map<Eigen::MatrixXf> C(_C, rowsA, colsB);

        C = A*B;
    }
}