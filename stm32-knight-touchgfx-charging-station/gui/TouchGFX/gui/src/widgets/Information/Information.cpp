#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/information/Information.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Information::Information()
	:	
	ms_(nullptr),
	in_animation_duration_(60),	
	transition_in_animation_ended_callback_(nullptr),
	transition_out_animation_ended_callback_(nullptr),
	on_button_clicked_(this, &Information::buttonClickedHandler)
{	
}

Information::~Information()
{	
}

void Information::initialize(MachineStatus* status)
{
	ms_ = status;

	info_.setVisible(false);
	info_.setAction(on_button_clicked_);
	add(info_);

	renderGraphic();
}

void Information::renderGraphic()
{
	if (ScreenNumber::SCREEN_BOOT == ms_->ux_screen_id_current ||
		ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
	{
		info_.setVisible(false);
	}
	else
	{
		info_.setVisible(true);

		if (WeatherStyle::NIGHT == ms_->ux_weather)
		{
			info_.setBitmaps(Bitmap(BITMAP_INFORMATION_NIGHT_ID), Bitmap(BITMAP_INFORMATION_NIGHT_ID));
		}
		else
		{
			info_.setBitmaps(Bitmap(BITMAP_INFORMATION_DAY_ID), Bitmap(BITMAP_INFORMATION_DAY_ID));
		}
	}

	info_.setXY(0, 0);
}

void Information::setInAnimationDuration(int duration)
{
	in_animation_duration_ = duration;
}

void Information::setOutAnimationDuration(int duration)
{
	out_animation_duration_ = duration;
}

void Information::setDeepTouchable(bool touchable)
{
	info_.setTouchable(touchable);
}

void Information::setInformationXY(int x, int y)
{
	info_.setXY(x, y);
}

void Information::setButtonClickedCallback(GenericCallback<const int>& callback)
{
	button_clicked_callback_ = &callback;
}

void Information::setTransitionInAnimationEndedCallback(GenericCallback<const int>& callback)
{
	transition_in_animation_ended_callback_ = &callback;
}

void Information::setTransitionOutAnimationEndedCallback(GenericCallback<const int>& callback)
{
	transition_out_animation_ended_callback_ = &callback;
}

void Information::buttonClickedHandler(const AbstractButton& button)
{
	button_clicked_callback_->execute(0);
}

void Information::beginTransitionInAnimation()
{
}

void Information::beginTransitionOutAnimation()
{
}

void Information::saveContainerStatus()
{	
}