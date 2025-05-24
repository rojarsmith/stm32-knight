#ifndef HOMEVIEW_HPP
#define HOMEVIEW_HPP

#include <gui_generated/home_screen/HomeViewBase.hpp>
#include <gui/home_screen/HomePresenter.hpp>
#include <gui/common/BaseView.hpp>
#include <gui/common/TargetFix.hpp>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <mvp/View.hpp>
#include <gui/common/EventManager.hpp>
#include <gui/common/BaseView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/home_screen/HomePresenter.hpp>
//#include <gui/widgets/context/ContextNameValue.hpp>
#include <gui/widgets/footer/Footer.hpp>
#include <gui/widgets/info/AbstractMessage.hpp>
#include <gui/widgets/info/MessageE5.hpp>
//#include <gui/widgets/language/Language.hpp>
//#include <gui/widgets/loading/Loading.hpp>
#include <gui/widgets/information/Information.hpp>
#include <gui/widgets/title/Title.hpp>
#include <gui/widgets/plugin/Plugin.hpp>
#include <gui/widgets/socket/Socket.hpp>
//#include <gui/widgets/socket_selector/SocketSelector.hpp>
#include <gui/widgets/wallpaper/Wallpaper.hpp>

class HomeView : public BaseView<HomePresenter, HomeViewBase>
{
public:
    HomeView();
	virtual ~HomeView();
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
	FrontendApplication& application()
	{
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
	ChargeSocketSelected socket_ret1_;

	//::[UX Item]::
	Wallpaper wallpaper_;
	ZoomAnimationImage pole_;
	Socket socket_right_;
	Socket socket_left_;
	Plugin plugin_right_;
	Plugin plugin_left_;
	Title title_;
	Information information_;
	//Language language_;
	//SocketSelector socket_slider_;
	Footer footer_;
	Box lang_mask_;

	Callback<HomeView, const ZoomAnimationImage&> poleAnimationEndedCallback;
	void poleAnimationEndedHandler(const ZoomAnimationImage& image);

	Callback<HomeView, const int> button_clicked_callback_;
	void buttonClickedHandler(const int source);
	//UX Item End

#pragma region Event
	enum EventList
	{
		EVENT_1TICK_LOOP,
		EVENT_RENDER_GRAPHIC = 3,
		EVENT_SEND_COMMAND,
		EVENT_CHANGE_SCREEN,
		EVENT_CHANGE_TO_STANDBY = 5,
		EVENT_COUNTDOWN_TO_STANDBY_SEND_COMMAND = 7,
		EVENT_ONE_TIME_RENDER = 10,
		EVENT_PLUG_NOT_IN_SOCKET = 15,
		EVENT_TRAN_OUT_RFID = 20,
		EVENT_TRAN_IN = 22,
		EVENT_TRAN_IN_END = 23,
		EVENT_TRAN_OUT = 25,
		EVENT_SEND_COMMAND_TO_0300 = 27,
		EVENT_CHANGE_SCREEN_TO_0300 = 28
	};
	Callback<HomeView, const int> event_trigger_callback_;
	void eventTriggerHandler(const int source);
	void event2();
	void eventRenderGraphic();
	void event6();  //weather changed.
	void eventTranIn();
	void eventTranOut();
#pragma endregion Event
};

#endif // HOMEVIEW_HPP
