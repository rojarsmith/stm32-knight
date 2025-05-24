#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/backto/Backto.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Backto::Backto()
	:	
	ms_(nullptr),
	in_animation_duration_(60),	
	transition_in_animation_ended_callback_(nullptr),
	transition_out_animation_ended_callback_(nullptr),
	on_button_clicked_(this, &Backto::buttonClickedHandler)
{	
}

Backto::~Backto()
{	
}

void Backto::initialize(MachineStatus* status)
{
	ms_ = status;

	back_.setVisible(false);
	back_.setAction(on_button_clicked_);
	add(back_);

	renderGraphic();
}

void Backto::renderGraphic()
{
	if (ScreenNumber::SCREEN_BOOT == ms_->ux_screen_id_current ||
		ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current ||
		ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current)
	{
		back_.setVisible(false);
	}
	else
	{
		back_.setVisible(true);

		if (WeatherStyle::NIGHT == ms_->ux_weather)
		{
			back_.setBitmaps(Bitmap(BITMAP_RETURN_NIGHT_ID), Bitmap(BITMAP_RETURN_NIGHT_ID));
		}
		else
		{
			back_.setBitmaps(Bitmap(BITMAP_RETURN_DAY_ID), Bitmap(BITMAP_RETURN_DAY_ID));
		}
	}	
	
	back_.setXY(0, 0);
}

void Backto::setInAnimationDuration(int duration)
{
	in_animation_duration_ = duration;
}

void Backto::setOutAnimationDuration(int duration)
{
	out_animation_duration_ = duration;
}

void Backto::setBacktoXY(int x, int y)
{
	back_.setXY(x, y);
}

void Backto::setButtonClickedCallback(GenericCallback<const int>& callback)
{
	button_clicked_callback_ = &callback;
}

void Backto::setTransitionInAnimationEndedCallback(GenericCallback<const int>& callback)
{
	transition_in_animation_ended_callback_ = &callback;
}

void Backto::setTransitionOutAnimationEndedCallback(GenericCallback<const int>& callback)
{
	transition_out_animation_ended_callback_ = &callback;
}

void Backto::buttonClickedHandler(const AbstractButton& button)
{
	button_clicked_callback_->execute(0);
}

void Backto::beginTransitionInAnimation()
{
}

void Backto::beginTransitionOutAnimation()
{
}

void Backto::saveContainerStatus()
{	
}