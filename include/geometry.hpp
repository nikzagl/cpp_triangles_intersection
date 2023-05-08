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

constexpr double max_error = 1e-7;
constexpr int triangle_points_number = 3;
bool is_approximately_equal(double a, double b);

void sort_points(std::vector<Point>& points, const Point& pivot);

struct Intersection
{
    Point point{0,0};
    bool is_defined = false;
};

#endif //CPP_TRIANGLES_INTERSECTION_GEOMETRY_H
