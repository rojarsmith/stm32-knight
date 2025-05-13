#ifndef LIGHTINGVIEW_HPP
#define LIGHTINGVIEW_HPP

#include <gui_generated/lighting_screen/LightingViewBase.hpp>
#include <gui/lighting_screen/LightingPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Slider.hpp>

class LightingView : public LightingViewBase
{
public:
    LightingView();
    virtual ~LightingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void buttonClicked(const AbstractButton &source);

    uint32_t screenwidthreal = 0;

    uint8_t redValue, greenValue, blueValue;

protected:
    uint8_t newValueHandlerCounter;
    Box backgroundColor;

    Image imgBackground, imgLogo;
    Button btnHome;

    RadioButtonGroup<3> radioButtonGroup;
    RadioButton btnDayMode, btnNightMode, btnCustomMode;

    uint8_t redValueCatch, greenValueCatch, blueValueCatch;

    // Rojar====================================================================
    // TouchArea mcuLoadArea;
    // McuLoadSlider mcuLoadSlider;
    // Callback<MusicView, const AbstractButton&> onMcuLoadClicked;
    //  TextArea mcuLoadTxt;
    //  TextAreaWithOneWildcard mcuLoadValueTxt;
    //  Unicode::UnicodeChar mcuLoadTxtValueBuffer[5];

    // virtual void updateProcessorLoad(uint8_t mcuLoadInProcent)
    // {
    //     Unicode::snprintf(mcuLoadTxtValueBuffer, 5, "%d", mcuLoadInProcent);
    //     mcuLoadValueTxt.invalidate();
    // }
    //=========================================================================

    Image imgLampshape, imgHalo;
    Box lightColor;
    uint8_t alphaValue;

    Image imgSliderPanel;
    Slider redSlider, greenSlider, blueSlider;

    bool custom;

    Callback<LightingView, const Slider &, int> newValueCallback;
    void newValueHandler(const Slider &slider, int value);

    Callback<LightingView, const AbstractButton &> buttonClickedCallback;

    Callback<LightingView, const AbstractButton &> radioButtonSelectedCallback;
    void radioButtonSelectedHandler(const AbstractButton &radioButton);
};

#endif // LIGHTINGVIEW_HPP
