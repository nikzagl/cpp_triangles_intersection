#include "GUI.hpp"

Window::Window()
{   
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        std::exit(1);

    #if defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    #endif

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, "Triangles intersection", NULL, NULL);
    if (window == NULL)
        std::exit(1);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

};

Window::~Window()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
};

void Window::Run()
{   
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glfwGetWindowSize(window, &width, &height);
        
        //main drawings
        Update();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    };

};

const triangle& UserInterface::Get1Triangle()
{
    return this->m_tr1;
};
const triangle& UserInterface::Get2Triangle()
{
    return this->m_tr2;
};

void UserInterface::Update()
{   

    ImGui::SetNextWindowPos(ImVec2(360, 120), ImGuiCond_Once, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(500, 80), ImGuiCond_Once);

    ImGui::Begin("Hello, user!");                        
    ImGui::Text("Here you can create 2 triangles and find their intersection.");         

    static bool show_settings1_window = false;
    static bool show_settings2_window = false;

    if (ImGui::Button("Add triangles"))
        {
            show_settings1_window = true;
            show_settings2_window = true;
        }
    if (show_settings1_window)
    {
        ImGui::SetNextWindowPos(ImVec2(50, 200), ImGuiCond_Once, ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);

        ImGui::Begin("Settings1", &show_settings1_window);
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        draw_list->AddTriangleFilled(m_tr1.point1, m_tr1.point2, m_tr1.point3, m_tr1.color);
        ImGui::Text("Coordinates:");
        ImGui::Spacing();

        ImGui::SeparatorText("1st point");
        ImGui::SliderFloat("x1", &m_tr1.point1.x, 0, width);
        ImGui::SliderFloat("y1", &m_tr1.point1.y, 0, height);

        ImGui::SeparatorText("2nd point");
        ImGui::SliderFloat("x2", &m_tr1.point2.x, 0, width);
        ImGui::SliderFloat("y2", &m_tr1.point2.y, 0, height);

        ImGui::SeparatorText("3rd point");
        ImGui::SliderFloat("x3", &m_tr1.point3.x, 0, width);
        ImGui::SliderFloat("y3", &m_tr1.point3.y, 0, height);

        ImGui::End();
    };

    if (show_settings2_window)
    {
        m_tr2.color = ImColor(255, 0, 0);
        ImGui::SetNextWindowPos(ImVec2(1000, 200), ImGuiCond_Once, ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);

        ImGui::Begin("Settings2", &show_settings2_window);
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList(); 
        draw_list->AddTriangleFilled(m_tr2.point1, m_tr2.point2, m_tr2.point3, m_tr2.color);
        ImGui::Text("Coordinates:");
        ImGui::Spacing();

        ImGui::SeparatorText("1st point");
        ImGui::SliderFloat("x1", &m_tr2.point1.x, 0, width);
        ImGui::SliderFloat("y1", &m_tr2.point1.y, 0, height);

        ImGui::SeparatorText("2nd point");
        ImGui::SliderFloat("x2", &m_tr2.point2.x, 0, width);
        ImGui::SliderFloat("y2", &m_tr2.point2.y, 0, height);

        ImGui::SeparatorText("3rd point");
        ImGui::SliderFloat("x3", &m_tr2.point3.x, 0, width);
        ImGui::SliderFloat("y3", &m_tr2.point3.y, 0, height);

        ImGui::End();
    }

    if (show_settings1_window && show_settings2_window)
    {
        std::vector<Point> points_1 = {{{m_tr1.point1.x,m_tr1.point1.y},{m_tr1.point2.x,m_tr1.point2.y},{m_tr1.point3.x,m_tr1.point3.y}}};
        std::vector<Point> points_2 = {{{m_tr2.point1.x,m_tr2.point1.y},{m_tr2.point2.x,m_tr2.point2.y},{m_tr2.point3.x,m_tr2.point3.y}}};
        Polygon tr1 = Polygon(points_1);
        Polygon tr2 = Polygon(points_2);

        auto intersection_points = tr1.intersect(tr2);

        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

        for(int i = 0; i < intersection_points.size(); ++i)
        {
            Point point = intersection_points[i];
            Point point_next = intersection_points[(i+1)%intersection_points.size()];
            draw_list->AddLine(ImVec2(point.get_x(),point.get_y()),ImVec2(point_next.get_x(),point_next.get_y()),ImColor(255, 255, 102), 3);
        }
    }

    ImGui::End();
    
};