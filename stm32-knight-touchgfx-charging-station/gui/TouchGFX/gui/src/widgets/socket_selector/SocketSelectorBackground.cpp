#include <cstddef>
#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/widgets/socket_selector/SocketSelectorBackground.hpp>

SocketSelectorBackground::SocketSelectorBackground()
	:	
    side_(true),
	is_target_circle_animate_(false),
	target_circle_animation_duration_(60), //None used.
	target_circle_z_angle_(0.0f),
	target_circle_delta_z_angle_(0.029f * 2),
    animation_interval_(4),
    integration_(0),
    integration_interval_(4),	
	integration_l2_(60),
	integration_direction_(true),
	plug_status_(0),
    plug_status_prv_(0)
{		
}

SocketSelectorBackground::~SocketSelectorBackground()
{
	Application::getInstance()->unregisterTimerWidget(this);
}

void SocketSelectorBackground::initialize(MachineStatus* status)
{
	ms_ = status;

	layer_charging_.initialize(ms_);
	layer_charging_.setPosition(0, 0, 175, 62); // 800x480
	//layer_charging_.setPosition(0, 0, 280, 100);
	layer_charging_.setVisible(false);
	add(layer_charging_);

	layer_3_.setVisible(false);
	add(layer_3_);
	
	title_.setVisible(false);
	add(title_);

	target_circle_.setBitmap(Bitmap(BITMAP_SLIDER_TARGET_CIRCLE_ID));
	int target_circle_right_width_ = target_circle_.getBitmap().getWidth();
	int target_circle_right_width_height_ = target_circle_.getBitmap().getHeight();
	if (side_) 
	{
		target_circle_.setXY(128, 14);
		//target_circle_.setXY(205, 23);
	}
	else
	{
		target_circle_.setXY(15, 14);
		//target_circle_.setXY(24, 23);
	}
	target_circle_.setCameraDistance(100.0f);
	target_circle_.setCamera(
		target_circle_.getBitmapPositionX() + (target_circle_right_width_ / 2),
		target_circle_.getBitmapPositionY() + (target_circle_right_width_height_ / 2));
	target_circle_.setOrigo(
		target_circle_.getBitmapPositionX() + (target_circle_right_width_ / 2),
		target_circle_.getBitmapPositionY() + (target_circle_right_width_height_ / 2),
		target_circle_.getCameraDistance());
	target_circle_.setVisible(false);
	add(target_circle_);

	event_13();

	updateGraphic();

	Application::getInstance()->registerTimerWidget(this);
}

void SocketSelectorBackground::setSide(bool side)
{
	side_ = side;

	layer_charging_.setSide(side);

	/*if (side)
	{
		title_.setXY(140, 38);
	}
	else
	{
		title_.setXY(40, 38);
	}*/
}

void SocketSelectorBackground::setAnimationInterval(int interval)
{
	animation_interval_ = interval;
}

void SocketSelectorBackground::setTargetCircleAnimate(bool enable)
{
	is_target_circle_animate_ = enable;
}

void SocketSelectorBackground::handleTickEvent()
{	
	if (NULL == ms_)
	{
		return;
	}
		
	if (side_) 
	{
		plug_status_ = ms_->ux_socket_status_right;

		if (is_target_circle_animate_)
		{
			target_circle_z_angle_ += target_circle_delta_z_angle_;
			target_circle_.updateAngles(0.0F, 0.0F, target_circle_z_angle_);
		}
	}
	else
	{
		plug_status_ = ms_->ux_socket_status_left;

		if (is_target_circle_animate_)
		{
			target_circle_z_angle_ -= target_circle_delta_z_angle_;
			target_circle_.updateAngles(0.0F, 0.0F, target_circle_z_angle_);
		}
	}
	
	if (plug_status_prv_ != plug_status_)
	{		
		event_[6] = 6;
	}
	else
	{
		event_[6] = false;
	}

	//if (event_[3])
	//{
	//	event_3();
	//}

	//if (event_[4])
	//{
	//	event_4();
	//}

	//if (event_[5])
	//{
	//	event_5();
	//}

	if (event_[6])
	{
		event_6();
	}

	if (event_[9])
	{
		event_9();
	}

	if (event_[10])
	{
		event_10();
	}

	if (event_[11])
	{
		event_11();
	}

	if (event_[12])
	{
		event_12();
	}

	if (event_[13])
	{
		event_13();
	}

	ContainerEx::handleTickEvent();

	plug_status_prv_ = plug_status_;
}

//void SocketSelectorBackground::event_3()
//{
//}

//void SocketSelectorBackground::event_4()
//{
//}

//void SocketSelectorBackground::event_5()
//{
//}

void SocketSelectorBackground::event_6()
{
	updateGraphic();	
}

void SocketSelectorBackground::updateGraphic()
{
	int s = 0;
	if (side_)
	{
		s = ms_->ux_socket_status_right;
	}
	else
	{
		s = ms_->ux_socket_status_left;
	}

	if (1 == s)
	{
		event_[9] = 9;
	}
	else if (3 == s)
	{
		event_[10] = 10;
	}
	else if (2 == s)
	{
		event_[11] = 11;		
	}
	else if (4 == s)
	{
		event_[12] = 12;
	}
	else if (0 == s)
	{
		event_[13] = 13;
	}
	else 
	{
		event_[13] = 13;
	}
}

void SocketSelectorBackground::event_9()
{
	layer_charging_.setVisible(false);
	layer_charging_.stopAnimation();
	
	if (side_)
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_AVAILABLE_RIGHT_ID));
	}
	else
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_AVAILABLE_LEFT_ID));
	}
	layer_3_.setVisible(true);	

	target_circle_.setVisible(true);

	title_.setVisible(false);

	layer_3_.invalidate();
}

void SocketSelectorBackground::event_10()
{
	layer_charging_.setVisible(true);
	layer_charging_.beginAnimation();

	layer_3_.setVisible(false);

	if (side_)
	{
		title_.setXY(87, 23);
		//title_.setXY(140, 38);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G1));
		title_.resizeToCurrentText();
	}
	else
	{
		title_.setXY(26, 23);
		//title_.setXY(42, 38);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G1));
		title_.resizeToCurrentText();
	}

	target_circle_.setVisible(false);

	title_.setVisible(true);	
}

void SocketSelectorBackground::event_11()
{
	layer_charging_.setVisible(false);
	layer_charging_.stopAnimation();
	
	layer_3_.setVisible(true);
	
	if (side_)
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_NOT_CHARGING_RIGHT_ID));

		title_.setXY(87, 23);
		//title_.setXY(140, 38);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G2));
		title_.resizeToCurrentText();
	}
	else
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_NOT_CHARGING_LEFT_ID));

		title_.setXY(26, 23);
		//title_.setXY(42, 38);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G2));
		title_.resizeToCurrentText();
	}

	target_circle_.setVisible(false);

	title_.setVisible(true);

	layer_3_.invalidate();
}

void SocketSelectorBackground::event_12()
{
	layer_charging_.setVisible(false);
	layer_charging_.stopAnimation();	
	   
	layer_3_.setVisible(true);

	if (side_)
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_ERROR_RIGHT_ID));		

		title_.setXY(140, 11);
		//title_.setXY(225, 18);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G10));
		title_.resizeToCurrentText();
	}
	else
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_ERROR_LEFT_ID));			

		title_.setXY(26, 11);
		//title_.setXY(42, 18);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G10));
		title_.resizeToCurrentText();
	}

	target_circle_.setVisible(false);

	title_.setVisible(true);

	layer_3_.invalidate();
}

void SocketSelectorBackground::event_13()
{
	layer_charging_.setVisible(false);
	layer_charging_.stopAnimation();
	
	layer_3_.setVisible(true);
	
	if (side_)
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_BLACK_RIGHT_ID));		

		title_.setXY(140, 11);
		//title_.setXY(225, 18);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G10));
		title_.resizeToCurrentText();		
	}
	else
	{
		layer_3_.setBitmap(Bitmap(BITMAP_SLIDER_BLACK_LEFT_ID));

		title_.setXY(26, 11);
		//title_.setXY(42, 18);
		title_.setAlpha(150);
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		title_.setLinespacing(0);
		title_.setTypedText(TypedText(T_G10));
		title_.resizeToCurrentText();
	}

	target_circle_.setVisible(false);

	title_.setVisible(true);

	layer_3_.invalidate();
}