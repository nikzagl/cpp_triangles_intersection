#ifndef GUI
#define GUI

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h" // Will drag system OpenGL headers
#include "polygon.hpp"
#include "imgui_internal.h"
#include <stdio.h>
#include <iostream>
#include <array>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

class Window{
protected:
    GLFWwindow* window;
    const int height,width;
    static constexpr ImVec4 clear_color{0.45f, 0.55f, 0.60f, 1.00f};
public:

    Window(int width=1280, int height=720);

    ~Window();
    
    void Run();

    virtual void Update() = 0;
};

class UserInterface : public Window
{
private:
    static constexpr int min_vertices = 3;
    static constexpr int max_vertices = 10;

    struct polygon
    {
        std::vector<ImVec2> points;
        int verices_num{-1};
        bool skew_sign;
        ImColor color;

        bool is_completed() const;
    };

    polygon m_tr1, m_tr2;
    int v1{min_vertices},v2{min_vertices};
    bool draw_mode_1{false},draw_mode_2{false};

    void __mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    void draw_buttons_set_mode();
    void draw_intersection();
    void draw_incompleted(ImDrawList *draw_list, bool poly_num);
    bool is_draw_mode() const;
public:
    UserInterface();
    ~UserInterface() = default;

    virtual void Update() final;

    polygon Get1Triangle();
    polygon Get2Triangle();
};
#endif