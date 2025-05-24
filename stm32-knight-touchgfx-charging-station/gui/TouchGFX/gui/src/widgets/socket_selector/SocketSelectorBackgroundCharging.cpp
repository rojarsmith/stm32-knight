#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/socket_selector/SocketSelectorBackgroundCharging.hpp>

int SocketSelectorBackgroundCharging::cam_[] = {0 ,0 ,0 ,5 ,10 ,15 ,20 ,25 ,30 ,35 ,40 ,45 ,50 ,55 ,60 ,65 ,70 ,75 ,80 ,85 ,90 ,95 ,100  ,105  ,110  ,115  ,120  ,125  ,130  ,135  ,140  ,145  ,150  ,155  ,160  ,165  ,170  ,175  ,180  ,185  ,190  ,195  ,200  ,205  ,210  ,215  ,220  ,225  ,230  ,235  ,240  ,245  ,250  ,255  ,255  ,255  ,255  ,255  ,255  ,255  ,255  ,255  ,255  ,250  ,245  ,240  ,235  ,230  ,225  ,220  ,215  ,210  ,205  ,200  ,195  ,190  ,185  ,180  ,175  ,170  ,165  ,160  ,155  ,150  ,145  ,140  ,135  ,130  ,125  ,120  ,115  ,110  ,105  ,100  ,95 ,90 ,85 ,80 ,75 ,70 ,65 ,60 ,55 ,50 ,45 ,40 ,35 ,30 ,25 ,20 ,15 ,10 ,5 ,0};

SocketSelectorBackgroundCharging::SocketSelectorBackgroundCharging()
	:
	side_(true),
	animation_play_(false),
	animation_time_interval_(6),
	animation_skip_interval_(1),
	cam_length_(0)
{
}

SocketSelectorBackgroundCharging::~SocketSelectorBackgroundCharging()
{
	animation_play_ = false;
	Application::getInstance()->unregisterTimerWidget(this);	
}

void SocketSelectorBackgroundCharging::handleTickEvent()
{	
	if (animation_play_ &&
		0 == ms_->ui_tick % animation_time_interval_)
	{
		layer_2_.setAlpha(cam_[(ms_->ui_tick % (cam_length_ / animation_skip_interval_))* animation_skip_interval_]);
		layer_2_.invalidate();
	}	
}

void SocketSelectorBackgroundCharging::initialize(MachineStatus* status)
{
	ms_ = status;	

	cam_length_ = sizeof(cam_) / sizeof(int);
	
	layer_1_.setXY(0, 0);	
	add(layer_1_);
	
	layer_2_.setXY(0, 0);
	add(layer_2_);
}

void SocketSelectorBackgroundCharging::setSide(bool side)
{
	side_ = side;

	layer_1_.setXY(0, 0);
	layer_2_.setXY(0, 0);

	if (side)
	{
		layer_1_.setBitmap(Bitmap(BITMAP_SLIDER_CHARGING_RIGHT_ID));
		layer_2_.setBitmap(Bitmap(BITMAP_SLIDER_CHARGING_RIGHT_MASK_ID));		
	}
	else
	{
		layer_1_.setBitmap(Bitmap(BITMAP_SLIDER_CHARGING_LEFT_ID));
		layer_2_.setBitmap(Bitmap(BITMAP_SLIDER_CHARGING_LEFT_MASK_ID));
	}
}

void SocketSelectorBackgroundCharging::beginAnimation()
{
	Application::getInstance()->registerTimerWidget(this);
	animation_play_ = true;
}

void SocketSelectorBackgroundCharging::stopAnimation()
{
	animation_play_ = false;
	Application::getInstance()->unregisterTimerWidget(this);
}