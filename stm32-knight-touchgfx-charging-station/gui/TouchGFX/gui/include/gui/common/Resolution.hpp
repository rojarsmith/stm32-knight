#ifndef RESOLUTION_HPP
#define RESOLUTION_HPP
#include <touchgfx/hal/Types.hpp>

using namespace touchgfx;

// Original resolution  : Portrait 1024x768 4:3
// STM32H747I Discovery : Portrait  640x480 4:3
class Resolution
{
public:

    int16_t getScaledY(int16_t height);
    int16_t getScaledYMax();
};

#endif // RESOLUTION_HPP
