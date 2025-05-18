#include <gui/widget/McuLoadSlider.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Application.hpp>

McuLoadSlider::McuLoadSlider() :
    animationCounter(0)
{
    // background.setBitmap(Bitmap(BITMAP_BASE_MCU_LOAD_BACKGROUND_ID));
    background.setBitmap(Bitmap(BITMAP_BASE_MCU_LOAD_BACKGROUNDX2_ID));
    setWidth(background.getWidth());
    setHeight(background.getHeight());

    // set background outside container
    background.setXY(background.getWidth(), 0);
    background.setAlpha(168);

    mcuLoadHeadline.setTypedText(TypedText(T_BASE_VIEW_MCU_LOAD_TEXT));
    // mcuLoadHeadline.setXY(background.getX(), 0);
    mcuLoadHeadline.setPosition(background.getX(), 0, background.getWidth(), 30);
    mcuLoadHeadline.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));


    // Setup mcuLoadTxt with correct initialized buffer
    // for wildcard text
    Unicode::snprintf(mcuLoadTxtbuf, 5, "%d", 0);
    mcuLoadTxt.setWildcard(mcuLoadTxtbuf);
    mcuLoadTxt.setTypedText(TypedText(T_BASE_VIEW_MCU_LOAD_VALUE));
    mcuLoadTxt.setPosition(background.getX(), 30, background.getWidth(), 30);
    mcuLoadTxt.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));

    add(background);
    add(mcuLoadHeadline);
    add(mcuLoadTxt);
}

void McuLoadSlider::setValue(uint8_t load)
{
    Unicode::snprintf(mcuLoadTxtbuf, 5, "%d", load);
    mcuLoadTxt.invalidate();
}

void McuLoadSlider::show()
{
    Application::getInstance()->registerTimerWidget(this);
    state = LEFT_ANIMATION;
    startPositionX = background.getWidth();
}

void McuLoadSlider::hide()
{
    Application::getInstance()->registerTimerWidget(this);
    state = RIGHT_ANIMATION;
    startPositionX = background.getX();
}

void McuLoadSlider::handleTickEvent()
{

    uint8_t duration = 7;

    if (animationCounter > duration)
    {
        // End of animation
        state = NO_ANIMATION;
        animationCounter = 0;
        Application::getInstance()->unregisterTimerWidget(this);
    }
    else if(state != NO_ANIMATION)
    {
        int8_t animationDirection = (state == LEFT_ANIMATION) ? -1 : 1;
        background.moveTo(startPositionX + animationDirection * EasingEquations::linearEaseNone(animationCounter, 0, getWidth(), duration), 0);
        mcuLoadHeadline.setPosition(background.getX(), 0, background.getWidth(), 30);
        mcuLoadTxt.setPosition(background.getX(), 30, background.getWidth(), 30);
        mcuLoadHeadline.invalidate();
        mcuLoadTxt.invalidate();
        animationCounter++;
    }
}
