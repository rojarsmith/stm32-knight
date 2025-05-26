#include <gui/widgets/info/Content0201.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Content0201::Content0201()
	:
    textarea_fade_ended_callback_(this, &Content0201::textareaFadeEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &Content0201::buttonwithlabelFadeEndedHandler),
	image_move_fade_ended_callback_(this, &Content0201::imageMoveFadeEndedHandler),
	image_fade_ended_callback_(this, &Content0201::imageFadeEndedHandler),
	button_clicked_(this, &Content0201::buttonClickedHandler)
{
}

Content0201::~Content0201()
{
	AbstractContent::~AbstractContent();
}

void Content0201::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void Content0201::initialize(MachineStatus *status)
{
	AbstractContent::initialize(status);

	title_.setTypedText(TypedText(T_S21_TITLE));
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(25, 31, 348, 87);
	//title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);

	ok_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_1_ID), Bitmap(BITMAP_BUTTON_INFO_1_PRESS_ID));
	ok_.setPosition(136, 459, 126, 45);
	//ok_.setPosition(219, 735, 202, 72);
	ok_.setLabelText(TypedText(T_GOT_IT));
	ok_.setLabelColor(Color::getColorFromRGB(255, 255, 255));
	ok_.setLabelColorPressed(Color::getColorFromRGB(255, 255, 255));
	ok_.setAlpha(0);
	ok_.setTouchable(false);
	ok_.setAction(button_clicked_);
	add(ok_);

	figure_.setBitmap(Bitmap(BITMAP_INFO_DRAG_1_ID));
	figure_.setXY(25, 137);
	//figure_.setXY(40, 220);
	figure_.setAlpha(0);
	add(figure_);
	
	hand_.setBitmap(Bitmap(BITMAP_INFO_DRAG_HAND_ID));
	hand_.setXY(HAND_RIGHT_BEGIN_X, HAND_Y);
	hand_.setAlpha(0);
	add(hand_);
}

void Content0201::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_--;
}

void Content0201::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void Content0201::imageMoveFadeEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image)
{
	animation_lock_--;
}

void Content0201::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void Content0201::buttonClickedHandler(const AbstractButton& source)
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

void Content0201::eventTriggerHandler(const int source)
{
	AbstractContent::eventTriggerHandler(source);

	switch (source)
	{
	case 10:
		event10();
		break;
	case 11:
		event11();
		break;
	case 12:
		event12();
		break;
	case 13:
		event13();
		break;
	case 14:
		event14();
		break;
	}
}

void Content0201::event2()
{
	AbstractContent::event2();

	animation_lock_ = 5;

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(255, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(255, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(255, animation_duration_);
	hand_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	hand_.startFadeAnimation(255, animation_duration_);

	figure_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	figure_.startFadeAnimation(255, animation_duration_);
}

void Content0201::event3()
{
	ok_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 300);
	em_.addCountDownEvent(10, HAND_ANIMATION_DURATION + 10);
}

void Content0201::event4()
{
	animation_lock_ = 5;

	ok_.setTouchable(false);

	AbstractContent::event4();

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(0, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(0, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(0, animation_duration_);

	figure_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	figure_.startFadeAnimation(0, animation_duration_);
	hand_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	hand_.startFadeAnimation(0, animation_duration_);
}

void Content0201::event5()
{
//	if (hand_.isFadeAnimationRunning())
	{
		hand_.cancelFadeAnimation();
	}
//	if (hand_.isMoveAnimationRunning()) 
	{
		hand_.cancelMoveAnimation();
	}
	AbstractContent::event5();
}

void Content0201::event6()
{
	AbstractContent::event6();

	em_.removeAllEvent();

	event4();
}

void Content0201::event10()
{
	hand_.startMoveAnimation(HAND_RIGHT_END_R_X, HAND_Y, HAND_ANIMATION_DURATION);
	hand_.startFadeAnimation(0, HAND_ANIMATION_DURATION, EasingEquations::cubicEaseIn);

	em_.addCountDownEvent(11, HAND_ANIMATION_DURATION + 10);
}

void Content0201::event11()
{
	hand_.setXY(HAND_RIGHT_BEGIN_X, HAND_Y);
	hand_.setAlpha(0);	
	hand_.startFadeAnimation(255, HAND_ANIMATION_DURATION);	

	em_.addCountDownEvent(12, HAND_ANIMATION_DURATION + 10);
}

void Content0201::event12()
{
	hand_.startMoveAnimation(HAND_RIGHT_END_L_X, HAND_Y, HAND_ANIMATION_DURATION);
	hand_.startFadeAnimation(0, HAND_ANIMATION_DURATION, EasingEquations::cubicEaseIn);

	em_.addCountDownEvent(13, HAND_ANIMATION_DURATION + 10);
}

void Content0201::event13()
{
	hand_.setXY(HAND_RIGHT_BEGIN_X, HAND_Y);
	hand_.setAlpha(0);
	hand_.startFadeAnimation(255, HAND_ANIMATION_DURATION);	

	em_.addCountDownEvent(10, HAND_ANIMATION_DURATION + 10);
}

void Content0201::event14()
{
}
