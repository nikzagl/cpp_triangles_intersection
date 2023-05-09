#include <iostream>
#include <cstdio>
#include "geometry.hpp"


int main() {
    std::array<Point, 3> points_1 = {{{0,0},{2,2},{4,0}}};
    std::array<Point, 3> points_2 = {{{-2, 2},{2, 2},{2, -2}}};
    Triangle tr1 = Triangle(points_1);
    Triangle tr2 = Triangle(points_2);
    for(Point point: get_triangle_intersection(tr1, tr2))
    {
        printf("x: %2.5f, y %2.5f\n", point.x, point.y);
    }
    return 0;
}
