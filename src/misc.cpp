#include "misc.hpp"
#include <cmath>

bool is_approximately_equal(double a, double b)
{
    return std::abs(a - b) <= max_error;
}