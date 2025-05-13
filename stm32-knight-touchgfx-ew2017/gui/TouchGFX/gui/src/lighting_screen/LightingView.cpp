#include <gui/lighting_screen/LightingView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

LightingView::LightingView()
    :
#ifndef SIMULATOR
      screenwidthreal(getScreenWidthReal()),
#else
      screenwidthreal(HAL::DISPLAY_WIDTH),
#endif
      newValueHandlerCounter(0),
      redValueCatch(0),
      greenValueCatch(0),
      blueValueCatch(0),
      newValueCallback(this, &LightingView::newValueHandler),
      buttonClickedCallback(this, &LightingView::buttonClicked),
      radioButtonSelectedCallback(this, &LightingView::radioButtonSelectedHandler)
{
}

void LightingView::setupScreen()
{
    LightingViewBase::setupScreen();

    imgBackground.setBitmap(Bitmap(BITMAP_MAINBG_ID));
    imgBackground.setXY(0, 0);
    add(imgBackground);

    imgLogo.setBitmap(Bitmap(BITMAP_LOGO_LARGE_ID));
    imgLogo.setXY(16, 16);
    add(imgLogo);

    btnHome.setBitmaps(Bitmap(BITMAP_BTN_HOME_RELEASED_ID), Bitmap(BITMAP_BTN_HOME_PRESSED_ID));

    int16_t imgSliderPanelPX = 255; // 800x600: 255 480x272: 154
    int16_t imgSliderPanelPY = 146; // 800x600: 88 480x272: 154
    imgSliderPanel.setBitmap(Bitmap(BITMAP_SLIDER_PANEL_ID));
    imgSliderPanel.setXY(imgSliderPanelPX, imgSliderPanelPY);
    add(imgSliderPanel);

    uint16_t func_btn_width = btnHome.getWidth();
    uint16_t func_btn_height = btnHome.getHeight();

    btnHome.setXY(screenwidthreal - 10 - func_btn_width, HAL::DISPLAY_HEIGHT - func_btn_height);
    btnHome.setAction(buttonClickedCallback);
    add(btnHome);

    btnDayMode.setBitmaps(Bitmap(BITMAP_BTN_DAY_RELEASED_ID), Bitmap(BITMAP_BTN_DAY_PRESSED_ID), Bitmap(BITMAP_BTN_DAY_PRESSED_ID), Bitmap(BITMAP_BTN_DAY_PRESSED_ID));
    btnNightMode.setBitmaps(Bitmap(BITMAP_BTN_NIGHT_RELEASED_ID), Bitmap(BITMAP_BTN_NIGHT_PRESSED_ID), Bitmap(BITMAP_BTN_NIGHT_PRESSED_ID), Bitmap(BITMAP_BTN_NIGHT_PRESSED_ID));
    btnCustomMode.setBitmaps(Bitmap(BITMAP_BTN_CUSTOM_RELEASED_ID), Bitmap(BITMAP_BTN_CUSTOM_PRESSED_ID), Bitmap(BITMAP_BTN_CUSTOM_PRESSED_ID), Bitmap(BITMAP_BTN_CUSTOM_PRESSED_ID));

    redSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_RED_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));
    greenSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_GREEN_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));
    blueSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_BLUE_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));

    uint16_t sliderWidth = 431; // 800x600: 431 480x272: 260
    uint16_t sliderHeight = 39; // 800x600: 39 480x272: 24
    uint16_t sliderStartx = imgSliderPanel.getX() + ((imgSliderPanel.getWidth() - sliderWidth) / 2);

    uint16_t modeWidth = btnDayMode.getWidth();
    uint16_t modeHeight = btnDayMode.getHeight();
    uint16_t modeStarty = modeHeight / 3;
    uint16_t modePitch = (sliderWidth - (modeWidth * 3)) / 2;

    btnDayMode.setXY(sliderStartx, modeStarty);
    btnNightMode.setXY(sliderStartx + modeWidth + modePitch, modeStarty);
    btnCustomMode.setXY(sliderStartx + (modeWidth * 2) + (modePitch * 2), modeStarty);

    radioButtonGroup.add(btnDayMode);
    radioButtonGroup.add(btnNightMode);
    radioButtonGroup.add(btnCustomMode);

    radioButtonGroup.setRadioButtonSelectedHandler(radioButtonSelectedCallback);

    add(btnDayMode);
    add(btnNightMode);
    add(btnCustomMode);

    radioButtonGroup.setSelected(btnDayMode);

    //uint16_t sliderHeightPitch = (imgSliderPanel.getHeight() - (sliderHeight * 3)) / 4;
    uint16_t sliderStarty1 = imgSliderPanel.getY() + 20;
    uint16_t sliderStarty2 = imgSliderPanel.getY() + ((imgSliderPanel.getHeight() - sliderHeight) / 2);
    uint16_t sliderStarty3 = imgSliderPanel.getY() + imgSliderPanel.getHeight() - 20 - sliderHeight;

    redSlider.setXY(sliderStartx, sliderStarty1);
    greenSlider.setXY(sliderStartx, sliderStarty2);
    blueSlider.setXY(sliderStartx, sliderStarty3);

    redSlider.setNewValueCallback(newValueCallback);
    greenSlider.setNewValueCallback(newValueCallback);
    blueSlider.setNewValueCallback(newValueCallback);

    // Setup slider background and indicator positions. The background does not take up
    // all the slider widget since the indicator needs to extend beyond the background in
    // the min and max positions. This is handled by placing the background at position (0, 0)
    int16_t indicatorMaxX = 391; // 800x600: 39 480x272: 236
    redSlider.setupHorizontalSlider(0, 0, 0, 0, indicatorMaxX);
    greenSlider.setupHorizontalSlider(0, 0, 0, 0, indicatorMaxX);
    blueSlider.setupHorizontalSlider(0, 0, 0, 0, indicatorMaxX);

    // Set the value range of the slider. Since the value us used for setting the 8bit alpha
    // value of the images, the range is set to 0-255.
    // Note that the slider indicator position range is only 192-8 = 184 pixels. This is, however, not a
    // problem just remember that in this case not all values can be set by the slider (since there is not a
    // pixel for each value)
    redSlider.setValueRange(0, 255);
    greenSlider.setValueRange(0, 255);
    blueSlider.setValueRange(0, 255);

    redValue = 168;
    greenValue = 203;
    blueValue = 228;

    redSlider.setValue(redValue);
    greenSlider.setValue(greenValue);
    blueSlider.setValue(blueValue);

    redSlider.setTouchable(false);
    greenSlider.setTouchable(false);
    blueSlider.setTouchable(false);

    add(redSlider);
    add(greenSlider);
    add(blueSlider);

    lightColor.setPosition(49, 167, 152, 190);
    // lightColor.setPosition(30, 101, 92, 115); // 480x272
    lightColor.setColor(Color::getColorFromRGB(redValue, greenValue, blueValue));
    add(lightColor);

    imgHalo.setBitmap(Bitmap(BITMAP_HALO_ID));
    imgHalo.setXY(49, 167);
    // imgHalo.setXY(30, 101); // 480x272
    imgHalo.setAlpha(255);
    add(imgHalo);

    imgLampshape.setBitmap(Bitmap(BITMAP_LAMPSHAPE_ID));
    imgLampshape.setXY(0, 146);
    // imgLampshape.setXY(0, 88); // 480x272
    add(imgLampshape);

    // Rojar====================================================================
    //  mcuLoadTxt.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_TEXT));
    //  mcuLoadTxt.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
    //  mcuLoadTxt.setHeight(100);
    //  mcuLoadTxt.setWidth(100);

    // Unicode::snprintf(mcuLoadTxtValueBuffer, 5, "%d", 0);
    // mcuLoadValueTxt.setWildcard(mcuLoadTxtValueBuffer);
    // mcuLoadValueTxt.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_VALUE));
    // mcuLoadValueTxt.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));

    // MCU Usage.
    //  mcuLoadTxt.setXY(10, 10 - mcuLoadTxt.getTypedText().getFont()->getFontHeight());
    //  mcuLoadValueTxt.setPosition(mcuLoadTxt.getRect().right(), mcuLoadTxt.getY(), 34, 14);
    //  add(mcuLoadTxt);
    //  add(mcuLoadValueTxt);
    //=========================================================================
}

void LightingView::tearDownScreen()
{
    LightingViewBase::tearDownScreen();
}

void LightingView::newValueHandler(const Slider &slider, int value)
{
    newValueHandlerCounter++;

    // if (!(newValueHandlerCounter % 2))
    //{
    //     return;
    // }

    if (&slider == &redSlider)
    {
        redValue = value;

        if (redValue == redValueCatch)
        {
            return;
        }

        redValueCatch = value;
    }
    else if (&slider == &greenSlider)
    {
        greenValue = value;

        if (greenValue == greenValueCatch)
        {
            return;
        }

        greenValueCatch = value;
    }
    else if (&slider == &blueSlider)
    {
        blueValue = value;

        if (blueValue == blueValueCatch)
        {
            return;
        }

        blueValueCatch = value;
    }

    alphaValue = 0;

    if (redValue > alphaValue)
    {
        alphaValue = redValue;
    }

    if (greenValue > alphaValue)
    {
        alphaValue = greenValue;
    }

    if (blueValue > alphaValue)
    {
        alphaValue = blueValue;
    }

    lightColor.setColor(Color::getColorFromRGB(redValue, greenValue, blueValue));
    lightColor.invalidate();

    imgHalo.setAlpha(alphaValue);

    presenter->setLED(redValue, greenValue, blueValue); // Add by jcc 2017.02.18
}

void LightingView::buttonClicked(const AbstractButton &source)
{
    if (&source == &btnHome)
    {
        presenter->gotoMainScreenFromLightingScreen();
    }
}

void LightingView::radioButtonSelectedHandler(const AbstractButton &radioButton)
{
    if (&btnDayMode == &radioButton)
    {
        redSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_RED_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));
        greenSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_GREEN_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));
        blueSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_BLUE_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));

        redValue = 168;
        greenValue = 203;
        blueValue = 228;

        redSlider.setTouchable(false);
        greenSlider.setTouchable(false);
        blueSlider.setTouchable(false);
    }

    if (&btnNightMode == &radioButton)
    {
        redSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_RED_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));
        greenSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_GREEN_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));
        blueSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_BLUE_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_DISABLE_ID));

        redValue = 116;
        greenValue = 139;
        blueValue = 152;

        redSlider.setTouchable(false);
        greenSlider.setTouchable(false);
        blueSlider.setTouchable(false);
    }

    if (&btnCustomMode == &radioButton)
    {
        redSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_RED_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_ID));
        greenSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_GREEN_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_ID));
        blueSlider.setBitmaps(Bitmap(BITMAP_RGBSLIDERBAR_BG_ID), Bitmap(BITMAP_RGBSLIDERBAR_BLUE_FILLED_ID), Bitmap(BITMAP_RGBSLIDER_KNOB_ID));

        redSlider.setTouchable(true);
        greenSlider.setTouchable(true);
        blueSlider.setTouchable(true);
    }

    redSlider.setValue(redValue);
    greenSlider.setValue(greenValue);
    blueSlider.setValue(blueValue);

    redSlider.invalidate();
    greenSlider.invalidate();
    blueSlider.invalidate();

    presenter->setLED(redValue, greenValue, blueValue); // Add by jcc 2017.02.18
}
