#include "line.hpp"
#include <memory>
Point Line::coordinate_view(double t) const
{
    double x = m_first_point.x * t + m_second_point.x * (1 - t);
    double y = m_first_point.y * t + m_second_point.y * (1 - t);
    return Point{x,y};

}
double Line::parametric_view(const Point& point) const
{
    double t = 0;
    if (!(is_approximately_equal(m_first_point.x, m_second_point.x)))
    {
        t = (point.x - m_second_point.x) / (m_first_point.x - m_second_point.x);
    }
    else
    {
        t = (point.y - m_second_point.y) / (m_first_point.y- m_second_point.y);
    }
    return t;
}

bool in_parametric_range(double parametric_view)
{
    return (parametric_view > 0) && (parametric_view < 1);
}

std::optional<Point> Line::get_intersection(const Line &other_line) const
{
    Vector2d first_line = get_vector(m_second_point, m_first_point);
    Vector2d second_line = get_vector(other_line.m_first_point, other_line.m_second_point);
    Matrix_2_2 A = Matrix_2_2(first_line.x, second_line.x, first_line.y, second_line.y);
    Vector2d b = get_vector(m_second_point, other_line.m_second_point);
    auto intersection_parameters = Point{0,0};
    bool is_intersects = true;
    if (is_approximately_equal(A.determinant(), 0))
    {
        is_intersects = false;
    }
    intersection_parameters = A.solve_linear_system(b);
    if (!((in_parametric_range(intersection_parameters.x)) && (in_parametric_range(intersection_parameters.y))))
    {
        is_intersects = false;
    }
    Point intersection_point = (coordinate_view(intersection_parameters.x));
    std::optional<Point> result = {};
    if (is_intersects)
    {
        result = std::optional<Point>{intersection_point};
    }
    return result;
}
double Line::skew_product_with_point(const Point& point) const {
    return skew_product(get_vector(point, m_second_point), get_vector(point, m_first_point));
}

 Point Line::first_point() const { return m_first_point; }
 Point Line::second_point() const {return m_second_point; }

Line::Line(const Point& first_point, const Point& second_point) : m_first_point(first_point), m_second_point(second_point) {}
