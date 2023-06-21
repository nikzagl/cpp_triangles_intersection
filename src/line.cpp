#include "line.hpp"


Point Line::coordinate_view(float t) const
{
    float x = m_first_point.get_x() * t + m_second_point.get_x() * (1 - t);
    float y = m_first_point.get_y()* t + m_second_point.get_y() * (1 - t);
    return {x, y};

}

float Line::length()
{
    return std::sqrt(std::pow(m_second_point.get_x() - m_first_point.get_x(), 2) + std::pow(m_second_point.get_y() - m_first_point.get_y(), 2));
}


bool in_parametric_range(float parametric_view)
{
    return (parametric_view > 0) && (parametric_view < 1);
}


Point Line::make_vector() const
{
    return m_second_point-m_first_point;
}


std::optional<Point> solve_linear_system(const matrix2d& matrix, const Point& b)
{
    float determinant = matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    if (numbers_comparison::is_approximately_equal(determinant, 0))
        return std::optional<Point>();
    float delta_x = b.get_x()*matrix[1][1] - matrix[0][1] * b.get_y();
    float delta_y = matrix[0][0]*b.get_y() - matrix[1][0] * b.get_x();
    return std::optional<Point>(Point(delta_x/determinant, delta_y/determinant));
}


std::optional<Point> Line::intersect(const Line &other_line) const
{
    Point first_row = -make_vector();
    Point second_row = other_line.make_vector();
    matrix2d A;
    A[0] = {first_row.get_x(), second_row.get_x()};
    A[1] = {first_row.get_y(), second_row.get_y()};
    Point b = Line(m_second_point, other_line.m_second_point).make_vector();
    std::optional<Point> intersection_parameters = solve_linear_system(A, b);
    if (!intersection_parameters || (!in_parametric_range(intersection_parameters.value().get_x()) || (!in_parametric_range(intersection_parameters.value().get_y()))))
        return std::optional<Point>();
    
    return std::optional<Point>(coordinate_view(intersection_parameters.value().get_x()));
}

float Line::skew_product_with_point(const Point& point) const
{
    Point first_vector = m_second_point-point;
    Point second_vector = m_first_point-point;
    return first_vector.skew_product(second_vector);
}
float Line::angle_with_x_axis() const
{
    Point line_vector = make_vector();
    if(numbers_comparison::is_approximately_equal(line_vector.get_y(),0) and numbers_comparison::is_approximately_equal(line_vector.get_x(),0))
        return -M_PI;
    return atan2(line_vector.get_y(), line_vector.get_x());
}

Point Line::get_first_point() const { return m_first_point; }
Point Line::get_second_point() const { return m_second_point; }

Line::Line(const Point& first_point, const Point& second_point) : m_first_point(first_point), m_second_point(second_point) {}