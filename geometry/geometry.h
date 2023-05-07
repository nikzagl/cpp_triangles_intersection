//
// Created by home on 20.04.23.
//
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#ifndef CPP_TRIANGLES_INTERSECTION_GEOMETRY_H
#define CPP_TRIANGLES_INTERSECTION_GEOMETRY_H
constexpr double max_error = 1e-7;
constexpr int triangle_points_number = 3;
bool is_approximately_equal(double a, double b);
struct Point
{
    double x, y;
};
struct Intersection
{
    Point point{0,0};
    bool is_defined = false;
};
double distance(Point first_point, Point second_point);
bool is_approximately_equal(Point first_point, Point second_point);
class Matrix_2_2
{
    std::array<std::array<double,2>,2> matrix{{0}};
public:
    Matrix_2_2(double a_11, double a_12, double a_21, double a_22);
    explicit Matrix_2_2(std::array<std::array<double,2>,2> array): matrix(array){};
    double determinant();
    Point solve_linear_system(Point b);
};
double skew_product(Point first_vector, Point second_vector);
class Line
{
    Point m_first_point;
    Point m_second_point;

public:
    Point first_point()const{return m_first_point;}
    Point second_point()const{return m_second_point;}
    Line(Point first_point, Point second_point): m_first_point(first_point), m_second_point(second_point){};
    Point coordinate_view(double t) const;
    double parametric_view(Point point) const;
    Intersection get_intersection(const Line& other_line);
    double skew_product_from_dot_to_line(Point point) const;
};
bool compare_points_through_angle(Point first_point, Point second_point, Point pivot);
class Triangle
{
    std::vector<Line> lines;
public:
    Triangle(const std::array<Point, triangle_points_number>& points);
    bool is_covering(Point point) const;
    const std::vector<Line> & get_lines() const {return lines;}
};

std::vector<Point> get_triangle_intersection(const Triangle& triangle1, const Triangle& triangle_2);
#endif //CPP_TRIANGLES_INTERSECTION_GEOMETRY_H
