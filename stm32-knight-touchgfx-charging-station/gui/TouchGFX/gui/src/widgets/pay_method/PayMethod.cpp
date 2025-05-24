#include <gui/widgets/pay_method/PayMethod.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

PayMethod::PayMethod()	
	//:
	//animation_duration_(0),
	//animation_lock_(0),
	//animation_stage_(AnimationStage::ANIMATION_STOP),
	//return_value_(ReturnValue::RETURN_NONE),
	//event_trigger_callback_(this, &PayMethod::eventTriggerHandler),
	//open_completed_callback_(nullptr),
	//close_completed_callback_(nullptr)
{
	//Application::getInstance()->registerTimerWidget(this);
	//em_.setEventTriggerCallback(event_trigger_callback_);
}

PayMethod::~PayMethod()
{
	Container::~Container();
}
//
//void PayMethod::handleTickEvent()
//{
//	if (AnimationStage::ANIMATION_OPEN == animation_stage_ &&
//		0 == animation_lock_)
//	{
//		animation_stage_ = AnimationStage::ANIMATION_STOP;
//		em_.addOneTimeEvent(3);
//	}
//	else if (AnimationStage::ANIMATION_CLOSE == animation_stage_ &&
//		0 == animation_lock_)
//	{
//		Application::getInstance()->unregisterTimerWidget(this);
//		animation_stage_ = AnimationStage::ANIMATION_STOP;
//		em_.addOneTimeEvent(5);
//	}
//}
//
//void PayMethod::initialize()
//{	
//}
//
//void PayMethod::setOpenCompletedCallback(GenericCallback<const int>& callback)
//{
//	this->open_completed_callback_ = &callback;
//}
//
//void PayMethod::setCloseCompletedCallback(GenericCallback<const int>& callback)
//{
//	this->close_completed_callback_ = &callback;
//}
//
//void PayMethod::open(int duration)
//{
//	animation_duration_ = duration;
//	em_.addOneTimeEvent(2);
//}
//
//void PayMethod::close(int duration)
//{
//	animation_duration_ = duration;
//	em_.addOneTimeEvent(3);
//}
//
//void PayMethod::eventTriggerHandler(const int source)
//{
//	switch (source)
//	{
//	case 2:
//		event2(); //Open.
//		break;
//	case 3:
//		event3(); //Open Completed.
//		break;
//	case 4:
//		event4(); //Close.
//		break;
//	case 5:
//		event5(); //Close Completed.
//		break;
//	case 6:
//		event6(); //Auto close.
//		break;
//	}
//}
//
//void PayMethod::event2()
//{
//	animation_stage_ = AnimationStage::ANIMATION_OPEN;
//}
//
//void PayMethod::event3()
//{
//	if (nullptr != open_completed_callback_ && open_completed_callback_->isValid())
//	{
//		this->open_completed_callback_->execute(0);
//	}
//}
//
//void PayMethod::event4()
//{
//	animation_stage_ = AnimationStage::ANIMATION_CLOSE;
//}
//
//void PayMethod::event5()
//{
//	if (nullptr != close_completed_callback_ && close_completed_callback_->isValid())
//	{
//		this->close_completed_callback_->execute(return_value_);
//	}
//}
//
//void PayMethod::event6()
//{
//
//}