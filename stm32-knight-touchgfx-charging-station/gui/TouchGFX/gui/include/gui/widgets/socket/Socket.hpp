#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class Socket : public Container
{
public:
	Socket(bool isMirrorMode, MachineStatus *machineStatus);
	virtual ~Socket();

	virtual void handleTickEvent();	
	
	virtual void initialize(MachineStatus *status, bool is_mirror);
	virtual void renderGraphic();
	virtual void renderElement();

	void beginAnimation(int end_x, int end_y, int end_width, int end_height, int end_alpha, int duration);
	//void setSlideAnimationEndedCallback(GenericCallback<const uint8_t>& callback);
	//void setBrightness(int value);
	//void bindMachineStatus(MachineStatus* status);
	//void updateGraphic();
	void saveMachineStatus();

	uint8_t getAlpha();
	
protected:
	
private:	
	enum AnimationStage
	{
		ANIMATION_STOP,
		ANIMATION_PLAY
	};

	static const int SELECTOR_SIZE_ = 230;
	static const int APLPHA_MAX_DISPLAY_POSITION_ = 170;
	static const int APLPHA_MINIMA_ = 52;
	
	//BitmapId socket_left_id_;
	//BitmapId socket_left_large_id_;
	ZoomAnimationImage socket_;
	
	//rfid_method_prv_ = ms_->rfid_method;
	int ux_socket_status_right_prv_;
	int ux_socket_status_left_prv_;
	bool is_mirror_;
	int original_point_;
	int alpha_;
	int alpha_delta_;
	int8_t direction_;
	int duration_;
	int tick_;
	CommonConstant& cc_ = CommonConstant::getInstance();
	ViewStage stage_;
	AnimationStage animation_stage_;
	MachineStatus *ms_;

	int encodeToAlpha(int src);
	void adjustAlpha(int x);

	const int16_t getSocketSmallRightBitmapID();
	const int16_t getSocketLargeRightBitmapID();
	const int16_t getSocketSmallLeftBitmapID();
	const int16_t getSocketLargeLeftBitmapID();

	Callback<Socket, const ZoomAnimationImage& > item_zoom_animation_ended_callback_;
	void itemZoomAnimationEndedHandler(const ZoomAnimationImage& source);
};

#endif /* SOCKET_HPP */