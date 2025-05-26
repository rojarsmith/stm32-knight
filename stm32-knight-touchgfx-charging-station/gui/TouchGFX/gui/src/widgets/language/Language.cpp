#include <gui/widgets/language/Language.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

Language::Language()
	:
	is_opened(false),
	integration_closed_callback_(this, &Language::integrationClosedHandler),
	button_clicked_(this, &Language::buttonClickedHandler),
	image_fade_ended_callback_(this, &Language::imageFadeEndedHandler),
	image_move_ended_callback_(this, &Language::imageMoveEndedHandler),
	button_fade_ended_callback_(this, &Language::buttonFadeEndedHandler),
	button_move_ended_callback_(this, &Language::buttonMoveEndedHandler),
	textareawithonewildcard_fade_ended_callback_(this, &Language::textareawithonewildcardFadeEndedHandler),
    textareawithonewildcard_move_ended_callback_(this, &Language::textareawithonewildcardMoveEndedHandler)
{	
}

Language::~Language()
{
}

void Language::initialize(MachineStatus* status)
{
	ms_ = status;
	
	background_left_.setBitmap(Bitmap(BITMAP_LANGUAGE_LEFT_ID));
	background_left_.setXY(0, 0);
	background_left_.setVisible(false);
	add(background_left_);

	view_port_.setPosition(20, 0, 221, 40); //800x480
	//view_port_.setPosition(32, 0, 354, 64);

	background_right_.setBitmap(Bitmap(BITMAP_LANGUAGE_RIGHT_ID));
	background_right_.setXY(0 - 201, 0);
	//background_right_.setXY(0 - 322, 0);
	background_right_.setVisible(false);
	view_port_.add(background_right_);

	add(view_port_);

	america_.setBitmaps(Bitmap(BITMAP_LANGUAGE_AMERICA_ID), Bitmap(BITMAP_LANGUAGE_AMERICA_ID));
	america_.setXY(6, icon_y_);
	//america_.setXY(10, 10);
	america_.setAction(button_clicked_);
	america_.setVisible(false);

	spain_.setBitmaps(Bitmap(BITMAP_LANGUAGE_SPAIN_ID), Bitmap(BITMAP_LANGUAGE_SPAIN_ID));
	spain_.setXY(6, icon_y_);
	//spain_.setXY(10, 10);
	spain_.setAction(button_clicked_);
	spain_.setVisible(false);

	germany_.setBitmaps(Bitmap(BITMAP_LANGUAGE_GERMANY_ID), Bitmap(BITMAP_LANGUAGE_GERMANY_ID));
	germany_.setXY(6, icon_y_);
	//germany_.setXY(10, 10);
	germany_.setAction(button_clicked_);
	germany_.setVisible(false);

	france_.setBitmaps(Bitmap(BITMAP_LANGUAGE_FRANCE_ID), Bitmap(BITMAP_LANGUAGE_FRANCE_ID));
	france_.setXY(6, icon_y_);
	//france_.setXY(10, 10);
	france_.setAction(button_clicked_);
	france_.setVisible(false);
	
	switch (ms_->ui_language)
	{
	case LanguageList::SPANISH:
		spain_.setVisible(true);
		break;
	case LanguageList::FRENCH:
		france_.setVisible(true);
		break;
	case LanguageList::GERMAN:
		germany_.setVisible(true);		
		break;
	default:
		america_.setVisible(true);
		break;
	}	

	add(america_);
	add(spain_);
	add(germany_);
	add(france_);

	menu_.setXY(6 + (21 + gap_) * 4, 11);
	//menu_.setXY(10 + (34 + gap_) * 4, 18);
	menu_.setAlpha(255);
	menu_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	menu_.setLinespacing(0);
	menu_.setTypedText(TypedText(T_LANGUAGE_SELECT));
	menu_.setVisible(false);
	add(menu_);

	mask_.setPosition(0, 0, 241, 40);
	//mask_.setPosition(0, 0, 386, 64);
	mask_.setAlpha(0);
	mask_.setTouchable(false);
	add(mask_);
}

void Language::handleTickEvent()
{	
	ContainerEx::handleTickEvent();
}

void Language::openContainer()
{
	open_container_animation_lock_ = 13;

	background_left_.setAlpha(0);
	background_left_.setVisible(true);
	background_left_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	background_left_.startFadeAnimation(255, animation_duration_);

	background_right_.setAlpha(0);
	background_right_.setXY(0 - 201, 0);
	//background_right_.setXY(0 - 322, 0);
	background_right_.setVisible(true);
	background_right_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	background_right_.setMoveAnimationEndedAction(image_move_ended_callback_);
	background_right_.startFadeAnimation(255, animation_duration_);
	background_right_.startMoveAnimation(0, 0, animation_duration_);

	if (LanguageList::ENGISH == ms_->ui_language)
	{
		america_.setAlpha(255);
	}
	else
	{
		america_.setAlpha(0);
	}
	america_.setXY(6, icon_y_);
	//america_.setXY(10, 10);
	america_.setVisible(true);
	america_.setTouchable(true);
	america_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	america_.setMoveAnimationEndedAction(button_move_ended_callback_);
	america_.startFadeAnimation(255, animation_duration_);
	america_.startMoveAnimation(6, icon_y_, animation_duration_);
	//america_.startMoveAnimation(10, 10, animation_duration_);

	if (LanguageList::SPANISH == ms_->ui_language)
	{
		spain_.setAlpha(255);
	}
	else
	{
		spain_.setAlpha(0);
	}
	spain_.setXY(6, icon_y_);
	//spain_.setXY(10, 10);
	spain_.setVisible(true);
	spain_.setTouchable(true);
	spain_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	spain_.setMoveAnimationEndedAction(button_move_ended_callback_);
	spain_.startFadeAnimation(255, animation_duration_);
	spain_.startMoveAnimation(6 + (27 + gap_) * 1, icon_y_, animation_duration_);
	//spain_.startMoveAnimation(10 + (44 + gap_) * 1, 10, animation_duration_);

	if (LanguageList::GERMAN == ms_->ui_language)
	{
		germany_.setAlpha(255);
	}
	else
	{
		germany_.setAlpha(0);
	}
	germany_.setXY(6, icon_y_);
	//germany_.setXY(10, 10);
	germany_.setVisible(true);
	germany_.setTouchable(true);
	germany_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	germany_.setMoveAnimationEndedAction(button_move_ended_callback_);
	germany_.startFadeAnimation(255, animation_duration_);
	germany_.startMoveAnimation(6 + (27 + gap_) * 2, icon_y_, animation_duration_);
	//germany_.startMoveAnimation(10 + (44 + gap_) * 2, 10, animation_duration_);

	if (LanguageList::FRENCH == ms_->ui_language)
	{
		france_.setAlpha(255);
	}
	else
	{
		france_.setAlpha(0);
	}
	france_.setXY(6, icon_y_);
	//france_.setXY(10, 10);
	france_.setVisible(true);
	france_.setTouchable(true);
	france_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	france_.setMoveAnimationEndedAction(button_move_ended_callback_);
	france_.startFadeAnimation(255, animation_duration_);
	france_.startMoveAnimation(6 + (27 + gap_) * 3, icon_y_, animation_duration_);
	//france_.startMoveAnimation(10 + (44 + gap_) * 3, 10, animation_duration_);

	menu_.setAlpha(0);
	menu_.setPosition(6, 11, 102, 37);
	//menu_.setPosition(10, 18, 164, 60);
	//menu_.setXY(10, 18);
	menu_.setVisible(true);
	menu_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	menu_.setMoveAnimationEndedAction(textareawithonewildcard_move_ended_callback_);
	menu_.startFadeAnimation(255, animation_duration_);
	menu_.startMoveAnimation(6 + (21 + gap_) * 4, 11, animation_duration_);
	//menu_.startMoveAnimation(10 + (34 + gap_) * 4, 18, animation_duration_);

	mask_.setTouchable(true);
}

void Language::buttonClickedHandler(const AbstractButton& source)
{
	begin_animation_callback_->execute(0);

	if (&america_ == &source)
	{
		ms_->ui_language = LanguageList::ENGISH;
		Texts::setLanguage(LANGUAGES::GB);
	}
	else if (&spain_ == &source)
	{
		ms_->ui_language = LanguageList::SPANISH;
		Texts::setLanguage(LANGUAGES::SPA);
	}
	else if (&germany_ == &source)
	{
		ms_->ui_language = LanguageList::GERMAN;
		Texts::setLanguage(LANGUAGES::GER);
	}
	else
	{
		ms_->ui_language = LanguageList::FRENCH;
		Texts::setLanguage(LANGUAGES::FRE);
	}
	menu_.invalidate();	

	if (!is_opened)
	{		
		openContainer();
	}
	else 
	{
		integration_.pause();
		integration_.setInterval(1);
		integration_.setTarget(60);
		integration_.setArrivedCallback(integration_closed_callback_);
		integration_.restart();
	}
}

void Language::setBeginAnimationCallback(GenericCallback<const int>& callback)
{
	this->begin_animation_callback_ = &callback;
}

void Language::lock()
{
	background_left_.setTouchable(false);
	view_port_.setTouchable(false);
	background_right_.setTouchable(false);
    america_.setTouchable(false);
    spain_.setTouchable(false);
    germany_.setTouchable(false);
    france_.setTouchable(false);
}

void Language::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	if (!is_opened)
	{
		decreaseOpenContainerAnimationLock();
	}
	else
	{
		decreaseCloseContainerAnimationLock();
	}
}

void Language::imageMoveEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image)
{
	if (!is_opened)
	{
		decreaseOpenContainerAnimationLock();
	}
	else
	{
		decreaseCloseContainerAnimationLock();
	}
}

void Language::buttonFadeEndedHandler(const FadeAnimator<Button>& button)
{
	if (!is_opened)
	{
		decreaseOpenContainerAnimationLock();
	}
	else
	{
		decreaseCloseContainerAnimationLock();
	}
}

void Language::buttonMoveEndedHandler(const MoveAnimator<FadeAnimator<Button>>& button)
{
	if (!is_opened)
	{
		decreaseOpenContainerAnimationLock();
	}
	else
	{
		decreaseCloseContainerAnimationLock();
	}
}

void Language::textareawithonewildcardFadeEndedHandler(const FadeAnimator<TextAreaWithOneWildcard>& text)
{
	if (!is_opened)
	{
		decreaseOpenContainerAnimationLock();
	}
	else
	{
		decreaseCloseContainerAnimationLock();
	}
}

void Language::textareawithonewildcardMoveEndedHandler(const MoveAnimator<FadeAnimator<TextAreaWithOneWildcard>>& text)
{
	if (!is_opened)
	{
		decreaseOpenContainerAnimationLock();
	}
	else
	{
		decreaseCloseContainerAnimationLock();
	}
}

void Language::event_1()
{
	mask_.setTouchable(false);

	is_opened = true;

	integration_.setInterval(1);
	integration_.setTarget(300);
	integration_.setArrivedCallback(integration_closed_callback_);
	integration_.restart();
}

void Language::event_2()
{
	if (ms_->ui_language != LanguageList::ENGISH)
	{
		america_.setVisible(false);
		america_.setTouchable(false);
	}

	if (ms_->ui_language != LanguageList::SPANISH)
	{
		spain_.setVisible(false);
		spain_.setTouchable(false);
	}

	if (ms_->ui_language != LanguageList::GERMAN)
	{
		germany_.setVisible(false);
		germany_.setTouchable(false);
	}

	if (ms_->ui_language != LanguageList::FRENCH)
	{
		france_.setVisible(false);
		france_.setTouchable(false);
	}

	america_.invalidate();
	spain_.invalidate();
	germany_.invalidate();
	france_.invalidate();

	mask_.setTouchable(false);

	is_opened = false;
}

void Language::integrationClosedHandler(const int source)
{
	closeContainer();
}

void Language::closeContainer()
{
	close_container_animation_lock_ = 13;

	background_left_.setAlpha(255);
	background_left_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	background_left_.startFadeAnimation(0, animation_duration_);

	background_right_.setAlpha(255);
	background_right_.setXY(0, 0);
	background_right_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	background_right_.setMoveAnimationEndedAction(image_move_ended_callback_);
	background_right_.startFadeAnimation(0, animation_duration_);
	background_right_.startMoveAnimation(0 - 201, 0, animation_duration_);
	//background_right_.startMoveAnimation(0 - 322, 0, animation_duration_);
	
	america_.setAlpha(255);
	america_.setXY(10, icon_y_);
	america_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	america_.setMoveAnimationEndedAction(button_move_ended_callback_);
	if (LanguageList::ENGISH == ms_->ui_language)
	{
		america_.startFadeAnimation(255, animation_duration_);		
	}
	else
	{				
		america_.startFadeAnimation(0, animation_duration_);		
	}
	america_.startMoveAnimation(6, 6, animation_duration_);
	//america_.startMoveAnimation(10, 10, animation_duration_);

	spain_.setAlpha(255);
	spain_.setXY(6 + (27 + gap_) * 1, icon_y_);
	//spain_.setXY(10 + (44 + gap_) * 1, 10);
	spain_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	spain_.setMoveAnimationEndedAction(button_move_ended_callback_);
	if (LanguageList::SPANISH == ms_->ui_language)
	{
		spain_.startFadeAnimation(255, animation_duration_);
	}
	else
	{
		spain_.startFadeAnimation(0, animation_duration_);
		
	}
	spain_.startMoveAnimation(10, icon_y_, animation_duration_);

	germany_.setAlpha(255);
	germany_.setXY(6 + (27 + gap_) * 2, icon_y_);
	//germany_.setXY(10 + (44 + gap_) * 2, 10);
	germany_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	germany_.setMoveAnimationEndedAction(button_move_ended_callback_);
	if (LanguageList::GERMAN == ms_->ui_language)
	{	
		germany_.startFadeAnimation(255, animation_duration_);
	}
	else
	{
		germany_.startFadeAnimation(0, animation_duration_);		
	}
	germany_.startMoveAnimation(10, 10, animation_duration_);

	france_.setAlpha(255);
	france_.setXY(6 + (27 + gap_) * 3, icon_y_);
	//france_.setXY(10 + (44 + gap_) * 3, 10);
	france_.setFadeAnimationEndedAction(button_fade_ended_callback_);
	france_.setMoveAnimationEndedAction(button_move_ended_callback_);
	if (LanguageList::FRENCH == ms_->ui_language)
	{
		france_.startFadeAnimation(255, animation_duration_);
	}
	else
	{
		france_.startFadeAnimation(0, animation_duration_);
	}
	france_.startMoveAnimation(6, 6, animation_duration_);
	//france_.startMoveAnimation(10, 10, animation_duration_);

	menu_.setAlpha(255);
	menu_.setXY(6 + (21 + gap_) * 4, 11);
	//menu_.setXY(10 + (34 + gap_) * 4, 18);
	menu_.setFadeAnimationEndedAction(textareawithonewildcard_fade_ended_callback_);
	menu_.setMoveAnimationEndedAction(textareawithonewildcard_move_ended_callback_);	
	menu_.startFadeAnimation(0, animation_duration_);
	menu_.startMoveAnimation(6, 11, animation_duration_);
	//menu_.startMoveAnimation(10, 18, animation_duration_);

	mask_.setTouchable(true);
}
