#ifndef CPP_TRIANGLES_INTERSECTION_POINT_HPP
#define CPP_TRIANGLES_INTERSECTION_POINT_HPP

#include <math.h>
#include "globals.hpp"

struct Point
{
    double x, y;
};

Point get_vector(Point first_point, Point second_point);
double distance(Point first_point, Point second_point);
bool compare_points_through_angle(Point first_point, Point second_point, Point pivot);

#endif