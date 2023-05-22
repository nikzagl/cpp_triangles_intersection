#ifndef CPP_TRIANGLES_INTERSECTION_TRIANGLE_HPP
#define CPP_TRIANGLES_INTERSECTION_TRIANGLE_HPP

#include <vector>
#include <algorithm>
#include <array>
#include <numeric>
#include "misc.hpp"
#include "point.hpp"
#include "line.hpp"
#include "globals.hpp"

class Polygon
{
private:
    std::vector<Line> m_lines;
public:
    explicit Polygon(const std::vector<Point>& points);
    [[nodiscard]] bool is_covering(const Point& point) const;
    [[nodiscard]] std::vector<Line> get_lines() const { return m_lines; }
    [[nodiscard]] std::vector<Point> intersect(const Polygon& other) const;
};


#endif