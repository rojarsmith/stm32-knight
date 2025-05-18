#include <gui/common/BasePresenter.hpp>

#include <stdlib.h>

BasePresenter::BasePresenter(BaseViewInterface& view) :
    viewInterface(view)
{
}

void BasePresenter::backOptionSelected()
{
    //static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreen();
}

void BasePresenter::mcuLoadSelected()
{
    //model->setMCULoadActive(!model->getMCULoadActive());
    showProcessorLoad();
}

void BasePresenter::mcuLoadUpdated(uint8_t mcuLoad)
{
    if (model->getMCULoadActive())
    {
        viewInterface.updateProcessorLoad(mcuLoad);
    }
}

void BasePresenter::viewStartupDone()
{
    // Ensure that the mcuLoad is activated on demo screen startup
    // if it was selected on the previous screen
    if (model->getMCULoadActive())
    {
        showProcessorLoad();
    }
}

void BasePresenter::showProcessorLoad()
{
//    viewInterface.showProcessorLoad(model->getMCULoadActive());
	viewInterface.showProcessorLoad(true);
}
