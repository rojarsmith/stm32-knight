#ifndef MCU_LOAD_SLIDER_HPP
#define MCU_LOAD_SLIDER_HPP

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>


using namespace touchgfx;

class McuLoadSlider : public Container
{
public:
    McuLoadSlider();

    void setValue(uint8_t load);
    void show();
    void showWithNoAnimation();

    void hide();

protected:
    enum AnimationState
    {
        LEFT_ANIMATION,
        RIGHT_ANIMATION,
        NO_ANIMATION
    } state;

    uint8_t mcuLoad; // mcu load in procent
    Image background;

    TextArea mcuLoadHeadline;
    TextAreaWithOneWildcard mcuLoadTxt;
    Unicode::UnicodeChar mcuLoadTxtbuf[5];

    int16_t startPositionX;
    uint8_t animationCounter;

    virtual void handleTickEvent();
};

#endif
