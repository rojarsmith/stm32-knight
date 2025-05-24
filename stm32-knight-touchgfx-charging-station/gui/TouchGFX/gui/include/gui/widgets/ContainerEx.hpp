#ifndef CONTAINEREX_HPP
#define CONTAINEREX_HPP

#include <touchgfx/containers/Container.hpp>

using namespace touchgfx;

class ContainerEx : public Container
{
public:
	ContainerEx();
	virtual ~ContainerEx();

	virtual void handleTickEvent();	

	virtual void setAnimationDuration(int duration);
	virtual void setOpenContainerCallback(GenericCallback<const int>& callback);
	virtual void setCloseContainerCallback(GenericCallback<const int>& callback);
	virtual void openContainer() {}
	virtual void closeContainer() {}
	virtual void decreaseOpenContainerAnimationLock();
	virtual void decreaseCloseContainerAnimationLock();
protected:
	int tick_;
	int animation_duration_;
	int open_container_animation_lock_;
	int close_container_animation_lock_;
	const int event_number_ = 20;
	int event_[20];

	virtual void event_1() {}
	virtual void event_2() {}
private:
	GenericCallback<const int>* open_container_callback_;
	GenericCallback<const int>* close_container_callback_;
};

#endif /* CONTAINEREX_HPP */
