#include "point.hpp"

Point get_vector(Point first_point, Point second_point)
{
    return Point{second_point.x - first_point.x, second_point.y - first_point.y};
}

double distance(Point first_point, Point second_point)
{
    return std::sqrt(std::pow(first_point.x - second_point.x, 2) + std::pow(first_point.y - second_point.y, 2));
}

bool is_approximately_equal(Point first_point, Point second_point)
{
    return is_approximately_equal(first_point.x, second_point.x) && is_approximately_equal(first_point.y, second_point.y);
}