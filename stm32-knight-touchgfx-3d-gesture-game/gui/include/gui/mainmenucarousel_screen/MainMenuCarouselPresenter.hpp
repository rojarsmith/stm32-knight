#ifndef MAINMENUCAROUSELPRESENTER_HPP
#define MAINMENUCAROUSELPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainMenuCarouselView;

class MainMenuCarouselPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainMenuCarouselPresenter(MainMenuCarouselView& v);

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

    void setSelectedDemoScreen(Defines::DemoID demoId);

    Defines::DemoID getSelectedDemoScreen();

    virtual ~MainMenuCarouselPresenter() {};

    virtual void screenSaverMinorTick();
    virtual void gestureTick(int eve, int op4);

    virtual MachineStatus* getMachineStatus();
private:
    MainMenuCarouselPresenter();

    MainMenuCarouselView& view;
};


#endif // MAINMENUCAROUSELPRESENTER_HPP
