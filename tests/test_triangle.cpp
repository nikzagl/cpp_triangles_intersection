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

TEST(test_triangle, test_get_triangle_intersection_expected_result_point){
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

TEST(test_triangle, test_get_triangle_intersection_expected_result_empty){
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

TEST(test_triangle, test_get_triangle_intersection_expected_result_line){
    Point p1{0, 0};
    Point p2{0, 1};
    Point p3{1, 0};
    Triangle t1{std::array<Point, triangle_points_num>{p1, p2, p3}};

    Point p1_{0, 1};
    Point p2_{1, 0};
    Point p3_{1, 1};

    Triangle t2{std::array<Point, triangle_points_num>{p1_, p2_, p3_}};
    auto res = get_triangle_intersection(t1, t2);
    ASSERT_EQ(res[0].x, 0);
    ASSERT_EQ(res[0].y, 1);
    ASSERT_EQ(res[1].x, 1);
    ASSERT_EQ(res[1].y, 0);
}

TEST(test_triangle, test_get_triangle_intersection_expected_result_3){
    Point p1{0, 0};
    Point p2{0, 2};
    Point p3{2, 0};
    Triangle t1{std::array<Point, triangle_points_num>{p1, p2, p3}};

    Point p1_{1, 0};
    Point p2_{2, 0};
    Point p3_{1, 1};

    Triangle t2{std::array<Point, triangle_points_num>{p1_, p2_, p3_}};
    auto res = get_triangle_intersection(t1, t2);
    ASSERT_EQ(res[0].x, 1);
    ASSERT_EQ(res[0].y, 1);
    ASSERT_EQ(res[1].x, 2);
    ASSERT_EQ(res[1].y, 0);
    ASSERT_EQ(res[2].x, 1);
    ASSERT_EQ(res[2].y, 0);
}

TEST(test_triangle, test_get_triangle_intersection_expected_result_4){
    Point p1{0, 0};
    Point p2{0, 5};
    Point p3{5, 0};
    Triangle t1{std::array<Point, triangle_points_num>{p1, p2, p3}};

    Point p1_{4, 0};
    Point p2_{2, 0};
    Point p3_{5, 5};

    Triangle t2{std::array<Point, triangle_points_num>{p1_, p2_, p3_}};
    auto res = get_triangle_intersection(t1, t2);
    ASSERT_DOUBLE_EQ(res[0].x, 3.125);
    ASSERT_DOUBLE_EQ(res[0].y, 1.875);
    ASSERT_DOUBLE_EQ(res[1].x, 4);
    ASSERT_DOUBLE_EQ(res[1].y, 0);
    ASSERT_DOUBLE_EQ(res[2].x, 2);
    ASSERT_DOUBLE_EQ(res[2].y, 0);
    ASSERT_DOUBLE_EQ(res[3].x, 4.166666666666667);
    ASSERT_DOUBLE_EQ(res[3].y, 0.83333333333333326);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}