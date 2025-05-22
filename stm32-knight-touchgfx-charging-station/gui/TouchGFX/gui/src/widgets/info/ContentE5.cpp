#include <gui/widgets/info/ContentE5.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

ContentE5::ContentE5()	
	:
	textarea_move_ended_callback_(this, &ContentE5::textareaMoveEndedHandler),
    textarea_fade_ended_callback_(this, &ContentE5::textareaFadeEndedHandler),
	buttonwithlabel_move_ended_callback_(this, &ContentE5::buttonwithlabelMoveEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &ContentE5::buttonwithlabelFadeEndedHandler),
	button_clicked_(this, &ContentE5::buttonClickedHandler)
{
}

ContentE5::~ContentE5()
{
	AbstractContent::~AbstractContent();
}

void ContentE5::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void ContentE5::initialize(MachineStatus *status)
{	
	AbstractContent::initialize(status);

	title_.setTypedText(TypedText(T_E5_TITLE));
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 40, 558, 160);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);		

	body_.setTypedText(TypedText(T_E5_BODY));
	body_.setColor(Color::getColorFromRGB(255, 255, 255));	
	body_.setPosition(40, 180, 558, 500);
	body_.setAlpha(0);
	body_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(body_);

	ok_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_1_ID), Bitmap(BITMAP_BUTTON_INFO_1_PRESS_ID));
	ok_.setPosition(219, 715, 200, 70);
	ok_.setLabelText(TypedText(T_GOT_IT));
	ok_.setLabelColor(Color::getColorFromRGB(255, 255, 255));
	ok_.setLabelColorPressed(Color::getColorFromRGB(0, 255, 0));
	ok_.setAlpha(0);
	ok_.setTouchable(false);
	ok_.setAction(button_clicked_);
	add(ok_);
}

void ContentE5::textareaMoveEndedHandler(const MoveAnimator<FadeAnimator<TextArea>>& textarea)
{
	animation_lock_--;
}

void ContentE5::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_--;
}

void ContentE5::buttonwithlabelMoveEndedHandler(const MoveAnimator<FadeAnimator<ButtonWithLabel>>& button)
{
	animation_lock_--;
}

void ContentE5::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void ContentE5::buttonClickedHandler(const AbstractButton& source)
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

void ContentE5::event2()
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

void ContentE5::event3()
{
	ok_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 300);
}

void ContentE5::event4()
{
	ok_.setTouchable(false);

	AbstractContent::event4();

	animation_lock_ = 3;

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(0, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(0, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(0, animation_duration_);
}

void ContentE5::event5()
{
	AbstractContent::event5();
}

void ContentE5::event6()
{
	AbstractContent::event6();

	event4();
}
