#ifndef SOCKETSELECTOR_HPP
#define SOCKETSELECTOR_HPP

#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/socket_selector/SocketSelectorBar.hpp>
#include <gui/widgets/ContainerEx.hpp>

using namespace touchgfx;

class SocketSelector : public Container//public ContainerEx
{
public:
	SocketSelector();
	virtual ~SocketSelector();
	virtual void handleClickEvent(const ClickEvent& evt);

	void initialize(MachineStatus* status);
	void setStyle(WeatherStyle style);	
	void setSlideDuration(int tick);
	void beginSlideAnimation(AnimationStyle animation, bool isRight);
	void setSocketSlidingCallback(GenericCallback<int>& callback);
	void setPlugNotInSocketCallback(GenericCallback<ChargeSocketSelected>& callback);
	void setBarMoveOutAnimationEndCallback(GenericCallback<ChargeSocketSelected>& callback);
	void setTouch(bool touchable);
	void updateView();	
protected:
	enum AnimationStage
	{
		ANIMATING_STAGE_OUT_SCREEN_1,
		ANIMATING_STAGE_OUT_SCREEN_2,
		ANIMATING_STAGE_NONE		
	};

	virtual void event_3(); //plug_in_socket
private:
	int ANIMATION_DURATION_S1_ = 30;
	const static int ANIMATION_DURATION_S2_ = 10;

	MoveAnimator<SocketSelectorBar> item_;

	WeatherStyle style_;

	int appearance_width_ = 240; // 800x480
	int appearance_height_ = 325;
	//int appearance_width_ = 384;
	//int appearance_height_ = 520;
	AnimationStage animation_stage_;
	MachineStatus *ms_;
	
	GenericCallback<int>* indicator_drag_callback_l2_;	
	GenericCallback<ChargeSocketSelected>* plug_not_in_socket_callback_;
	GenericCallback<ChargeSocketSelected>* bar_move_out_animation_end_callback_;

	Callback<SocketSelector, const MoveAnimator<SocketSelectorBar>& > item_move_animation_ended_callback_;
	void barMoveAnimationEndedHandler(const MoveAnimator<SocketSelectorBar>& source);

	Callback<SocketSelector, ChargeSocketSelected> selector_move_out_callback_;
	void selectorMoveAnimationEndHandler(ChargeSocketSelected socket);
};

#endif /* SOCKETSELECTOR_HPP */