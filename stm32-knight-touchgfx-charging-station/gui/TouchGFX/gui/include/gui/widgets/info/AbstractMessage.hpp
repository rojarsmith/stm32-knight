#ifndef ABSTRACTMESSAGE_HPP
#define ABSTRACTMESSAGE_HPP

#include <touchgfx/containers/Container.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/common/EventManager.hpp>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/info/AbstractContent.hpp>
#include <gui/widgets/info/Content0201.hpp>
#include <gui/widgets/info/Content0202.hpp>
#include <gui/widgets/info/Content0203.hpp>
#include <gui/widgets/info/Content0204.hpp>
#include <gui/widgets/info/Content0205.hpp>
#include <gui/widgets/info/Content0206.hpp>
#include <gui/widgets/info/Content0207.hpp>
#include <gui/widgets/info/Content0208.hpp>
#include <gui/widgets/info/Content0301.hpp>
#include <gui/widgets/info/Content0404.hpp>
#include <gui/widgets/info/Content0501.hpp>
#include <gui/widgets/info/Content0504.hpp>
#include <gui/widgets/info/ContentE1.hpp>
#include <gui/widgets/info/ContentE2.hpp>
#include <gui/widgets/info/ContentE3.hpp>
#include <gui/widgets/info/ContentE4.hpp>
#include <gui/widgets/info/ContentE5.hpp>
#include <gui/widgets/info/ContentE6.hpp>

using namespace touchgfx;

class AbstractMessage : public Container
{
public:
	enum ContentType
	{
		CONTENT_0201,
		CONTENT_0202,
		CONTENT_0203,
		CONTENT_0204,
		CONTENT_0205,
		CONTENT_0206,
		CONTENT_0207,
		CONTENT_0208,
		CONTENT_0212,
		CONTENT_0213,
		CONTENT_0214,
		CONTENT_0301,
		CONTENT_0302,
		CONTENT_0303,
		CONTENT_0404,
		CONTENT_0501,
		CONTENT_0504,
		CONTENT_E1,
		CONTENT_E2,
		CONTENT_E3,
		CONTENT_E4,
		CONTENT_E5,
		CONTENT_E6
	};

	AbstractMessage();
	virtual ~AbstractMessage();

	virtual void handleTickEvent();	

	virtual void initialize(MachineStatus *status, ContentType content);
	virtual void setAnimationDuration(int duration);
	virtual void setOpenCompletedCallback(GenericCallback<const int>& callback);		                
	virtual void setCloseCompletedCallback(GenericCallback<const int>& callback);
	virtual void open(int duration);
	virtual void close(int duration);
	virtual MessageNumber getInitializeType();
protected:
	enum AnimationStage
	{
		ANIMATION_STOP,
		ANIMATION_OPEN,
		ANIMATION_OPEN_CONTENT,
		ANIMATION_CLOSE,
		ANIMATION_CLOSE_CONTENT
	};
	
	MessageNumber message_number_;
	int animation_duration_;
	int animation_lock_;
	AnimationStage animation_stage_;
	int return_value_;
	ContentType content_type_;
	AbstractContent *content_;
	int pcount_;
	EventManager em_;
	MachineStatus *ms_;

	//::[Event]::
	Callback<AbstractMessage, const int> event_trigger_callback_;
	virtual void eventTriggerHandler(const int source);
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();

private:
	GenericCallback<const int>* open_completed_callback_;
	GenericCallback<const int>* close_completed_callback_;

	Callback<AbstractMessage, const int> content_open_end_callback_;
	void contentOpenEndHandler(const int source);

	Callback<AbstractMessage, const int> content_close_end_callback_;
	void contentCloseEndHandler(const int source);
};

#endif /* ABSTRACTMESSAGE_HPP */
