#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/common/ScrollingWheels/TemperatureScrollingWheel.hpp>
#include <gui/common/ScrollingWheels/HumidityScrollingWheel.hpp>
#include <gui/common/ScrollingWheels/TimerScrollingWheel.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateRemainingTime(Time time, Time ovenStartTime, Time ovenRunningTime);
protected:
    static const int MS_PER_TICK = 16; // The typical milliseconds per tick on demo boards

    enum State
    {
        OVEN_STOPPED,
        OVEN_STARTED
    };

    State currentState;

    TemperatureScrollingWheel temperatureScrollingWheel;
    HumidityScrollingWheel humidityScrollingWheel;
    TimerScrollingWheel timerScrollingWheel;

    int selectedRecipeIndex;
    Callback<MainView, const MoveAnimator<Container>& > ovenContainerMoveAnimationEndedCallback;
    void ovenContainerMoveAnimationEndedHandler(const MoveAnimator<Container>& container);

    void setState(State newState);

    void enableTopBar(bool enable);

    virtual void bottomBarButtonHandler();
    virtual void topBarButtonRecipesPressedHandler();

    virtual void selectRecipeButtonPressedHandler();


};

#endif // MAIN_VIEW_HPP
