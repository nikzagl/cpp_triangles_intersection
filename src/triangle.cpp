#include "triangle.hpp"

Triangle::Triangle(const std::array<Point,TRIANGLE_POINTS_NUM> &points)
{
    for (int line_index = 0; line_index <TRIANGLE_POINTS_NUM; line_index++)
    {
        lines.emplace_back(points[line_index], points[(line_index+1)%TRIANGLE_POINTS_NUM]);
    }
}

bool Triangle::is_covering(Point point) const {
    bool is_all_non_negative = true;
    bool is_all_non_positive = true;
    double curr_skew_product = 0;
    for (int i = 0; i < TRIANGLE_POINTS_NUM; i++)
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
    for (int i = 0; i <= TRIANGLE_POINTS_NUM; i++) {
        for (int j = 0; j <= TRIANGLE_POINTS_NUM; j++)
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