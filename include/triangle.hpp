#ifndef CPP_TRIANGLES_INTERSECTION_TRIANGLE_HPP
#define CPP_TRIANGLES_INTERSECTION_TRIANGLE_HPP

#include <vector>
#include "point.hpp"
#include "line.hpp"
#include "globals.hpp"

class Triangle
{
private:
    std::vector<Line> m_lines;
public:
    Triangle(const std::array<Point,triangle_points_num>& points);
    bool is_covering(const Point& point) const;
    const std::vector<Line>& get_lines() const;
};

std::vector<Point> get_triangle_intersection(const Triangle& triangle1, const Triangle& triangle_2) ;

#endif