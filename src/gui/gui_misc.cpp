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
    float res_sin = sin(res_angle);
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

::Polygon UserInterface::get_poly_from_vec_and_angle(const Line& vec, float angle)
{
    ::Polygon display_poly({{0,0},{width,0},{width,height},{0,height}});
    Point pivot = vec.get_first_point();
    std::vector<Point> res_poly_points{vec.get_first_point()};
    Point dir_vec = vec.make_vector();
    bool is_up = dir_vec.get_y() > 0;
    bool is_right = dir_vec.get_x() > 0;
    if(dir_vec.get_x() > 0)
    {
        float second_point_y = dir_vec.get_tan()*(width-pivot.get_x());
        res_poly_points.emplace_back(width,second_point_y);
    }
    else
    {
        float second_point_y = dir_vec.get_tan()*(pivot.get_x());
        res_poly_points.emplace_back(0,second_point_y);
    }
    Point dir_vec_other = get_vec_from_angle(dir_vec,angle);
    if(dir_vec_other.get_x() > 0)
    {
        float third_point_y = dir_vec_other.get_tan()*(width-pivot.get_x());
        res_poly_points.emplace_back(width,third_point_y);
    }
    else
    {
        float third_point_y = dir_vec_other.get_tan()*(pivot.get_x());
        res_poly_points.emplace_back(0,third_point_y);
    }
    
    return ::Polygon(display_poly.intersect(::Polygon(res_poly_points)));
}