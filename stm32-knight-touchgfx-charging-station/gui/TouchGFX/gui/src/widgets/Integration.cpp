#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/Integration.hpp>
#include <touchgfx/Application.hpp>

Integration::Integration()
	: 
	tick_(0),
	interval_(0),
	output_(0),
	target_(0),
	event_{0}
{
}

Integration::~Integration()
{	
	Application::getInstance()->unregisterTimerWidget(this);
}

void Integration::handleTickEvent()
{	
	run();

	if (event_[1])
	{
		event_1();
		if (arrived_callback_ && arrived_callback_->isValid())
		{
			this->arrived_callback_->execute(event_[1]);
		}
	}

	//clear event.
	for (int i = 0; i < event_number_; i++) 
	{
		event_[i] = 0;
	}

	tick_++;
}

void Integration::setArrivedCallback(GenericCallback<const int>& callback)
{
	this->arrived_callback_ = &callback;
}

void Integration::setInterval(int interval)
{
	interval_ = interval;
}

void Integration::setTarget(int target)
{
	target_ = target;
}

void Integration::restart()
{
	output_ = 0;
	Application::getInstance()->registerTimerWidget(this);
}

void Integration::pause()
{
	Application::getInstance()->unregisterTimerWidget(this);
}

void Integration::run()
{
	output_++;

	if (target_ <= output_)
	{
		Application::getInstance()->unregisterTimerWidget(this);
		event_[1] = 1;
	}
}