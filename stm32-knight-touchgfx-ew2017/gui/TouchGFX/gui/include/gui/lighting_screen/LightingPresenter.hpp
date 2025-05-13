#ifndef LIGHTINGPRESENTER_HPP
#define LIGHTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class LightingView;

class LightingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    LightingPresenter(LightingView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~LightingPresenter() {}

    void gotoMainScreenFromLightingScreen();
    void setLED(uint8_t LED_R, uint8_t LED_G, uint8_t LED_B);
private:
    LightingPresenter();

    LightingView& view;
};

#endif // LIGHTINGPRESENTER_HPP
