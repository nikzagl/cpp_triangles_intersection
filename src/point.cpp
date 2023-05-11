#include "point.hpp"
#include <cmath>
#include <memory>
Vector2d get_vector(const Point& first_point, const Point& second_point)
{
    double x = second_point.x - first_point.x;
    double y = second_point.y - first_point.y;
    return Vector2d {x,y};
}

double distance(const Point& first_point, const Point& second_point)
{
    return std::sqrt(std::pow(first_point.x - second_point.x, 2) + std::pow(first_point.y - second_point.y, 2));
}

bool is_approximately_equal(const Point& first_point, const Point& second_point)
{
    return distance(first_point,second_point) <= max_error;
}