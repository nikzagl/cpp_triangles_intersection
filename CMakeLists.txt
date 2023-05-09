cmake_minimum_required(VERSION 3.10)

project(MySDL2Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} include)
add_subdirectory(tests)

file(GLOB SOURCES "src/*.cpp")

add_executable(MySDL2Project ${SOURCES})
target_link_libraries(MySDL2Project ${SDL2_LIBRARIES})