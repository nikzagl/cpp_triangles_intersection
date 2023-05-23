#include "gui.hpp"

bool UserInterface::polygon::is_completed() const
{
    return verices_num == points.size();
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

Point get_vec_from_angle(const Point& anchor, float angle)
{
    Point x_axis(1,0);
    float anchor_angle = x_axis.get_angle(anchor);
    float res_angle = anchor_angle + angle;
    res_angle = res_angle > 2*M_PI ? 2*M_PI-res_angle : res_angle;
    float res_sin = -sin(res_angle);
    float res_cos = cos(res_angle);
    return Point(res_cos,res_sin);
}

void UserInterface::count_angles_sum()
{
    m_tr1.angles_sum = m_tr2.angles_sum = 0;
    for(int i(0); i < int(m_tr1.points.size())-1; ++i)
    {
        if(i > 0)
        {
            Point first_vec(m_tr1.points[i].x-m_tr1.points[i-1].x,m_tr1.points[i].y-m_tr1.points[i-1].y);
            Point second_vec(m_tr1.points[i+1].x-m_tr1.points[i].x,m_tr1.points[i+1].y-m_tr1.points[i].y);
            float angle = first_vec.get_angle(second_vec);
            angle = angle < M_PI ? M_PI-angle : angle-M_PI;
            m_tr1.angles_sum += angle;
        }
    }
    for(int i(0); i < int(m_tr2.points.size())-1; ++i)
    {
        if(i > 0)
        {
            Point first_vec(m_tr2.points[i].x-m_tr2.points[i-1].x,m_tr2.points[i].y-m_tr2.points[i-1].y);
            Point second_vec(m_tr2.points[i+1].x-m_tr2.points[i].x,m_tr2.points[i+1].y-m_tr2.points[i].y);
            float angle = first_vec.get_angle(second_vec);
            angle = angle < M_PI ? M_PI-angle : angle-M_PI;
            m_tr2.angles_sum += angle;
        }
    }
}

Point UserInterface::get_border_intersect_point(const Point& dir_vec, const Point& pivot)
{
    int width,height;
    glfwGetFramebufferSize(window,&width,&height);
    if(dir_vec.get_x() > dir_vec.get_y())
    {
        if(dir_vec.get_x() > 0)
        {
            float second_point_y = pivot.get_y() + dir_vec.get_tan()*(width-pivot.get_x());
            return Point(width,second_point_y);
        }
        else
        {
            float second_point_y = pivot.get_y() - dir_vec.get_tan()*(pivot.get_x());
            return Point(0,second_point_y);
        }
    }
    else
    {
        if(dir_vec.get_y() > 0)
        {
            float second_point_x = pivot.get_x() + dir_vec.get_ctan()*(height-pivot.get_y());
            return Point(second_point_x,height);
        }
        else
        {
            float second_point_x = pivot.get_x() - dir_vec.get_ctan()*(pivot.get_y());
            return Point(second_point_x,0);
        }
    }
}

std::vector<Point> UserInterface::get_poly_from_vec_and_angle(const Line& vec, float angle)
{
    int width,height;
    glfwGetFramebufferSize(window,&width,&height);
    width--;
    height--;
    ::Polygon display_poly({Point(0,0),Point(width,0),Point(width,height),Point(0,height)});
    Point pivot = vec.get_second_point();
    std::vector<Point> res_poly_points{pivot};
    Point dir_vec = vec.make_vector();
    dir_vec = dir_vec / dir_vec.length();
    res_poly_points.push_back(get_border_intersect_point(dir_vec,pivot));
    Point dir_vec_other = get_vec_from_angle(dir_vec,angle);
    res_poly_points.push_back(get_border_intersect_point(dir_vec_other,pivot));

    auto res_poly = display_poly.intersect(::Polygon(res_poly_points));
    
    return res_poly;
}