#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/hal/HAL.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{
}

void MainPresenter::activate()
{
    HAL::getInstance()->setFrameRateCompensation(true);
}

void MainPresenter::deactivate()
{

}

void MainPresenter::timeUpdated(Time time)
{
    view.updateRemainingTime(time, model->getOvenStartTime(), model->getOvenTotalRunningTime());
}

void MainPresenter::ovenStarted(int hour, int minute, int second)
{
    model->setOvenStartedTime(model->getCurrentTime(), hour, minute, second);
}
