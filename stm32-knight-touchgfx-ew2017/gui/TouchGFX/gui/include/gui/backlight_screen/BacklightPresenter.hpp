#ifndef BACKLIGHTPRESENTER_HPP
#define BACKLIGHTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class BacklightView;

class BacklightPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    BacklightPresenter(BacklightView& v);

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

    virtual ~BacklightPresenter() {}

    void gotoMainScreenFromBacklightScreen();
    void setBL(uint8_t pwm);
    uint8_t getpwm();
private:
    BacklightPresenter();

    BacklightView& view;
};

#endif // BACKLIGHTPRESENTER_HPP
