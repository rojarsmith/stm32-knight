#ifndef BOOTVIEW_HPP
#define BOOTVIEW_HPP

#include <gui_generated/boot_screen/BootViewBase.hpp>
#include <gui/boot_screen/BootPresenter.hpp>
#include <gui/common/BaseView.hpp>

class BootView : public BaseView<BootPresenter, BootViewBase>
{
public:
    BootView();
    virtual ~BootView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
	Box box1_;
	Box box2_;

	//Event
	enum EventList
	{
		EVENT_SEND_COMMAND,
		EVENT_CHANGE_SCREEN
	};
	Callback<BootView, const int> event_trigger_callback_;
	void eventTriggerHandler(const int source);
	void eventSendCommand();
	void eventChangeScreen();
	//Event End
};

#endif // BOOTVIEW_HPP
