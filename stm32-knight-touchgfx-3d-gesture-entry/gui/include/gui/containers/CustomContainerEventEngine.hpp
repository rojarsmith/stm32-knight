#ifndef EVENT_CUSTOMCONTAINEREVENTENGINE_HPP
#define EVENT_CUSTOMCONTAINEREVENTENGINE_HPP

#define EVENT_MAXIMUM_NUMBER 20

#include <touchgfx/containers/Container.hpp>

using namespace touchgfx;

class CustomContainerEventEngine : public Container
{
public:
	enum EventType 
	{
		ONE_TIME, 
		ALWAYS_KEEP, 
		COUNT_DOWN, 
		LOCK_COUNT, 
		LOOP_CHAIN, 
		RANGE_INCREASE, 
		ONLY_ACCEPT_DIFF_EVENT_BEFORE_COUNT_DOWN
	};

	CustomContainerEventEngine();
	virtual ~CustomContainerEventEngine();
	virtual void handleTickEvent();
	virtual void setEventTriggerCallback(GenericCallback<const int>& callback);
	virtual void addOneTimeEvent(int id);
	virtual void addAlwaysKeepEvent(int id, int op1); //op1:Frequency Divider
	virtual void addCountDownEvent(int id, int op1); //op1:One time Event
	/**
	 * @fn virtual void CustomContainerEventEngine::addLockCountEvent(int id, int op1);
	 *
	 * @brief Adds a Lock Count Event.
	 *
	 * @note 60 == 1 sec
	 *
	 * @param
	 */
	virtual void addLockCountEvent(int id, int op1);
	virtual void addLoopChainEvent(int id, int op1, int op2); //op1:Count down, op2:Next One time Event
	virtual void addRangeIncreaseEvent(int id, int op1, int op2); //op1:low, op2:high
	virtual void removeEvent(int id);
	virtual void removeAllEvent();
	virtual void reduceLock(int id);
	virtual int getCountOfEvent(int id);
	virtual int getOp1(int id);
	virtual int getOp2(int id);
	virtual int getTickNow();
	virtual void setOp1(int id, int value);
	virtual void setReject(int id, bool enable);
	virtual void setReject();
	virtual bool getReject(int id);
private:

	bool trigger_[EVENT_MAXIMUM_NUMBER];
	int op1_[EVENT_MAXIMUM_NUMBER]; //time count.
	int op2_[EVENT_MAXIMUM_NUMBER]; //reserve.
	bool reject_[EVENT_MAXIMUM_NUMBER]; //protect group.
	//0, other = one time clear each loop or none event.
	//1 = keep always.
	//2 = count down event.
	//3 = lock count event.
	//4 = loop chain event.
	//5 = Range Increase event.
	uint8_t type_[EVENT_MAXIMUM_NUMBER];
	GenericCallback<const int>* event_trigger_callback_;
	int tick_;
};

#endif
