#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView& v)
    : 
    // BasePresenter(v),
    view(v)
{

}

void MainPresenter::activate()
{
    timeUpdated(model->getCurrentTime());
}

void MainPresenter::deactivate()
{

}

void MainPresenter::timeUpdated(Time time)
{
	view.handleTimeUpdated(time.getValueInMillis());
	//view.handleTimeUpdated(time.hours, time.minutes, time.seconds);
}

void MainPresenter::setLoad(uint16_t persent)
{
	model->setData(persent);
}

uint16_t MainPresenter::readLoad()
{
	return model->readData();
}

void MainPresenter::backOptionSelected()
{
    //static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreen();
}

void MainPresenter::mcuLoadSelected()
{
    //model->setMCULoadActive(!model->getMCULoadActive());
    showProcessorLoad(true);
}

void MainPresenter::mcuLoadUpdated(uint8_t mcuLoad)
{
    if (model->getMCULoadActive())
    {
        view.updateProcessorLoad(mcuLoad);
    }
}

void MainPresenter::viewStartupDone()
{
    // Ensure that the mcuLoad is activated on demo screen startup
    // if it was selected on the previous screen
    if (model->getMCULoadActive())
    {
        showProcessorLoad(true);
    }
}

void MainPresenter::showProcessorLoad(bool visible)
{
//    viewInterface.showProcessorLoad(model->getMCULoadActive());
	view.showProcessorLoad(true);
}
