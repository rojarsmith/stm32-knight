#ifndef SOCKETSELECTORBAR_HPP
#define SOCKETSELECTORBAR_HPP

#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui/common/EventManager.hpp>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/ContainerEx.hpp>
#include <gui/widgets/socket_selector/SocketSelectorBackground.hpp>

using namespace touchgfx;

//#define SELECTOR_X_HELF_SIZE 35
#define SELECTOR_CORRDINATE_RIGHT_LIMIT 302 // 800x480
#define SELECTOR_CORRDINATE_LEFT_LIMIT 15
//#define SELECTOR_CORRDINATE_RIGHT_LIMIT 484
//#define SELECTOR_CORRDINATE_LEFT_LIMIT 24
//#define SELECTOR_SIZE 230

class SocketSelectorBar : public ContainerEx
{
public:
	SocketSelectorBar();
	virtual ~SocketSelectorBar();

	virtual void handleDragEvent(const DragEvent& evt);
	virtual void handleTickEvent();	
	virtual void handleClickEvent(const ClickEvent& evt);	
		
	void initialize(MachineStatus* status);
	//void setViewData(MachineStatusProperties * data);	
	void setIndicatorDragCallback(GenericCallback<int>& callback);
	void setSocketSelectedCallback(GenericCallback<ChargeSocketSelected>& callback);
	void updateView();
protected:
	enum AnimationState
	{		
		ANIMATING_SNAP,   
		ANIMATING_DRAG,   
		NO_ANIMATION      
	};

	AnimationState current_animation_state_;

	void moveIndicator(int new_x_position);
	void animateIndicator(int new_x_position, int duration, EasingEquation equation);	
private:	
	//static const int VORIGINAL_POINT_ = 0;
	//static const int VSELECTOR_SIZE_ = 200;
	static const int ORIGINAL_POINT_ = 175;
	static const int SELECTOR_SIZE_ = 143;
	//static const int ORIGINAL_POINT_ = 280;
	//static const int SELECTOR_SIZE_ = 230;	
	//static const int VDIRECTION_MAX_DISPLAY_POSITION_ = 160;
	static const int DIRECTION_MAX_DISPLAY_POSITION_ = 106;
	static const int DIRECTION_NOT_ALLOW_MAX_DISPLAY_POSITION_ = 18;
	//static const int DIRECTION_MAX_DISPLAY_POSITION_ = 170;
	//static const int DIRECTION_NOT_ALLOW_MAX_DISPLAY_POSITION_ = 30;
	AnimatedImage animation_;
	BitmapId background_left_id_;
	Image background_right_;
	Image background_left_;
	AnimationTextureMapper target_circle_right_;
	AnimationTextureMapper target_circle_left_;
	MoveAnimator<Container> ind_;
	Image indicator_;
	Image indicator_direction_;
		
	SocketSelectorBackground socket_slider_animation_right_;
	SocketSelectorBackground socket_slider_animation_left_;

	int draw_interval;
	//int tick_;
	bool is_grabbed_;
	bool is_animate_indicator_;
	bool is_animate_indicator_hack_;
	int doriginal_point_;
	int dnot_allow_selecte_threshold_right_;
	int dnot_allow_selecte_threshold_left_;
	//bool is_target_circle_right_animate_;
	//bool is_target_circle_left_animate_;
	int shift_x_indicator_direction_;
	int right_cut_off_;
	int left_cut_off_;
	int right_grab_threshold_;
	int left_grab_threshold_;
	int vgrab_threshold_right_;
	int vgrab_threshold_left_;
	int vnot_allow_selecte_threshold_right_;
	int vnot_allow_selecte_threshold_left_;
	int vvalid_selected_threshold_right_;
	int vvalid_selected_threshold_left_;
	int valid_selected_threshold_;
	int indicator_width_helf_;
	int indicator_width_quarter_;
	int vx_;
	//float vratio_;
	ChargeSocketSelected charge_socket_selected_;
	MachineStatus *ms_;

	//Target Circle
	int target_circle_animation_duration_;
	float target_circle_z_angle_;
	float target_circle_delta_z_angle_;
	
	void adjustIndicatorDirectionAlpha(int x);
	void adjustForBoundriesRight(int& new_x_value);
	void adjustForBoundriesLeft(int& new_x_value);
	void snap(int x);
	int encodePhase(int src, int src_rng_start, int src_rng_end, int dist_rng_start, int dist_rng_end);
	int encodeToAlpha(int src);

	GenericCallback<int>* indicator_drag_callback_;

	GenericCallback<ChargeSocketSelected>* socket_selected_callback_;

	//Callback<SocketSelectorBar, const MoveAnimator<Image>& > image_move_ended_callback_;
	//void imageMoveEndedHandler(const MoveAnimator<Image>& image);

	Callback<SocketSelectorBar, const MoveAnimator<Container>& > container_move_ended_callback_;
	void containerMoveEndedHandler(const MoveAnimator<Container>& container);

	//::[Event]::
	EventManager em_;
	Callback<SocketSelectorBar, const int> event_trigger_callback_;
	void eventTriggerHandler(const int source);
	void event1();
	void event2();
	void event3();
};

#endif /* SOCKETSELECTORBAR_HPP */