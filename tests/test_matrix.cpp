#include <gtest/gtest.h>

#include "../include/matrix.hpp"

TEST(test_matrix, test_determinant_expected_result){
    Matrix_2_2 m{1.0,2.0,3.0,4.0};
    ASSERT_DOUBLE_EQ(m.determinant(), -2.0);
}

TEST(test_matrix, test_solve_linear_system_expected_result){
    Matrix_2_2 m{1.0,2.0,3.0,4.0};
    Point p{10.5, 12.3};
    Point res = m.solve_linear_system(p);
    ASSERT_DOUBLE_EQ(res.x, -8.7);
    ASSERT_DOUBLE_EQ(res.y, 9.6);
}