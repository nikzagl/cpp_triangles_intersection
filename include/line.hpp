#ifndef CPP_TRIANGLES_INTERSECTION_LINE_HPP
#define CPP_TRIANGLES_INTERSECTION_LINE_HPP

#include "point.hpp"
#include "geometry.hpp"
#include "matrix.hpp"

class Line
{
    Point m_first_point;
    Point m_second_point;

public:
    Point first_point()const{return m_first_point;}
    Point second_point()const{return m_second_point;}
    Line(Point first_point, Point second_point): m_first_point(first_point), m_second_point(second_point){};
    Point coordinate_view(double t) const;
    double parametric_view(Point point) const;
    Intersection get_intersection(const Line& other_line);
    double skew_product_from_dot_to_line(Point point) const;
};

#endif