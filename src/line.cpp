#include "line.hpp"
#include "misc.hpp"
#include <memory>
Point Line::coordinate_view(float t) const
{
    float x = m_first_point.x() * t + m_second_point.x() * (1 - t);
    float y = m_first_point.y()* t + m_second_point.y() * (1 - t);
    return {x, y};

}
float Line::parametric_view(const Point& point) const
{
    float t = 0;
    if (!(numbers_comparison::is_approximately_equal(m_first_point.x(), m_second_point.x())))
    {
        t = (point.x() - m_second_point.x()) / (m_first_point.x() - m_second_point.x());
    }
    else
    {
        t = (point.y() - m_second_point.y()) / (m_first_point.y() - m_second_point.y());
    }
    return t;
}
float Line::length()
{
    return static_cast<float>(std::sqrt(std::pow(m_second_point.x() - m_first_point.x(), 2) + std::pow(m_second_point.y() - m_first_point.y(), 2)));
}
bool in_parametric_range(float parametric_view)
{
    return (parametric_view > 0) && (parametric_view < 1);
}
Point Line::get_vector(bool reversed) const
{
    float x = m_second_point.x() - m_first_point.x();
    float y = m_second_point.y() - m_first_point.y();
    if (reversed)
    {
        return {-x, -y};
    }
    return {x, y};
}
Point solve_linear_system(const std::array<std::array<float, 2>, 2>& matrix, const Point& b)
{
    float delta_x = b.x()*matrix[1][1] - matrix[0][1] * b.y();
    float delta_y = matrix[0][0]*b.y() - matrix[1][0] * b.x();
    float determinant = matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    return {delta_x/determinant, delta_y/determinant};
}
std::optional<Point> Line::get_intersection(const Line &other_line) const
{
    Point first_row = get_vector(true);
    Point second_row = other_line.get_vector();
    std::array<std::array<float, 2>, 2> A {{{first_row.x(), second_row.x()}, {first_row.y(), second_row.y()}}};
    Point b = Line(m_second_point, other_line.m_second_point).get_vector();
    auto intersection_parameters = Point{0,0};
    bool is_intersects = true;
    float determinant = A[0][0]*A[1][1] - A[0][1]*A[0][1];
    if (numbers_comparison::is_approximately_equal(determinant, 0))
    {
        is_intersects = false;
    }
    intersection_parameters = solve_linear_system(A, b);
    if ((!in_parametric_range(intersection_parameters.x()) || (!in_parametric_range(intersection_parameters.y()))))
    {
        is_intersects = false;
    }
    Point intersection_point = (coordinate_view(intersection_parameters.x()));
    std::optional<Point> result = {};
    if (is_intersects)
    {
        result = std::optional<Point>{intersection_point};
    }
    return result;
}

float Line::skew_product_with_point(const Point& point) const {
    Point first_vector = Line(point, m_second_point).get_vector();
    Point second_vector = Line(point, m_first_point).get_vector();
    return first_vector.skew_product(second_vector);
}
float Line::angle_with_x_axis() const
{
    Point line_vector = get_vector();
    return atan2(line_vector.y(), line_vector.x());
}
 Point Line::first_point() const { return m_first_point; }
 Point Line::second_point() const {return m_second_point; }

Line::Line(const Point& first_point, const Point& second_point) : m_first_point(first_point), m_second_point(second_point) {}
