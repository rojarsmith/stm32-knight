#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/widgets/socket_selector/SocketSelector.hpp>
#include <touchgfx/hal/HAL.hpp>

SocketSelector::SocketSelector()
	:
	animation_stage_(AnimationStage::ANIMATING_STAGE_NONE),
	item_move_animation_ended_callback_(this, &SocketSelector::barMoveAnimationEndedHandler),
	selector_move_out_callback_(this, &SocketSelector::selectorMoveAnimationEndHandler)
{	
}

SocketSelector::~SocketSelector()
{
	Application::getInstance()->unregisterTimerWidget(this); //TODO : not sure.
}

void SocketSelector::initialize(MachineStatus* status)
{
	ms_ = status;

	item_.initialize(ms_);
	item_.setPosition(65, 62, 350, 62); // 800x480
	//item_.setPosition(104, 100, 560, 100);
	item_.setVisible(false);
	item_.setSocketSelectedCallback(selector_move_out_callback_);
	add(item_);

	Application::getInstance()->registerTimerWidget(this);
}

void SocketSelector::setStyle(WeatherStyle style)
{
	style_ = style;
}

void SocketSelector::setSlideDuration(int tick)
{
	ANIMATION_DURATION_S1_ = tick;
}

void SocketSelector::setTouch(bool touchable)
{
	if (true == touchable)
	{
		item_.setTouchable(true);
	}
	else
	{
		item_.setTouchable(false);
	}
}

void SocketSelector::beginSlideAnimation(AnimationStyle animation, bool is_right)
{	
	item_.setVisible(true);

	switch (animation)
	{
	case SLIDE_IN:
		if (is_right)
		{
			item_.setXY(HAL::DISPLAY_WIDTH, 0);
		}
		else
		{
			item_.setXY(-350, 0);
			//item_.setXY(-560, 0);
		}
		//item_.startMoveAnimation(104, 0, ANIMATION_TRANSITION_IN_DURATION, EasingEquations::linearEaseIn);
		item_.startMoveAnimation(65, 0, ANIMATION_TRANSITION_IN_DURATION, EasingEquations::linearEaseIn);
		break;	
	case SLIDE_IN_FROM_BOTTON:
		item_.setXY(65, 187);
		//item_.setXY(104, 300);
		//item_.startMoveAnimation(104, 0, ANIMATION_TRANSITION_IN_DURATION, EasingEquations::linearEaseIn);
		item_.startMoveAnimation(65, 0, ANIMATION_TRANSITION_IN_DURATION, EasingEquations::linearEaseIn);
		break;
	case SLIDE_OUT_TO_BOTTON:
		item_.setXY(65, 0);
		//item_.setXY(104, 0);
		//item_.startMoveAnimation(104, 300, ANIMATION_TRANSITION_IN_DURATION, EasingEquations::linearEaseIn);
		item_.startMoveAnimation(65, 187, ANIMATION_TRANSITION_IN_DURATION, EasingEquations::linearEaseIn);
		break;
	}
}

void SocketSelector::setSocketSlidingCallback(GenericCallback<int>& callback)
{
	item_.setIndicatorDragCallback(callback);
}

void SocketSelector::setPlugNotInSocketCallback(GenericCallback<ChargeSocketSelected>& callback)
{	
	plug_not_in_socket_callback_ = &callback;	
}

void SocketSelector::setBarMoveOutAnimationEndCallback(GenericCallback<ChargeSocketSelected>& callback)
{
	bar_move_out_animation_end_callback_ = &callback;
}

void SocketSelector::selectorMoveAnimationEndHandler(ChargeSocketSelected socket)
{	
	ms_->operation_charge_socket_selected = socket;
		
	
	//if (ms_->ux_drag_selector_vx > 220)
	if (ms_->ux_drag_selector_vx > 137)
	{
		ms_->operation_charge_socket_selected = ChargeSocketSelected::CHARGE_SOCKET_RIGHT;
	}
	//else if (ms_->ux_drag_selector_vx < -220)
	else if (ms_->ux_drag_selector_vx < -137)
	{
		ms_->operation_charge_socket_selected = ChargeSocketSelected::CHARGE_SOCKET_LEFT;
	}

	if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == ms_->operation_charge_socket_selected)
	{
		if (UXSocketStatus::UX_SOCKET_AVAILABLE == ms_->ux_socket_status_right)
		{
			animation_stage_ = ANIMATING_STAGE_OUT_SCREEN_1;
			item_.setMoveAnimationEndedAction(item_move_animation_ended_callback_);
			item_.startMoveAnimation(item_.getX() - 25, item_.getY(), ANIMATION_DURATION_S1_, EasingEquations::linearEaseIn);
			//item_.startMoveAnimation(item_.getX() - 40, item_.getY(), ANIMATION_DURATION_S1_, EasingEquations::linearEaseIn);
		}
		else
		{
			plug_not_in_socket_callback_->execute(socket);
		}
	}
	else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		if (UXSocketStatus::UX_SOCKET_AVAILABLE == ms_->ux_socket_status_left)
		{
			animation_stage_ = ANIMATING_STAGE_OUT_SCREEN_1;
			item_.setMoveAnimationEndedAction(item_move_animation_ended_callback_);
			item_.startMoveAnimation(item_.getX() + 25, item_.getY(), ANIMATION_DURATION_S1_, EasingEquations::linearEaseIn);
			//item_.startMoveAnimation(item_.getX() + 40, item_.getY(), ANIMATION_DURATION_S1_, EasingEquations::linearEaseIn);
		}
		else
		{
			plug_not_in_socket_callback_->execute(socket);
		}
	}
	else if (ms_->ux_socket_status_limit)
	{
		plug_not_in_socket_callback_->execute(socket);
	}
}

void SocketSelector::handleClickEvent(const ClickEvent& evt)
{
	if (evt.getType() == ClickEvent::PRESSED)
	{	
	}
}

void SocketSelector::updateView()
{

}

void SocketSelector::barMoveAnimationEndedHandler(const MoveAnimator<SocketSelectorBar>& source)
{
	if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == ms_->operation_charge_socket_selected &&
		animation_stage_ == ANIMATING_STAGE_OUT_SCREEN_1)
	{
		animation_stage_ = ANIMATING_STAGE_OUT_SCREEN_2;
		item_.startMoveAnimation(HAL::DISPLAY_WIDTH, item_.getY(), ANIMATION_DURATION_S2_, EasingEquations::linearEaseIn);
	}
	else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected &&
		animation_stage_ == ANIMATING_STAGE_OUT_SCREEN_1)
	{
		animation_stage_ = ANIMATING_STAGE_OUT_SCREEN_2;
		item_.startMoveAnimation(-HAL::DISPLAY_WIDTH, item_.getY(), ANIMATION_DURATION_S2_, EasingEquations::linearEaseIn);
	}
	else if (animation_stage_ == ANIMATING_STAGE_OUT_SCREEN_2)
	{
		animation_stage_ = ANIMATING_STAGE_NONE;
		bar_move_out_animation_end_callback_->execute(ms_->operation_charge_socket_selected);
	}
}

void SocketSelector::event_3()
{

}