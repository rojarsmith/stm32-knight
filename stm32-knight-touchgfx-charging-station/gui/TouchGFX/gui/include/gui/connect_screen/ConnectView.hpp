#ifndef CONNECTVIEW_HPP
#define CONNECTVIEW_HPP

#include <gui_generated/connect_screen/ConnectViewBase.hpp>
#include <gui/connect_screen/ConnectPresenter.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <mvp/View.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/common/BaseView.hpp>
#include <gui/widgets/backto/Backto.hpp>
#include <gui/widgets/car/Car.hpp>
#include <gui/widgets/footer/Footer.hpp>
#include <gui/widgets/information/Information.hpp>
#include <gui/widgets/language/Language.hpp>
#include <gui/widgets/loading/Loading.hpp>
#include <gui/widgets/title/Title.hpp>
#include <gui/widgets/wallpaper/Wallpaper.hpp>
#include <gui/widgets/plugin/Plugin.hpp>
#include <gui/widgets/socket/Socket.hpp>

class ConnectView : public BaseView<ConnectPresenter, ConnectViewBase>
{
public:
    ConnectView();
    virtual ~ConnectView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
	FrontendApplication& application()
	{
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
	BitmapId socket_left_id_;
	BitmapId plugin_black_left_id_;
	Information information_;
	Language language_;
	Backto backto_;
	ZoomAnimationImage pole_;
	Socket socket_right_;
	Socket socket_left_;
	MoveAnimator<AnimationTextureMapper> socket_right_old_;
	MoveAnimator<AnimationTextureMapper> socket_left_old_;
	Plugin plugin_right_;
	Plugin plugin_left_;
	FadeAnimator<Image> plugin_out_;
	MoveAnimator<AnimationTextureMapper> plugin_black_right_old_;
	MoveAnimator<AnimationTextureMapper> plugin_black_left_old_;
	Car car_;
	Title title_;
	Footer footer_;
	Loading checking_;
	Wallpaper wallpaper_;

	int animation_duration = 60;
	int animation_locker_ = 0;
	int animation_locker_transition_in_ = 1;
	int animation_locker_transition_out_ = 1;
	int plug_status_;
	int plug_status_prv_;
	ScreenNumber scenario_prev_;

	Callback<ConnectView, const int> button_clicked_callback_;
	void buttonClickedHandler(const int source);

	Callback<ConnectView, const int> backto_button_clicked_callback_;
	void backtoButtonClickedHandler(const int source);

	Callback<ConnectView, const int> checking_open_end_callback_;
	void checkingOpenEndHandler(const int source);

	Callback<ConnectView, const int> checking_hide_end_callback_;
	void checkinghideEndHandler(const int source);

	Callback<ConnectView, const int> checking_close_end_callback_;
	void checkingCloseEndHandler(const int source);

	Callback<ConnectView, const uint8_t> carMoveAnimationEndedCallback;
	void carMoveAnimationEndedHandler(const uint8_t source);

	Callback<ConnectView, const int> message_open_end_callback_;
	void messageOpenEndHandler(const int source);

	Callback<ConnectView, const int> message_close_end_callback_;
	void messageCloseEndHandler(const int source);

	Callback<ConnectView, const MoveAnimator<Footer>& > footerMoveAnimationEndedCallback;
	void footerMoveAnimationEndedHandler(const MoveAnimator<Footer>& source);

	//::[Event]::
	enum EventList
	{
		EVENT_RENDER_GRAPHIC = 3,
		EVENT_TRAN_IN = 10,
		EVENT_TRAN_IN_END = 11,
		EVENT_0500 = 12,
		EVENT_AFTER_CHECKING_OPENED = 18,
		EVENT_AFTER_CHECKING_CLOSED = 19,
		EVENT_TRAN_OUT = 21,
		EVENT_TRAN_OUT_END = 26,
		EVENT_OPEN_CHECKING = 28,
		EVENT_CLOSE_CHECKING = 29
	};
	Callback<ConnectView, const int> event_trigger_callback_;
	virtual void eventTriggerHandler(const int source);
	virtual void event1();
	virtual void event2();
	virtual void eventRenderGraphic();
	virtual void event9();
	virtual void eventTranIn();
	virtual void eventTranInEnd();
	virtual void event0500();
	virtual void event15();
	virtual void event16();
	virtual void event17();
	virtual void eventAfterCheckingOpened();
	virtual void eventAfterCheckingClosed();
	virtual void event20();
	virtual void eventTranOut();
	virtual void event22();
	virtual void event23();
	virtual void event24();
	virtual void event25();
	virtual void eventTranOutEnd();
	virtual void eventOpenChecking();
	virtual void eventCloseChecking();

#pragma region get style resource
	const bool getCarIsMirrored();
	const ChargeSocketSelected getCarChargeSocket();
	const int16_t getCarX();
	const int16_t getPoleReturnX();
	const ZoomAnimationImage::ZoomMode getPoleReturnZoomMode();
	const int16_t getCheckingX();
#pragma endregion get style resource
};

#endif // CONNECTVIEW_HPP
