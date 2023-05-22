#ifndef GUI
#define GUI

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h" // Will drag system OpenGL headers
#include "polygon.hpp"
#include <stdio.h>
#include <iostream>
#include <array>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

class Window{
private:
    GLFWwindow* window;
    ImVec4 clear_color{0.45f, 0.55f, 0.60f, 1.00f};
public:

    inline static int width, height;

    Window();

    ~Window();
    
    void Run();

    virtual void Update() = 0;
};

struct triangle
{
    ImVec2 point1 = ImVec2(50, 100);
    ImVec2 point2 = ImVec2(100, 50);
    ImVec2 point3 = ImVec2(150, 100);
    ImColor color = ImColor(0, 0, 255);
};

class UserInterface : public Window
{
private:
    inline static triangle m_tr1, m_tr2;
public:
    UserInterface() = default;
    ~UserInterface() = default;

    virtual void Update() final;

    const triangle& Get1Triangle();
    const triangle& Get2Triangle();
};
#endif