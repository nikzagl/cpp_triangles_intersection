#include <iostream>
#include <cstdio>
#include "geometry.hpp"
#include "desmos.hpp"

constexpr int common_line_r = 95;
constexpr int common_line_g = 91;
constexpr int common_line_b = 88;

constexpr int intersect_line_r = 192;
constexpr int intersect_line_g = 42;
constexpr int intersect_line_b = 22;


int main() {
    std::array<Point, 3> points_1 = {{{0,0},{2,2},{4,0}}};
    std::array<Point, 3> points_2 = {{{-2, 2},{2, 2},{2, -2}}};
    Triangle tr1 = Triangle(points_1);
    Triangle tr2 = Triangle(points_2);
    desmos renderer(600,800);
    for(const auto& line : tr1.get_lines())
        renderer.add_line(line,{common_line_r,common_line_g,common_line_b},2);
    for(const auto& line : tr2.get_lines())
        renderer.add_line(line,{common_line_r,common_line_g,common_line_b},2);
    auto intersection_points = get_triangle_intersection(tr1, tr2);
    std::vector<Line> intersection_lines;
    for(int i = 0; i < intersection_points.size(); ++i)
    {
        Point point = intersection_points[i];
        Point point_next = intersection_points[(i+1)%intersection_points.size()];
        intersection_lines.emplace_back(point,point_next);
        renderer.add_line(*intersection_lines.rbegin(),{intersect_line_r,intersect_line_g,intersect_line_b},4);
        printf("x: %2.5f, y %2.5f\n", point.x, point.y);
    }
    renderer.render();

    return 0;
}
