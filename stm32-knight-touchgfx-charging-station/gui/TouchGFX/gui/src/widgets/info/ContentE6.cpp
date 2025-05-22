#include <gui/widgets/info/ContentE6.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

ContentE6::ContentE6()	
	:
	textarea_move_ended_callback_(this, &ContentE6::textareaMoveEndedHandler),
    textarea_fade_ended_callback_(this, &ContentE6::textareaFadeEndedHandler),
	textareawithtwowildcards_fade_ended_callback_(this, &ContentE6::textareawithtwowildcardsFadeEndedHandler),
	buttonwithlabel_move_ended_callback_(this, &ContentE6::buttonwithlabelMoveEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &ContentE6::buttonwithlabelFadeEndedHandler),
	button_clicked_(this, &ContentE6::buttonClickedHandler)
{
}

ContentE6::~ContentE6()
{
	AbstractContent::~AbstractContent();
}

void ContentE6::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void ContentE6::initialize(MachineStatus *status)
{	
	AbstractContent::initialize(status);

	title_.setTypedText(TypedText(T_E6_TITLE));
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 40, 558, 160);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);		

	body_.setTypedText(TypedText(T_E6_BODY));
	body_.setColor(Color::getColorFromRGB(255, 255, 255));	
	body_.setPosition(40, 180, 558, 500);
	body_.setAlpha(0);
	body_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	int body_buffer1_len = sizeof(ms_->ux_phone);
	body_buffer1_[body_buffer1_len - 1] = 0;
	Unicode::strncpy(body_buffer1_, ms_->ux_phone, body_buffer1_len);
	body_.setWildcard1(body_buffer1_);
	int body_buffer2_len = sizeof(ms_->ux_charger_id);
	body_buffer2_[body_buffer2_len - 1] = 0;
	Unicode::strncpy(body_buffer2_, ms_->ux_charger_id, body_buffer2_len);
	body_.setWildcard2(body_buffer2_);
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

void ContentE6::textareaMoveEndedHandler(const MoveAnimator<FadeAnimator<TextArea>>& textarea)
{
	animation_lock_--;
}

void ContentE6::textareawithtwowildcardsFadeEndedHandler(const FadeAnimator<TextAreaWithTwoWildcards>& textarea)
{
	animation_lock_--;
}

void ContentE6::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_--;
}

void ContentE6::buttonwithlabelMoveEndedHandler(const MoveAnimator<FadeAnimator<ButtonWithLabel>>& button)
{
	animation_lock_--;
}

void ContentE6::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void ContentE6::buttonClickedHandler(const AbstractButton& source)
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

void ContentE6::event2()
{
	AbstractContent::event2();

	animation_lock_ = 3;

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(255, animation_duration_);
	body_.setFadeAnimationEndedAction(textareawithtwowildcards_fade_ended_callback_);
	body_.startFadeAnimation(255, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(255, animation_duration_);
}

void ContentE6::event3()
{
	ok_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 300);
}

void ContentE6::event4()
{
	ok_.setTouchable(false);

	AbstractContent::event4();

	animation_lock_ = 3;

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(0, animation_duration_);
	body_.setFadeAnimationEndedAction(textareawithtwowildcards_fade_ended_callback_);
	body_.startFadeAnimation(0, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(0, animation_duration_);
}

void ContentE6::event5()
{
	AbstractContent::event5();
}

void ContentE6::event6()
{
	AbstractContent::event6();

	event4();
}
