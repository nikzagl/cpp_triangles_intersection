#include "misc.hpp"
#include <cmath>

bool numbers_comparison::is_approximately_equal(float a, float b)
{
    return std::abs(a - b) <= max_error;
}
