#include <gui/mainmenucarousel_screen/MainMenuCarouselView.hpp>
#include <gui/mainmenucarousel_screen/MainMenuCarouselPresenter.hpp>

MainMenuCarouselPresenter::MainMenuCarouselPresenter(MainMenuCarouselView& v)
    : view(v)
{
}

void MainMenuCarouselPresenter::activate()
{

}

void MainMenuCarouselPresenter::deactivate()
{

}

void MainMenuCarouselPresenter::setSelectedDemoScreen(Defines::DemoID elementIndex)
{
    model->setSelectedDemoScreen(elementIndex);
}

Defines::DemoID MainMenuCarouselPresenter::getSelectedDemoScreen()
{
    return model->getSelectedDemoScreen();
}

void MainMenuCarouselPresenter::screenSaverMinorTick()
{
    view.screenSaverMinorTick();
}

void MainMenuCarouselPresenter::gestureTick(int eve, int op4)
{
    view.gestureTick(eve, op4);
}

MachineStatus* MainMenuCarouselPresenter::getMachineStatus()
{
    return model->getMachineStatus();
}