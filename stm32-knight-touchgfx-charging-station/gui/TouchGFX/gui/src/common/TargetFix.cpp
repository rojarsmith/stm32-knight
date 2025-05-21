#include <gui/common/TargetFix.hpp>
#include <touchgfx/hal/HAL.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

uint32_t TargetFix::getFixedDisplayHeight()
{
#ifndef SIMULATOR
    return getScreenWidthReal();
#endif

    return HAL::DISPLAY_HEIGHT;
}
