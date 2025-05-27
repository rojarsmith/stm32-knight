#include <gui/common/Resolution.hpp>
#include <touchgfx/hal/HAL.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

int16_t Resolution::getScaledY(int16_t height)
{
    // 800x480
    return height + 80;
}

int16_t Resolution::getUnscaledY(int16_t height)
{
    // 640x480
    return height - 80;
}

int16_t Resolution::getScaledYMax()
{
    // Portrait 4:3 480x640 @ 480x800
    return 640;
}
