#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/widgets/socket_selector/SocketSelectorBar.hpp>

SocketSelectorBar::SocketSelectorBar()
	:
	vx_(0),
	current_animation_state_(NO_ANIMATION),
	draw_interval(2),
	is_grabbed_(false),
	is_animate_indicator_(false),
	is_animate_indicator_hack_(false),
	shift_x_indicator_direction_(10),
	right_cut_off_(SELECTOR_CORRDINATE_RIGHT_LIMIT - 9),
    left_cut_off_(SELECTOR_CORRDINATE_LEFT_LIMIT - 9),
	valid_selected_threshold_(35),
	charge_socket_selected_(ChargeSocketSelected::CHARGE_SOCKET_NONE),
	container_move_ended_callback_(this, &SocketSelectorBar::containerMoveEndedHandler),
	indicator_drag_callback_(nullptr)
{		
	indicator_width_helf_ = Bitmap(BITMAP_SLIDER_SELECTOR_ID).getWidth() / 2;
	indicator_width_quarter_ = indicator_width_helf_ / 2;

	doriginal_point_ = ORIGINAL_POINT_ - indicator_width_helf_;

	vgrab_threshold_right_ = DIRECTION_NOT_ALLOW_MAX_DISPLAY_POSITION_;
	vgrab_threshold_left_ = -DIRECTION_NOT_ALLOW_MAX_DISPLAY_POSITION_;

	vnot_allow_selecte_threshold_right_ = indicator_width_quarter_;
	vnot_allow_selecte_threshold_left_ = -indicator_width_quarter_;

	dnot_allow_selecte_threshold_right_ = doriginal_point_ + vnot_allow_selecte_threshold_right_;
	dnot_allow_selecte_threshold_left_ = doriginal_point_ + vnot_allow_selecte_threshold_left_;

	vvalid_selected_threshold_right_ = SELECTOR_SIZE_ - (indicator_width_quarter_ * 3);
	vvalid_selected_threshold_left_ = -SELECTOR_SIZE_ + (indicator_width_quarter_ * 3);

	right_grab_threshold_ = ORIGINAL_POINT_ + indicator_width_helf_ + 10;
	left_grab_threshold_ = ORIGINAL_POINT_ - indicator_width_helf_ - 10;
}

SocketSelectorBar::~SocketSelectorBar()
{
	Application::getInstance()->unregisterTimerWidget(this);	
}

void SocketSelectorBar::handleClickEvent(const ClickEvent& evt)
{
	if (evt.getType() == ClickEvent::PRESSED)
	{
		if (current_animation_state_ == NO_ANIMATION &&
			evt.getX() > left_grab_threshold_ &&
			evt.getX() < right_grab_threshold_)
		{
			is_grabbed_ = true;
			//is_animate_indicator_ = true;
			current_animation_state_ = ANIMATING_DRAG;
		}
	}
	else if (evt.getType() == ClickEvent::RELEASED && current_animation_state_ == ANIMATING_DRAG && is_grabbed_ == true)
	{
		is_grabbed_ = false;
		//is_animate_indicator_ = true;
		//snap(evt.getX());
		snap(ms_->ux_drag_selector_vx);
	}
}

void SocketSelectorBar::handleDragEvent(const DragEvent& evt)
{
	if (ANIMATING_DRAG == current_animation_state_ && true == is_grabbed_)
	{
		vx_ = ind_.getX() + evt.getDeltaX() + indicator_width_helf_ - ORIGINAL_POINT_;

	    int delta_x = evt.getDeltaX();
		moveIndicator(ind_.getX() + delta_x);
	}
}



void SocketSelectorBar::handleTickEvent()
{	
	ms_->ux_drag_selector_vx_prev = ms_->ux_drag_selector_vx;
	ms_->ux_drag_selector_x_prev = ms_->ux_drag_selector_x;
	ms_->ux_drag_selector_vx = ind_.getX() + indicator_width_helf_ - ORIGINAL_POINT_;
	ms_->ux_drag_selector_x = vx_;


	if (0 == (tick_ % draw_interval))
	{
		if (ms_->ux_drag_selector_vx_prev != ms_->ux_drag_selector_vx)
		{
			adjustIndicatorDirectionAlpha(ms_->ux_drag_selector_vx);
		}
	}
	//Not correct
	/*if ((0 == (tick_ % draw_interval)) && is_animate_indicator_ && false == is_animate_indicator_hack_)
	{
		int alpha = (int)(ind_.getX() * 1.1);
		indicator_drag_callback_->execute(alpha);
	}*/

	//if (is_animate_indicator_ || is_grabbed_ )//&& false == is_animate_indicator_hack_)
	//{
	//	//int alpha = (int)(ind_.getX() * 1.1);
		//indicator_drag_callback_->execute(ind_.getX() + indicator_width_helf_ - original_point_);
	//}

	tick_++;
}

void SocketSelectorBar::initialize(MachineStatus* status)
{
	ms_ = status;

	//Item
	socket_slider_animation_right_.setSide(true);
	socket_slider_animation_right_.initialize(ms_);
	socket_slider_animation_right_.setAnimationInterval(4);	
	socket_slider_animation_right_.setPosition(175, 0, 175, 62);
	//socket_slider_animation_right_.setPosition(280, 0, 280, 100);
	add(socket_slider_animation_right_);

	//Item
	socket_slider_animation_left_.setSide(false);
	socket_slider_animation_left_.initialize(ms_);
	socket_slider_animation_left_.setAnimationInterval(4);	
	socket_slider_animation_left_.setPosition(0, 0, 175, 62);
	//socket_slider_animation_left_.setPosition(0, 0, 280, 100);
	add(socket_slider_animation_left_);

	//Item Group		
	ind_.setPosition(ORIGINAL_POINT_ - indicator_width_helf_, 9, 43, 43);
	//ind_.setPosition(ORIGINAL_POINT_ - indicator_width_helf_, 15 ,70, 70);
	ind_.setMoveAnimationEndedAction(container_move_ended_callback_);

	indicator_.setBitmap(Bitmap(BITMAP_SLIDER_SELECTOR_ID));
    indicator_.setXY(0, 0);
	ind_.add(indicator_);

	indicator_direction_.setBitmap(Bitmap(BITMAP_SLIDER_SELECTOR_DIRECTION_ID));
	indicator_direction_.setXY(shift_x_indicator_direction_, 12);
	//indicator_direction_.setXY(shift_x_indicator_direction_, 20);
	ind_.add(indicator_direction_);

	add(ind_);

	this->setTouchable(true);
	Application::getInstance()->registerTimerWidget(this);
}

void SocketSelectorBar::moveIndicator(int new_x_position)
{
	if (0 < new_x_position - ORIGINAL_POINT_) 
	{
		adjustForBoundriesRight(new_x_position);
	}
	else if (0 > new_x_position - ORIGINAL_POINT_)
	{
		adjustForBoundriesLeft(new_x_position);
	}
	
	ind_.moveTo(new_x_position, ind_.getY());
}

void SocketSelectorBar::animateIndicator(int new_x_position, int duration, EasingEquation equation)
{
	is_animate_indicator_ = true;
	
	int y = ind_.getY();
	//ind_.setMoveAnimationEndedAction(container_move_ended_callback_);

	//if (0 == (tick_ % draw_interval))
	//{
		ind_.startMoveAnimation(
			new_x_position,
			y,
			duration,
			equation,
			EasingEquations::linearEaseNone);
	//}
}

void SocketSelectorBar::adjustIndicatorDirectionAlpha(int x)
{
	int alpha = encodeToAlpha(x);

	indicator_direction_.setAlpha(alpha);
	indicator_direction_.invalidate();
}

void SocketSelectorBar::adjustForBoundriesRight(int& new_x_value)
{	
	if (UXSocketStatus::UX_SOCKET_AVAILABLE == ms_->ux_socket_status_right &&
		UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_right &&
		new_x_value > right_cut_off_)
	{		
		new_x_value = right_cut_off_;
	}
	else if (UXSocketStatus::UX_SOCKET_AVAILABLE == ms_->ux_socket_status_right &&
		UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_right)
	{
	}
	else
	{
		if (dnot_allow_selecte_threshold_right_ < new_x_value)
		{
			ms_->ux_socket_status_limit = true;
			new_x_value = dnot_allow_selecte_threshold_right_;
			ms_->ux_socket_status_limit_target = ChargeSocketSelected::CHARGE_SOCKET_RIGHT;
		}
	}
}
void SocketSelectorBar::adjustForBoundriesLeft(int& new_x_value)
{
    if (UXSocketStatus::UX_SOCKET_AVAILABLE == ms_->ux_socket_status_left &&
		UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_left &&
		new_x_value < left_cut_off_)
	{
		new_x_value = left_cut_off_;
	}
	else if (UXSocketStatus::UX_SOCKET_AVAILABLE == ms_->ux_socket_status_left &&
		UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_left)
	{

	}
	else
	{
		if (dnot_allow_selecte_threshold_left_ > new_x_value)
		{
			ms_->ux_socket_status_limit = true;
			new_x_value = dnot_allow_selecte_threshold_left_;
			ms_->ux_socket_status_limit_target = ChargeSocketSelected::CHARGE_SOCKET_LEFT;
		}
	}
}

void SocketSelectorBar::snap(int x)
{
	current_animation_state_ = ANIMATING_SNAP;
	
	if (UXSocketStatus::UX_SOCKET_CHARGING == ms_->ux_socket_status_right &&
		vnot_allow_selecte_threshold_right_ < x)
	{
		charge_socket_selected_ = ChargeSocketSelected::CHARGE_SOCKET_RIGHT;
		animateIndicator(doriginal_point_, 30, EasingEquations::quadEaseOut);
	}
	else if (UXSocketStatus::UX_SOCKET_CHARGING == ms_->ux_socket_status_left &&
		vnot_allow_selecte_threshold_left_ > x)
	{
		charge_socket_selected_ = ChargeSocketSelected::CHARGE_SOCKET_LEFT;
		animateIndicator(doriginal_point_, 30, EasingEquations::quadEaseOut);
	}
	else if (vvalid_selected_threshold_right_ < x)
	{
		charge_socket_selected_ = ChargeSocketSelected::CHARGE_SOCKET_RIGHT;
		animateIndicator(doriginal_point_ + SELECTOR_SIZE_, 30, EasingEquations::quadEaseOut);
	}
	else if (vvalid_selected_threshold_left_ > x)
	{
		charge_socket_selected_ = ChargeSocketSelected::CHARGE_SOCKET_LEFT;
		animateIndicator(doriginal_point_ - SELECTOR_SIZE_, 30, EasingEquations::quadEaseOut);
	}
	else 
	{
		charge_socket_selected_ = ChargeSocketSelected::CHARGE_SOCKET_NONE;
		animateIndicator(doriginal_point_, 30, EasingEquations::linearEaseIn);
	}	
}

int SocketSelectorBar::encodePhase(int src, int src_rng_start, int src_rng_end, int dist_rng_start, int dist_rng_end)
{
	return 0;
}

int SocketSelectorBar::encodeToAlpha(int src)
{	
	if (0 == src) return 255;

	if (src < 0)
	{
		src *= -1;
	}

	if (src > DIRECTION_MAX_DISPLAY_POSITION_) return 0;	

	src = DIRECTION_MAX_DISPLAY_POSITION_ - src;

	float unit = (float)255 / DIRECTION_MAX_DISPLAY_POSITION_;
	int alpha = (int)(unit * src);

	return alpha;
}

void SocketSelectorBar::setIndicatorDragCallback(GenericCallback<int>& callback)
{
	indicator_drag_callback_ = &callback;
}

void SocketSelectorBar::setSocketSelectedCallback(GenericCallback<ChargeSocketSelected>& callback)
{
	socket_selected_callback_ = &callback;
}

void SocketSelectorBar::updateView()
{
}

void SocketSelectorBar::containerMoveEndedHandler(const MoveAnimator<Container>& container)
{
	if (current_animation_state_ == ANIMATING_SNAP)
	{
		current_animation_state_ = NO_ANIMATION;

		if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == charge_socket_selected_ && SELECTOR_SIZE_ <= ms_->ux_drag_selector_vx)
		{
			indicator_direction_.setVisible(false);
			socket_slider_animation_right_.setTargetCircleAnimate(true);
		}
		else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == charge_socket_selected_ && (-SELECTOR_SIZE_) >= ms_->ux_drag_selector_vx)
		{
			indicator_direction_.setVisible(false);
			socket_slider_animation_left_.setTargetCircleAnimate(true);
		}
		else
		{
			indicator_direction_.setVisible(true);
			socket_slider_animation_right_.setTargetCircleAnimate(false);
			socket_slider_animation_left_.setTargetCircleAnimate(false);
		}

		indicator_direction_.invalidate();
		socket_selected_callback_->execute(charge_socket_selected_);
	}
	else
	{
		current_animation_state_ = NO_ANIMATION;
	}

	indicator_direction_.invalidate();
	is_animate_indicator_ = false;
}

void SocketSelectorBar::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 1:
		event1();
		break;
	case 2:
		event2();
		break;
	case 3:
		event3();
		break;
	}
}

void SocketSelectorBar::event1()
{

}

void SocketSelectorBar::event2()
{
}

void SocketSelectorBar::event3()
{

}

