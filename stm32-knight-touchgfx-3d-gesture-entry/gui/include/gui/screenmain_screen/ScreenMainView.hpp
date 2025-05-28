#ifndef SCREENMAINVIEW_HPP
#define SCREENMAINVIEW_HPP

#include <gui_generated/screenmain_screen/ScreenMainViewBase.hpp>
#include <gui/screenmain_screen/ScreenMainPresenter.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <gui/containers/CustomContainerEventEngine.hpp>

class ScreenMainView : public ScreenMainViewBase
{
public:
    ScreenMainView();
    virtual ~ScreenMainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	virtual void handleTickEvent();
protected:
	virtual void enableMouseMode();
private:
	bool isMouseMode_;
	int helf_hand_w_;
	int helf_hand_h_;
	int d3x_;
	int d3y_;
	const int item_fade_ = 60; //60 == 1Sec
	const int item_fade_margin_ = 20;

	CustomContainerEventEngine ee_;	

	void changeAlphaByDistance();

#pragma region Event
	enum EventList
	{
		EVENT_KNOB_FADE_IN,
		EVENT_KNOB_FADE_OUT,
		EVENT_KNOB_PAD_IN,
		EVENT_KNOB_PAD_OUT
	};
	Callback<ScreenMainView, const int> event_trigger_callback_;
	void eventTriggerHandler(const int source);
	void eventKnobFadeIn();
	void eventKnobFadeOut();
	void eventPadFadeIn();
	void eventPadFadeOut();
#pragma endregion Event
};

#endif // SCREENMAINVIEW_HPP
