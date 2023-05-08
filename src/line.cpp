#include "line.hpp"

Point Line::coordinate_view(double t) const
{
    double x = m_first_point.x * t + m_second_point.x * (1 - t);
    double y = m_first_point.y * t + m_second_point.y * (1 - t);
    return Point{x,y};

}
double Line::parametric_view(Point point) const
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

Intersection Line::get_intersection(const Line &other_line)
{
    Point first_line = get_vector(m_second_point, m_first_point);
    Point second_line = get_vector(other_line.m_first_point, other_line.m_second_point);
    Matrix_2_2 A = Matrix_2_2(first_line.x, second_line.x, first_line.y, second_line.y);
    Point b = get_vector(m_second_point, other_line.m_second_point);
    Point intersection_parameters{0,0};
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
    Point intersection_point = coordinate_view(intersection_parameters.x);
    return Intersection{intersection_point, is_intersects};
}
double Line::skew_product_from_dot_to_line(Point point) const {
    return skew_product(get_vector(point, m_second_point), get_vector(point, m_first_point));
}