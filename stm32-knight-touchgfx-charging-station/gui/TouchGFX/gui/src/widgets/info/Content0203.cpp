#include <gui/widgets/info/Content0203.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Content0203::Content0203()
	:
    textarea_fade_ended_callback_(this, &Content0203::textareaFadeEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &Content0203::buttonwithlabelFadeEndedHandler),
	image_fade_ended_callback_(this, &Content0203::imageFadeEndedHandler),
	button_clicked_(this, &Content0203::buttonClickedHandler)
{
}

Content0203::~Content0203()
{
	AbstractContent::~AbstractContent();
}

void Content0203::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void Content0203::initialize(MachineStatus *status)
{
	AbstractContent::initialize(status);

	title_.setTypedText(TypedText(T_P0203_TITLE));
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(25, 31, 348, 87);
	//title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);

	body_.setTypedText(TypedText(T_P0203_BODY));
	body_.setColor(Color::getColorFromRGB(255, 255, 255));
	body_.setPosition(25, 125, 348, 312);
	//body_.setPosition(40, 200, 558, 500);
	body_.setAlpha(0);
	body_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(body_);

	ok_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_1_ID), Bitmap(BITMAP_BUTTON_INFO_1_PRESS_ID));
	ok_.setPosition(136, 459, 126, 45);
	//ok_.setPosition(219, 735, 202, 72);
	ok_.setLabelText(TypedText(T_P0203_BUTTON));
	ok_.setLabelColor(Color::getColorFromRGB(255, 255, 255));
	ok_.setLabelColorPressed(Color::getColorFromRGB(255, 255, 255));
	ok_.setAlpha(0);
	ok_.setTouchable(false);
	ok_.setAction(button_clicked_);
	add(ok_);
}

void Content0203::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_--;
}

void Content0203::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void Content0203::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void Content0203::buttonClickedHandler(const AbstractButton& source)
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

void Content0203::eventTriggerHandler(const int source)
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

void Content0203::event2()
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

void Content0203::event3()
{
	ok_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 1200);
	em_.addCountDownEvent(10, 180);
}

void Content0203::event4()
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

void Content0203::event5()
{
	AbstractContent::event5();
}

void Content0203::event6()
{
	AbstractContent::event6();

	event4();
}