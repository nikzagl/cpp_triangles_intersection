#ifndef CPP_TRIANGLES_INTERSECTION_POINT_HPP
#define CPP_TRIANGLES_INTERSECTION_POINT_HPP

#include <cmath>
#include <vector>
#include "globals.hpp"

struct Point
{
    double x, y;
};

struct Intersection
{
    Point point{0,0};
    bool is_defined = false;
};


Point get_vector(Point first_point, Point second_point);
double distance(Point first_point, Point second_point);
bool compare_points_through_angle(Point first_point, Point second_point, Point pivot);
double skew_product(Point first_vector, Point second_vector);
void sort_points(std::vector<Point>& points, const Point& pivot);

#endif