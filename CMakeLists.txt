cmake_minimum_required(VERSION 3.10)

project(cpp_triangles_intersection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} include)

file(GLOB SOURCES "src/*.cpp")

add_executable(cpp_triangles_intersection ${SOURCES})
target_link_libraries(cpp_triangles_intersection ${SDL2_LIBRARIES})