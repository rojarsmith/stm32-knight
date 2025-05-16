#include <gui/common/AppConfig.hpp>
#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

#if defined(ST) && !defined(SIMULATOR)
extern volatile bool disableChromArt;
#endif

MainView::MainView() : 
    waterValueCache((uint8_t)((std::numeric_limits<int>::max)())),
    beanValueCache((uint8_t)((std::numeric_limits<int>::max)())),
    milkValueCache((uint8_t)((std::numeric_limits<int>::max)())),
    steamValueCache((uint8_t)((std::numeric_limits<int>::max)())),
    sugarValueCache((uint8_t)((std::numeric_limits<int>::max)())),
    waterValue(0),
    beanValue(0),
    milkValue(0),
    steamValue(0),
    sugarValue(0),
    imgFilledCoffee(BITMAP_FILLED_COFFEE_01_ID, BITMAP_FILLED_COFFEE_05_ID, 2),
    setupScreenLock(false),
    newValueLock(false),
    newValueCallback(this, &MainView::newValueHandler)
{
}

void MainView::setupScreen()
{
    setupScreenLock = true;

    // Setup background images.
#if   LCD_RESOLUTION == 13
    imgBackground.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
    imgBackground.setXY(0, 0);
#elif LCD_RESOLUTION == 17
    imgBackground.setBitmap(Bitmap(BITMAP_BACKGROUND_17_ID));
    imgBackground.setXY(0, 0);
#endif
    add(imgBackground);

    // Setup lef side sliders.
#if   LCD_RESOLUTION == 13
    waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
    beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
    milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
    steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
    sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));

    waterSlider.setXY(60, 44);
    beanSlider.setXY(60, 117);
    milkSlider.setXY(60, 190);
    steamSlider.setXY(60, 263);
    sugarSlider.setXY(60, 336);
#elif LCD_RESOLUTION == 17
    waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
    beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
    milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
    steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
    sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));

    waterSlider.setXY(76, 55);
    beanSlider.setXY(76, 146);
    milkSlider.setXY(76, 237);
    steamSlider.setXY(76, 328);
    sugarSlider.setXY(76, 420);
#endif

    waterSlider.setNewValueCallback(newValueCallback);
    beanSlider.setNewValueCallback(newValueCallback);
    milkSlider.setNewValueCallback(newValueCallback);
    steamSlider.setNewValueCallback(newValueCallback);
    sugarSlider.setNewValueCallback(newValueCallback);

#if   LCD_RESOLUTION == 13
    waterSlider.setupHorizontalSlider(0, 0, 0, 0, 128);
    beanSlider.setupHorizontalSlider(0, 0, 0, 0, 128);
    milkSlider.setupHorizontalSlider(0, 0, 0, 0, 128);
    steamSlider.setupHorizontalSlider(0, 0, 0, 0, 128);
    sugarSlider.setupHorizontalSlider(0, 0, 0, 0, 128);
#elif LCD_RESOLUTION == 17
    waterSlider.setupHorizontalSlider(0, 0, 0, 0, 166);
    beanSlider.setupHorizontalSlider(0, 0, 0, 0, 166);
    milkSlider.setupHorizontalSlider(0, 0, 0, 0, 166);
    steamSlider.setupHorizontalSlider(0, 0, 0, 0, 166);
    sugarSlider.setupHorizontalSlider(0, 0, 0, 0, 166);
#endif

    add(waterSlider);
    add(beanSlider);
    add(milkSlider);
    add(steamSlider);
    add(sugarSlider);

    // Setup coffee selector (wheel selector)
#if   LCD_RESOLUTION == 13
    kindSelector.setXY(384, 0);
    kindSelector.setup(113, 480, 0, 184, BITMAP_SELECT_KIND_THIN_ID);
#elif LCD_RESOLUTION == 17
    kindSelector.setXY(491, 0);
    kindSelector.setup(141, 600, 0, 230, BITMAP_SELECT_KIND_THIN_17_ID);
#endif

    kindSelector.setSlider(waterSlider, beanSlider, milkSlider, steamSlider, sugarSlider);
    add(kindSelector);

    // Setup center frame
#if   LCD_RESOLUTION == 13
    imgCenterFrame.setBitmap(Bitmap(BITMAP_CENTER_FRAME_ID));
    imgCenterFrame.setXY(374, 0);
#elif LCD_RESOLUTION == 17
    imgCenterFrame.setBitmap(Bitmap(BITMAP_CENTER_FRAME_17_ID));
    imgCenterFrame.setXY(478, 0);
#endif

    add(imgCenterFrame);

    // Setup rightside coffee display
#if   LCD_RESOLUTION == 13
    CoffeeViewPort.setPosition(rightSideStartX, 0, 313, 480);
#elif LCD_RESOLUTION == 17
    CoffeeViewPort.setPosition(rightSideStartX_17, 0, 400, 600);
#endif
    add(CoffeeViewPort);



#if   LCD_RESOLUTION == 13
    imgFilledSugar.setBitmap(Bitmap(BITMAP_FILLED_SUGAR_THIN_ID));
    imgFilledWater.setBitmap(Bitmap(BITMAP_FILLED_WATER_THIN_ID));
    imgFilledFoam.setBitmap(Bitmap(BITMAP_FILLED_FOAM_THIN_ID));
    imgFilledMilk.setBitmap(Bitmap(BITMAP_FILLED_MILK_THIN_ID));

    imgEspressoGlass.setBitmap(Bitmap(BITMAP_ESPRESSO_GLASS_ID));
    imgCappuccinoGlass.setBitmap(Bitmap(BITMAP_CAPPUCCINO_GLASS_ID));
    imgLatteGlass.setBitmap(Bitmap(BITMAP_LATTE_GLASS_ID));
    imgWaterGlass.setBitmap(Bitmap(BITMAP_WATER_GLASS_ID));
    imgEmptyGlass.setBitmap(Bitmap(BITMAP_EMPTY_GLASS_ID));
#elif LCD_RESOLUTION == 17
    imgFilledSugar.setBitmap(Bitmap(BITMAP_FILLED_SUGAR_THIN_17_ID));
    imgFilledWater.setBitmap(Bitmap(BITMAP_FILLED_WATER_THIN_17_ID));
    imgFilledFoam.setBitmap(Bitmap(BITMAP_FILLED_FOAM_THIN_17_ID));
    imgFilledMilk.setBitmap(Bitmap(BITMAP_FILLED_MILK_THIN_17_ID));

    imgEspressoGlass.setBitmap(Bitmap(BITMAP_ESPRESSO_GLASS_17_ID));
    imgCappuccinoGlass.setBitmap(Bitmap(BITMAP_CAPPUCCINO_GLASS_17_ID));
    imgLatteGlass.setBitmap(Bitmap(BITMAP_LATTE_GLASS_17_ID));
    imgWaterGlass.setBitmap(Bitmap(BITMAP_WATER_GLASS_17_ID));
    imgEmptyGlass.setBitmap(Bitmap(BITMAP_EMPTY_GLASS_17_ID));
#endif

    imgEspressoGlass.setXY(0, 0);
    imgCappuccinoGlass.setXY(0, 0);
    imgLatteGlass.setXY(0, 0);
    imgWaterGlass.setXY(0, 0);
    imgEmptyGlass.setXY(0, 0);

    CoffeeViewPort.add(imgFilledFoam);
    CoffeeViewPort.add(imgFilledCoffee);
    CoffeeViewPort.add(imgFilledMilk);
    CoffeeViewPort.add(imgFilledSugar);
    CoffeeViewPort.add(imgFilledWater);

    CoffeeViewPort.add(imgEspressoGlass);
    CoffeeViewPort.add(imgCappuccinoGlass);
    CoffeeViewPort.add(imgLatteGlass);
    CoffeeViewPort.add(imgWaterGlass);
    CoffeeViewPort.add(imgEmptyGlass);

    setupScreenLock = false;

    CoffeeAnimation = NO_ANIMATION;
    coffee = coffee_prev = ESPRESSO;
    setCoffeeViewPort(coffee);

    txtCopyRight.setTypedText(TypedText(T_COPYRIGHT));
	txtCopyRight.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	/*txtCopyRight.setHeight(100);
	txtCopyRight.setWidth(255);*/
	txtCopyRight.setXY(20, 400 + txtCopyRight.getTypedText().getFont()->getBaseline());
	add(txtCopyRight);
}

void MainView::tearDownScreen()
{
}

void MainView::newValueHandler(const Slider& slider, int value)
{
    if (setupScreenLock) return;

    if (&slider == &waterSlider)
    {
        waterValue = value;

        if (waterValue == waterValueCache) return;
        waterValueCache = value;

        if (coffee == WATER)
        {
#if   LCD_RESOLUTION == 13
            imgFilledWater.moveTo(waterStartX, (emptyWaterRangeMax - waterValue + waterStartY));
#elif LCD_RESOLUTION == 17
            imgFilledWater.moveTo((int16_t)(waterStartX * 1.28), (int16_t)((emptyWaterRangeMax - waterValue + waterStartY) * 1.25));
#endif
        }
        else
        {
#if   LCD_RESOLUTION == 13
            imgFilledCoffee.moveTo(emptyCoffeeStartX, (emptyCoffeeRangeMax - waterValue + emptyCoffeeStartY));
#elif LCD_RESOLUTION == 17
            imgFilledCoffee.moveTo((int16_t)(emptyCoffeeStartX * 1.28), (int16_t)((emptyCoffeeRangeMax - waterValue + emptyCoffeeStartY) * 1.25));
#endif
        }
    }

    else if (&slider == &beanSlider)
    {
        beanValue = value + 5; //Magic number for serial image ID.

        if (beanValue == beanValueCache) return;
        beanValueCache = beanValue;

        imgFilledCoffee.Image::setBitmap(Bitmap(beanValue));
        imgFilledCoffee.invalidate();
    }

    else if (&slider == &milkSlider)
    {
        milkValue = value;

        if (milkValue == milkValueCache) return;
        milkValueCache = value;

#if   LCD_RESOLUTION == 13
        imgFilledMilk.moveTo(emptyMilkStartX, (emptyMilkRangeMax - milkValue + emptyMilkStartY));
#elif LCD_RESOLUTION == 17
        imgFilledMilk.moveTo((int16_t)(emptyMilkStartX * 1.58), (int16_t)((emptyMilkRangeMax - milkValue + emptyMilkStartY) * 1.25));
#endif

    }

    else if (&slider == &steamSlider)
    {
        steamValue = value;

        if (steamValue == steamValueCache) return;
        steamValueCache = value;

#if   LCD_RESOLUTION == 13
        imgFilledFoam.moveTo(emptyFoamStartX, (emptyFoamRangeMax - steamValue + emptyFoamStartY));
#elif LCD_RESOLUTION == 17
        imgFilledFoam.moveTo((int16_t)(emptyFoamStartX * 1.28), (int16_t)((emptyFoamRangeMax - steamValue + emptyFoamStartY) * 1.25));
#endif
    }

    else if ((true != setupScreenLock) && (&slider == &sugarSlider))
    {
        sugarValue = value;

        if (sugarValue == sugarValueCache) return;
        sugarValueCache = value;

#if   LCD_RESOLUTION == 13
        imgFilledSugar.moveTo(emptySugarStartX, emptySugarStartY + emptySugarRangeMax - sugarValue);
#elif LCD_RESOLUTION == 17
        imgFilledSugar.moveTo((int16_t)(emptySugarStartX * 1.28), (int16_t)((emptySugarStartY + emptySugarRangeMax - sugarValue) * 1.25));
#endif

    }
}


void MainView::handleTickEvent()
{
    if (kindSelector.getWheelDragStatus() == true)
    {
        switch (kindSelector.getSelectedIndex())
        {
        case 0:
            coffee = ESPRESSO;
            if (coffee_prev != coffee)
            {
                CoffeeAnimation = ANIMATE_RIGHT;
            }
            break;

        case 1:
            coffee = CAPPUCCINO;
            if (coffee_prev != coffee)
            {
                CoffeeAnimation = ANIMATE_RIGHT;
            }
            break;

        case 2:
            coffee = LATTE;
            if (coffee_prev != coffee)
            {
                CoffeeAnimation = ANIMATE_RIGHT;
            }
            break;

        case 3:
            coffee = WATER;
            if (coffee_prev != coffee)
            {
                CoffeeAnimation = ANIMATE_RIGHT;
            }
            break;

        case 4:
            coffee = EMPTY;
            if (coffee_prev != coffee)
            {
                CoffeeAnimation = ANIMATE_RIGHT;
            }
            break;

        default:
            break;
        }
        kindSelector.setWheelDragStatus();
    }

    if (CoffeeAnimation != NO_ANIMATION)
    {
        switch (CoffeeAnimation)
        {
        case ANIMATE_LEFT:
#if   LCD_RESOLUTION == 13
            if (CoffeeViewPort.getX() > rightSideStartX)
#elif LCD_RESOLUTION == 17
            if (CoffeeViewPort.getX() > rightSideStartX_17)
#endif
            {
                CoffeeViewPort.moveRelative((int16_t)((-horizontal_distance) * 1.25), 0);
                //CoffeeViewPort.invalidate();
            }
            else
            {
                CoffeeAnimation = NO_ANIMATION;
            }
            break;

        case ANIMATE_RIGHT:
            if (CoffeeViewPort.getX() < HAL::DISPLAY_WIDTH)
            {
                CoffeeViewPort.moveRelative((int16_t)(horizontal_distance * 1.25), 0);
                //CoffeeViewPort.invalidate();
            }
            else
            {
                //setCoffeeViewPort(coffee_prev);
                setCoffeeViewPort(coffee);
                CoffeeAnimation = ANIMATE_LEFT;
            }
            break;

        default:
            break;
        }
    }
}

void MainView::setCoffeeViewPort(KindOfCoffee val)
{
    switch (val)
    {
    case ESPRESSO:
        imgEspressoGlass.setVisible(true);
        imgCappuccinoGlass.setVisible(false);
        imgLatteGlass.setVisible(false);
        imgWaterGlass.setVisible(false);
        imgEmptyGlass.setVisible(false);

        imgFilledFoam.setVisible(false);
        imgFilledCoffee.setVisible(true);
        imgFilledMilk.setVisible(false);
        imgFilledSugar.setVisible(true);
        imgFilledWater.setVisible(false);

#if   LCD_RESOLUTION == 13
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
#elif LCD_RESOLUTION == 17
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
#endif

        waterSlider.setTouchable(false);
        beanSlider.setTouchable(false);
        milkSlider.setTouchable(false);
        steamSlider.setTouchable(false);
        sugarSlider.setTouchable(true);

        waterValue = emptyCoffeeRangeMax - espressoCoffeeStartY;
        beanValue = emptyBeanRangeMax;
        milkValue = steamValue = sugarValue = 0;

#if   LCD_RESOLUTION == 13
        waterSlider.setValueRange(emptyCoffeeRangeMin, emptyCoffeeRangeMax, waterValue);
        beanSlider.setValueRange(emptyBeanRangeMin, emptyBeanRangeMax, beanValue);
        milkSlider.setValueRange(emptyMilkRangeMin, emptyMilkRangeMax, milkValue);
        steamSlider.setValueRange(emptyFoamRangeMin, emptyFoamRangeMax, steamValue);
        sugarSlider.setValueRange(emptySugarRangeMin, (emptySugarRangeMax / 2), sugarValue);
#elif LCD_RESOLUTION == 17
        waterSlider.setValueRange(emptyCoffeeRangeMin, emptyCoffeeRangeMax, waterValue);
        beanSlider.setValueRange(emptyBeanRangeMin, emptyBeanRangeMax, beanValue);
        milkSlider.setValueRange(emptyMilkRangeMin, emptyMilkRangeMax, milkValue);
        steamSlider.setValueRange(emptyFoamRangeMin, emptyFoamRangeMax, steamValue);
        sugarSlider.setValueRange(emptySugarRangeMin, (int)((emptySugarRangeMax / 2) * 1.25), sugarValue);
#endif



        imgFilledCoffee.Image::setBitmap(Bitmap(beanValue));

        break;

    case CAPPUCCINO:
        imgEspressoGlass.setVisible(false);
        imgCappuccinoGlass.setVisible(true);
        imgLatteGlass.setVisible(false);
        imgWaterGlass.setVisible(false);
        imgEmptyGlass.setVisible(false);

        imgFilledFoam.setVisible(true);
        imgFilledCoffee.setVisible(true);
        imgFilledMilk.setVisible(true);
        imgFilledSugar.setVisible(true);
        imgFilledWater.setVisible(false);

#if   LCD_RESOLUTION == 13
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
#elif LCD_RESOLUTION == 17
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
#endif

        waterSlider.setTouchable(false);
        beanSlider.setTouchable(false);
        milkSlider.setTouchable(false);
        steamSlider.setTouchable(false);
        sugarSlider.setTouchable(true);

        waterValue = (emptyCoffeeRangeMax - cappuccinoCoffeeStartY);
        beanValue = emptyBeanRangeMax;
        milkValue = (emptyMilkRangeMax - cappuccinoMilkStartY);
        steamValue = (emptyFoamRangeMax - cappuccinoFoamStartY);
        sugarValue = 0;

        waterSlider.setValueRange(emptyCoffeeRangeMin, emptyCoffeeRangeMax, waterValue);
        beanSlider.setValueRange(emptyBeanRangeMin, emptyBeanRangeMax, beanValue);
        milkSlider.setValueRange(emptyMilkRangeMin, emptyMilkRangeMax, milkValue);
        steamSlider.setValueRange(emptyFoamRangeMin, emptyFoamRangeMax, steamValue);
        sugarSlider.setValueRange(emptySugarRangeMin, (emptySugarRangeMax / 2), sugarValue);

        imgFilledCoffee.Image::setBitmap(Bitmap(beanValue));

        break;

    case LATTE:
        imgEspressoGlass.setVisible(false);
        imgCappuccinoGlass.setVisible(false);
        imgLatteGlass.setVisible(true);
        imgWaterGlass.setVisible(false);
        imgEmptyGlass.setVisible(false);

        imgFilledFoam.setVisible(true);
        imgFilledCoffee.setVisible(true);
        imgFilledMilk.setVisible(true);
        imgFilledSugar.setVisible(true);
        imgFilledWater.setVisible(false);

#if   LCD_RESOLUTION == 13
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
#elif LCD_RESOLUTION == 17
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
#endif

        waterSlider.setTouchable(false);
        beanSlider.setTouchable(false);
        milkSlider.setTouchable(false);
        steamSlider.setTouchable(false);
        sugarSlider.setTouchable(true);

        waterValue = (emptyCoffeeRangeMax - latteCoffeeStartY);
        beanValue = emptyBeanRangeMax;
        milkValue = (emptyMilkRangeMax - latteMilkStartY);
        steamValue = (emptyFoamRangeMax - latteFoamStartY);
        sugarValue = 0;

        waterSlider.setValueRange(emptyCoffeeRangeMin, emptyCoffeeRangeMax, waterValue);
        beanSlider.setValueRange(emptyBeanRangeMin, emptyBeanRangeMax, beanValue);
        milkSlider.setValueRange(emptyMilkRangeMin, emptyMilkRangeMax, milkValue);
        steamSlider.setValueRange(emptyFoamRangeMin, emptyFoamRangeMax, steamValue);
        sugarSlider.setValueRange(emptySugarRangeMin, emptySugarRangeMax, sugarValue);

        imgFilledCoffee.Image::setBitmap(Bitmap(beanValue));

        break;

    case WATER:
        imgEspressoGlass.setVisible(false);
        imgCappuccinoGlass.setVisible(false);
        imgLatteGlass.setVisible(false);
        imgWaterGlass.setVisible(true);
        imgEmptyGlass.setVisible(false);

        imgFilledFoam.setVisible(false);
        imgFilledCoffee.setVisible(false);
        imgFilledMilk.setVisible(false);
        imgFilledSugar.setVisible(false);
        imgFilledWater.setVisible(true);

#if   LCD_RESOLUTION == 13
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_ID));
#elif LCD_RESOLUTION == 17
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_DISABLE_17_ID));
#endif

        waterSlider.setTouchable(true);
        beanSlider.setTouchable(false);
        milkSlider.setTouchable(false);
        steamSlider.setTouchable(false);
        sugarSlider.setTouchable(false);

        waterValue = emptyWaterRangeMax;
        beanValue = 0;
        milkValue = 0;
        steamValue = 0;
        sugarValue = 0;

        waterSlider.setValueRange(emptyWaterRangeMin, emptyWaterRangeMax, waterValue);
        beanSlider.setValueRange(emptyBeanRangeMin, emptyBeanRangeMax, beanValue);
        milkSlider.setValueRange(emptyMilkRangeMin, emptyMilkRangeMax, milkValue);
        steamSlider.setValueRange(emptyFoamRangeMin, emptyFoamRangeMax, steamValue);
        sugarSlider.setValueRange(emptySugarRangeMin, emptySugarRangeMax, sugarValue);

        imgFilledCoffee.Image::setBitmap(Bitmap(beanValue));

        break;

    case EMPTY:
        imgEspressoGlass.setVisible(false);
        imgCappuccinoGlass.setVisible(false);
        imgLatteGlass.setVisible(false);
        imgWaterGlass.setVisible(false);
        imgEmptyGlass.setVisible(true);

        imgFilledFoam.setVisible(true);
        imgFilledCoffee.setVisible(true);
        imgFilledMilk.setVisible(true);
        imgFilledSugar.setVisible(true);
        imgFilledWater.setVisible(false);

#if   LCD_RESOLUTION == 13
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_SLIDER_FILLED_ID), Bitmap(BITMAP_SLIDER_KNOB_ID));
#elif LCD_RESOLUTION == 17
        waterSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
        beanSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
        milkSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
        steamSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
        sugarSlider.setBitmaps(Bitmap(BITMAP_SLIDER_BACKGROUND_17_ID), Bitmap(BITMAP_SLIDER_FILLED_17_ID), Bitmap(BITMAP_SLIDER_KNOB_17_ID));
#endif

        waterSlider.setTouchable(true);
        beanSlider.setTouchable(true);
        milkSlider.setTouchable(true);
        steamSlider.setTouchable(true);
        sugarSlider.setTouchable(true);

        waterValue = beanValue = milkValue = steamValue = sugarValue = 0;

        waterSlider.setValueRange(emptyCoffeeRangeMin, emptyCoffeeRangeMax, waterValue);
        beanSlider.setValueRange(emptyBeanRangeMin, emptyBeanRangeMax, beanValue);
        milkSlider.setValueRange(emptyMilkRangeMin, emptyMilkRangeMax, milkValue);
        steamSlider.setValueRange(emptyFoamRangeMin, emptyFoamRangeMax, steamValue);
        sugarSlider.setValueRange(emptySugarRangeMin, emptySugarRangeMax, sugarValue);

        imgFilledCoffee.Image::setBitmap(Bitmap(beanValue));

        break;

    default:
        break;
    }

    coffee_prev = coffee;
}
