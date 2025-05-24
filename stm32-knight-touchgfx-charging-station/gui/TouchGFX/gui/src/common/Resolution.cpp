#include <gui/common/Resolution.hpp>
#include <touchgfx/hal/HAL.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

int16_t Resolution::getScaledHeight(int16_t height)
{
    // 800x480
    return height + 80;
}

int16_t Resolution::getScaledHeightMax()
{
    // Portrait 4:3 480x640 @ 480x800
    return 640;
}
