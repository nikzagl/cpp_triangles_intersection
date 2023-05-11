#ifndef CPP_TRIANGLES_INTERSECTION_MATRIX_HPP
#define CPP_TRIANGLES_INTERSECTION_MATRIX_HPP

#include <array>
#include "point.hpp"

class Matrix_2_2
{
private:
    std::array<std::array<double,2>,2> matrix{{0}};
public:
    Matrix_2_2(double a_11, double a_12, double a_21, double a_22);
    explicit Matrix_2_2(const std::array<std::array<double,2>,2>& array): matrix(array){};
    double determinant();
    Point solve_linear_system(const Vector2d& b);
};

#endif