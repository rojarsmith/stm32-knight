#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <BitmapDatabase.hpp>

MainView::MainView()
	:
	stage1(0),
	stage2(0),
	currentState(ANIMATION_STOP),
	containerDeskAnimationEndedCallback(this, &MainView::containerDeskAnimationEndedCallbackHandler),
	taskBarWheelMoveAnimationEndedCallback(this, &MainView::taskBarWheelMoveAnimationEndedHandler),
	taskBarItemClickedThroughCallback(this, &MainView::taskBarItemClickedThroughHandler),
	buttonClickedThroughCallback(this, &MainView::buttonClickedThroughHandler),
	buttonClickedThroughCallback2(this, &MainView::buttonClickedThroughHandler2)
{

}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();

    // CanvasWidgetRenderer::setupBuffer(canvasBufferMain, CANVAS_BUFFER_SIZE);

	disableTouchAll();

	backgroundColor.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	add(backgroundColor);

	leftBackground.setPosition(-(taskBarWidth + taskBarPadding * 2), 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	leftBackground.setBitmap(Bitmap(BITMAP_BACKGROUND_10_130X480_ID));

	add(leftBackground);

	taskBar.addTaskBarItem(BITMAP_ITEM1R_100X100_ID, BITMAP_ITEM1P_100X100_ID, T_ICON_AUTO, CONTAINER_DESK_PAGE_1);
	taskBar.addTaskBarItem(BITMAP_ITEM2R_100X100_ID, BITMAP_ITEM2P_100X100_ID, T_ICON_CONFIG, CONTAINER_DESK_PAGE_2);
	taskBar.addTaskBarItem(BITMAP_ITEM0R_100X100_ID, BITMAP_ITEM0P_100X100_ID, T_ICON_HOME, CONTAINER_DESK_PAGE_0);
	taskBar.addTaskBarItem(BITMAP_ITEM0R_100X100_ID, BITMAP_ITEM0P_100X100_ID, T_ICON_NONE, CONTAINER_DESK_PAGE_1, false);
	taskBar.addTaskBarItem(BITMAP_ITEM0R_100X100_ID, BITMAP_ITEM0P_100X100_ID, T_ICON_NONE, CONTAINER_DESK_PAGE_1, false);
	taskBar.addTaskBarItem(BITMAP_ITEM0R_100X100_ID, BITMAP_ITEM0P_100X100_ID, T_ICON_NONE, CONTAINER_DESK_PAGE_1, false);
	taskBar.initialize(taskBarWidth, HAL::DISPLAY_HEIGHT);
	taskBar.setTaskBarItemClickedThroughAction(taskBarItemClickedThroughCallback);
	taskBar.setMoveAnimationEndedAction(taskBarWheelMoveAnimationEndedCallback);
	taskBar.setXY(-(taskBarWidth + taskBarPadding), 0);

	add(taskBar);

	desk.setAnimationEndedAction(containerDeskAnimationEndedCallback);
	int desk_min_X = HAL::DISPLAY_WIDTH - taskBarWidth - taskBarPadding * 2;
	desk.setPosition(taskBarWidth + taskBarPadding * 2, 0, HAL::DISPLAY_WIDTH - taskBarWidth - taskBarPadding * 2, HAL::DISPLAY_HEIGHT);

	page0.setPosition(desk_min_X, 0, desk_min_X, 480);
	desk.addContainer(page0);

	page1.setPosition(desk_min_X, 0, desk_min_X, 480);
	desk.addContainer(page1);

	page2.setPosition(desk_min_X, 0, desk_min_X, 480);
	desk.addContainer(page2);

	add(desk);

	leftUp.setPosition(0, 0, HAL::DISPLAY_WIDTH, Bitmap(BITMAP_NAVI_20_130X10_ID).getHeight());
	leftUp.setBitmap(Bitmap(BITMAP_NAVI_20_130X10_ID));

	add(leftUp);

	leftDown.setPosition(0, HAL::DISPLAY_HEIGHT - Bitmap(BITMAP_NAVI_21_130X10_ID).getHeight(), HAL::DISPLAY_WIDTH, Bitmap(BITMAP_NAVI_21_130X10_ID).getHeight());
	leftDown.setBitmap(Bitmap(BITMAP_NAVI_21_130X10_ID));

	add(leftDown);

	blockShadow.setBitmap(Bitmap(BITMAP_SHADOW_20_10X480_ID));
	blockShadow.setXY(taskBarWidth + taskBarPadding * 2, 0);
	//blockShadow.setXY(desk_min_X, 0);
	blockShadow.setAlpha(150);
	add(blockShadow);

	alartDialog.setVisible(false);
	alartDialog.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	alartDialog.setClickedAction(buttonClickedThroughCallback2);
	add(alartDialog);

	page2.setPopupAction(buttonClickedThroughCallback);
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::buttonClickedThroughHandler2(const uint8_t source)
{
	switch (source)
	{
	case 0:

		break;
	case 1:
		page2.restAll();
		break;
	default:
		break;
	}
	// invalidateRect(touchgfx::Rect(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT));
	touchgfx::Rect fullScreenRect(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
    invalidateRect(fullScreenRect);
}

void MainView::buttonClickedThroughHandler(const uint8_t source)
{
	alartDialog.setTouchable(true);
	alartDialog.setVisible(true);
	alartDialog.setResizeText();
	alartDialog.invalidate();
}

void MainView::afterTransition()
{
	int duration = 15;
	taskBar.startMoveAnimation(taskBarPadding, 0, duration, EasingEquations::cubicEaseOut);
	leftBackground.startMoveAnimation(0, 0, duration, EasingEquations::cubicEaseOut);
}

void MainView::handleTickEvent()
{
	if (1 == stage1)
	{
		enableTouchAll();
		stage1 = 0;
	}

	if (1 == stage2)
	{
		enableTouchAll();
		stage2 = 0;
	}
}

void MainView::taskBarWheelMoveAnimationEndedHandler(const MoveAnimator<TaskBarWheel>& source)
{
	stage1++;
}

void MainView::containerDeskAnimationEndedCallbackHandler(const ContainerDesk& source)
{
	stage2++;

	enableTouchAll();
}

void MainView::taskBarItemClickedThroughHandler(const uint8_t source)
{
	disableTouchAll();

	if (ContainerDesk::ANIMATION_STOP != desk.getCurrentState())
	{
		return;
	}

	switch (source)
	{
	case CONTAINER_DESK_PAGE_0:
		desk.changePage(page0, 0);
		break;
	case CONTAINER_DESK_PAGE_1:
		desk.changePage(page1, 1);
		break;
	case CONTAINER_DESK_PAGE_2:
		desk.changePage(page2, 2);
		break;
	default:
		break;
	}

	blockShadow.invalidate();
}

void MainView::enableTouchAll()
{
	taskBar.setScrollable();
	taskBar.setTouchable(true);
	desk.setTouchable(true);
}

void MainView::disableTouchAll()
{
	taskBar.setScrollable(false);
	taskBar.setTouchable(false);
	desk.setTouchable(false);
}
