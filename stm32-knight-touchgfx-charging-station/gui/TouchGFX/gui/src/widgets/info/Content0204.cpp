#include <gui/widgets/info/Content0204.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Content0204::Content0204()
	:
    textarea_fade_ended_callback_(this, &Content0204::textareaFadeEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &Content0204::buttonwithlabelFadeEndedHandler),
	image_fade_ended_callback_(this, &Content0204::imageFadeEndedHandler),
	button_clicked_(this, &Content0204::buttonClickedHandler)
{
}

Content0204::~Content0204()
{
	AbstractContent::~AbstractContent();
}

void Content0204::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void Content0204::initialize(MachineStatus *status)
{
	AbstractContent::initialize(status);

	title_.setTypedText(TypedText(T_P0204_TITLE));
	title_.setColor(Color::getColorFromRGB(0, 0, 0));
	title_.setPosition(25, 25, 348, 100);
	//title_.setPosition(40, 40, 558, 160);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);

	body_.setTypedText(TypedText(T_P0204_BODY));
	body_.setColor(Color::getColorFromRGB(255, 255, 255));
	body_.setPosition(25, 125, 384, 312);
	//body_.setPosition(40, 200, 558, 500);
	body_.setAlpha(0);
	body_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(body_);

	ok_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_2_ID), Bitmap(BITMAP_BUTTON_INFO_2_PRESS_ID));
	ok_.setPosition(136, 459, 126, 45);
	//ok_.setPosition(219, 735, 202, 72);
	ok_.setLabelText(TypedText(T_P0204_BUTTON));
	ok_.setLabelColor(Color::getColorFromRGB(0, 0, 0));
	ok_.setLabelColorPressed(Color::getColorFromRGB(0, 0, 0));
	ok_.setAlpha(0);
	ok_.setTouchable(false);
	ok_.setAction(button_clicked_);
	add(ok_);
}

void Content0204::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_--;
}

void Content0204::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void Content0204::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void Content0204::buttonClickedHandler(const AbstractButton& source)
{
	if (&ok_ == &source)
	{
		return_value_ = ReturnValue::RETURN_OK;
	}
	else
	{
		return_value_ = ReturnValue::RETURN_NO;
	}

	ms_->ux_return_value = return_value_;

	sendCommandReturn();

	em_.removeAllEvent();

	em_.addOneTimeEvent(4);
}

void Content0204::eventTriggerHandler(const int source)
{
	AbstractContent::eventTriggerHandler(source);

	//switch (source)
	//{
	//case 10:
	//	event10();
	//	break;
	//case 11:
	//	event11();
	//	break;
	//case 12:
	//	event12();
	//	break;
	//}
}

void Content0204::event2()
{
	AbstractContent::event2();

	animation_lock_ = 3;

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(255, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(255, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(255, animation_duration_);
}

void Content0204::event3()
{
	ok_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 1200);

	em_.addCountDownEvent(10, 180);
}

void Content0204::event4()
{
	animation_lock_ = 3;

	ok_.setTouchable(false);

	AbstractContent::event4();

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(0, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(0, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(0, animation_duration_);
}

void Content0204::event5()
{
	AbstractContent::event5();
}

void Content0204::event6()
{
	AbstractContent::event6();

	event4();
}