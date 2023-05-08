//d
// Created by home on 20.04.23.
//
#include "geometry.hpp"

bool is_approximately_equal(double a, double b)
{
    return std::abs(a - b) <= MAX_ERROR;
}

double skew_product(Point first_vector, Point second_vector)
{
    Matrix_2_2 vector_matrix(first_vector.x, first_vector.y,second_vector.x, second_vector.y);
    return vector_matrix.determinant();
}
double angle_with_x_axis(Point first_point, Point second_point)
{
    Point line_vector = get_vector(first_point, second_point);
    return atan(line_vector.y / line_vector.x);
}

bool compare_points_through_angle(Point first_point, Point second_point, Point pivot)
{
    double first_angle = angle_with_x_axis(first_point, pivot);
    double second_angle = angle_with_x_axis(second_point, pivot);
    if (is_approximately_equal(first_angle, second_angle))
    {
        return distance(first_point,pivot) < distance(second_point, pivot);
    }
    return first_angle < second_angle;
}
void sort_points(std::vector<Point>& points, const Point& pivot)
{
    std::sort(points.begin(), points.end(),
              [&](const Point& a, const Point& b) {
                  return compare_points_through_angle(a, b, pivot);
    });
}
