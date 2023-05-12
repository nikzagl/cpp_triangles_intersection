#ifndef CPP_TRIANGLES_INTERSECTION_POINT_HPP
#define CPP_TRIANGLES_INTERSECTION_POINT_HPP

#include <cmath>
#include <vector>
#include "globals.hpp"
typedef struct CoordinatePair
{
    double x, y;

}Point, Vector2d;
struct compare_points {
    bool operator()(const Point & a, const Point & b) {
        return ( a.x<b.x && a.y<b.y );
    }
};



Vector2d get_vector(const Point& first_point, const Point& second_point);
double distance(const Point& first_point, const Point& second_point);
bool compare_points(const Point& first_point, const Point& second_point, const Point& pivot);
double skew_product(const Point& first_vector, const Point& second_vector);
void sort_points(std::vector<Point>& points, const Point& pivot);
bool is_approximately_equal(const Point& first_point, const Point& second_point);
#endif