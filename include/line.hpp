#ifndef CPP_TRIANGLES_INTERSECTION_LINE_HPP
#define CPP_TRIANGLES_INTERSECTION_LINE_HPP

#include "point.hpp"
#include "misc.hpp"
#include <optional>
#include <array>
#include <stdexcept>

typedef std::array<std::array<float,2>,2> matrix2d;

class Line
{
private:
    Point m_first_point;
    Point m_second_point;
public:
    Line(const Point& first_point, const Point& second_point);
    [[nodiscard]] Point make_vector() const;
    [[nodiscard]] float length();
    [[nodiscard]] Point get_first_point() const;
    [[nodiscard]] Point get_second_point() const;
    [[nodiscard]] Point coordinate_view(float t) const;
    [[nodiscard]] std::optional<Point> intersect(const Line& other_line) const;
    [[nodiscard]] float skew_product_with_point(const Point& point) const;
    [[nodiscard]] float angle_with_x_axis() const;

};

#endif