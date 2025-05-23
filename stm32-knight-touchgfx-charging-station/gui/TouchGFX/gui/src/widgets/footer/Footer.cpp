#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/footer/Footer.hpp>
#include <touchgfx/hal/HAL.hpp>

Footer::Footer()
	:	
	animation_duration_(60),
	slide_animation_ended_callback_(0),
	itemMoveAnimationEndedCallback(this, &Footer::itemMoveAnimationEndedHandler)
{	
}

Footer::~Footer()
{
	
}

void Footer::initialize(MachineStatus* status)
{
	ms_ = status;

	footer_.initialize(status);
	footer_.setPosition(
		0,
		ms_->footer_y,
		HAL::DISPLAY_WIDTH,
		APPEARANCE_HEIGHT);
	footer_.setMoveAnimationEndedAction(itemMoveAnimationEndedCallback);
	add(footer_);

	footer_.renderElementLowSpeed();
}

void Footer::renderGraphic()
{
	footer_.renderGraphic();
}

void Footer::setAnimationDuration(int duration)
{
	animation_duration_ = duration;
}

void Footer::setItemXY(int x, int y)
{
	footer_.setXY(x, y);
}

void Footer::beginSlideAnimation(AnimationStyle animation)
{
	switch (animation)
	{
	case SLIDE_IN:
		footer_.startMoveAnimation(0, 0, animation_duration_, EasingEquations::linearEaseIn);
		break;
	case SLIDE_OUT:
		footer_.startMoveAnimation(0, APPEARANCE_HEIGHT, animation_duration_, EasingEquations::linearEaseIn);
		break;
	case STATIC_IN:
		footer_.startMoveAnimation(0, 0, animation_duration_, EasingEquations::linearEaseIn);
		break;	
	default:
		footer_.setXY(0, 0);
		footer_.invalidate();
		break;
	}	
}

void Footer::setSlideAnimationEndedCallback(GenericCallback<const uint8_t>& callback)
{
	slide_animation_ended_callback_ = &callback;
}

void Footer::itemMoveAnimationEndedHandler(const MoveAnimator<FooterItemGroup>& source)
{
    saveElementStatus();

	if (slide_animation_ended_callback_ &&
		slide_animation_ended_callback_->isValid()) {
		slide_animation_ended_callback_->execute(0);
	}
}

void Footer::saveElementStatus() 
{
	ms_->footer_y = footer_.getY();
}