#ifndef CPP_TRIANGLES_INTERSECTION_LINE_HPP
#define CPP_TRIANGLES_INTERSECTION_LINE_HPP

#include "point.hpp"
#include "matrix.hpp"
#include "misc.hpp"

class Line
{
private:
    Point m_first_point;
    Point m_second_point;
public:
    Line(Point first_point, Point second_point);
    Point first_point() const;
    Point second_point() const;
    Point coordinate_view(double t) const;
    double parametric_view(Point point) const;
    Intersection get_intersection(const Line& other_line);
    double skew_product_from_dot_to_line(Point point) const;
};

#endif