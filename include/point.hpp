#ifndef CPP_TRIANGLES_INTERSECTION_POINT_HPP
#define CPP_TRIANGLES_INTERSECTION_POINT_HPP

#include <cmath>
#include <vector>
#include "globals.hpp"
class Point
{
    float m_x = 0;
    float m_y = 0;
public:
    Point() = default;
    Point(float x, float y):m_x(x), m_y(y){};
    Point(const Point& other) = default;
    float x() const {return m_x;} ;
    float y() const {return m_y;} ;
    bool operator == (const Point& other) const;
    bool operator != (const Point& other) const;
    bool operator < (const Point& other) const;
    float skew_product(const Point& other)const;

};



#endif