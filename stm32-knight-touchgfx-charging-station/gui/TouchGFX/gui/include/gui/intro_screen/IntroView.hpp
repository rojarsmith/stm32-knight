#ifndef INTROVIEW_HPP
#define INTROVIEW_HPP

#include <gui_generated/intro_screen/IntroViewBase.hpp>
#include <gui/common/BaseView.hpp>
#include <gui/common/TargetFix.hpp>
#include <gui/intro_screen/IntroPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>

//using touchgfx::View<IntroPresenter>::presenter;

class IntroView : public BaseView<IntroPresenter, IntroViewBase>
{
public:
    IntroView();
    virtual ~IntroView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void showBitmap(BitmapId id);
protected:
	BitmapId id_;
	Box background_;
	Image image_;
	Image image2_;

	////Event
	enum EventList
	{
		EVENT_1TICK_LOOP,
		EVENT_SEND_COMMAND,
		EVENT_CHANGE_SCREEN
	};
	Callback<IntroView, const int> event_trigger_callback_;
	void eventTriggerHandler(const int source);
	void event1TickLoop();
	void eventSendCommand();
	void eventChangeScreen();
};

#endif // INTROVIEW_HPP
