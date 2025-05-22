#include <gui/common/EventManager.hpp>

EventManager::EventManager()
	:
	trigger_{ false },
	op1_{ 0 },
	op2_{ 0 },
	reject_{ false },
	type_{ 0 },
	tick_(0)
{
	Application::getInstance()->registerTimerWidget(this);
}

EventManager::~EventManager()
{
	Application::getInstance()->unregisterTimerWidget(this);
}

void EventManager::handleTickEvent()
{
	for (int i = 0; i < EVENT_MAXIMUM_NUMBER; i++)
	{
		if (trigger_[i]) 
		{
			switch (type_[i])
			{
			case 1:
				if (0 == (tick_ % op1_[i]))
				{
					this->event_trigger_callback_->execute(i);
				}
				break;
			case 2:
				if (1 <= op1_[i])
				{
					op1_[i] = op1_[i] - 1;
				}
				else
				{
					this->event_trigger_callback_->execute(i);
					trigger_[i] = 0;
				}
				break;
			case 3:
				if (0 >= op1_[i])				
				{
					this->event_trigger_callback_->execute(i);
					trigger_[i] = 0;
				}
				break;
			case 4:
				if (1 <= op1_[i])
				{
					this->event_trigger_callback_->execute(i);
					op1_[i] = op1_[i] - 1;
				}
				else
				{										
					this->event_trigger_callback_->execute(op2_[i]);
					trigger_[i] = 0;
				}
				break;
			case 5:
				this->event_trigger_callback_->execute(i);

				if (op1_[i] < op2_[i])
				{
					op1_[i] += 1;
				}
				else if (op1_[i] == op2_[i])
				{
					trigger_[i] = 0;
				}
				break;
			default://0
				if (event_trigger_callback_ &&
					event_trigger_callback_->isValid()) 
				{
					this->event_trigger_callback_->execute(i);
				}
				trigger_[i] = 0;
				break;
			}
		}
	}

	tick_++;

	if (tick_ >= 60000) 
	{
		tick_ = 0;
	}
}

void EventManager::setEventTriggerCallback(GenericCallback<const int>& callback)
{
	event_trigger_callback_ = &callback;
}

void EventManager::addOneTimeEvent(int id)
{	
	if (reject_[id])
	{
		return;
	}

	removeEvent(id);
	type_[id] = EventType::ONE_TIME;
	trigger_[id] = true;	
}

void EventManager::addAlwaysKeepEvent(int id, int op1)
{
	if (0 >= op1)
	{
		return;
	}
	removeEvent(id);
	type_[id] = EventType::ALWAYS_KEEP;
	trigger_[id] = true;
	op1_[id] = op1;
}

void EventManager::addCountDownEvent(int id, int op1)
{
	if (reject_[id])
	{
		return;
	}

	removeEvent(id);
	type_[id] = EventType::COUNT_DOWN;
	trigger_[id] = true;
	op1_[id] = op1;	
}

void EventManager::addLockCountEvent(int id, int op1)
{
	removeEvent(id);
	type_[id] = EventType::LOCK_COUNT;
	trigger_[id] = true;
	op1_[id] = op1;
}

void EventManager::addLoopChainEvent(int id, int op1, int op2)
{
	removeEvent(id);
	type_[id] = EventType::LOOP_CHAIN;
	trigger_[id] = true;
	op1_[id] = op1;
	op2_[id] = op2;
}

void EventManager::addRangeIncreaseEvent(int id, int op1, int op2)
{
	removeEvent(id);
	type_[id] = EventType::RANGE_INCREASE;
	trigger_[id] = true;
	op1_[id] = op1;
	op2_[id] = op2;	
}

void EventManager::removeEvent(int id)
{
	type_[id] = 0;
	trigger_[id] = false;
	op1_[id] = 0;
	op2_[id] = 0;
}

void EventManager::removeAllEvent()
{
	for (int i = 0; i < EVENT_MAXIMUM_NUMBER; i++)
	{
		removeEvent(i);
	}
}

void EventManager::reduceLock(int id)
{
	op1_[id] = op1_[id] - 1;
}

int EventManager::getCountOfEvent(int id)
{
	int r = 0;

	for (int i = 0; i < EVENT_MAXIMUM_NUMBER; i++)
	{
		if (trigger_[i])
		{
			r++;
		}
	}

	return r;
}

int EventManager::getOp1(int id)
{
	return op1_[id];
}

int EventManager::getOp2(int id)
{
	return op2_[id];
}

int EventManager::getTickNow()
{
	return tick_;
}

void EventManager::setOp1(int id, int value)
{
	op1_[id] = value;
}

void EventManager::setReject(int id, bool enable)
{
	reject_[id] = enable;
}

void EventManager::setReject()
{
	for (int i = 0; i < EVENT_MAXIMUM_NUMBER; i++)
	{
		reject_[i] = false;
	}
}

bool EventManager::getReject(int id)
{
	return reject_[id];	
}