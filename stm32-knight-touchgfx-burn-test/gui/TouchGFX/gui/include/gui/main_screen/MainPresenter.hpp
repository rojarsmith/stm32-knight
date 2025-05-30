#ifndef MAINPRESENTER_HPP
#define MAINPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/BasePresenter.hpp>

using namespace touchgfx;

class MainView;

// class MainPresenter : public BasePresenter // public touchgfx::Presenter, public ModelListener
class MainPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainPresenter(MainView& v);

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

    virtual ~MainPresenter() {}

	virtual void timeUpdated(Time time);

	void setLoad(uint16_t persent);
	uint16_t readLoad();

    // MCU Load
    void backOptionSelected();
    void mcuLoadSelected();
    virtual void mcuLoadUpdated(uint8_t mcuLoad);

    virtual void viewStartupDone();
    virtual void showProcessorLoad(bool visible);
private:
    MainPresenter();

    MainView& view;
};

#endif // MAINPRESENTER_HPP
