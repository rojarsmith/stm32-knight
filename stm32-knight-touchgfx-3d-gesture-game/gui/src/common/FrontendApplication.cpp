#include <gui/common/FrontendApplication.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap) :
    FrontendApplicationBase(m, heap),
    tick_counter_(0),
    screen_saver_tick_(0),
    last_click_time_(0)
{
    resetScreenSaver();
}

void FrontendApplication::handleTickEvent()
{
    model.tick();
    FrontendApplicationBase::handleTickEvent();
    tick_counter_++;

    // Screen saver functionality:
    if (last_click_time_.hasValue() && (model.getCurrentTime() - last_click_time_) >= SCREEN_SAVER_TIMEOUT)
    {
        screen_saver_tick_++;
        if (screen_saver_tick_ % MINOR_TICK_FREQ == 0)
        {
            model.screenSaverMinorTick();
        }
    }
}

void FrontendApplication::handleClickEvent(const ClickEvent& evt)
{
    MVPApplication::handleClickEvent(evt);

    // A click event has been registered so reset last click time
    resetScreenSaver();
}

void FrontendApplication::handleDragEvent(const DragEvent& evt)
{
    MVPApplication::handleDragEvent(evt);

    // A drag event has been registered so reset last click time
    resetScreenSaver();
}

void FrontendApplication::resetScreenSaver()
{
    last_click_time_ = model.getCurrentTime();
    screen_saver_tick_ = 0;
}