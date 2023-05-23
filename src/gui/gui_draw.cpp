#include "gui.hpp"

void UserInterface::draw_buttons_set_mode()
{
    std::string button1_msg = draw_mode_1 ? "Discard" : m_tr1.verices_num > 0 ? "Redraw polygon 1" : "Draw polygon 1";
    std::string button2_msg = draw_mode_2 ? "Discard" : m_tr2.verices_num > 0 ? "Redraw polygon 2" : "Draw polygon 2";
    if(ImGui::Button(button1_msg.c_str()))
    {
        if(draw_mode_1)
        {
            m_tr1.verices_num = -1;
            draw_mode_1 = false;
        }
        else
        {
            m_tr1.verices_num = v1;
            draw_mode_1 = true;
        }
        draw_mode_2 = false;
        m_tr1.points.clear();
    
        if(!m_tr2.is_completed())
            m_tr2.points.clear();
    }
    else if(ImGui::Button(button2_msg.c_str()))
    {
        if(draw_mode_2)
        {
            m_tr2.verices_num = -1;
            draw_mode_2 = false;
        }
        else
        {
            m_tr2.verices_num = v2;
            draw_mode_2 = true;
        }
        draw_mode_1 = false;
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

void UserInterface::draw_valid_vertices_area(bool poly_num)
{
    if(!(!poly_num && draw_mode_1 || poly_num && draw_mode_2))
        return;
    polygon& target_poly = poly_num ? m_tr2 : m_tr1;
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if(target_poly.points.size() < 2)
    {
        int width,height;
        glfwGetFramebufferSize(window,&width,&height);
        draw_list->AddRectFilled(ImVec2(0,0),ImVec2(width,height),ImGui::ColorConvertFloat4ToU32(valid_vertices_area_color));
    }
    else
    {
        float remaining_angles_sum = (180*(target_poly.verices_num-2)-target_poly.angles_sum);
        int remaining_angles_num = target_poly.verices_num-target_poly.points.size()+2;
        float angle = remaining_angles_sum - M_PI*remaining_angles_num;
        Line vec(
            Point(
                (target_poly.points.rbegin()+1)->x,
                (target_poly.points.rbegin()+1)->y
            ),
            Point(
                target_poly.points.back().x,
                target_poly.points.back().y
            )
        );
        std::vector<Point> area_poly = get_poly_from_vec_and_angle(vec,angle);
        std::vector<ImVec2> area_poly_im;
        std::transform(area_poly.begin(),area_poly.end(),std::back_inserter(area_poly_im),[](const Point& p) { return ImVec2(p.get_x(),p.get_y()); });
        draw_list->AddConvexPolyFilled(area_poly_im.data(),area_poly_im.size(),ImGui::ColorConvertFloat4ToU32(valid_vertices_area_color));
    }
}

void UserInterface::draw_incompleted(ImDrawList *draw_list, bool poly_num)
{
    polygon& target_poly = poly_num ? m_tr2 : m_tr1;
    target_poly.angles_sum = 0;
    for(int i(0); i < int(target_poly.points.size())-1; ++i)
        draw_list->AddLine(target_poly.points[i],target_poly.points[i+1],target_poly.color);
    for(ImVec2 p : target_poly.points)
        draw_list->AddCircleFilled(p,3.0,target_poly.color);
}

void UserInterface::draw_draw_mode_message()
{
    std::string draw_mode_message;
    draw_mode_message += "Drawing polygon ";
    draw_mode_message += draw_mode_1 ? "1 " : "2 ";
    draw_mode_message += "with " + std::to_string(draw_mode_1 ? m_tr1.verices_num : m_tr2.verices_num) + " vertices";
    ImGui::Text(draw_mode_message.c_str());
}