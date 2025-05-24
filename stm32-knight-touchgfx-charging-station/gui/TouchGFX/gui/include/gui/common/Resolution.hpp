#ifndef RESOLUTION_HPP
#define RESOLUTION_HPP
#include <touchgfx/hal/Types.hpp>

using namespace touchgfx;

class Resolution
{
public:
    int16_t getScaledY(int16_t height);
    int16_t getScaledYMax();
};

#endif // RESOLUTION_HPP
