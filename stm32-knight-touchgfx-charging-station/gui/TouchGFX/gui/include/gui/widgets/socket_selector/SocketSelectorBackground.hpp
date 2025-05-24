#ifndef SOCKETSELECTORBACKGROUND_HPP
#define SOCKETSELECTORBACKGROUND_HPP

#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/ContainerEx.hpp>
#include <gui/widgets/socket_selector/SocketSelectorBackgroundCharging.hpp>

using namespace touchgfx;

class SocketSelectorBackground : public ContainerEx
{
public:
	SocketSelectorBackground();
	virtual ~SocketSelectorBackground();

	virtual void handleTickEvent();

	void initialize(MachineStatus* status);
	void setSide(bool side); //true=right.
	void setAnimationInterval(int interval);
	void setTargetCircleAnimate(bool enable);
	void updateGraphic();
protected:
	//virtual void event_3();
	//virtual void event_4();
	//virtual void event_5();
	virtual void event_6(); //UpdateGraphic
	//virtual void event_7(); //Circle rotate start
	//virtual void event_8(); //Circle rotate stop
	virtual void event_9(); //Available
	virtual void event_10(); //Charging
	virtual void event_11(); //Full
	virtual void event_12(); //plug not in socket
	virtual void event_13(); //UI black
private:	
	bool side_;
	int animation_interval_;
	int integration_;
	int integration_interval_;	
	int integration_l2_;
	bool integration_direction_;
	int plug_status_;
	int plug_status_prv_;
	MachineStatus *ms_;

	//Target Circle
	int target_circle_animation_duration_;
	float target_circle_z_angle_;
	float target_circle_delta_z_angle_;
	bool is_target_circle_animate_;


	SocketSelectorBackgroundCharging layer_charging_;	
	Image layer_3_;
	AnimationTextureMapper target_circle_;
	TextArea title_;
};

#endif /* SOCKETSELECTORBACKGROUND_HPP */