#ifndef CPP_TRIANGLES_INTERSECTION_POINT_HPP
#define CPP_TRIANGLES_INTERSECTION_POINT_HPP

#include <cmath>
#include <vector>
#include "misc.hpp"
#include "globals.hpp"


class Point
{
private:
    float m_x = 0;
    float m_y = 0;
public:
    Point() = default;
    Point(float x, float y);
    Point(const Point& other) = default;
    [[nodiscard]] float get_x() const;
    [[nodiscard]] float get_y() const;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    bool operator<(const Point& other) const;
    Point operator-() const;
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator/(float n) const;
    [[nodiscard]] float skew_product(const Point& other)const;

};



#endif