#include <gui/containers/CustomContainerEventEngine.hpp>
#include <touchgfx/Application.hpp>

CustomContainerEventEngine::CustomContainerEventEngine()
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

CustomContainerEventEngine::~CustomContainerEventEngine()
{
	Application::getInstance()->unregisterTimerWidget(this);
}

void CustomContainerEventEngine::handleTickEvent()
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
			case LOCK_COUNT:				
				this->event_trigger_callback_->execute(i);
				trigger_[i] = 0;
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
			case ONLY_ACCEPT_DIFF_EVENT_BEFORE_COUNT_DOWN:
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
		else
		{
			switch (type_[i])
			{
			case LOCK_COUNT:
				if (op1_[i] >= 1)
				{
					op1_[i] = op1_[i] - 1;
				}				
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

void CustomContainerEventEngine::setEventTriggerCallback(GenericCallback<const int>& callback)
{
	event_trigger_callback_ = &callback;
}

void CustomContainerEventEngine::addOneTimeEvent(int id)
{
	if (reject_[id])
	{
		return;
	}

	removeEvent(id);
	type_[id] = EventType::ONE_TIME;
	trigger_[id] = true;
}

void CustomContainerEventEngine::addAlwaysKeepEvent(int id, int op1)
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

void CustomContainerEventEngine::addCountDownEvent(int id, int op1)
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

void CustomContainerEventEngine::addLockCountEvent(int id, int op1)
{
	if (op1_[id] >= 1)
	{
		return;
	}

	removeEvent(id);
	type_[id] = EventType::LOCK_COUNT;
	trigger_[id] = true;
	op1_[id] = op1;
}

void CustomContainerEventEngine::addLoopChainEvent(int id, int op1, int op2)
{
	removeEvent(id);
	type_[id] = EventType::LOOP_CHAIN;
	trigger_[id] = true;
	op1_[id] = op1;
	op2_[id] = op2;
}

void CustomContainerEventEngine::addRangeIncreaseEvent(int id, int op1, int op2)
{
	removeEvent(id);
	type_[id] = EventType::RANGE_INCREASE;
	trigger_[id] = true;
	op1_[id] = op1;
	op2_[id] = op2;
}

void CustomContainerEventEngine::removeEvent(int id)
{
	type_[id] = 0;
	trigger_[id] = false;
	op1_[id] = 0;
	op2_[id] = 0;
}

void CustomContainerEventEngine::removeAllEvent()
{
	for (int i = 0; i < EVENT_MAXIMUM_NUMBER; i++)
	{
		removeEvent(i);
	}
}

void CustomContainerEventEngine::reduceLock(int id)
{
	op1_[id] = op1_[id] - 1;
}

int CustomContainerEventEngine::getCountOfEvent(int id)
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

int CustomContainerEventEngine::getOp1(int id)
{
	return op1_[id];
}

int CustomContainerEventEngine::getOp2(int id)
{
	return op2_[id];
}

int CustomContainerEventEngine::getTickNow()
{
	return tick_;
}

void CustomContainerEventEngine::setOp1(int id, int value)
{
	op1_[id] = value;
}

void CustomContainerEventEngine::setReject(int id, bool enable)
{
	reject_[id] = enable;
}

void CustomContainerEventEngine::setReject()
{
	for (int i = 0; i < EVENT_MAXIMUM_NUMBER; i++)
	{
		reject_[i] = false;
	}
}

bool CustomContainerEventEngine::getReject(int id)
{
	return reject_[id];
}