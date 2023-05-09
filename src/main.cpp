#include <iostream>
#include <cstdio>
#include "geometry.hpp"
#include "desmos.hpp"

constexpr int common_line_r = 95;
constexpr int common_line_g = 91;
constexpr int common_line_b = 88;


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
    renderer.render();
    for(Point point: get_triangle_intersection(tr1, tr2))
    {
        printf("x: %2.5f, y %2.5f\n", point.x, point.y);
    }
    return 0;
}
