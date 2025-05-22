#include <gui/common/BasePresenter.hpp>

BasePresenter::BasePresenter(BaseViewInterface& view) :
    viewInterface(view)
{
}

void BasePresenter::machineStatusUpdated(MachineStatus* status)
{
	viewInterface.updateMachineStatus(status);
}

void BasePresenter::screenChanged(ScreenNumber id)
{
	viewInterface.changeScreen(id);
}

MachineStatus* BasePresenter::getMachineStatus()
{
	return model->getMachineStatus();
}
