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
    [[nodiscard]] Point make_vector(bool reversed = false) const;
    float length();
    [[nodiscard]] Point get_first_point() const;
    [[nodiscard]] Point get_second_point() const;
    [[nodiscard]] Point coordinate_view(float t) const;
    [[nodiscard]] float parametric_view(const Point& point) const;
    [[nodiscard]] std::optional<Point> intersect(const Line& other_line) const;
    [[nodiscard]] float skew_product_with_point(const Point& point) const;
    float angle_with_x_axis() const;

};

#endif