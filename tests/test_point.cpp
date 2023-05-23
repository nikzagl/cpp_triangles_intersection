#include <gtest/gtest.h>
#include "../include/point.hpp"
#include "../include/misc.hpp"

TEST(test_point,point_angle_deg_between_points_1)
{
    Point p1(10,17);
    Point p2(6,1);
    float expect = 50.0721328725145;
    ASSERT_NEAR(expect,p1.get_angel_deg(p2),result_max_error);
}

TEST(test_point,point_angle_deg_between_points_2)
{
    Point p1(-1.78,10);
    Point p2(-8.95,-0.1);
    float expect = 360-80.5472098375415;
    ASSERT_NEAR(expect,p1.get_angel_deg(p2),result_max_error);
}

TEST(test_point,point_angle_deg_between_points_3)
{
    Point p1(0,0);
    Point p2(-8.95,-0.1);
    float expect = 0.0;
    ASSERT_NEAR(expect,p1.get_angel_deg(p2),result_max_error);
}

TEST(test_point,point_angle_deg_between_points_4)
{
    Point p1(-10.78,10);
    Point p2(-10.78,10);
    float expect = 0.0;
    float res = p1.get_angel_deg(p2);
    ASSERT_TRUE(numbers_comparison::is_approximately_equal(expect,res) || numbers_comparison::is_approximately_equal(expect,360-res));
}