#include <gtest/gtest.h>

#include "../include/polygon.hpp"
TEST(test_polygon, test_is_covering_expected_result) {
    Point p1{ 0, 0 };
    Point p2{ 0, 1 };
    Point p3{ 1, 1 };
    Point p4{ 2, 0 };
    Point p5{ 1, -1 };
    Polygon poly{ {p1, p2, p3, p4, p5} };

    Point p{ 1, 0 };
    ASSERT_TRUE(poly.is_covering(p));
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_empty) {
    Point p1{ -4, 3 };
    Point p2{ -5, 1 };
    Point p3{ -4, -2 };
    Point p4{ -2, -2 };
    Point p5{ 0, 0 };
    Point p6{ -2, 5 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ 2, 1 };
    Point p2_{ 6, 1 };
    Point p3_{ 5, -4 };
    Point p4_{ 1, 0 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };
    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.empty());
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_inside_1) {
    Point p1{ 2, 5 };
    Point p2{ 1, 4 };
    Point p3{ 0, 0 };
    Point p4{ 2, 0 };
    Point p5{ 3, 2 };
    Point p6{ 3, 4 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ 0, 0 };
    Point p2_{ 1, -2 };
    Point p3_{ 5, 2 };
    Point p4_{ 1, 7 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 6);
    ASSERT_NEAR(res[0].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[0].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[1].get_x(), 2, result_max_error);
    ASSERT_NEAR(res[1].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[2].get_x(), 3, result_max_error);
    ASSERT_NEAR(res[2].get_y(), 2, result_max_error);
    ASSERT_NEAR(res[3].get_x(), 3, result_max_error);
    ASSERT_NEAR(res[3].get_y(), 4, result_max_error);
    ASSERT_NEAR(res[4].get_x(), 2, result_max_error);
    ASSERT_NEAR(res[4].get_y(), 5, result_max_error);
    ASSERT_NEAR(res[5].get_x(), 1, result_max_error);
    ASSERT_NEAR(res[5].get_y(), 4, result_max_error);

}

TEST(test_polygon, test_get_polygon_intersection_expected_result_inside_2) {
    Point p1{ -6, 8 };
    Point p2{ -10, 2 };
    Point p3{ -10, 0 };
    Point p4{ -4, -2 };
    Point p5{ 0, 0 };
    Point p6{ 4, 6 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ -4, 6 };
    Point p2_{ 0, 4 };
    Point p3_{ -2, 2 };
    Point p4_{ -6, 2 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 4);
    ASSERT_NEAR(res[0].get_x(), -6, result_max_error);
    ASSERT_NEAR(res[0].get_y(), 2, result_max_error);
    ASSERT_NEAR(res[1].get_x(), -2, result_max_error);
    ASSERT_NEAR(res[1].get_y(), 2, result_max_error);
    ASSERT_NEAR(res[2].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[2].get_y(), 4, result_max_error);
    ASSERT_NEAR(res[3].get_x(), -4, result_max_error);
    ASSERT_NEAR(res[3].get_y(), 6, result_max_error);

}

TEST(test_polygon, test_get_polygon_intersection_expected_result_point) {
    Point p1{ 0, 0 };
    Point p2{ 0, 1 };
    Point p3{ 2, 1 };
    Point p4{ 0.5, 2 };
    Polygon poly1{ {p1, p2, p3, p4} };

    Point p1_{ 0.5, 2 };
    Point p2_{ 0, 2 };
    Point p3_{ -1, 3 };
    Polygon poly2{ {p1_, p2_, p3_} };

    auto res = poly1.intersect(poly2);
    ASSERT_TRUE(res.size() == 1);
    ASSERT_NEAR(res[0].get_x(), 0.5, result_max_error);
    ASSERT_NEAR(res[0].get_y(), 2, result_max_error);
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_line) {
    Point p1{ -4, 3 };
    Point p2{ -5, 1 };
    Point p3{ -4, -2 };
    Point p4{ -2, -2 };
    Point p5{ 0, 0 };
    Point p6{ -1, 3 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ -5, -2 };
    Point p2_{ -1, -2 };
    Point p3_{ -2, -7 };
    Point p4_{ -6, -3 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 2);
    ASSERT_NEAR(res[0].get_x(), -4, result_max_error);
    ASSERT_NEAR(res[0].get_y(), -2, result_max_error);
    ASSERT_NEAR(res[1].get_x(), -2, result_max_error);
    ASSERT_NEAR(res[1].get_y(), -2, result_max_error);
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_3) {
    Point p1{ -4, 3 };
    Point p2{ -5, 1 };
    Point p3{ -4, -2 };
    Point p4{ -2, -2 };
    Point p5{ 0, 0 };
    Point p6{ -1, 3 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ -1, 3 };
    Point p2_{ 3, 3 };
    Point p3_{ 2, -2 };
    Point p4_{ -2, 2 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 3);
    ASSERT_NEAR(res[0].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[0].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[1].get_x(), -1, result_max_error);
    ASSERT_NEAR(res[1].get_y(), 3, result_max_error);
    ASSERT_NEAR(res[2].get_x(), -2, result_max_error);
    ASSERT_NEAR(res[2].get_y(), 2, result_max_error);
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_4) {
    Point p1{ -4, 3 };
    Point p2{ -5, 1 };
    Point p3{ -4, -2 };
    Point p4{ -2, -2 };
    Point p5{ 0, 0 };
    Point p6{ -1, 3 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ -2, 0 };
    Point p2_{ 2, 0 };
    Point p3_{ 1, -5 };
    Point p4_{ -3, -1 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 4);
    ASSERT_NEAR(res[0].get_x(), -2, result_max_error);
    ASSERT_NEAR(res[0].get_y(), -2, result_max_error);
    ASSERT_NEAR(res[1].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[1].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[2].get_x(), -2, result_max_error);
    ASSERT_NEAR(res[2].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[3].get_x(), -3, result_max_error);
    ASSERT_NEAR(res[3].get_y(), -1, result_max_error);
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_5) {
    Point p1{ -4, 3 };
    Point p2{ -5, 1 };
    Point p3{ -4, -2 };
    Point p4{ -2, -2 };
    Point p5{ 0, 0 };
    Point p6{ 0, 7 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ -4, 5 };
    Point p2_{ 1, 0 };
    Point p3_{ -2, -2 };
    Point p4_{ -4, 3 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 5);
    ASSERT_NEAR(res[0].get_x(), -2, result_max_error);
    ASSERT_NEAR(res[0].get_y(), -2, result_max_error);
    ASSERT_NEAR(res[1].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[1].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[2].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[2].get_y(), 1, result_max_error);
    ASSERT_NEAR(res[3].get_x(), -3, result_max_error);
    ASSERT_NEAR(res[3].get_y(), 4, result_max_error);
    ASSERT_NEAR(res[4].get_x(), -4, result_max_error);
    ASSERT_NEAR(res[4].get_y(), 3, result_max_error);
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_6) {
    Point p1{ -1.6, 7.25 };
    Point p2{ -4, 4 };
    Point p3{ -5, 2 };
    Point p4{ -4, 0 };
    Point p5{ 0, 0 };
    Point p6{ 0, 8 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ 0, 6 };
    Point p2_{ 0, 2 };
    Point p3_{ -2, -3 };
    Point p4_{ -6, 10.8 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 6);
    ASSERT_NEAR(res[0].get_x(), -2.87, result_max_error);
    ASSERT_NEAR(res[0].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[1].get_x(), -0.8, result_max_error);
    ASSERT_NEAR(res[1].get_y(), 0, result_max_error);
    ASSERT_NEAR(res[2].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[2].get_y(), 2, result_max_error);
    ASSERT_NEAR(res[3].get_x(), 0, result_max_error);
    ASSERT_NEAR(res[3].get_y(), 6, result_max_error);
    ASSERT_NEAR(res[4].get_x(), -1.6, result_max_error);
    ASSERT_NEAR(res[4].get_y(), 7.25, result_max_error);
    ASSERT_NEAR(res[5].get_x(), -4, result_max_error);
    ASSERT_NEAR(res[5].get_y(), 4, result_max_error);
    
}

TEST(test_polygon, test_get_polygon_intersection_expected_result_8) {
    Point p1{ 2, 7 };
    Point p2{ 4, 7 };
    Point p3{ 6, 3 };
    Point p4{ 5, 1 };
    Point p5{ 0, 0 };
    Point p6{ -1, 4 };
    Polygon t1{ {p1, p2, p3, p4, p5, p6} };

    Point p1_{ 1, 7 };
    Point p2_{ -1, 2 };
    Point p3_{ 2, -1 };
    Point p4_{ 6, 6 };
    Polygon t2{ {p1_, p2_, p3_, p4_} };

    auto res = t1.intersect(t2);
    ASSERT_TRUE(res.size() == 8);
    ASSERT_NEAR(res[0].get_x(), 0.83, result_max_error);
    ASSERT_NEAR(res[0].get_y(), 0.17, result_max_error);
    ASSERT_NEAR(res[1].get_x(), 2.9, result_max_error);
    ASSERT_NEAR(res[1].get_y(), 0.58, result_max_error);
    ASSERT_NEAR(res[2].get_x(), 5.2, result_max_error);
    ASSERT_NEAR(res[2].get_y(), 4.6, result_max_error);
    ASSERT_NEAR(res[3].get_x(), 4.33, result_max_error);
    ASSERT_NEAR(res[3].get_y(), 6.33, result_max_error);
    ASSERT_NEAR(res[4].get_x(), 1.83, result_max_error);
    ASSERT_NEAR(res[4].get_y(), 6.83, result_max_error);
    ASSERT_NEAR(res[5].get_x(), 0.33, result_max_error);
    ASSERT_NEAR(res[5].get_y(), 5.33, result_max_error);
    ASSERT_NEAR(res[6].get_x(), -0.69, result_max_error);
    ASSERT_NEAR(res[6].get_y(), 2.77, result_max_error);
    ASSERT_NEAR(res[7].get_x(), -0.33, result_max_error);
    ASSERT_NEAR(res[7].get_y(), 1.33, result_max_error);
}