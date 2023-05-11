#include "matrix.hpp"

Matrix_2_2::Matrix_2_2(double a_11, double a_12, double a_21, double a_22)
{
    matrix = std::array<std::array<double,2>, 2>{{{a_11, a_12}, {a_21, a_22}}};
}

double Matrix_2_2::determinant()
{
    return matrix[0][0] * matrix[1][1] - matrix[1][0]*matrix[0][1];
}

Point Matrix_2_2::solve_linear_system(const Vector2d& b)
{
    std::array<std::array<double, 2>, 2> delta_x = matrix;
    std::array<std::array<double,2>, 2> delta_y = matrix;
    delta_x[0][0] = b.x;
    delta_x[1][0] = b.y;
    delta_y[0][1] = b.x;
    delta_y[1][1] = b.y;
    Point result{0,0};
    result.x = Matrix_2_2(delta_x).determinant()/determinant();
    result.y = Matrix_2_2(delta_y).determinant()/determinant();
    return result;
}