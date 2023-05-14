#ifndef CPP_TRIANGLES_INTERSECTION_LINE_HPP
#define CPP_TRIANGLES_INTERSECTION_LINE_HPP

#include "point.hpp"
#include <optional>
class Line
{
private:
    Point m_first_point;
    Point m_second_point;
public:
    Line(const Point& first_point, const Point& second_point);
    Point get_vector(bool reversed = false) const;
    float length();
    Point first_point() const;
    Point second_point() const;
    Point coordinate_view(float t) const;
    float parametric_view(const Point& point) const;
    std::optional<Point> get_intersection(const Line& other_line) const;
    float skew_product_with_point(const Point& point) const;
    float angle_with_x_axis() const;

};

#endif