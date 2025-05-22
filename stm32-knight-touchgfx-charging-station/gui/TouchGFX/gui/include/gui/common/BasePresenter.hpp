#ifndef BASE_PRESENTER_HPP
#define BASE_PRESENTER_HPP

#include <mvp/Presenter.hpp>
#include <gui/common/BaseViewInterface.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/model/ModelListener.hpp>

using namespace touchgfx;

class BasePresenter : public Presenter, public ModelListener
{
public:
    BasePresenter(BaseViewInterface& view);

	virtual void machineStatusUpdated(MachineStatus* status);
	virtual void screenChanged(ScreenNumber id);

	virtual MachineStatus * getMachineStatus();
protected:


private:
	BaseViewInterface& viewInterface;
};

#endif
