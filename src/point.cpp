#include "point.hpp"
#include <cmath>
#include <memory>
#include "misc.hpp"
bool Point::operator==(const Point &other) const
{
    return (numbers_comparison::is_approximately_equal(m_x, other.m_x))&&(numbers_comparison::is_approximately_equal(m_y, other.m_y));
}
bool Point::operator!=(const Point &other) const
{
    return !((*this) == other);
}
bool Point::operator<(const Point &other) const
{
    if (numbers_comparison::is_approximately_equal(m_y,other.m_y))
    {
        return m_x < other.m_x;
    }
    return m_y < other.m_y;
}
float Point::skew_product(const Point& other)const
{
    return get_x()*other.get_y() + get_y()*other.get_x();
}

