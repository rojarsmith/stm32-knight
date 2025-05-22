#include <gui/widgets/info/Content0501.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Content0501::Content0501()	
	:
    textarea_fade_ended_callback_(this, &Content0501::textareaFadeEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &Content0501::buttonwithlabelFadeEndedHandler),
	image_fade_ended_callback_(this, &Content0501::imageFadeEndedHandler),
	button_clicked_(this, &Content0501::buttonClickedHandler)
{
}

Content0501::~Content0501()
{
	AbstractContent::~AbstractContent();
}

void Content0501::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void Content0501::initialize(MachineStatus *status)
{	
	AbstractContent::initialize(status);

	title_.setTypedText(TypedText(T_P0501_TITLE));
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);		

	body_.setTypedText(TypedText(T_P0501_BODY));
	body_.setColor(Color::getColorFromRGB(255, 255, 255));	
	body_.setPosition(40, 200, 558, 800);
	body_.setAlpha(0);	
	body_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(body_);

	ok_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_1_ID), Bitmap(BITMAP_BUTTON_INFO_1_PRESS_ID));
	ok_.setPosition(104, 735, 200, 70);
	ok_.setLabelText(TypedText(T_P0501_BUTTON1));
	ok_.setLabelColor(Color::getColorFromRGB(255, 255, 255));
	ok_.setLabelColorPressed(Color::getColorFromRGB(255, 255, 255));
	ok_.setAlpha(0);
	ok_.setTouchable(false);
	ok_.setAction(button_clicked_);
	add(ok_);

	no_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_1_ID), Bitmap(BITMAP_BUTTON_INFO_1_PRESS_ID));
	no_.setPosition(334, 735, 200, 70);
	no_.setLabelText(TypedText(T_P0501_BUTTON2));
	no_.setLabelColor(Color::getColorFromRGB(255, 255, 255));
	no_.setLabelColorPressed(Color::getColorFromRGB(255, 255, 255));
	no_.setAlpha(0);
	no_.setTouchable(false);
	no_.setAction(button_clicked_);
	add(no_);

	//figure_.setBitmap(Bitmap(BITMAP_GUIDENCE_PAYMENT1_IMAGE_QR_CODE_ID));
	//figure_.setXY(40, 220);
	//figure_.setAlpha(0);
	//add(figure_);

	//indicator_1_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_SELECTED_10_ID));
	//indicator_1_.setXY(528, 720);
	//indicator_1_.setAlpha(0);
	//add(indicator_1_);

	//indicator_2_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
	//indicator_2_.setXY(548, 720);
	//indicator_2_.setAlpha(0);
	//add(indicator_2_);

	//indicator_3_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
	//indicator_3_.setXY(568, 720);
	//indicator_3_.setAlpha(0);
	//add(indicator_3_);
}

void Content0501::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_--;
}

void Content0501::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void Content0501::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void Content0501::buttonClickedHandler(const AbstractButton& source)
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

void Content0501::eventTriggerHandler(const int source)
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

void Content0501::event2()
{
	AbstractContent::event2();

	animation_lock_ = 4;
	
	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(255, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(255, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(255, animation_duration_);
	no_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	no_.startFadeAnimation(255, animation_duration_);

	//figure_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//figure_.startFadeAnimation(255, animation_duration_);
	//indicator_1_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//indicator_1_.startFadeAnimation(255, animation_duration_);
	//indicator_2_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//indicator_2_.startFadeAnimation(255, animation_duration_);
	//indicator_3_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//indicator_3_.startFadeAnimation(255, animation_duration_);
}

void Content0501::event3()
{
	ok_.setTouchable(true);
	no_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 1200);
	em_.addCountDownEvent(10, 180);
}

void Content0501::event4()
{
	animation_lock_ = 4;

	ok_.setTouchable(false);
	no_.setTouchable(false);

	AbstractContent::event4();
	
	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(0, animation_duration_);
	body_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	body_.startFadeAnimation(0, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(0, animation_duration_);
	no_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	no_.startFadeAnimation(0, animation_duration_);

	//figure_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//figure_.startFadeAnimation(0, animation_duration_);
	//indicator_1_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//indicator_1_.startFadeAnimation(0, animation_duration_);
	//indicator_2_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//indicator_2_.startFadeAnimation(0, animation_duration_);
	//indicator_3_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	//indicator_3_.startFadeAnimation(0, animation_duration_);
}

void Content0501::event5()
{
	AbstractContent::event5();
}

void Content0501::event6()
{
	AbstractContent::event6();

	event4();
}

//void Content0501::event10()
//{
//	title_.setTypedText(TypedText(T_S31_TITLE_PAGE2));
//	title_.setColor(Color::getColorFromRGB(255, 255, 255));
//	title_.setPosition(40, 50, 558, 140);
//	title_.setAlpha(255);
//	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);	
//	title_.invalidate();
//
//	figure_.setBitmap(Bitmap(BITMAP_GUIDENCE_PAYMENT2_IMAGE_EV_CARD_ID));
//	figure_.setXY(40, 220);	
//	figure_.invalidate();
//
//	indicator_1_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
//	indicator_1_.setXY(528, 720);
//	indicator_1_.invalidate();
//	
//	indicator_2_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_SELECTED_10_ID));
//	indicator_2_.setXY(548, 720);	
//	indicator_2_.invalidate();
//
//	indicator_3_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
//	indicator_3_.setXY(568, 720);
//	indicator_3_.invalidate();
//
//	em_.addCountDownEvent(11, 180);
//}
//
//void Content0501::event11()
//{
//	title_.setTypedText(TypedText(T_S31_TITLE_PAGE3));
//	title_.setColor(Color::getColorFromRGB(255, 255, 255));
//	title_.setPosition(40, 50, 558, 140);
//	title_.setAlpha(255);
//	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
//	title_.invalidate();
//
//	figure_.setBitmap(Bitmap(BITMAP_GUIDENCE_PAYMENT3_IMAGE_CREDIT_CARD_ID));
//	figure_.setXY(40, 220);
//	figure_.invalidate();
//
//	indicator_1_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
//	indicator_1_.setXY(528, 720);
//	indicator_1_.invalidate();
//
//	indicator_2_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
//	indicator_2_.setXY(548, 720);
//	indicator_2_.invalidate();
//
//	indicator_3_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_SELECTED_10_ID));
//	indicator_3_.setXY(568, 720);
//	indicator_3_.invalidate();
//
//	em_.addCountDownEvent(12, 180);
//}
//
//void Content0501::event12()
//{
//	title_.setTypedText(TypedText(T_S31_TITLE_PAGE1));
//	title_.setColor(Color::getColorFromRGB(255, 255, 255));
//	title_.setPosition(40, 50, 558, 140);
//	title_.setAlpha(255);
//	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
//	title_.invalidate();
//
//	figure_.setBitmap(Bitmap(BITMAP_GUIDENCE_PAYMENT1_IMAGE_QR_CODE_ID));
//	figure_.setXY(40, 220);
//	figure_.invalidate();
//
//	indicator_1_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_SELECTED_10_ID));
//	indicator_1_.setXY(528, 720);
//	indicator_1_.invalidate();
//
//	indicator_2_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
//	indicator_2_.setXY(548, 720);
//	indicator_2_.invalidate();
//
//	indicator_3_.setBitmap(Bitmap(BITMAP_DOT_INDICATOR_UNSELECT_10_ID));
//	indicator_3_.setXY(568, 720);
//	indicator_3_.invalidate();
//
//	em_.addCountDownEvent(10, 180);
//}