#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/widgets/socket/Socket.hpp>
#include <touchgfx/Application.hpp>
#include <touchgfx/hal/HAL.hpp>

Socket::Socket(bool isMirrorMode, MachineStatus *machineStatus)
	:	
	ux_socket_status_right_prv_(UXSocketStatus::UX_SOCKET_ERROR),
    ux_socket_status_left_prv_(UXSocketStatus::UX_SOCKET_ERROR),
	ms_(nullptr),
	animation_stage_(ANIMATION_STOP),
	original_point_(280),	
	alpha_(255),
	alpha_delta_(0),
	direction_(0),
	tick_(0),
	item_zoom_animation_ended_callback_(this, &Socket::itemZoomAnimationEndedHandler)
{
	
}

Socket::~Socket()
{	
	saveMachineStatus();
	
	Application::getInstance()->unregisterTimerWidget(this);
}

void Socket::initialize(MachineStatus *status, bool is_mirror)
{
	ms_ = status;
	is_mirror_ = is_mirror;
	ux_socket_status_right_prv_ = ms_->ux_socket_status_right;

	Application::getInstance()->registerTimerWidget(this);

	socket_.setAnimationEndedCallback(item_zoom_animation_ended_callback_);
	add(socket_);

	renderElement();
}

void Socket::renderGraphic()
{
	if ((!is_mirror_ && ux_socket_status_right_prv_ != ms_->ux_socket_status_right) ||
		(is_mirror_ && ux_socket_status_left_prv_ != ms_->ux_socket_status_left))
	{
		renderElement();
	}
}

void Socket::renderElement()
{
	if (!is_mirror_)
	{
			ms_->socket_right_image_id_small = getSocketSmallRightBitmapID();
			ms_->socket_right_image_id_large = getSocketLargeRightBitmapID();

			socket_.setBitmaps(Bitmap(ms_->socket_right_image_id_small), Bitmap(ms_->socket_right_image_id_large));
			if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
			{
				socket_.setPosition(
					HAL::DISPLAY_WIDTH,
					263, // 800x480
					//421,
					ms_->socket_right_previous_width,
					ms_->socket_right_previous_height);
			}
			else
			{
				socket_.setPosition(
					ms_->socket_right_previous_x,
					ms_->socket_right_previous_y,
					ms_->socket_right_previous_width,
					ms_->socket_right_previous_height);
			}
			socket_.setAlpha(ms_->socket_right_previous_alpha);

			ux_socket_status_right_prv_ = ms_->ux_socket_status_right;		
	}
	else
	{		
			ms_->socket_left_image_id_small = getSocketSmallLeftBitmapID();
			ms_->socket_left_image_id_large = getSocketLargeLeftBitmapID();

			socket_.setBitmaps(Bitmap(ms_->socket_left_image_id_small), Bitmap(ms_->socket_left_image_id_large));
			if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
			{
				socket_.setPosition(
					-96,
					421,
					ms_->socket_right_previous_width,
					ms_->socket_right_previous_height);
			}
			else 
			{
				socket_.setPosition(
					ms_->socket_left_previous_x,
					ms_->socket_left_previous_y,
					ms_->socket_left_previous_width,
					ms_->socket_left_previous_height);
			}
			socket_.setAlpha(ms_->socket_left_previous_alpha);

			ux_socket_status_left_prv_ = ms_->ux_socket_status_left;		
	}
}

void Socket::handleTickEvent()
{
	if (ANIMATION_PLAY == animation_stage_)
	{
		if (!is_mirror_)
		{
			if (1 <= direction_ && 
				(ms_->socket_right_previous_alpha + alpha_delta_) <= alpha_)
			{
				ms_->socket_right_previous_alpha += alpha_delta_;
			}

			else if (-1 >= direction_ &&
				(ms_->socket_right_previous_alpha + alpha_delta_) >= alpha_)
			{
				ms_->socket_right_previous_alpha += alpha_delta_;
			}
			else if (1 <= direction_ || -1 >= direction_)
			{
				ms_->socket_right_previous_alpha = alpha_;
			}

			socket_.setAlpha(ms_->socket_right_previous_alpha);
			socket_.invalidate();			
		}
		else
		{
			if (1 <= direction_ &&
				(ms_->socket_left_previous_alpha + alpha_delta_) <= alpha_)
			{
				ms_->socket_left_previous_alpha += alpha_delta_;
			}

			else if (-1 >= direction_ &&
				(ms_->socket_left_previous_alpha + alpha_delta_) >= alpha_)
			{
				ms_->socket_left_previous_alpha += alpha_delta_;
			}
			else if (1 <= direction_ || -1 >= direction_)
			{
				ms_->socket_left_previous_alpha = alpha_;
			}

			socket_.setAlpha(ms_->socket_left_previous_alpha);
			socket_.invalidate();
			//if (SCREEN_BOOT == ms_->ux_screen_id_previous &&
			//	(ms_->socket_left_previous_alpha + alpha_delta_) <= alpha_)
			//{
			//	ms_->socket_left_previous_alpha += alpha_delta_;
			//	socket_.setAlpha(ms_->socket_left_previous_alpha);
			//	socket_.invalidate();
			//}
			//else if (SCREEN_PAYMENT == ms_->ux_screen_id_previous &&
			//	(ms_->socket_left_previous_alpha - alpha_delta_) >= alpha_)
			//{
			//	ms_->socket_left_previous_alpha += alpha_delta_;
			//	socket_.setAlpha(ms_->socket_left_previous_alpha);
			//	socket_.invalidate();
			//}
		}
	}

	if (ANIMATION_PLAY != animation_stage_ && 0 == (tick_ % 2) && tick_ > 60)
	{
		if (ms_->ux_drag_selector_vx_prev != ms_->ux_drag_selector_vx)
		{
			adjustAlpha(ms_->ux_drag_selector_vx);
		}
	}

	tick_++;
}

uint8_t Socket::getAlpha()
{
	return socket_.getAlpha();
}

void Socket::beginAnimation(int end_x, int end_y, int end_width, int end_height,int end_alpha, int duration)
{
	if (0 == duration)
	{
		duration = 1;
	}

	duration_ = duration;
	alpha_ = end_alpha;

	if (end_alpha > socket_.getAlpha())
	{
		direction_ = 1;
	}
	else if (end_alpha < socket_.getAlpha())
	{
		direction_ = -1;
	}
	else
	{
		direction_ = 0;
	}

	alpha_delta_ = (alpha_ - socket_.getAlpha()) / duration_;
	//if (!is_mirror_)
	//{
	//	alpha_delta_ = (alpha_ - socket_.getAlpha()) / duration_;
	//}
	//else
	//{
	//	alpha_delta_ = (alpha_ - socket_.getAlpha()) / duration_;
	//}
	if (0 == alpha_delta_ && 0 != direction_)
	{
		if (1 <= direction_) 
		{
			alpha_delta_ = 1;
		}
		else if (-1 >= direction_)
		{
			alpha_delta_ = -1;
		}
	}

	animation_stage_ = ANIMATION_PLAY;
	
	if (!is_mirror_)
	{
		ms_->socket_right_previous_alpha = socket_.getAlpha();
		socket_.setPosition(
			ms_->socket_right_previous_x,
			ms_->socket_right_previous_y,
			ms_->socket_right_previous_width,
			ms_->socket_right_previous_height);
		//socket_.setAlpha(ms_->socket_right_previous_alpha);
	}
	else
	{
		ms_->socket_left_previous_alpha = socket_.getAlpha();
		socket_.setPosition(
			ms_->socket_left_previous_x,
			ms_->socket_left_previous_y,
			ms_->socket_left_previous_width,
			ms_->socket_left_previous_height);
		//socket_.setAlpha(ms_->socket_left_previous_alpha);
	}
	socket_.startZoomAndMoveAnimation(end_x, end_y, end_width, end_height, duration);
}

void Socket::saveMachineStatus() 
{
	if (!is_mirror_)
	{
		ms_->socket_right_previous_x = socket_.getX();
		ms_->socket_right_previous_y = socket_.getY();
		ms_->socket_right_previous_width = socket_.getWidth();
		ms_->socket_right_previous_height = socket_.getHeight();
		ms_->socket_right_previous_alpha = socket_.getAlpha();
	}
	else
	{
		ms_->socket_left_previous_x = socket_.getX();
		ms_->socket_left_previous_y = socket_.getY();
		ms_->socket_left_previous_width = socket_.getWidth();
		ms_->socket_left_previous_height = socket_.getHeight();
		ms_->socket_left_previous_alpha = socket_.getAlpha();
	}
}

void Socket::itemZoomAnimationEndedHandler(const ZoomAnimationImage& source)
{
	saveMachineStatus();

	animation_stage_ = ANIMATION_STOP;
}

int Socket::encodeToAlpha(int src)
{
	if ((!is_mirror_ && src <= 0) ||
		(is_mirror_ && src >= 0))
	{
		return cc_.SocketAlphaHomeBegin;
	}

	//if (0 == src) return APLPHA_MINIMA_;

	if (src < 0)
	{
		src *= -1;
	}

	if (src > APLPHA_MAX_DISPLAY_POSITION_) return 255;

	//src = APLPHA_MAX_DISPLAY_POSITION_ - src;

	float unit = ((float)255 - cc_.SocketAlphaHomeBegin) / APLPHA_MAX_DISPLAY_POSITION_;
	int alpha = (int)(unit * src) + cc_.SocketAlphaHomeBegin;

	return alpha;
}

void Socket::adjustAlpha(int x)
{
	int alpha = encodeToAlpha(x);

	if (!is_mirror_)
	{
		ms_->socket_right_previous_alpha = alpha;
	}
	else
	{
		ms_->socket_left_previous_alpha = alpha;
	}	

	socket_.setAlpha(alpha);
	socket_.invalidate();
}

const int16_t Socket::getSocketSmallRightBitmapID()
{
	if (nullptr != ms_)
	{
		switch (ms_->ux_socket_status_right)
		{
		case UXSocketStatus::UX_SOCKET_AVAILABLE:
			return BITMAP_SOCKET_GREEN_RIGHT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_CHARGING:
			return BITMAP_SOCKET_BLUE_RIGHT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_ERROR:
			return BITMAP_SOCKET_RED_RIGHT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_FULL:
			return BITMAP_SOCKET_YELLOW_RIGHT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_WARNING:
			return BITMAP_SOCKET_GREY_RIGHT_ID;
			break;
		default:
			return BITMAP_SOCKET_GREY_RIGHT_ID;
			break;
		}
	}
	else
	{
		return BITMAP_SOCKET_GREY_RIGHT_ID;
	}
}

const int16_t Socket::getSocketLargeRightBitmapID()
{
	if (nullptr != ms_)
	{
		switch (ms_->ux_socket_status_right)
		{
		case UXSocketStatus::UX_SOCKET_AVAILABLE:
			return BITMAP_SOCKET_GREEN_RIGHT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_CHARGING:
			return BITMAP_SOCKET_BLUE_RIGHT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_ERROR:
			return BITMAP_SOCKET_RED_RIGHT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_FULL:
			return BITMAP_SOCKET_YELLOW_RIGHT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_WARNING:
			return BITMAP_SOCKET_GREY_RIGHT_LARGE_ID;
			break;
		default:
			return BITMAP_SOCKET_GREY_RIGHT_LARGE_ID;
			break;
		}
	}
	else
	{
		return BITMAP_SOCKET_GREY_RIGHT_LARGE_ID;
	}
}

const int16_t Socket::getSocketSmallLeftBitmapID()
{
	if (nullptr != ms_)
	{
		switch (ms_->ux_socket_status_left)
		{
		case UXSocketStatus::UX_SOCKET_AVAILABLE:
			return BITMAP_SOCKET_GREEN_LEFT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_CHARGING:
			return BITMAP_SOCKET_BLUE_LEFT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_ERROR:
			return BITMAP_SOCKET_RED_LEFT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_FULL:
			return BITMAP_SOCKET_YELLOW_LEFT_ID;
			break;
		case UXSocketStatus::UX_SOCKET_WARNING:
			return BITMAP_SOCKET_GREY_LEFT_ID;
			break;
		default:
			return BITMAP_SOCKET_GREY_LEFT_ID;
			break;
		}
	}
	else
	{
		return BITMAP_SOCKET_GREY_LEFT_ID;
	}
}

const int16_t Socket::getSocketLargeLeftBitmapID()
{
	if (nullptr != ms_)
	{
		switch (ms_->ux_socket_status_left)
		{
		case UXSocketStatus::UX_SOCKET_AVAILABLE:
			return BITMAP_SOCKET_GREEN_LEFT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_CHARGING:
			return BITMAP_SOCKET_BLUE_LEFT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_ERROR:
			return BITMAP_SOCKET_RED_LEFT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_FULL:
			return BITMAP_SOCKET_YELLOW_LEFT_LARGE_ID;
			break;
		case UXSocketStatus::UX_SOCKET_WARNING:
			return BITMAP_SOCKET_GREY_LEFT_LARGE_ID;
			break;
		default:
			return BITMAP_SOCKET_GREY_LEFT_LARGE_ID;
			break;
		}
	}
	else
	{
		return BITMAP_SOCKET_GREY_LEFT_LARGE_ID;
	}
}