#include "triangle.hpp"
#include <algorithm>
#include "misc.hpp"
Triangle::Triangle(const std::array<Point,triangle_points_num> &points)
{
    for (int line_index = 0; line_index <triangle_points_num; line_index++)
    {
        m_lines.emplace_back(points[line_index], points[(line_index+1)%triangle_points_num]);
    }
}


bool Triangle::is_covering(const Point& point) const {
    bool is_all_non_negative = true;
    bool is_all_non_positive = true;
    double curr_skew_product = 0;
    for (int i = 0; i < triangle_points_num; i++)
    {
        curr_skew_product = m_lines[i].skew_product_with_point(point);
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
bool is_in(const std::vector<Point>& points, const Point& comparing_point)
{
    auto condition = [&comparing_point](const Point& point)
            {return is_approximately_equal(point, comparing_point);};
    return std::any_of(points.begin(), points.end(), condition);
}
bool compare_points(const Point& first_point, const Point& second_point, const Point& pivot)
{
    Line first_line = Line(pivot, first_point);
    Line second_line = Line(pivot, second_point);
    float first_angle = first_line.angle_with_x_axis();
    float second_angle = second_line.angle_with_x_axis();
    if (numbers_comparison::is_approximately_equal(first_angle, second_angle))
    {
        return first_line.length() < second_line.length();
    }
    return first_angle < second_angle;
}
void sort_points(std::vector<Point>& points, const Point& pivot)
{
    std::sort(points.begin(), points.end(),
              [&](const Point& a, const Point& b) {
                  return compare_points(a, b, pivot);
              });
}
std::vector<Point> Triangle::get_intersection(const Triangle& other)const
{
    std::vector<Point> points;
    std::vector<Line> this_lines = lines();
    std::vector<Line> other_lines = other.lines();
    for (const Line& line: this_lines)
    {
        if (other.is_covering(line.first_point()))
        {
            points.push_back(line.first_point());
        }
    }
    for (const Line& line: other_lines)
    {

        if(!is_in(points, line.first_point()) && (is_covering(line.first_point())))
        {
            points.push_back(line.first_point());
        }
    }
    std::optional<Point> curr_intersection;
    for (int i = 0; i <= triangle_points_num; i++) {
        for (int j = 0; j <= triangle_points_num; j++)
        {
            curr_intersection = this_lines[i].get_intersection(other_lines[j]);
            if (curr_intersection)
            {
                points.push_back(curr_intersection.value());
            }
        }
    }
    if (points.empty())
        return points;
    Point pivot = points[0];
    for (Point & point : points) {
        if ((point.y() < pivot.y()) || (numbers_comparison::is_approximately_equal(point.y(), pivot.y())&& (point.x() < pivot.x())))
        {
            pivot = Point{point};
        }
    }
    sort_points(points, pivot);
    return points;
}