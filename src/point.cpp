#include "point.hpp"

Point::Point(float x, float y) : m_x(x), m_y(y) {}

float Point::get_x() const
{
    return m_x;
}

float Point::get_y() const
{
    return m_y;
} 

bool Point::operator==(const Point& other) const
{
    return (numbers_comparison::is_approximately_equal(m_x, other.m_x)) && (numbers_comparison::is_approximately_equal(m_y, other.m_y));
}

bool Point::operator!=(const Point& other) const
{
    return !((*this) == other);
}

bool Point::operator<(const Point& other) const
{
    if (numbers_comparison::is_approximately_equal(m_y,other.m_y))
        return m_x < other.m_x;
    return m_y < other.m_y;
}

Point Point::operator+(const Point& other) const
{
    return {m_x+other.m_x,m_y+other.m_y};
}

Point Point::operator-(const Point& other) const
{
    return {m_x-other.m_x,m_y-other.m_y};
}

Point Point::operator/(float n) const
{
    return {m_x/n,m_y/n};
}

Point Point::operator-() const
{
    return {-m_x,-m_y};
}

float Point::skew_product(const Point& other)const
{
    return get_x()*other.get_y() - get_y()*other.get_x();
}

