#include <gui/widgets/info/AbstractMessage.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

AbstractMessage::AbstractMessage()	
	:
	pcount_(0),
	return_value_(0),
	animation_duration_(60),
	animation_lock_(0),
	animation_stage_(AnimationStage::ANIMATION_STOP),
	content_open_end_callback_(this, &AbstractMessage::contentOpenEndHandler),
	content_close_end_callback_(this, &AbstractMessage::contentCloseEndHandler),
	event_trigger_callback_(this, &AbstractMessage::eventTriggerHandler),
	open_completed_callback_(nullptr),
	close_completed_callback_(nullptr)
{
	Application::getInstance()->registerTimerWidget(this);
	em_.setEventTriggerCallback(event_trigger_callback_);
	add(em_);
}

AbstractMessage::~AbstractMessage()
{
	Application::getInstance()->unregisterTimerWidget(this);

	Container::~Container();
}

void AbstractMessage::handleTickEvent()
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
		animation_stage_ = AnimationStage::ANIMATION_STOP;
		em_.addOneTimeEvent(5);
	}
}

void AbstractMessage::initialize(MachineStatus *status, ContentType content)
{	
	ms_ = status;
	ms_->popup_opened = false;
	message_number_ = (MessageNumber)status->ux_popup_number;

	content_type_ = content;
	switch (content)
	{
	case ContentType::CONTENT_0201:
		content_ = new Content0201();
		break;
	case ContentType::CONTENT_0202:
		content_ = new Content0202();
		break;
	case ContentType::CONTENT_0203:
		content_ = new Content0203();
		break;
	case ContentType::CONTENT_0204:
		content_ = new Content0204();
		break;
	case ContentType::CONTENT_0205:
		content_ = new Content0205();
		break;
	case ContentType::CONTENT_0206:
		content_ = new Content0206();
		break;
	case ContentType::CONTENT_0207:
		content_ = new Content0207();
		break;
	case ContentType::CONTENT_0208:
		content_ = new Content0208();
		break;
	case ContentType::CONTENT_0301:
		content_ = new Content0301();
		break;
	case ContentType::CONTENT_0404:
		content_ = new Content0404();
		break;
	case ContentType::CONTENT_0501:
		content_ = new Content0501();
		break;
	case ContentType::CONTENT_0504:
		content_ = new Content0504();
		break;	
	case ContentType::CONTENT_E2:
		content_ = new ContentE2();
		break;
	case ContentType::CONTENT_E3:
		content_ = new ContentE3();
		break;
	case ContentType::CONTENT_E4:
		content_ = new ContentE4();
		break;
	case ContentType::CONTENT_E5:
		content_ = new ContentE5();
		break;
	case ContentType::CONTENT_E6:
		content_ = new ContentE6();
		break;
	case ContentType::CONTENT_E1:
	default:
		content_ = new ContentE1();
		break;
	}
	pcount_++;

	content_->setPosition(0, 12, 398, 523); // 480x800
	//content_->setPosition(0, 20, 638, 838);
	content_->initialize(ms_);
	content_->setOpenCompletedCallback(content_open_end_callback_);
	content_->setCloseCompletedCallback(content_close_end_callback_);
	add(*content_);
}

void AbstractMessage::setAnimationDuration(int duration)
{
	animation_duration_ = duration;
}

MessageNumber AbstractMessage::getInitializeType()
{
	return message_number_;
}

void AbstractMessage::setOpenCompletedCallback(GenericCallback<const int>& callback)
{
	this->open_completed_callback_ = &callback;
}

void AbstractMessage::setCloseCompletedCallback(GenericCallback<const int>& callback)
{
	this->close_completed_callback_ = &callback;
}

void AbstractMessage::open(int duration)
{
	ms_->popup_opened = true;

	animation_duration_ = duration / 2;

	em_.addOneTimeEvent(2);
}

void AbstractMessage::close(int duration)
{
	animation_duration_ = duration / 2;

	em_.removeAllEvent();
	em_.addOneTimeEvent(6);
}

void AbstractMessage::contentOpenEndHandler(const int source)
{
	if (nullptr != open_completed_callback_ && open_completed_callback_->isValid())
	{
		this->open_completed_callback_->execute(0);
	}
}

void AbstractMessage::contentCloseEndHandler(const int source)
{
	return_value_ = source;

	em_.addOneTimeEvent(4);
}

void AbstractMessage::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 2:
		event2(); //Open message.
		break;
	case 3:
		event3(); //Open context.
		break;
	case 4:
		event4(); //Close message.
		break;
	case 5:
		event5(); //Close Completed.
		break;
	case 6:
		event6(); //Close Completed.
		break;
	}
}

void AbstractMessage::event2()
{
	animation_stage_ = AnimationStage::ANIMATION_OPEN;
}

void AbstractMessage::event3()
{
	animation_stage_ = AnimationStage::ANIMATION_OPEN_CONTENT;

	content_->open(animation_duration_);
}

void AbstractMessage::event4()
{
	animation_stage_ = AnimationStage::ANIMATION_CLOSE;
}

void AbstractMessage::event5()
{
	animation_stage_ = AnimationStage::ANIMATION_CLOSE_CONTENT;

	if (1 <= pcount_) 
	{
		remove(*content_);
		delete content_;
	}
	ms_->popup_opened = false;

	this->close_completed_callback_->execute(return_value_);
}

void AbstractMessage::event6()
{
	content_->close(animation_duration_);
}