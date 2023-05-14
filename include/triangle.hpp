#ifndef CPP_TRIANGLES_INTERSECTION_TRIANGLE_HPP
#define CPP_TRIANGLES_INTERSECTION_TRIANGLE_HPP

#include <vector>
#include "point.hpp"
#include "line.hpp"
#include "globals.hpp"
#include <array>
class Triangle
{
private:
    std::vector<Line> m_lines;
public:
    Triangle(const std::array<Point,triangle_points_num>& points);
    bool is_covering(const Point& point) const;
    std::vector<Line> lines() const { return m_lines; }
    std::vector<Point> get_intersection(const Triangle& other) const;
};


#endif