#ifndef MAINMENUCAROUSELVIEW_HPP
#define MAINMENUCAROUSELVIEW_HPP

#include <gui_generated/mainmenucarousel_screen/MainMenuCarouselViewBase.hpp>
#include <gui/mainmenucarousel_screen/MainMenuCarouselPresenter.hpp>
#include <gui/container/Carousel.hpp>
#include <gui/common/Defines.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/model/ModelSchema.hpp>

class MainMenuCarouselView : public MainMenuCarouselViewBase
{
public:
    MainMenuCarouselView();
    virtual ~MainMenuCarouselView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    virtual void handleDragEvent(const DragEvent& evt);
    virtual void handleClickEvent(const ClickEvent& evt);

    virtual void screenSaverMinorTick();
    virtual void gestureTick(int eve, int op4);

protected:    
    enum State
    {
        ELEMENT_SELECTED,
        NO_STATE
    };

    State currentState_;

    Defines::DemoID demoIDs_[Defines::NUMBER_OF_DEMO_SCREENS];
    Defines::DemoID selectedDemoScreen_;

    Carousel carousel_;

    TEXTS headlines_[Defines::NUMBER_OF_DEMO_SCREENS];

    int pauses_;

    void setupCarousel();

    Callback<MainMenuCarouselView, const Carousel&> carouselAnimationEnded_;
    void carouselAnimationEndedhandler(const Carousel& c);

    void updateDemoText();

    void setSelectedDemoScreen(Defines::DemoID demoId);
    void gotoSelectedDemoScreen();

    int16_t dragDistance_;
    bool dragInsideCarousel_;
    bool dragInsideCenterButton_;
    bool hasAnimatedDrag_;

    bool first_time_;
private:
    MachineStatus* ms_;
};

#endif // MAINMENUCAROUSELVIEW_HPP
