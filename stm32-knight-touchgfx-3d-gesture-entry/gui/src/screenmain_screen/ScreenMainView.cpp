#include <gui/screenmain_screen/ScreenMainView.hpp>
#include <platform/hal/simulator/sdl2/HALSDL2.hpp>
#include <platform/hal/simulator/sdl2/vendor/SDL2/SDL_mouse.h>

ScreenMainView::ScreenMainView() :
	event_trigger_callback_(this, &ScreenMainView::eventTriggerHandler)
{
	isMouseMode_ = false;
	helf_hand_w_ = 220 / 2;
	helf_hand_h_ = 265 / 2;

	ee_.setEventTriggerCallback(event_trigger_callback_);
	add(ee_);
}

void ScreenMainView::setupScreen()
{
	ScreenMainViewBase::setupScreen();
}

void ScreenMainView::tearDownScreen()
{
	ScreenMainViewBase::tearDownScreen();
}

void ScreenMainView::handleTickEvent()
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);

	d3x_ = mx;
	d3y_ = my;

	customContainerHand.setXY(mx - helf_hand_w_, my - helf_hand_h_);
	customContainerHand.invalidate();

	if (isMouseMode_) 
	{
		changeAlphaByDistance();
	}

	boxBackground.invalidate();
}

void ScreenMainView::enableMouseMode()
{
	if (!isMouseMode_)
	{
		customContainerHand.setVisible(true);
		customContainerHand.invalidate();
		isMouseMode_ = true;
	}
	else
	{
		customContainerHand.setVisible(false);
		customContainerHand.invalidate();
		isMouseMode_ = false;
	}
}

void ScreenMainView::changeAlphaByDistance()
{
	if (isMouseMode_)
	{
		if ((customContainerKnob.getX() - item_fade_margin_) <= d3x_ &&
			d3x_ <= (customContainerKnob.getX() + customContainerKnob.getWidth() + item_fade_margin_) &&
			customContainerKnob.getY() - item_fade_margin_ <= d3y_ &&
			d3y_ <= customContainerKnob.getY() + customContainerKnob.getHeight() + item_fade_margin_
			)
		{
			if (!customContainerKnob.getSelected())
			{
				customContainerKnob.setSelected(true);
				ee_.addLockCountEvent(EventList::EVENT_KNOB_FADE_IN, item_fade_);
			}
		}
		else
		{
			if (customContainerKnob.getSelected())
			{
				customContainerKnob.setSelected(false);
				ee_.addLockCountEvent(EventList::EVENT_KNOB_FADE_OUT, item_fade_);
			}
		}

		if ((customContainerDirPad.getX() - item_fade_margin_) <= d3x_ &&
			d3x_ <= (customContainerDirPad.getX() + customContainerDirPad.getWidth() + item_fade_margin_) &&
			customContainerDirPad.getY() - item_fade_margin_ <= d3y_ &&
			d3y_ <= customContainerDirPad.getY() + customContainerDirPad.getHeight() + item_fade_margin_
			)
		{
			if (!customContainerDirPad.getSelected())
			{
				customContainerDirPad.setSelected(true);
				ee_.addLockCountEvent(EventList::EVENT_KNOB_FADE_IN, item_fade_);
			}
		}
		else
		{
			if (customContainerDirPad.getSelected())
			{
				customContainerDirPad.setSelected(false);
				ee_.addLockCountEvent(EventList::EVENT_KNOB_FADE_OUT, item_fade_);
			}
		}
	}
}

void ScreenMainView::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case EVENT_KNOB_FADE_IN:
		eventKnobFadeIn();
		break;
	case EVENT_KNOB_FADE_OUT:
		eventKnobFadeOut();
		break;
	case EVENT_KNOB_PAD_IN:
		eventPadFadeIn();
		break;
	case EVENT_KNOB_PAD_OUT:
		eventPadFadeOut();
		break;
	}
}

void ScreenMainView::eventKnobFadeIn()
{
	customContainerKnob.actionFadeIn();
}

void ScreenMainView::eventKnobFadeOut()
{
	customContainerKnob.actionFadeOut();
}

void ScreenMainView::eventPadFadeIn()
{
	customContainerDirPad.actionFadeIn();
}

void ScreenMainView::eventPadFadeOut()
{
	customContainerDirPad.actionFadeOut();
}