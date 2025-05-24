#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/ContainerEx.hpp>
#include <touchgfx/Application.hpp>

ContainerEx::ContainerEx()
	:
	tick_(0),
	animation_duration_(0),
	open_container_animation_lock_(0),
	close_container_animation_lock_(0),
	event_{0}
{
	Application::getInstance()->registerTimerWidget(this);
}

ContainerEx::~ContainerEx()
{
	Application::getInstance()->unregisterTimerWidget(this);
}

void ContainerEx::handleTickEvent()
{	
	if (event_[1])
	{
		event_1();
		this->open_container_callback_->execute(event_[1]);
	}

	if (event_[2])
	{
		event_2();
		this->close_container_callback_->execute(event_[2]);
	}

	//clear event.
	for (int i = 0; i < event_number_; i++) 
	{
		event_[i] = 0;
	}

	tick_++;

	if (60000 <= tick_)
	{
		tick_ = 0;
	}
}

void ContainerEx::setOpenContainerCallback(GenericCallback<const int>& callback)
{
	this->open_container_callback_ = &callback;
}


void ContainerEx::setCloseContainerCallback(GenericCallback<const int>& callback)
{
	this->close_container_callback_ = &callback;
}

void ContainerEx::setAnimationDuration(int duration)
{
	animation_duration_ = duration;
}

void ContainerEx::decreaseOpenContainerAnimationLock()
{
	open_container_animation_lock_--;

	if (0 == open_container_animation_lock_)
	{
		event_[1] = 1;
	}
}

void ContainerEx::decreaseCloseContainerAnimationLock()
{
	close_container_animation_lock_--;

	if (0 == close_container_animation_lock_)
	{
		event_[2] = 2;
	}
}
