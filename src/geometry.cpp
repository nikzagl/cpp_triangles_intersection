//d
// Created by home on 20.04.23.
//
#include <cmath>
#include "geometry.hpp"

double skew_product(const Vector2d& first_vector, const Vector2d& second_vector)
{
    Matrix_2_2 vector_matrix(first_vector.x, first_vector.y,second_vector.x, second_vector.y);
    return vector_matrix.determinant();
}

double angle_with_x_axis(const Point& first_point, const Point& second_point)
{
    Point line_vector = get_vector(first_point, second_point);
    double angle_with_sign = atan(line_vector.y / line_vector.x);
    if (angle_with_sign >= 0) {
        return angle_with_sign;
    }
    return 2*M_PI-angle_with_sign;
}

bool compare_points(const Point& first_point, const Point& second_point, const Point& pivot)
{
    double first_angle = angle_with_x_axis(first_point, pivot);
    double second_angle = angle_with_x_axis(second_point, pivot);
    if (is_approximately_equal(first_angle, second_angle))
    {
        return distance(first_point,pivot) > distance(second_point, pivot);
    }
    return first_angle > second_angle;
}
void sort_points(std::vector<Point>& points, const Point& pivot)
{
    std::sort(points.begin(), points.end(),
              [&](const Point& a, const Point& b) {
                  return compare_points(a, b, pivot);
    });
}
