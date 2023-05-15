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
    explicit Triangle(const std::array<Point,triangle_points_num>& points);
    [[nodiscard]] bool is_covering(const Point& point) const;
    [[nodiscard]] std::vector<Line> get_lines() const { return m_lines; }
    [[nodiscard]] std::vector<Point> intersect(const Triangle& other) const;
};


#endif