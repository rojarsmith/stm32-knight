#ifndef HUMIDITYSCROLLINGWHEELSMALL_HPP
#define HUMIDITYSCROLLINGWHEELSMALL_HPP

#include <touchgfx/containers/Container.hpp>
#include <gui/common/ScrollingWheels/ScrollingWheel.hpp>
#include <gui/common/ScrollingWheels/TextAreaWithOneWildcardContainer.hpp>

using namespace touchgfx;

class HumidityScrollingWheel : public ScrollingWheel
{
public:
    HumidityScrollingWheel();

    static const int NUMBER_OF_ITEMS = 17;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> backgroundScrollingMenuItems;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> centerScrollingMenuItems;

    void initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex);
    void initializeCenterScrollingMenuItem(int containerIndex, int itemIndex);
};

#endif // HUMIDITYSCROLLINGWHEELSMALL_HPP
