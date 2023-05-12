#include "triangle.hpp"
#include <algorithm>
Triangle::Triangle(const std::array<Point,triangle_points_num> &points)
{
    for (int line_index = 0; line_index <triangle_points_num; line_index++)
    {
        m_lines.emplace_back(points[line_index], points[(line_index+1)%triangle_points_num]);
    }
}

const std::vector<Line>& Triangle::get_lines() const { return m_lines; }

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

        if(!is_in(points, line.first_point()) && (triangle_1.is_covering(line.first_point())))
        {
            points.push_back(line.first_point());
        }
    }
    std::optional<Point> curr_intersection;
    for (int i = 0; i <= triangle_points_num; i++) {
        for (int j = 0; j <= triangle_points_num; j++)
        {
            curr_intersection = triangle_1_lines[i].get_intersection(triangle_2_lines[j]);
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
        if (point.y < pivot.y || (point.y == pivot.y && point.x < pivot.x))
        {
            pivot = point;
        }
    }
    sort_points(points, pivot);
    return points;
}