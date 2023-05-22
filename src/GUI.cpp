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

bool UserInterface::polygon::is_completed() const
{
    return verices_num == points.size();
}

UserInterface::UserInterface()
{
    m_tr1.color = ImColor(0, 0, 255);
    m_tr2.color = ImColor(255, 0, 0);
    glfwSetWindowUserPointer(window,this);
    glfwSetMouseButtonCallback(window,mouse_button_callback);
}

UserInterface::polygon UserInterface::Get1Triangle()
{
    return m_tr1;
};

UserInterface::polygon UserInterface::Get2Triangle()
{
    return m_tr2;
};

bool UserInterface::is_draw_mode() const
{
    return draw_mode_1 || draw_mode_2;
}

void UserInterface::__mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if(is_draw_mode())
        {
            polygon& target_poly = draw_mode_1 ? m_tr1 : m_tr2;
            double xpos,ypos;
            glfwGetCursorPos(window,&xpos,&ypos);
            if(target_poly.points.size() > 1)
            {
                ImVec2 last = target_poly.points.back();
                ImVec2 lastlast = *(target_poly.points.rbegin()+1);
                Point last_p(last.x,last.y);
                Point lastlast_p(lastlast.x,lastlast.y);
                Point curr(xpos,ypos);
                Point curr_vec = curr-last_p;
                Point last_vec = last_p-lastlast_p;
                bool curr_skew_sign = curr_vec.skew_product(last_vec) > 0 ? true : false;
                if(target_poly.points.size() == 2)
                    target_poly.skew_sign = curr_skew_sign;
                if(target_poly.skew_sign == curr_skew_sign)
                    if(target_poly.points.size()+1 != target_poly.verices_num)
                        target_poly.points.push_back(ImVec2(xpos,ypos));
                    else
                    {
                        ImVec2 first = target_poly.points[0];
                        Point first_p(first.x,first.y);
                        last_vec = curr_vec;
                        curr_vec = first_p-curr;
                        curr_skew_sign = curr_vec.skew_product(last_vec) > 0 ? true : false;
                        if(target_poly.skew_sign == curr_skew_sign)
                            target_poly.points.push_back(ImVec2(xpos,ypos));
                    }
            }
            else
                target_poly.points.push_back(ImVec2(xpos,ypos));
            if(target_poly.points.size() == target_poly.verices_num)
                draw_mode_1 = draw_mode_2 = false;
        }
    }
}

void UserInterface::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    UserInterface *instance = static_cast<UserInterface*>(glfwGetWindowUserPointer(window));
    instance->__mouse_button_callback(window,button,action,mods);
}

void UserInterface::draw_buttons_set_mode()
{
    if(ImGui::Button("Draw polygon 1"))
    {
        draw_mode_1 = true;
        draw_mode_2 = false;
        m_tr1.points.clear();
        m_tr1.verices_num = v1;
        if(!m_tr2.is_completed())
            m_tr2.points.clear();
    }
    else if(ImGui::Button("Draw polygon 2"))
    {
        draw_mode_1 = false;
        draw_mode_2 = true;
        m_tr2.points.clear();
        m_tr2.verices_num = v2;
        if(!m_tr1.is_completed())
            m_tr1.points.clear();
    }
}

void UserInterface::draw_intersection()
{
    std::vector<Point> points1,points2;
    for(ImVec2 p : m_tr1.points)
        points1.emplace_back(p.x,p.y);
    for(ImVec2 p : m_tr2.points)
        points2.emplace_back(p.x,p.y);
    
    Polygon tr1 = Polygon(points1);
    Polygon tr2 = Polygon(points2);

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

    auto intersection_points = tr1.intersect(tr2);
    for(int i = 0; i < intersection_points.size(); ++i)
    {
        Point point = intersection_points[i];
        Point point_next = intersection_points[(i+1)%intersection_points.size()];
        draw_list->AddLine(ImVec2(point.get_x(),point.get_y()),ImVec2(point_next.get_x(),point_next.get_y()),ImColor(255, 255, 102), 3);
    }
}

void UserInterface::Update()
{   

    ImGui::SetNextWindowPos(ImVec2(360, 120), ImGuiCond_Once, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(500, 160), ImGuiCond_Once);

    ImGui::Begin("Hello, user!");                        
    ImGui::Text("Here you have to draw polygons point-by-point.");
    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, draw_mode_1);
    ImGui::SliderInt("Vertex num 1",&v1,min_vertices,max_vertices);
    ImGui::PopItemFlag();
    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, draw_mode_2);
    ImGui::SliderInt("Vertex num 2",&v2,min_vertices,max_vertices);
    ImGui::PopItemFlag();
    draw_buttons_set_mode();

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if(!m_tr1.is_completed())
        for(int i(0); i < int(m_tr1.points.size())-1; ++i)
            draw_list->AddLine(m_tr1.points[i],m_tr1.points[i+1],m_tr1.color);
    else
        draw_list->AddConvexPolyFilled(m_tr1.points.data(),m_tr1.points.size(),m_tr1.color);

    draw_list = ImGui::GetBackgroundDrawList();
    if(!m_tr2.is_completed())
        for(int i(0); i < int(m_tr2.points.size())-1; ++i)
            draw_list->AddLine(m_tr2.points[i],m_tr2.points[i+1],m_tr2.color);
    else
        draw_list->AddConvexPolyFilled(m_tr2.points.data(),m_tr2.points.size(),m_tr2.color);

    if(m_tr1.is_completed() && m_tr2.is_completed())
    {
        draw_intersection();
    }
    ImGui::End();
};