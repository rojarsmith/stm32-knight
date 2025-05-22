#include <gui/widgets/info/Content0301.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Content0301::Content0301()	
	:
    textarea_fade_ended_callback_(this, &Content0301::textareaFadeEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &Content0301::buttonwithlabelFadeEndedHandler),
	image_fade_ended_callback_(this, &Content0301::imageFadeEndedHandler),
	button_clicked_(this, &Content0301::buttonClickedHandler)
{
}

Content0301::~Content0301()
{
	AbstractContent::~AbstractContent();
}

void Content0301::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void Content0301::initialize(MachineStatus *status)
{	
	AbstractContent::initialize(status);

	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);		

	ok_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_1_ID), Bitmap(BITMAP_BUTTON_INFO_1_PRESS_ID));
	ok_.setPosition(219, 735, 200, 70);
	ok_.setLabelText(TypedText(T_GOT_IT));
	ok_.setLabelColor(Color::getColorFromRGB(255, 255, 255));
	ok_.setLabelColorPressed(Color::getColorFromRGB(255, 255, 255));
	ok_.setAlpha(0);
	ok_.setTouchable(false);
	ok_.setAction(button_clicked_);
	add(ok_);

	figure_.setXY(40, 220);
	figure_.setAlpha(0);
	add(figure_);
}

void Content0301::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_--;
}

void Content0301::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void Content0301::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void Content0301::buttonClickedHandler(const AbstractButton& source)
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

void Content0301::eventTriggerHandler(const int source)
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
	}
}

void Content0301::event2()
{
	AbstractContent::event2();

	animation_lock_ = 4;
	
	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(255, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(255, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(255, animation_duration_);

	figure_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	figure_.startFadeAnimation(255, animation_duration_);
}

void Content0301::event3()
{
	ok_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 1200);	

	switch (ms_->ux_screen_id_current)
	{
	case ScreenNumber::SCENARIO_2_36:
		em_.addOneTimeEvent(10);
		break;
	case ScreenNumber::SCENARIO_2_37:
		em_.addOneTimeEvent(11);
		break;
	case ScreenNumber::SCENARIO_2_38:
		em_.addOneTimeEvent(12);
		break;
	default:
		break;
	}		
}

void Content0301::event4()
{
	animation_lock_ = 4;

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
}

void Content0301::event5()
{
	AbstractContent::event5();
}

void Content0301::event6()
{
	AbstractContent::event6();

	event4();
}

void Content0301::event10()
{
	title_.setTypedText(TypedText(T_S31_TITLE_PAGE2)); //Payment can be done using Charge card
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(255);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);	
	title_.invalidate();

	figure_.setBitmap(Bitmap(BITMAP_GUIDENCE_PAYMENT2_IMAGE_EV_CARD_ID));
	figure_.setXY(40, 220);	
	figure_.invalidate();
}

void Content0301::event11()
{
	title_.setTypedText(TypedText(T_S31_TITLE_PAGE3)); //Payment can be done using Credit card
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(255);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	title_.invalidate();

	figure_.setBitmap(Bitmap(BITMAP_GUIDENCE_PAYMENT3_IMAGE_CREDIT_CARD_ID));
	figure_.setXY(40, 220);
	figure_.invalidate();
}

void Content0301::event12()
{
	title_.setTypedText(TypedText(T_S31_TITLE_PAGE1)); //Payment can be done using QR code
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(255);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	title_.invalidate();

	figure_.setBitmap(Bitmap(BITMAP_GUIDENCE_PAYMENT1_IMAGE_QR_CODE_ID));
	figure_.setXY(40, 220);
	figure_.invalidate();
}