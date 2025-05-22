#include <gui/widgets/info/AbstractContent.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <touchgfx/Application.hpp>

AbstractContent::AbstractContent()	
	:
	animation_duration_(60),
	animation_lock_(1),
	animation_stage_(AnimationStage::ANIMATION_STOP),
	return_value_(ReturnValue::RETURN_NONE),
	event_trigger_callback_(this, &AbstractContent::eventTriggerHandler),
	open_completed_callback_(nullptr),
	close_completed_callback_(nullptr)
{
	Application::getInstance()->registerTimerWidget(this);
	em_.setEventTriggerCallback(event_trigger_callback_);
	add(em_);
}

AbstractContent::~AbstractContent()
{
	Container::~Container();
}

void AbstractContent::handleTickEvent()
{
	if (AnimationStage::ANIMATION_OPEN == animation_stage_ &&
		0 == animation_lock_)
	{
		animation_stage_ = AnimationStage::ANIMATION_STOP;
		em_.addOneTimeEvent(3);
	}
	else if (AnimationStage::ANIMATION_CLOSE == animation_stage_ &&
		0 == animation_lock_)
	{
		Application::getInstance()->unregisterTimerWidget(this);
		animation_stage_ = AnimationStage::ANIMATION_STOP;
		em_.addOneTimeEvent(5);
	}
}

void AbstractContent::initialize(MachineStatus *status)
{	
	ms_ = status;
}

void AbstractContent::setOpenCompletedCallback(GenericCallback<const int>& callback)
{
	this->open_completed_callback_ = &callback;
}

void AbstractContent::setCloseCompletedCallback(GenericCallback<const int>& callback)
{
	this->close_completed_callback_ = &callback;
}

void AbstractContent::open(int duration)
{
	animation_duration_ = duration;

	//em_.removeAllEvent();
	em_.addOneTimeEvent(2);
}

void AbstractContent::close(int duration)
{
	animation_duration_ = duration;

	em_.removeAllEvent();
	em_.addOneTimeEvent(4);
}

void AbstractContent::sendCommandReturn()
{
	if (nullptr != ms_)
	{
		ms_->ux_screen_id_next = ms_->ux_screen_id_previous;
		ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_ON;
		ms_->ux_screen_status = UXScreenStatus::UX_NOT_OPERABLE;
	}
}

void AbstractContent::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 2:
		event2(); //Open.
		break;
	case 3:
		event3(); //Open Completed.
		break;
	case 4:
		event4(); //Close.
		break;
	case 5:
		event5(); //Close Completed.
		break;
	case 6:
		event6(); //Auto close.
		break;
	}
}

void AbstractContent::event2()
{
	animation_stage_ = AnimationStage::ANIMATION_OPEN;
}

void AbstractContent::event3()
{
	if (nullptr != open_completed_callback_ && open_completed_callback_->isValid())
	{
		this->open_completed_callback_->execute(0);
	}
}

void AbstractContent::event4()
{
	animation_stage_ = AnimationStage::ANIMATION_CLOSE;
}

void AbstractContent::event5()
{
	em_.removeAllEvent();

	if (nullptr != close_completed_callback_ && close_completed_callback_->isValid())
	{
		this->close_completed_callback_->execute(return_value_);
	}
}

void AbstractContent::event6()
{	
	//ms_->ux_screen_id_current = ms_->ux_screen_id_next;
	//ms_->ux_screen_id_next = ms_->ux_screen_id_previous;
	//ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_ON;
}