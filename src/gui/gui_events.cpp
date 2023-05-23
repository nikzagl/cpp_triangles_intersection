#include "gui.hpp"

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