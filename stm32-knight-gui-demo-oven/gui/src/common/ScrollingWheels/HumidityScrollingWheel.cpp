#include <gui/common/ScrollingWheels/HumidityScrollingWheel.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

HumidityScrollingWheel::HumidityScrollingWheel() : ScrollingWheel()

{
    background.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_BACKGROUND_ID));

    backgroundScrollingMenu.setXY(background.getX() + 17, background.getY() + 8);
    backgroundScrollingMenu.setup(
        false,              //horizontal
        false,              //isCircular
        216,                //width
        148,                //height
        58,                 //selectedItemOffset
        50,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        backgroundScrollingMenuItems.getElementCallback,
        initializeBackgroundScrollingMenuItemCallback);
    backgroundScrollingMenu.setSwipeAcceleration(60);

    shadowOverlay.setXY(0, 0);
    shadowOverlay.setBitmap(Bitmap(BITMAP_WHEEL_SELECTOR_OVERLAY_ID));

    centerScrollingMenu.setXY(backgroundScrollingMenu.getX(), shadowOverlay.getY() + 53);
    centerScrollingMenu.setup(
        false,              //horizontal
        false,              //isCircular
        216,                //width
        57,                 //height
        8,                  //selectedItemOffset
        50,                 //containerSize
        0,                  //containerSpacing
        NUMBER_OF_ITEMS,    //numItems
        5,                  //numContainers
        centerScrollingMenuItems.getElementCallback,
        initializeCenterScrollingMenuItemCallback);
    centerScrollingMenu.setSwipeAcceleration(60);

    setup();

    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        backgroundScrollingMenuItems.element[i].setWidth(216);
        backgroundScrollingMenuItems.element[i].setHeight(50);
        backgroundScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        backgroundScrollingMenuItems.element[i].setTypedText(TypedText(T_HUMIDITY_VALUE));

        centerScrollingMenuItems.element[i].setWidth(216);
        centerScrollingMenuItems.element[i].setHeight(50);
        centerScrollingMenuItems.element[i].setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
        centerScrollingMenuItems.element[i].setTypedText(TypedText(T_HUMIDITY_VALUE_CENTER));
    }
}

void HumidityScrollingWheel::initializeBackgroundScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(backgroundScrollingMenuItems.element[containerIndex].textBuffer,
        backgroundScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%i", 80 - (itemIndex * 5));
}

void HumidityScrollingWheel::initializeCenterScrollingMenuItem(int containerIndex, int itemIndex)
{
    Unicode::snprintf(centerScrollingMenuItems.element[containerIndex].textBuffer,
        centerScrollingMenuItems.element[containerIndex].TEXT_SIZE, "%i", 80 - (itemIndex * 5));
}