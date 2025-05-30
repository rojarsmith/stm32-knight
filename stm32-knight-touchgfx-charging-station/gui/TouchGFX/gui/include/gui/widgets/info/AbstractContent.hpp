#ifndef ABSTRACTCONTENT_HPP
#define ABSTRACTCONTENT_HPP

#include <touchgfx/containers/Container.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/common/EventManager.hpp>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class AbstractContent : public Container
{
public:	
	AbstractContent();
	virtual ~AbstractContent();

	virtual void handleTickEvent();	

	virtual void initialize(MachineStatus *status);
	virtual void setOpenCompletedCallback(GenericCallback<const int>& callback);		                
	virtual void setCloseCompletedCallback(GenericCallback<const int>& callback);
	virtual void open(int duration);
	virtual void close(int duration);
protected:
	enum AnimationStage
	{
		ANIMATION_STOP,
		ANIMATION_OPEN,
		ANIMATION_CLOSE,
	};

	int animation_duration_;
	int animation_lock_;
	AnimationStage animation_stage_;
	ReturnValue return_value_;
	MachineStatus *ms_;
	EventManager em_;	

	void sendCommandReturn();

	//::[Event]::
	Callback<AbstractContent, const int> event_trigger_callback_;
	virtual void eventTriggerHandler(const int source);
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();

private:
	GenericCallback<const int>* open_completed_callback_;
	GenericCallback<const int>* close_completed_callback_;
};

#endif /* ABSTRACTCONTENT_HPP */
