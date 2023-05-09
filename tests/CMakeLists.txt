cmake_minimum_required(VERSION 3.10)

project(tests)
set(CMAKE_CXX_STANDARD 17)
set(BINARY ${CMAKE_PROJECT_NAME}_tst)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/bc860af08783b8113005ca7697da5f5d49a8056f.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        test_geometry
        test_geometry.cpp
        test_line
        test_line.cpp
        test_matrix
        test_matrix.cpp
        test_triangle
        test_triangle.cpp
)

target_link_libraries(
        test_geometry test_line test_matrix test_triangle gtest
)

include(GoogleTest)
gtest_discover_tests(test_geometry test_line test_matrix test_triangle)