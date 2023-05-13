#include "point.hpp"
#include <cmath>
#include <memory>
bool is_approximately_equal(float a, float b)
{
    return std::abs(a - b) <= max_error;
}
bool Point::operator==(const Point &other) const
{
    return (is_approximately_equal(m_x, other.m_x))&&(is_approximately_equal(m_y, other.m_y));
}
bool Point::operator!=(const Point &other) const
{
    return !((*this) == other);
}
bool Point::operator<(const Point &other) const
{
    if (is_approximately_equal(m_y,other.m_y))
    {
        return m_x < other.m_x;
    }
    return m_y < other.m_y;
}
float Point::skew_product(const Point& other)const
{
    return x()*other.y() - y()*other.x();
}

