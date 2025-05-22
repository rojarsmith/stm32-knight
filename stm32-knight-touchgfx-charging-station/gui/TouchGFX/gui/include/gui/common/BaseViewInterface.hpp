#ifndef BASE_VIEW_INTERFACE_HPP
#define BASE_VIEW_INTERFACE_HPP

#include <touchgfx/hal/Types.hpp>
#include <gui/model/Model.hpp>

using namespace touchgfx;

class BaseViewInterface
{
public:
    virtual ~BaseViewInterface() {}    

	virtual void changeScreen(ScreenNumber id) {}	
	virtual void updateMachineStatus(MachineStatus* status) {}
	virtual void updateGraphic() {}
};

#endif