#ifndef SOCKETSELECTORBACKGROUNDCHARGING_HPP
#define SOCKETSELECTORBACKGROUNDCHARGING_HPP

#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class SocketSelectorBackgroundCharging : public Container
{
public:
	SocketSelectorBackgroundCharging();
	virtual ~SocketSelectorBackgroundCharging();
	virtual void handleTickEvent();	
	void initialize(MachineStatus* status);
	void setSide(bool side); //true=right.
	virtual void beginAnimation();
	virtual void stopAnimation();	
protected:
	bool side_;
	bool animation_play_;	
	static int cam_[];
	int cam_length_;
	int animation_time_interval_;
	int animation_skip_interval_;
private:
	MachineStatus *ms_;

	Image layer_1_;
	FadeAnimator<Image> layer_2_;
};

#endif /* SOCKETSELECTORBACKGROUNDCHARGING_HPP */
