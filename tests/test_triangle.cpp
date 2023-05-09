#include <gtest/gtest.h>

#include "../include/triangle.hpp"

TEST(test_triangle, test_is_covering_expected_result){
    Point p1{0, 0};
    Point p2{0, 1};
    Point p3{1, 0};
    Triangle t1{std::array<Point, triangle_points_num>{p1, p2, p3}};

    Point p{0.5, 0.5};
    ASSERT_TRUE(t1.is_covering(p));
}

TEST(test_triangle, test_get_triangle_intersection_expected_result_1){
    Point p1{0, 0};
    Point p2{0, 1};
    Point p3{1, 0};
    Triangle t1{std::array<Point, triangle_points_num>{p1, p2, p3}};

    Point p1_{0.5, 0.5};
    Point p2_{2, 2};
    Point p3_{3, 0};
    Triangle t2{std::array<Point, triangle_points_num>{p1_, p2_, p3_}};

    auto res = get_triangle_intersection(t1, t2);
    ASSERT_TRUE(res.size() == 1);
    ASSERT_DOUBLE_EQ(res[0].x, 0.5);
    ASSERT_DOUBLE_EQ(res[0].y, 0.5);
}

TEST(test_triangle, test_get_triangle_intersection_expected_result_2){
    Point p1{0, 0};
    Point p2{0, 1};
    Point p3{1, 0};
    Triangle t1{std::array<Point, triangle_points_num>{p1, p2, p3}};

    Point p1_{5, 5};
    Point p2_{10, 10};
    Point p3_{0, 6};

    Triangle t2{std::array<Point, triangle_points_num>{p1_, p2_, p3_}};
    auto res = get_triangle_intersection(t1, t2);
    ASSERT_TRUE(res.empty());
}