cmake_minimum_required(VERSION 3.16)

project(cpp_triangles_intersection)

set(CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_subdirectory(glfw)

#imgui
set(IMGUI_INCLUDE_DIR imgui)

file(GLOB IMGUI_SOURCES imgui/*.cpp)
file(GLOB IMGUI_HEADERS imgui/*.h)

set(IMGUI_BACKENDS_DIR imgui/backends)
set(IMGUI_BACKEND_SOURCES
        ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp)
set(IMGUI_BACKEND_HEADERS
        ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.h
        ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.h)

add_library(imgui STATIC
        ${IMGUI_SOURCES} ${IMGUI_HEADERS}
        ${IMGUI_BACKEND_HEADERS} ${IMGUI_BACKEND_SOURCES})

set(GLFW_INCLUDE_DIR glfw/include/GLFW)
set(GLAD_INCLUDE_DIR glfw/deps/glad)

target_include_directories(imgui PUBLIC
        ${IMGUI_INCLUDE_DIR}
        ${IMGUI_BACKENDS_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR})

target_link_libraries(imgui
        ${OPENGL_LIBRARIES}
        glfw
        )

set(INCLUDE_DIR include)

file(GLOB SOURCES src/*.cpp)

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC ${INCLUDE_DIR})

target_link_libraries(main ${OPENGL_LIBRARIES} glfw imgui)