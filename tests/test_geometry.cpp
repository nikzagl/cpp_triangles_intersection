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
    ASSERT_TRUE(is_approximately_equal(first_point, second_point));
}