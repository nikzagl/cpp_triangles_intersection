#include "GUI.hpp"
#include "geometry.hpp"

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

    std::array<Point, 3> points_1 = {{{m_tr1.point1.x,m_tr1.point1.y},{m_tr1.point2.x,m_tr1.point2.y},{m_tr1.point3.x,m_tr1.point3.y}}};
    std::array<Point, 3> points_2 = {{{m_tr2.point1.x,m_tr2.point1.y},{m_tr2.point2.x,m_tr2.point2.y},{m_tr2.point3.x,m_tr2.point3.y}}};
    Triangle tr1 = Triangle(points_1);
    Triangle tr2 = Triangle(points_2);

    auto intersection_points = get_triangle_intersection(tr1, tr2);

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

    for(int i = 0; i < intersection_points.size(); ++i)
    {
        Point point = intersection_points[i];
        Point point_next = intersection_points[(i+1)%intersection_points.size()];
        draw_list->AddLine(ImVec2(point.x,point.y),ImVec2(point_next.x,point_next.y),ImColor(255, 255, 102));
        
    }

    ImGui::End();
    
};