#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <limits>
#include <mvp/View.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/common/WheelSelector.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

/**
 * The View for a main screen. In the MVP paradigm, the view is a
 * passive interface that only displays the user interface and routes
 * any events from the user interface to the presenter. Normally it is the
 * responsibility of the presenter to act upon those events.
 *
 * By deriving from View, this class has a presenter pointer, which is configured
 * automatically.
 */
class MainView : public View<MainPresenter>
{
public:
    /**
     * The view constructor. Note that the constructor runs before the new screen is
     * completely initialized, so do not place code here that causes anything to be drawn.
     * Use the setupScreen function instead.
     */
    MainView();

    virtual ~MainView() {}

    virtual void handleTickEvent();

    /**
     * This function is called automatically when the view is activated. This function
     * should add widgets to the root container, configure widget sizes and event
     * callbacks, et cetera.
     */
    virtual void setupScreen();

    /**
     * This function is called automatically when transitioning to a different screen
     * than this one. Can optionally be used to clean up.
     */
    virtual void tearDownScreen();

    void BarStatus();

protected:
    enum KindOfCoffee
    {
        ESPRESSO,
        LATTE,
        CAPPUCCINO,
        WATER,
        EMPTY
    };

    KindOfCoffee coffee, coffee_prev;

    enum Animation
    {
        ANIMATE_LEFT,
        ANIMATE_RIGHT,
        NO_ANIMATION
    };

    Animation CoffeeAnimation;

    uint8_t index;

private:
    uint8_t waterValueCache, beanValueCache, milkValueCache, steamValueCache, sugarValueCache;
    uint8_t waterValue, beanValue, milkValue, steamValue, sugarValue;

    Image imgBackground;
    Image imgCenterFrame;
    Slider waterSlider, beanSlider, milkSlider, steamSlider, sugarSlider;

    WheelSelector kindSelector;

    Container CoffeeViewPort;

    MoveAnimator<Image> imgFilledFoam, imgFilledMilk, imgFilledSugar, imgFilledWater;
    AnimatedImage imgFilledCoffee;
    Image imgEspressoGlass, imgCappuccinoGlass, imgLatteGlass, imgWaterGlass, imgEmptyGlass;

    static const uint16_t rightSideStartX = 488;
    static const uint16_t rightSideStartX_17 = 624;

    static const uint16_t emptyWaterRangeMin = 0;
    static const uint16_t emptyWaterRangeMax = 100;
    static const uint16_t emptyCoffeeRangeMin = 0;
    static const uint16_t emptyCoffeeRangeMax = 127;
    static const uint16_t emptyBeanRangeMin = 5;
    static const uint16_t emptyBeanRangeMax = 9;
    static const uint16_t emptyMilkRangeMin = 0;
    static const uint16_t emptyMilkRangeMax = 94;
    static const uint16_t emptyFoamRangeMin = 0;
    static const uint16_t emptyFoamRangeMax = 148;
    static const uint16_t emptySugarRangeMin = 0;
    static const uint16_t emptySugarRangeMax = 20;

    static const uint16_t espressoCoffeeStartX = 64;
    static const uint16_t espressoCoffeeStartY = 64;

    static const uint16_t cappuccinoFoamStartY = 52;
    static const uint16_t cappuccinoCoffeeStartY = 58;
    static const uint16_t cappuccinoMilkStartY = 60;

    static const uint16_t latteFoamStartY = 0;
    static const uint16_t latteCoffeeStartY = 0;
    static const uint16_t latteMilkStartY = 0;

    static const uint16_t waterStartX = 63;
    static const uint16_t waterStartY = 209;

    static const uint16_t emptyFoamStartX = 58;
    static const uint16_t emptyFoamStartY = 160;
    static const uint16_t emptyCoffeeStartX = 60;
    static const uint16_t emptyCoffeeStartY = 178;
    static const uint16_t emptyMilkStartX = 61;
    static const uint16_t emptyMilkStartY = 200;

    static const uint16_t emptySugarStartX = 56;
    static const uint16_t emptySugarStartY = 288;

    //double_t sizeRatioX = 1.25;
    //double_t sizeRatioY = 1.28;

    // Animation
    static const uint16_t horizontal_distance = 78; // 1, 2, 3, 4, 6, 8, 12, 24, 26, 39, 52, 78, 104, 156, 312

    bool setupScreenLock;
    bool newValueLock;

    TextArea txtCopyRight;

    Callback<MainView, const Slider&, int> newValueCallback;
    void newValueHandler(const Slider& slider, int value);

    void setCoffeeViewPort(KindOfCoffee val);
};

#endif // MAIN_VIEW_HPP
