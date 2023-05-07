//d
// Created by home on 20.04.23.
//
#include "geometry.h"
bool is_approximately_equal(double a, double b)
{
    return std::abs(a - b) <= max_error;
}
Point get_vector(Point first_point, Point second_point)
{
    return Point{second_point.x - first_point.x, second_point.y - first_point.y};
}
double distance(Point first_point, Point second_point)
{
    return std::sqrt(std::pow(first_point.x - second_point.x, 2) + std::pow(first_point.y - second_point.y, 2));
}
bool is_approximately_equal(Point first_point, Point second_point)
{
    return is_approximately_equal(first_point.x, second_point.x) && is_approximately_equal(first_point.y, second_point.y);
}
Matrix_2_2::Matrix_2_2(double a_11, double a_12, double a_21, double a_22)
{
    matrix = std::array<std::array<double,2>, 2>{{{a_11, a_12}, {a_21, a_22}}};
}
double Matrix_2_2::determinant()
{
    return matrix[0][0] * matrix[1][1] - matrix[1][0]*matrix[0][1];
}
Point Matrix_2_2::solve_linear_system(Point b)
{
    std::array<std::array<double, 2>, 2> delta_x = matrix;
    std::array<std::array<double,2>, 2> delta_y = matrix;
    delta_x[0][0] = b.x;
    delta_x[1][0] = b.y;
    delta_y[0][1] = b.x;
    delta_y[1][1] = b.y;
    Point result{0,0};
    result.x = Matrix_2_2(delta_x).determinant()/determinant();
    result.y = Matrix_2_2(delta_y).determinant()/determinant();
    return result;
}



double skew_product(Point first_vector, Point second_vector)
{
    Matrix_2_2 vector_matrix(first_vector.x, first_vector.y,second_vector.x, second_vector.y);
    return vector_matrix.determinant();
}
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
double angle_with_x_axis(Point first_point, Point second_point)
{
    Point line_vector = get_vector(first_point, second_point);
    return atan(line_vector.y / line_vector.x);
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
Triangle::Triangle(const std::array<Point, triangle_points_number> &points)
{
    for (int line_index = 0; line_index <triangle_points_number; line_index++)
    {
        lines.emplace_back(points[line_index], points[(line_index+1)%triangle_points_number]);
    }
}
bool Triangle::is_covering(Point point) const {
    bool is_all_non_negative = true;
    bool is_all_non_positive = true;
    double curr_skew_product = 0;
    for (int i = 0; i < triangle_points_number; i++)
    {
        curr_skew_product = lines[i].skew_product_from_dot_to_line(point);
        if (curr_skew_product < 0)
        {
            is_all_non_positive = false;
        }
        if (curr_skew_product > 0)
        {
            is_all_non_negative = false;
        }
    }
    return is_all_non_negative || is_all_non_positive;
}
bool compare_points_through_angle(Point first_point, Point second_point, Point pivot)
{
    double first_angle = angle_with_x_axis(first_point, pivot);
    double second_angle = angle_with_x_axis(second_point, pivot);
    if (is_approximately_equal(first_angle, second_angle))
    {
        return distance(first_point,pivot) < distance(second_point, pivot);
    }
    return first_angle < second_angle;
}
void sort_points(std::vector<Point>& points, const Point& pivot)
{
    std::sort(points.begin(), points.end(),
              [&](const Point& a, const Point& b) {
                  return compare_points_through_angle(a, b, pivot);
    });
}
std::vector<Point> get_triangle_intersection(const Triangle& triangle_1, const Triangle& triangle_2)
{
    std::vector<Point> points;
    std::vector<Line> triangle_1_lines = triangle_1.get_lines();
    std::vector<Line> triangle_2_lines = triangle_2.get_lines();
    for (const Line& line: triangle_1_lines)
    {
        if (triangle_2.is_covering(line.first_point()))
        {
            points.push_back(line.first_point());
        }
    }
    for (const Line& line: triangle_2_lines)
    {
        if (triangle_1.is_covering(line.first_point()))
        {
            points.push_back(line.first_point());
        }
    }
    Intersection curr_intersection;
    for (int i = 0; i <= triangle_points_number; i++) {
        for (int j = 0; j <= triangle_points_number; j++)
        {
            curr_intersection = triangle_1_lines[i].get_intersection(triangle_2_lines[j]);
            if (curr_intersection.is_defined)
            {
                points.push_back(curr_intersection.point);
            }
        }
    }
    Point pivot = points[0];
    for (Point & point : points) {
        if (point.y < pivot.y || (point.y == pivot.y && point.x < pivot.x))
        {
            pivot = point;
        }
    }
    sort_points(points, pivot);
    return points;
}