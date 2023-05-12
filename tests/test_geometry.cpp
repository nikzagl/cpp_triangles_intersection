#include <gtest/gtest.h>

#include "../include/geometry.hpp"

TEST(test_geometry, is_approximately_equal_true){
    Point first_point{1.0, 1.0};
    Point second_point{1.00000001, 1.00000002};
    ASSERT_TRUE(is_approximately_equal(first_point, second_point));
}

TEST(test_geometry, is_approximately_equal_false){
    Point first_point{1.0, 1.0};
    Point second_point{2.0, 2.0};
    ASSERT_FALSE(is_approximately_equal(first_point, second_point));
}


TEST(test_geometry, angle_with_x_axis_expected_result_postive_angle){
    Point first_point{1.0, 1.0};
    Point second_point{2.0, 2.0};
    Point vector{second_point.x - first_point.x, second_point.y - first_point.y};
    ASSERT_DOUBLE_EQ(angle_with_x_axis(first_point, second_point), atan(vector.y / vector.x));
}

TEST(test_geometry, angle_with_x_axis_expected_result_negative_angle){
    Point first_point{1.0, 1.0};
    Point second_point{-1.0, 2.0};
    Point vector{second_point.x - first_point.x, second_point.y - first_point.y};
    ASSERT_DOUBLE_EQ(angle_with_x_axis(first_point, second_point), 2*M_PI-atan(vector.y / vector.x));
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}