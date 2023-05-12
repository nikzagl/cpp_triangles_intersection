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

bool is_approximately_equal(const Point& first_point, const Point& second_point);

double angle_with_x_axis(const Point& first_point, const Point& second_point);

#endif //CPP_TRIANGLES_INTERSECTION_GEOMETRY_H
