#include <gtest/gtest.h>
#include "../include/globals.hpp"
#include "../include/line.hpp"
TEST(test_line, test_coordinate_view_expected_result) {
    Point first_point{3.0, 1.0};
    Point second_point{4.0, 2.0};
    Line line(first_point, second_point);
    double t = 3.45;
    Point result = line.coordinate_view(t);
    ASSERT_NEAR(result.get_x(), first_point.get_x() * t + second_point.get_x() * (1 - t), result_max_error);
    ASSERT_NEAR(result.get_y(), first_point.get_y() * t + second_point.get_y() * (1 - t), result_max_error);
}

TEST(test_line, test_parametric_view_expected_result) {
    Point first_point{1.0, 1.0};
    Point second_point{4.0, 2.0};
    Line line(first_point, second_point);
    Point p{3.4, 5.6};
    double result = line.parametric_view(p);
    ASSERT_NEAR(result, (p.get_x() - second_point.get_x()) / (first_point.get_x() - second_point.get_x()), result_max_error);
}

TEST(test_line, test_parametric_view_expected_result_2) {
    Point first_point{1.0, 1.0};
    Point second_point{1.00000002, 2.0};
    Line line(first_point, second_point);
    Point p{3.4, 5.6};
    double result = line.parametric_view(p);
    ASSERT_NEAR(result, (p.get_y() - second_point.get_y()) / (first_point.get_y() - second_point.get_y()),result_max_error);
}
 
TEST(test_line, get_intersection_expected_result_intersect) {
    Point p1{14.0, 33.0};
    Point p2{130.0, 53.0};

    Line l1(p1, p2);

    Point p1_{132.0, 3.0};
    Point p2_{102.0, 253.0};

    Line l2(p1_, p2_);

    auto p = l1.intersect(l2).value();
    ASSERT_NEAR(p.get_x(), 126.08108108108108, result_max_error);
    ASSERT_NEAR(p.get_y(),  52.324324324324323, result_max_error);
}
