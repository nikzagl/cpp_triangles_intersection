cmake_minimum_required(VERSION 3.10)

project(tests_tst)
set(CMAKE_CXX_STANDARD 17)

# используем C++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# включаем CTest
enable_testing()

# в качестве фреймворка для тестирования используем GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# исполняемый файл тестов
set(TEST_SOURCES  test.cpp test_triangle.cpp test_line.cpp test_geometry.cpp test_matrix.cpp)
add_executable(test_tst ${TEST_SOURCES})
target_link_libraries(test_tst ${GTEST_LIBRARIES} pthread)