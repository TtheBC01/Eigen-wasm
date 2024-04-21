#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cassert>
#include <iostream>

extern "C"
{
    float float_norm(int rows, int cols, float* _A)
    {
        Eigen::Map<Eigen::MatrixXf> A(_A, rows, cols);
        return A.norm();
    }

    void float_random_matrix(int rows, int cols, float* _A)
    {
        Eigen::Map<Eigen::MatrixXf> A(_A, rows, cols);
        A.setRandom();
    }

    void float_matrix_matrix_mult(int rowsA, int colsA, float* _A, int rowsB, int colsB, float* _B, float* _C)
    {
        assert(colsA == rowsB);
        Eigen::Map<Eigen::MatrixXf> A(_A, rowsA, colsA);
        Eigen::Map<Eigen::MatrixXf> B(_B, rowsB, colsB);
        Eigen::Map<Eigen::MatrixXf> C(_C, rowsA, colsB);

        C = A*B;
    }

    void float_system_solve(int rowsA, int colsA, float* _A, float* _b, float* _x)
    {
        Eigen::Map<Eigen::MatrixXf> A(_A, rowsA, colsA);
        Eigen::Map<Eigen::MatrixXf> x(_x, colsA, 1);
        Eigen::Map<Eigen::MatrixXf> b(_b, rowsA, 1);
        x = A.template jacobiSvd<Eigen::ComputeThinU | Eigen::ComputeThinV>().solve(b);
    }
}