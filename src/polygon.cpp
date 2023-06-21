#include "polygon.hpp"


Polygon::Polygon(const std::vector<Point> &points)
{
    for (int line_index = 0; line_index < points.size(); line_index++)
        m_lines.emplace_back(points[line_index], points[(line_index+1)%points.size()]);
}


bool Polygon::is_covering(const Point& point) const
{
    std::vector<float> skews;
    std::transform(m_lines.begin(),m_lines.end(),std::back_inserter(skews),[point](const Line& x) { return x.skew_product_with_point(point); });
    bool sign = *std::find_if(skews.begin(),skews.end(),[](float x) { return not numbers_comparison::is_approximately_equal(x,0); }) > 0;
    return std::all_of(skews.begin(),skews.end(),[sign](float x) { return (x > 0) == sign or numbers_comparison::is_approximately_equal(x,0); });
}

bool is_in(const std::vector<Point>& points, const Point& comparing_point)
{
    auto condition = [&comparing_point](const Point& point)
            {return point == comparing_point;};
    return std::any_of(points.begin(), points.end(), condition);
}

bool compare_points(const Point& first_point, const Point& second_point, const Point& pivot)
{
    Line first_line = Line(pivot, first_point);
    Line second_line = Line(pivot, second_point);
    float first_angle = first_line.angle_with_x_axis();
    float second_angle = second_line.angle_with_x_axis();
    return first_angle < second_angle;
}

std::vector<Point> Polygon::intersect(const Polygon& other) const
{
    std::vector<Point> points;
    std::vector<Line> this_lines = get_lines();
    std::vector<Line> other_lines = other.get_lines();
    for (const Line& line: this_lines)
        if (other.is_covering(line.get_first_point()))
            points.push_back(line.get_first_point());
    for (const Line& line: other_lines)
        if(!is_in(points, line.get_first_point()) && (is_covering(line.get_first_point())))
            points.push_back(line.get_first_point());
    std::optional<Point> curr_intersection;
    for (int i = 0; i < this_lines.size(); i++)
        for (int j = 0; j < other_lines.size(); j++)
        {
            std::optional<Point> curr_intersection = this_lines[i].intersect(other_lines[j]);
            if (curr_intersection)
                points.push_back(curr_intersection.value());
        }
    Point pivot = {0,0};
    if(not points.empty())
        pivot = *std::min_element(points.begin(),points.end(),
        [](const Point& a, const Point& b)
        {
            return not numbers_comparison::is_approximately_equal(a.get_y(),b.get_y()) ? a.get_y() < b.get_y() : a.get_x() < b.get_x();
        });
    //pivot = std::accumulate(points.begin(),points.end(),pivot)/points.size();
    std::sort(points.begin(), points.end(),
              [&](const Point& a, const Point& b) {
                  return compare_points(a, b, pivot);
              });
    auto remove_first = std::unique(points.begin(),points.end(),[](const Point& a, const Point& b) { return a == b; });
    points.erase(remove_first,points.end());

    return points;
}