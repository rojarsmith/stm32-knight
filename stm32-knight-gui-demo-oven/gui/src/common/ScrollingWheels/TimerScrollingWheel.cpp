#include <gui/common/ScrollingWheels/TimerScrollingWheel.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include  <BitmapDatabase.hpp>

TimerScrollingWheelHour::TimerScrollingWheelHour() : ScrollingWheel()

{
    background.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_SMALL_BACKGROUND_LEFT_ID));

    backgroundScrollingMenu.setXY(background.getX() + 10, background.getY() + 10);
    backgroundScrollingMenu.setup(
        false,              //horizontal
        false,              //isCircular
        154,                //width
        108,                //height
        40,                 //selectedItemOffset
        36,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        backgroundScrollingMenuItems.getElementCallback,
        initializeBackgroundScrollingMenuItemCallback);
    backgroundScrollingMenu.setSwipeAcceleration(60);

    shadowOverlay.setXY(0, 0);
    shadowOverlay.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_SMALL_OVERLAY_LEFT_ID));

    centerScrollingMenu.setXY(backgroundScrollingMenu.getX(), shadowOverlay.getY() + 46);
    centerScrollingMenu.setup(
        false,              //horizontal
        false,              //isCircular
        154,                //width
        38,                 //height
        4,                  //selectedItemOffset
        36,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        centerScrollingMenuItems.getElementCallback,
        initializeCenterScrollingMenuItemCallback);
    centerScrollingMenu.setSwipeAcceleration(60);

    setup();

    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        backgroundScrollingMenuItems.element[i].setWidth(154);
        backgroundScrollingMenuItems.element[i].setHeight(36);
        backgroundScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        backgroundScrollingMenuItems.element[i].setTypedText(TypedText(T_TIMER_HOUR));

        centerScrollingMenuItems.element[i].setWidth(154);
        centerScrollingMenuItems.element[i].setHeight(36);
        centerScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        centerScrollingMenuItems.element[i].setTypedText(TypedText(T_TIMER_HOUR));
    }
}

void TimerScrollingWheelHour::initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(backgroundScrollingMenuItems.element[containerIndex].textBuffer,
        backgroundScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%02i", 10 - itemIndex);
}

void TimerScrollingWheelHour::initializeCenterScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(centerScrollingMenuItems.element[containerIndex].textBuffer,
        centerScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%02i", 10 - itemIndex);
}

TimerScrollingWheelMinute::TimerScrollingWheelMinute() : ScrollingWheel()

{
    background.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_SMALL_BACKGROUND_CENTER_ID));

    backgroundScrollingMenu.setXY(background.getX() + 10, background.getY() + 10);
    backgroundScrollingMenu.setup(
        false,              //horizontal
        true,               //isCircular
        154,                //width
        108,                //height
        40,                 //selectedItemOffset
        36,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        backgroundScrollingMenuItems.getElementCallback,
        initializeBackgroundScrollingMenuItemCallback);
    backgroundScrollingMenu.setSwipeAcceleration(60);

    shadowOverlay.setXY(0, 0);
    shadowOverlay.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_SMALL_OVERLAY_CENTER_ID));

    centerScrollingMenu.setXY(backgroundScrollingMenu.getX(), shadowOverlay.getY() + 46);
    centerScrollingMenu.setup(
        false,              //horizontal
        true,               //isCircular
        154,                //width
        38,                 //height
        4,                  //selectedItemOffset
        36,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        centerScrollingMenuItems.getElementCallback,
        initializeCenterScrollingMenuItemCallback);
    centerScrollingMenu.setSwipeAcceleration(60);

    setup();

    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        backgroundScrollingMenuItems.element[i].setWidth(154);
        backgroundScrollingMenuItems.element[i].setHeight(36);
        backgroundScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        backgroundScrollingMenuItems.element[i].setTypedText(TypedText(T_TIMER_MIN));

        centerScrollingMenuItems.element[i].setWidth(154);
        centerScrollingMenuItems.element[i].setHeight(36);
        centerScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        centerScrollingMenuItems.element[i].setTypedText(TypedText(T_TIMER_MIN));
    }
}

void TimerScrollingWheelMinute::initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(backgroundScrollingMenuItems.element[containerIndex].textBuffer,
        backgroundScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%02i", 59 - itemIndex);
}

void TimerScrollingWheelMinute::initializeCenterScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(centerScrollingMenuItems.element[containerIndex].textBuffer,
        centerScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%02i", 59 - itemIndex);
}

TimerScrollingWheelSecond::TimerScrollingWheelSecond() : ScrollingWheel()

{
    background.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_SMALL_BACKGROUND_RIGHT_ID));

    backgroundScrollingMenu.setXY(background.getX() + 10, background.getY() + 10);
    backgroundScrollingMenu.setup(
        false,              //horizontal
        true,               //isCircular
        154,                //width
        108,                //height
        40,                 //selectedItemOffset
        36,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        backgroundScrollingMenuItems.getElementCallback,
        initializeBackgroundScrollingMenuItemCallback);
    backgroundScrollingMenu.setSwipeAcceleration(60);

    shadowOverlay.setXY(0, 0);
    shadowOverlay.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_SMALL_OVERLAY_RIGHT_ID));

    centerScrollingMenu.setXY(backgroundScrollingMenu.getX(), shadowOverlay.getY() + 46);
    centerScrollingMenu.setup(
        false,              //horizontal
        true,               //isCircular
        154,                //width
        38,                 //height
        4,                  //selectedItemOffset
        36,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        centerScrollingMenuItems.getElementCallback,
        initializeCenterScrollingMenuItemCallback);
    centerScrollingMenu.setSwipeAcceleration(60);

    setup();

    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        backgroundScrollingMenuItems.element[i].setWidth(154);
        backgroundScrollingMenuItems.element[i].setHeight(36);
        backgroundScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        backgroundScrollingMenuItems.element[i].setTypedText(TypedText(T_TIMER_SECOND));

        centerScrollingMenuItems.element[i].setWidth(154);
        centerScrollingMenuItems.element[i].setHeight(36);
        centerScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        centerScrollingMenuItems.element[i].setTypedText(TypedText(T_TIMER_SECOND));
    }
}

void TimerScrollingWheelSecond::initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(backgroundScrollingMenuItems.element[containerIndex].textBuffer,
        backgroundScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%02i", 50 - (itemIndex * 10));
}

void TimerScrollingWheelSecond::initializeCenterScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(centerScrollingMenuItems.element[containerIndex].textBuffer,
        centerScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%02i", 50 - (itemIndex * 10));
}

TimerScrollingWheel::TimerScrollingWheel()

{
    hourScrollingWheel.setXY(0, 0);
    add(hourScrollingWheel);

    minuteScrollingWheel.setXY(hourScrollingWheel.getRect().right(), 0);
    add(minuteScrollingWheel);

    secondScrollingWheel.setXY(minuteScrollingWheel.getRect().right(), 0);
    add(secondScrollingWheel);

    setWidth(secondScrollingWheel.getRect().right());
    setHeight(hourScrollingWheel.getHeight());
}

void TimerScrollingWheel::setSelectedItems(uint8_t hourIndex, uint8_t minuteIndex, uint8_t secondIndex)
{
    hourIndex = MIN(hourIndex, TimerScrollingWheelHour::NUMBER_OF_ITEMS - 1);
    minuteIndex = MIN(minuteIndex, TimerScrollingWheelMinute::NUMBER_OF_ITEMS - 1);
    secondIndex = MIN(secondIndex, TimerScrollingWheelSecond::NUMBER_OF_ITEMS - 1);

    hourScrollingWheel.setSelectedItem(hourIndex);
    minuteScrollingWheel.setSelectedItem(minuteIndex);
    secondScrollingWheel.setSelectedItem(secondIndex);
}

void TimerScrollingWheel::setTouchable(bool touchable)
{
    hourScrollingWheel.setTouchable(touchable);
    minuteScrollingWheel.setTouchable(touchable);
    secondScrollingWheel.setTouchable(touchable);
}

int TimerScrollingWheel::getSelectedHour()
{
    return 10 - hourScrollingWheel.getSelectedItem();
}

int TimerScrollingWheel::getSelectedMinute()
{
    return 59 - minuteScrollingWheel.getSelectedItem();
}

int TimerScrollingWheel::getSelectedSecond()
{
    return 50 - (secondScrollingWheel.getSelectedItem() * 10);
}

int TimerScrollingWheel::getHourIndex(int hours)
{
    return 10 - hours;
}

int TimerScrollingWheel::getMinuteIndex(int minutes)
{
    return 59 - minutes;
}

int TimerScrollingWheel::getSecondIndex(int seconds)
{
    return 5 - (seconds / 10);
}

void TimerScrollingWheel::setTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    setSelectedItems(getHourIndex(hours), getMinuteIndex(minutes), getSecondIndex(seconds));
}
