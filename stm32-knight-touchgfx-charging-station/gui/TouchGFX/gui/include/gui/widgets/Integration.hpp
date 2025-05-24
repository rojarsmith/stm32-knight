#ifndef INTEGRATION_HPP
#define INTEGRATION_HPP

#include <touchgfx/containers/Container.hpp>

using namespace touchgfx;

class Integration : public Container
{
public:
	Integration();
	virtual ~Integration();

	virtual void handleTickEvent();	

	virtual void setInterval(int interval);
	virtual void setTarget(int target);
	virtual void setArrivedCallback(GenericCallback<const int>& callback);	
	virtual void restart();
	virtual void pause();
protected:
	int tick_;
	int interval_;
	int output_;
	int target_;
	const int event_number_ = 4;
	int event_[4];

	virtual void run();
	virtual void event_1() {}
private:
	GenericCallback<const int>* arrived_callback_;	
};

#endif /* INTEGRATION_HPP */
