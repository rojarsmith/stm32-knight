#include <gui/widgets/info/Content0207.hpp>
#include <stdio.h>
#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Content0207::Content0207()
	:
    textarea_fade_ended_callback_(this, &Content0207::textareaFadeEndedHandler),
	textareawithonewildcard_fade_ended_callback_(this, &Content0207::textareawithonewildcardFadeEndedHandler),
	buttonwithlabel_fade_ended_callback_(this, &Content0207::buttonwithlabelFadeEndedHandler),
	image_fade_ended_callback_(this, &Content0207::imageFadeEndedHandler),
	button_clicked_(this, &Content0207::buttonClickedHandler)
{
}

Content0207::~Content0207()
{
	AbstractContent::~AbstractContent();
}

void Content0207::handleTickEvent()
{
	AbstractContent::handleTickEvent();
}

void Content0207::initialize(MachineStatus *status)
{
	AbstractContent::initialize(status);
	
	title_.setTypedText(TypedText(T_P0207_TITLE));
	title_.setColor(Color::getColorFromRGB(255, 255, 255));
	title_.setPosition(40, 50, 558, 140);
	title_.setAlpha(0);
	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(title_);

	int ox = 113;
	int oy = 210;
	int sx = 236;
	int dy = 68;
	
	tfa_1_.setTypedText(TypedText(T_P0207_TFA1));
	tfa_1_.setColor(Color::getColorFromRGB(255, 255, 255));
	tfa_1_.setPosition(ox, oy, 558, 54);
	tfa_1_.setAlpha(0);
	tfa_1_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(tfa_1_);

	tfb_11_.setPosition(ox + 116, oy, 200, 54);
	tfb_11_.setAlpha(0);
	tfb_11_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	tfb_11_.setLinespacing(0);
	tfb_11_.setTypedText(TypedText(T_P0207_TFB11));
	int tfb_11_len = sizeof(ms_->ux_duration_h);
	tfb_11_buffer_[tfb_11_len - 1] = 0;
	Unicode::strncpy(tfb_11_buffer_, ms_->ux_duration_h, tfb_11_len);
	tfb_11_.setWildcard(tfb_11_buffer_);
	add(tfb_11_);

	tfb_12_.setPosition(ox + 236, oy, 200, 54);
	tfb_12_.setAlpha(0);
	tfb_12_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	tfb_12_.setLinespacing(0);
	tfb_12_.setTypedText(TypedText(T_P0207_TFB12));
	int tfb_12_len = sizeof(ms_->ux_duration_m);
	tfb_12_buffer_[tfb_12_len - 1] = 0;
	Unicode::strncpy(tfb_12_buffer_, ms_->ux_duration_m, tfb_12_len);
	tfb_12_.setWildcard(tfb_12_buffer_);
	add(tfb_12_);

	oy += dy;

	tfa_2_.setTypedText(TypedText(T_P0207_TFA2));
	tfa_2_.setColor(Color::getColorFromRGB(255, 255, 255));
	tfa_2_.setPosition(ox, oy, 558, 140);
	tfa_2_.setAlpha(0);
	tfa_2_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(tfa_2_);

	tfb_2_.setPosition(ox + 236, oy, 200, 54);
	tfb_2_.setAlpha(0);
	tfb_2_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	tfb_2_.setLinespacing(0);
	tfb_2_.setTypedText(TypedText(T_P0207_TFB2));
	int tfb_2_len = sizeof(ms_->ux_energy);
	tfb_2_buffer_[tfb_2_len - 1] = 0;
	Unicode::strncpy(tfb_2_buffer_, ms_->ux_energy, tfb_2_len);
	tfb_2_.setWildcard(tfb_2_buffer_);
	add(tfb_2_);

	oy += dy;

	tfa_3_.setTypedText(TypedText(T_P0207_TFA3));
	tfa_3_.setColor(Color::getColorFromRGB(255, 255, 255));
	tfa_3_.setPosition(ox, oy, 558, 140);
	tfa_3_.setAlpha(0);
	tfa_3_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	add(tfa_3_);

	tfb_3_.setPosition(ox + 236, oy, 200, 54);
	tfb_3_.setAlpha(0);
	tfb_3_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	tfb_3_.setLinespacing(0);
	tfb_3_.setTypedText(TypedText(T_P0207_TFB3));
	int tfb_3_len = sizeof(ms_->ux_paid);
	tfb_3_buffer_[tfb_3_len - 1] = 0;
	Unicode::strncpy(tfb_3_buffer_, ms_->ux_paid, tfb_3_len);
	tfb_3_.setWildcard(tfb_3_buffer_);
	add(tfb_3_);

	ok_.setBitmaps(Bitmap(BITMAP_BUTTON_INFO_1_ID), Bitmap(BITMAP_BUTTON_INFO_1_PRESS_ID));
	ok_.setPosition(219, 735, 202, 72);
	ok_.setLabelText(TypedText(T_P0207_BUTTON));
	ok_.setLabelColor(Color::getColorFromRGB(255, 255, 255));
	ok_.setLabelColorPressed(Color::getColorFromRGB(255, 255, 255));
	ok_.setAlpha(0);
	ok_.setTouchable(false);
	ok_.setAction(button_clicked_);
	add(ok_);

	bc_.setTypedText(TypedText(T_P0207_BUTTON2));
	bc_.setColor(Color::getColorFromRGB(255, 255, 255));
	bc_.setPosition(410 - 65 - 16 - 6 - 2, 900 - 160 + 20 - 7, 50, 25);
	bc_.setAlpha(0);
	bc_.setWideTextAction(WIDE_TEXT_WORDWRAP);
	//char cd[] = { 51, 48 };
	//int bc_buffer_len = sizeof(cd) / sizeof(const char);
	//bc_buffer_[bc_buffer_len] = 0;
	//Unicode::strncpy(bc_buffer_, cd, bc_buffer_len);
	//bc_.setWildcard(bc_buffer_);
	add(bc_);
}

void Content0207::textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea)
{
	animation_lock_ = animation_lock_ - 1;
}

void Content0207::textareawithonewildcardFadeEndedHandler(const FadeAnimator<TextAreaWithOneWildcard>& textarea)
{
	animation_lock_--;
}

void Content0207::buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& button)
{
	animation_lock_--;
}

void Content0207::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void Content0207::buttonClickedHandler(const AbstractButton& source)
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

void Content0207::eventTriggerHandler(const int source)
{
	AbstractContent::eventTriggerHandler(source);

	switch (source)
	{
	case 17:
		event17();
		break;
		//case 10:
		//	event10();
		//	break;
		//case 11:
		//	event11();
		//	break;
		//case 12:
		//	event12();
		//	break;
	}
}

void Content0207::event2()
{
	AbstractContent::event2();

	animation_lock_ = 10;

	title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(255, animation_duration_);
	tfa_1_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	tfa_1_.startFadeAnimation(255, animation_duration_);
	tfa_2_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	tfa_2_.startFadeAnimation(255, animation_duration_);
	tfa_3_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	tfa_3_.startFadeAnimation(255, animation_duration_);
	tfb_11_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_11_.startFadeAnimation(255, animation_duration_);
	tfb_12_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_12_.startFadeAnimation(255, animation_duration_);
	tfb_2_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_2_.startFadeAnimation(255, animation_duration_);
	tfb_3_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_3_.startFadeAnimation(255, animation_duration_);
	ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(255, animation_duration_);
	bc_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	bc_.startFadeAnimation(255, animation_duration_);
}

void Content0207::event3()
{
	ok_.setTouchable(true);

	AbstractContent::event3();

	//em_.addCountDownEvent(6, 1800);
	em_.addLoopChainEvent(17, 1800, 18);
}

void Content0207::event4()
{
	AbstractContent::event4();

	animation_lock_ = 10;

	ok_.setTouchable(false);
	
	//title_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	title_.startFadeAnimation(0, animation_duration_);
	//tfa_1_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	tfa_1_.startFadeAnimation(0, animation_duration_);
	//tfa_2_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	tfa_2_.startFadeAnimation(0, animation_duration_);
	//tfa_3_.setFadeAnimationEndedAction(textarea_fade_ended_callback_);
	tfa_3_.startFadeAnimation(0, animation_duration_);
	//tfb_11_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_11_.startFadeAnimation(0, animation_duration_);
	//tfb_12_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_12_.startFadeAnimation(0, animation_duration_);
	//tfb_2_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_2_.startFadeAnimation(0, animation_duration_);
	//tfb_3_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	tfb_3_.startFadeAnimation(0, animation_duration_);
	//ok_.setFadeAnimationEndedAction(buttonwithlabel_fade_ended_callback_);
	ok_.startFadeAnimation(0, animation_duration_);
	//bc_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	bc_.startFadeAnimation(0, animation_duration_);
}

void Content0207::event5()
{
	AbstractContent::event5();
}

void Content0207::event6()
{
	AbstractContent::event6();

	event4();
}

void Content0207::event17()
{
	if (0 == (em_.getOp1(17) % 60))
	{
		int t = em_.getOp1(17) / 60;
		Unicode::UnicodeChar str[4] = { 0 };
		Unicode::snprintf(str, 3, "%d", t);
		int str_len = sizeof(str) / sizeof(Unicode::UnicodeChar);
		bc_buffer_[str_len - 1] = '\0';
		Unicode::strncpy(bc_buffer_, str, str_len);
		bc_.setWildcard(bc_buffer_);
		bc_.invalidate();	

		if (1 == t)
		{
			buttonClickedHandler(ok_);
		}
	}
}

void Content0207::event18()
{
	//char cd[] = { 51, 48 };
	//int bc_buffer_len = sizeof(cd) / sizeof(const char);
	//bc_buffer_[bc_buffer_len] = 0;
	//Unicode::strncpy(bc_buffer_, cd, bc_buffer_len);
	//bc_.setWildcard(bc_buffer_);
}

//
//void Content0207::event10()
//{
//	title_.setTypedText(TypedText(T_S21_TITLE));
//	title_.setColor(Color::getColorFromRGB(255, 255, 255));
//	title_.setPosition(40, 50, 558, 140);
//	title_.setAlpha(255);
//	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
//	title_.invalidate();
//
//	figure_.setBitmap(Bitmap(BITMAP_INFO_DRAG_2_ID));
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
//void Content0207::event11()
//{
//	title_.setTypedText(TypedText(T_S21_TITLE));
//	title_.setColor(Color::getColorFromRGB(255, 255, 255));
//	title_.setPosition(40, 50, 558, 140);
//	title_.setAlpha(255);
//	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
//	title_.invalidate();
//
//	figure_.setBitmap(Bitmap(BITMAP_INFO_DRAG_3_ID));
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
//void Content0207::event12()
//{
//	title_.setTypedText(TypedText(T_S21_TITLE));
//	title_.setColor(Color::getColorFromRGB(255, 255, 255));
//	title_.setPosition(40, 50, 558, 140);
//	title_.setAlpha(255);
//	title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
//	title_.invalidate();
//
//	figure_.setBitmap(Bitmap(BITMAP_INFO_DRAG_1_ID));
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
