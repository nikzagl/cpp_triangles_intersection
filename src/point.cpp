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

float Point::length() const
{
    return std::sqrt(std::pow(m_x,2) + std::pow(m_y,2));
}

float Point::skew_product(const Point& other) const
{
    return m_x*other.m_y - m_y*other.m_x;
}

float Point::dot_product(const Point& other) const
{
    return m_x*other.m_x + m_y*other.m_y;
}

float Point::get_angle(const Point& other) const
{
    float len = length();
    float len_other = other.length();
    if(numbers_comparison::is_approximately_equal(len,0.0) || numbers_comparison::is_approximately_equal(len_other,0.0))
        return 0.0;
    float _sin = -std::max(-1.0f,std::min(1.0f,skew_product(other)/length()/other.length()));
    float _cos = std::max(-1.0f,std::min(1.0f,dot_product(other)/length()/other.length()));
    float angle_ambig = acos(_cos);

    return _sin > 0 ? angle_ambig : 2*M_PI - angle_ambig;

}

float Point::get_tan() const
{
    return m_y/m_x;
}

float Point::get_ctan() const
{
    return m_x/m_y;
}
