#ifndef CPP_TRIANGLES_INTERSECTION_LINE_HPP
#define CPP_TRIANGLES_INTERSECTION_LINE_HPP

#include "point.hpp"
#include "matrix.hpp"
#include "misc.hpp"
#include <optional>
class Line
{
private:
    Point m_first_point;
    Point m_second_point;
public:
    Line(const Point& first_point, const Point& second_point);
    Point first_point() const;
    Point second_point() const;
    Point coordinate_view(double t) const;
    double parametric_view(const Point& point) const;
    std::optional<Point> get_intersection(const Line& other_line) const;
    double skew_product_with_point(const Point& point) const;
};

#endif