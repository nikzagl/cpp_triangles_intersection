//
// Created by home on 20.04.23.
//
#ifndef CPP_TRIANGLES_INTERSECTION_GEOMETRY_HPP
#define CPP_TRIANGLES_INTERSECTION_GEOMETRY_HPP

#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include "point.hpp"
#include "line.hpp"
#include "matrix.hpp"
#include "triangle.hpp"
#include "globals.hpp"

bool is_approximately_equal(Point first_point, Point second_point);
void sort_points(std::vector<Point>& points, const Point& pivot);
double skew_product(Point first_vector, Point second_vector);
double angle_with_x_axis(Point first_point, Point second_point);

struct Intersection
{
    Point point{0,0};
    bool is_defined = false;
};

#endif //CPP_TRIANGLES_INTERSECTION_GEOMETRY_H
