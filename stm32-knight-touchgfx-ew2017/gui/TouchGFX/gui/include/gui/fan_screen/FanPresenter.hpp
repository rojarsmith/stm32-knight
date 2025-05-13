#ifndef FANPRESENTER_HPP
#define FANPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class FanView;

class FanPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    FanPresenter(FanView& v);

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

    virtual ~FanPresenter() {}

    void gotoMainScreenFromFanScreen();

    void setFan(uint8_t fan);

private:
    FanPresenter();

    FanView& view;
};

#endif // FANPRESENTER_HPP
