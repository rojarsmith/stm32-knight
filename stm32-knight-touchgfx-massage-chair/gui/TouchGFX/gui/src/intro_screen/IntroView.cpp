#include <gui/intro_screen/IntroView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#ifdef __ICCARM__
#include "FreeRTOS.h"
#include "task.h"
#endif
#ifndef SIMULATOR
#include "main.h"
#endif

IntroView::IntroView() :
    screenStage(SCREEN_REVEAL),
#ifndef SIMULATOR
    screenwidthreal(getScreenWidthReal()),
#else
    screenwidthreal(HAL::DISPLAY_WIDTH),
#endif
    boxFadeAnimationEndedCallback(this, &IntroView::boxFadeAnimationEndedHandler),
    imageFadeAnimationEndedCallback(this, &IntroView::imageFadeAnimationEndedHandler)
{
}

void IntroView::setupScreen()
{
    IntroViewBase::setupScreen();

	backgroundColor2.setPosition(0, 0, screenwidthreal, HAL::DISPLAY_HEIGHT);
	backgroundColor2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

	backgroundColor.setPosition(0, 0, screenwidthreal, HAL::DISPLAY_HEIGHT);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	backgroundColor.setAlpha(0);

	int16_t w = Bitmap(BITMAP_LOGO_ID).getWidth() / 2;
	int16_t h = Bitmap(BITMAP_LOGO_ID).getHeight() / 2;

	logo.setXY(screenwidthreal / 2 - w, HAL::DISPLAY_HEIGHT / 2 - h);
	logo.setBitmap(Bitmap(BITMAP_LOGO_ID));
	logo.setAlpha(0);

	add(backgroundColor2);
	add(backgroundColor);
	add(logo);
}

void IntroView::tearDownScreen()
{
    IntroViewBase::tearDownScreen();

	backgroundColor.clearFadeAnimationEndedAction();
	logo.clearFadeAnimationEndedAction();
}

void IntroView::afterTransition()
{
	backgroundColor.setFadeAnimationEndedAction(boxFadeAnimationEndedCallback);
	backgroundColor.startFadeAnimation(255, 15, EasingEquations::linearEaseIn);
}

void IntroView::boxFadeAnimationEndedHandler(const FadeAnimator<Box>& source)
{
	if (SCREEN_REVEAL == screenStage) {
		logo.setFadeAnimationEndedAction(imageFadeAnimationEndedCallback);
		logo.startFadeAnimation(255, 15, EasingEquations::linearEaseIn);

		screenStage = SCREEN_WAIT;
	}
	else if (SCREEN_WAIT == screenStage)
	{
		backgroundColor.startFadeAnimation(0, 60, EasingEquations::linearEaseIn);
		screenStage = SCREEN_CHANGE_SCREEN;
	}
	else if (SCREEN_CHANGE_SCREEN == screenStage)
	{
//#ifdef _MSC_VER
//		const int32_t delayTime = 1000000000;
//		for (uint32_t i = 0; i < delayTime; i++) {}
//#elif __ICCARM__
//		TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
//		vTaskDelay(xDelay);
//#endif
		getApplication().gotoScanScreenFromIntroScreen();
	}
}

void IntroView::imageFadeAnimationEndedHandler(const FadeAnimator<Image>& source)
{
	if (SCREEN_WAIT == screenStage) {
		logo.startFadeAnimation(255, 120, EasingEquations::linearEaseIn);
		screenStage = SCREEN_REVEAL;
	}
	else if (SCREEN_REVEAL == screenStage) {
//#ifdef _MSC_VER
//		const int32_t delayTime = 1000000000;
//		for (uint32_t i = 0; i < delayTime; i++) {}
//#elif __ICCARM__
//		TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
//		vTaskDelay(xDelay);
//#endif
		logo.startFadeAnimation(0, 15, EasingEquations::linearEaseIn);

		screenStage = SCREEN_LEAVE;
	}
	else if (SCREEN_LEAVE == screenStage) {
		backgroundColor.setFadeAnimationEndedAction(boxFadeAnimationEndedCallback);
		backgroundColor.startFadeAnimation(0, 15, EasingEquations::linearEaseIn);

		screenStage = SCREEN_WAIT;
		//screenStage = SCREEN_CHANGE_SCREEN;
	}
}

void IntroView::handleTickEvent()
{

}

