#include "gui.hpp"

UserInterface::UserInterface()
{
    m_tr1.color = ImColor(0, 0, 255);
    m_tr2.color = ImColor(255, 0, 0);
    glfwSetWindowUserPointer(window,this);
    glfwSetMouseButtonCallback(window,mouse_button_callback);
}

void UserInterface::Update()
{   

    ImGui::SetNextWindowPos(ImVec2(360, 120), ImGuiCond_Once, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(500, 160), ImGuiCond_Once);

    ImGui::Begin("Hello, user!");                        
    ImGui::Text("Here you have to draw polygons point-by-point.");
    ImGui::SliderInt("Vertex num 1",&v1,min_vertices,max_vertices);
    ImGui::SliderInt("Vertex num 2",&v2,min_vertices,max_vertices);
    draw_buttons_set_mode();
    if(is_draw_mode())
        draw_draw_mode_message();

    ImDrawList *draw_list = ImGui::GetBackgroundDrawList();
    if(!m_tr1.is_completed())
        draw_incompleted(draw_list,false);
    else
        draw_list->AddConvexPolyFilled(m_tr1.points.data(),m_tr1.points.size(),m_tr1.color);

    if(!m_tr2.is_completed())
        draw_incompleted(draw_list,true);
    else
        draw_list->AddConvexPolyFilled(m_tr2.points.data(),m_tr2.points.size(),m_tr2.color);

    if(m_tr1.is_completed() && m_tr2.is_completed())
        draw_intersection();
    
    ImGui::End();
};