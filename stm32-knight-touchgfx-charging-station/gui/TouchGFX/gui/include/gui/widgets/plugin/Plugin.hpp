#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <gui/common/EventManager.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/model/ModelSchema.hpp>
#include <gui/common/Resolution.hpp>

using namespace touchgfx;

class Plugin : public Container, Resolution
{
public:
	Plugin(bool is_mirrored, MachineStatus *machine_status);
	virtual ~Plugin();

	void initialize(MachineStatus* status, bool is_mirrored);
	void beginAnimation(int end_x, int end_y, int end_width, int end_height, int end_alpha, int duration);	
	void renderGraphic();
	void saveMachineStatus();
protected:
	
private:	
	int16_t PLUGIN_HOME_IN_X_OG_RIGHT_ = 318;
	int16_t PLUGIN_HOME_IN_X_OG_LEFT_ = -80;
	int16_t PLUGIN_HOME_IN_Y_OG_ = -158;
	int16_t PLUGIN_HOME_IN_W_OG_ = 241;
	int16_t PLUGIN_HOME_IN_H_OG_ = 1111;
	int16_t PLUGIN_RIGHT_LARGE_X_SHIFT_ = 58;
	int16_t PLUGIN_LEFT_LARGE_X_SHIFT_ = 428;
	//int16_t PLUGIN_HOME_IN_X_OG_RIGHT_ = 510;
	//int16_t PLUGIN_HOME_IN_X_OG_LEFT_ = -129;
	//int16_t PLUGIN_HOME_IN_Y_OG_ = -254;
	//int16_t PLUGIN_HOME_IN_W_OG_ = 387;
	//int16_t PLUGIN_HOME_IN_H_OG_ = 1779;
	//int16_t PLUGIN_RIGHT_LARGE_X_SHIFT_ = 93;
	//int16_t PLUGIN_LEFT_LARGE_X_SHIFT_ = 686;

	ZoomAnimationImage plugin_mask_;
	ZoomAnimationImage plugin_;	
	
	bool is_mirrored_;
	int plugin_mask_alpha_;
	int alpha_;
	int alpha_delta_;
	int duration_;	
	int ux_plugin_in_out_status_prev_;
	int ux_plugin_usability_status_prev_;
	bool is_inoutexg_;	
	MachineStatus *ms_;
	EventManager em_;

	Callback<Plugin, const ZoomAnimationImage& > item_zoom_animation_ended_callback_;
	void itemZoomAnimationEndedHandler(const ZoomAnimationImage& source);

	//::[Event]::
	Callback<Plugin, const int> event_trigger_callback_;
	void eventTriggerHandler(const int source);
	void event1();
	void event30(); //Mapping to mask.
	void event31(); //Load next.
	void event32(); //Begin exchange.
	void event33(); //Hide.
	void event34(); //

	int16_t getBitmapPluginX();
	int16_t getBitmapPluginY();
	int getBitmapPluginIdSmall();
	int getBitmapPluginIdLarge();
	int getBitmapPluginPositionShift();
	int getBitmapPluginWidth();
	int getBitmapPluginHeight();
};

#endif /* PLUGIN_HPP */