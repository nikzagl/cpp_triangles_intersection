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