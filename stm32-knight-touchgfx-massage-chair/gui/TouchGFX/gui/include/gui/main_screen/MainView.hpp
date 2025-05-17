#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/widget/ContainerDesk.hpp>
#include <gui/widget/ContainerDeskPage0.hpp>
#include <gui/widget/ContainerDeskPage1.hpp>
#include <gui/widget/ContainerDeskPage2.hpp>
#include <gui/widget/TaskBarWheel.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
// #include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

// #define CANVAS_BUFFER_SIZE (40000)

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	virtual void afterTransition();
	virtual void handleTickEvent();
protected:
	FrontendApplication& application() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
    // static uint8_t canvasBufferMain[CANVAS_BUFFER_SIZE];

	int stage1;
	int stage2;
	enum States
	{
		ANIMATE_RUN,
		AFTER_ANIMATE_RUN,
		ANIMATION_STOP
	} currentState;

	enum CallbackIds
	{
		CONTAINER_DESK_PAGE_0 = 0,
		CONTAINER_DESK_PAGE_1,
		CONTAINER_DESK_PAGE_2
	};

	const static int16_t taskBarPadding = 15;
	const static int16_t taskBarWidth = 100;

	ModalDialog alartDialog;

	Box backgroundColor;
	Image blockShadow;
	MoveAnimator<Image> leftUp;
	MoveAnimator<Image> leftDown;
	MoveAnimator<Image> leftBackground;
	MoveAnimator<ContainerDesk> desk;
	MoveAnimator<TaskBarWheel> taskBar;
	ContainerDeskPage0 page0;
	ContainerDeskPage1 page1;
	ContainerDeskPage2 page2;

	void enableTouchAll();
	void disableTouchAll();

	Callback<MainView, const ContainerDesk& >containerDeskAnimationEndedCallback;
	void containerDeskAnimationEndedCallbackHandler(const ContainerDesk& source);

	Callback<MainView, const MoveAnimator<TaskBarWheel>& >taskBarWheelMoveAnimationEndedCallback;
	void taskBarWheelMoveAnimationEndedHandler(const MoveAnimator<TaskBarWheel>& source);

	Callback<MainView, const uint8_t>taskBarItemClickedThroughCallback;
	void taskBarItemClickedThroughHandler(const uint8_t source);

	Callback<MainView, const uint8_t>buttonClickedThroughCallback;
	void buttonClickedThroughHandler(const uint8_t source);

	Callback<MainView, const uint8_t>buttonClickedThroughCallback2;
	void buttonClickedThroughHandler2(const uint8_t source);
};

#endif // MAINVIEW_HPP
