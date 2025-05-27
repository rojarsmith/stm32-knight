#ifndef TIMERSCROLLINGWHEELSMALL_HPP
#define TIMERSCROLLINGWHEELSMALL_HPP

#include <touchgfx/containers/Container.hpp>
#include <gui/common/ScrollingWheels/ScrollingWheel.hpp>
#include <gui/common/ScrollingWheels/TextAreaWithOneWildcardContainer.hpp>

using namespace touchgfx;


class TimerScrollingWheelHour : public ScrollingWheel
{
public:
    TimerScrollingWheelHour();

    static const int NUMBER_OF_ITEMS = 11;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> backgroundScrollingMenuItems;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> centerScrollingMenuItems;

    void initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex);
    void initializeCenterScrollingMenuItem(int containerIndex, int itemIndex);
};

class TimerScrollingWheelMinute : public ScrollingWheel
{
public:
    TimerScrollingWheelMinute();

    static const int NUMBER_OF_ITEMS = 60;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> backgroundScrollingMenuItems;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> centerScrollingMenuItems;

    void initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex);
    void initializeCenterScrollingMenuItem(int containerIndex, int itemIndex);
};

class TimerScrollingWheelSecond : public ScrollingWheel
{
public:
    TimerScrollingWheelSecond();

    static const int NUMBER_OF_ITEMS = 6;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> backgroundScrollingMenuItems;
    SparseContainerItems<TextAreaWithOneWildcardContainer, NUMBER_OF_ITEMS> centerScrollingMenuItems;

    void initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex);
    void initializeCenterScrollingMenuItem(int containerIndex, int itemIndex);
};

class TimerScrollingWheel : public Container
{
public:
    TimerScrollingWheel();

    void setSelectedItems(uint8_t hourIndex, uint8_t minuteIndex, uint8_t secondIndex);
    void setTouchable(bool touchable);

    int getSelectedHour();
    int getSelectedMinute();
    int getSelectedSecond();
    int getHourIndex(int hours);
    int getMinuteIndex(int minutes);
    int getSecondIndex(int seconds);


    void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
protected:

    TimerScrollingWheelHour hourScrollingWheel;
    TimerScrollingWheelMinute minuteScrollingWheel;
    TimerScrollingWheelSecond secondScrollingWheel;

};

#endif // TIMERSCROLLINGWHEELSMALL_HPP
