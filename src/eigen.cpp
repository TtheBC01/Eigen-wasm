#include <math.h>
#include <Eigen/Core>
#include <cstdio>

extern "C"
{
    float float_norm(int rows, int cols, float* data)
    {
        Eigen::Map<Eigen::MatrixXf> x(data, rows, cols);
        float myNorm = x.sum();
        printf("Number of rows: %ld\n", x.rows());
        printf("Number of cols: %ld\n", x.cols());
        printf("The value of myNorm is: %f\n", myNorm);
        printf("my matrix element: %f\n", x(0,0));
        printf("my data element: %f\n", data[0]);
        return myNorm;
    }
}