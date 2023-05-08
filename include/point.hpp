#ifndef CPP_TRIANGLES_INTERSECTION_POINT_HPP
#define CPP_TRIANGLES_INTERSECTION_POINT_HPP

#include <math.h>

bool is_approximately_equal(double a, double b);

struct Point
{
    double x, y;
};

Point get_vector(Point first_point, Point second_point);
bool is_approximately_equal(Point first_point, Point second_point);
double distance(Point first_point, Point second_point);
double skew_product(Point first_vector, Point second_vector);
bool compare_points_through_angle(Point first_point, Point second_point, Point pivot);
#endif