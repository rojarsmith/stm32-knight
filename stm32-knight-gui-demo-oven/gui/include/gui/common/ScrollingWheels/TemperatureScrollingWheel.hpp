#ifndef TEMPERATURESCROLLINGWHEELSMALL_HPP
#define TEMPERATURESCROLLINGWHEELSMALL_HPP

#include <touchgfx/containers/Container.hpp>
#include <gui/common/ScrollingWheels/ScrollingWheel.hpp>
#include <gui/common/ScrollingWheels/TextAreaWithOneWildcardContainer.hpp>

using namespace touchgfx;

class TemperatureScrollingWheel : public ScrollingWheel
{
public:
    TemperatureScrollingWheel();

    static const int NUMBER_OF_ITEMS = 9;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> backgroundScrollingMenuItems;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> centerScrollingMenuItems;

    void initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex);
    void initializeCenterScrollingMenuItem(int containerIndex, int itemIndex);
};

#endif // TEMPERATURESCROLLINGWHEELSMALL_HPP
