#ifndef FANVIEW_HPP
#define FANVIEW_HPP

#include <gui_generated/fan_screen/FanViewBase.hpp>
#include <gui/fan_screen/FanPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/fan_screen/KnobPointer.hpp>

class FanView : public FanViewBase
{
public:
    FanView();
    virtual ~FanView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    void buttonClicked(const AbstractButton& source);

    uint32_t screenwidthreal = 0;

    uint8_t temperatureValue;
    bool power_en;
protected:
private:
    Image imgBackground, imgLogo;
    Image imgScalePanel, imgScaleKnob;
    Image btnHeat, btnAuto;
    Button btnHome;

    RadioButtonGroup<2> radioButtonGroup;
    RadioButton btnCool, btnOff;

    Button btnHigh, btnMedium, btnLow;

    KnobPointer knobpPointer;

    static const uint8_t txtWidth = 140;
    static const uint8_t txtHeight = 50;

    TextAreaWithOneWildcard temperatureTxt;
    Unicode::UnicodeChar temperatureTxtbuf[txtWidth];

    TextAreaWithOneWildcard fanoffTxt;
    Unicode::UnicodeChar fanoffTxtbuf[txtWidth];

    Callback<FanView, const AbstractButton&> buttonClickedCallback;
    Callback<FanView, const AbstractButton&> radioButtonSelectedCallback;

    void radioButtonSelectedHandler(const AbstractButton& radioButton);
};

#endif // FANVIEW_HPP
