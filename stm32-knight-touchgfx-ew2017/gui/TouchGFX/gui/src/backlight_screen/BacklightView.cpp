#include <gui/backlight_screen/BacklightView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

BacklightView::BacklightView()
	:
#ifndef SIMULATOR
	  screenwidthreal(getScreenWidthReal()),
#else
	  screenwidthreal(HAL::DISPLAY_WIDTH),
#endif
	  funcState(INIT),
	  titleAnimationCounter(0),
	  titleAnimationState(NO_ANIMATION),
	  middleFiledAnimationState(MF_ANIMATE_NO),
	  sliderValueCatch(0),
	  sliderValueCatchL2(0),
	  brightnessValueFilterCounter(0),
	  brightnessValueTextAnimationCounter(0),
	  brightnessValueTextAnimationState(BRI_ANIMATE_TEXT_NO),
	  foreground1Step(0),
	  fadeAnimationEndedCallback(this, &BacklightView::fadeAnimationEndedCallbackHandler),
	  moveAnimationEndedCallback(this, &BacklightView::moveAnimationEndedCallbackHandler),
	  zoomAnimationEndedCallback(this, &BacklightView::zoomAnimationEndedHandler),
	  buttonClickedCallback(this, &BacklightView::buttonClickedCallbackHandler),
	  newValueCallback(this, &BacklightView::newValueCallbackHandler)
{
}

void BacklightView::setupScreen()
{
	BacklightViewBase::setupScreen();

	backgroundColor.setPosition(0, 0, 800, 480);
	/*backgroundColor.setPosition(0, 0, 480, 272);*/
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

	backgroundFAni1.setBitmap(Bitmap(BITMAP_BG1_ID));
	backgroundFAni1.setAlpha(0);

	foregroundHome.setBitmaps(Bitmap(BITMAP_BTN_HOME2_RELEASED_ID), Bitmap(BITMAP_BTN_HOME2_PRESSED_ID));
	foregroundHome.setXY(screenwidthreal, HAL::DISPLAY_HEIGHT);
	foregroundHome.setMoveAnimationEndedAction(moveAnimationEndedCallback);
	foregroundHome.setTouchable(false);

	titleY = -43;
	// titleY = -26;
	title.setTypedText(TypedText(T_BACKLIGHT_TITLE));
	title.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	title.setPosition(33, titleY, 266, 66);
	// title.setPosition(20, titleY, 160, 40);
	title.setAlpha(129);

	middleFiled.setBitmaps(Bitmap(BITMAP_MBG1_ID), Bitmap(BITMAP_MBG2_ID));
	middleFiled.setPosition(-static_cast<uint16_t>(screenwidthreal), HAL::DISPLAY_HEIGHT / 2, screenwidthreal, 1);
	middleFiled.setAlpha(33);
	middleFiled.setAnimationEndedCallback(zoomAnimationEndedCallback);
	middleFiled.startZoomAndMoveAnimation(0, HAL::DISPLAY_HEIGHT / 2, screenwidthreal, 1, 15);
	middleFiledAnimationState = MF_ANIMATE_ZOOMIN;

	// sliderX = 29;
	/*sliderX = -300;
	sliderY = 114;*/
	sliderX = -498;
	sliderY = 190;
	slider.setBitmaps(Bitmap(BITMAP_FAT_SLIDER_BACKGROUND_ID), Bitmap(BITMAP_FAT_SLIDER_FILLED_ID), Bitmap(BITMAP_FAT_SLIDER_KNOB_ID));
	slider.setXY(sliderX, sliderY);
	slider.setNewValueCallback(newValueCallback);
	slider.setupHorizontalSlider(0, 0, 13, 0, 391);
	/*slider.setupHorizontalSlider(0, 0, 8, 0, 236);*/
	slider.setValueRange(0, 100);
	// sliderValue = presenter->getpwm();
	sliderValue = 100;
	slider.setValue(sliderValue);
	slider.setTouchable(true);

	brightnessValueText.setWildcard(brightnessValueBuffer);
	brightnessValueText.setTypedText(TypedText(T_BACKLIGHT_VALUE));
	brightnessValueText.setColor(Color::getColorFromRGB(0, 176, 80));
	// updateBrightnessValue(sliderValue);
	brightnessValueText.invalidate();
	int16_t bvt = brightnessValueText.getHeight();
	// int16_t bvtd2 = bvt / 2;
	// brightnessValueTextX = 340;
	brightnessValueTextX = screenwidthreal;
	/*int16_t brightnessValueTextY = 91;*/
	/*int16_t brightnessValueTextY = 161;*/
	int16_t brightnessValueTextY = (HAL::DISPLAY_HEIGHT / 2) - bvt + 5;
	/*brightnessValueText.setPosition(brightnessValueTextX, brightnessValueTextY, 110, 70);*/
	brightnessValueText.setPosition(brightnessValueTextX, brightnessValueTextY, 182, bvt);

	add(backgroundColor);
	add(backgroundFAni1);
	add(middleFiled);
	add(slider);
	add(brightnessValueText);
	add(foregroundHome);
	add(title);
}

void BacklightView::tearDownScreen()
{
	BacklightViewBase::tearDownScreen();
}

void BacklightView::afterTransition()
{
	backgroundFAni1.setFadeAnimationEndedAction(fadeAnimationEndedCallback);
	backgroundFAni1.startFadeAnimation(255, 30, EasingEquations::linearEaseIn);

	int foregroundHomeAnimationDuration = 28;
	foregroundHome.startMoveAnimation(screenwidthreal - Bitmap(BITMAP_BTN_HOME2_RELEASED_ID).getWidth() / 2, HAL::DISPLAY_HEIGHT - Bitmap(BITMAP_BTN_HOME2_RELEASED_ID).getHeight() / 2, foregroundHomeAnimationDuration, EasingEquations::cubicEaseOut);
	foregroundHome.setAction(buttonClickedCallback);

	setTitleAnimationState(ANIMATE_TEXT_IN);
}

void BacklightView::handleTickEvent()
{
	if (ANIMATE_TEXT_OUT == titleAnimationState)
	{
		titleAnimateTextOut();
	}
	else if (ANIMATE_TEXT_IN == titleAnimationState)
	{
		titleAnimateTextIn();
	}

	if (BRI_ANIMATE_TEXT_IN == brightnessValueTextAnimationState)
	{
		brightnessValueTextAnimateTextIn();
	}
	else if (BRI_ANIMATE_TEXT_OUT == brightnessValueTextAnimationState)
	{
		brightnessValueTextAnimateTextOut();
	}

	if (sliderValueCatchL2 == sliderValueCatch)
	{
		brightnessValueFilterCounter++;
	}

	if (brightnessValueFilterCounter >= 30)
	{
		brightnessValueFilterCounter = 0;
		updateBrightnessValue(sliderValueCatchL2);
	}

	sliderValueCatchL2 = sliderValueCatch;
}

void BacklightView::titleAnimateTextIn()
{
	uint16_t duration = 30;

	if (titleAnimationCounter <= duration)
	{
		// uint16_t delta = EasingEquations::cubicEaseOut(titleAnimationCounter, 0, 40, duration);
		uint16_t delta = EasingEquations::cubicEaseOut(titleAnimationCounter, 0, 66, duration); // 800x480
		title.moveTo(title.getX(), titleY + delta);
	}
	else
	{
		setTitleAnimationState(NO_ANIMATION);
		titleY = title.getY();
		return;
	}
	titleAnimationCounter++;
}

void BacklightView::titleAnimateTextOut()
{
	uint16_t duration = 30;

	if (titleAnimationCounter <= duration)
	{
		uint16_t delta = EasingEquations::cubicEaseOut(titleAnimationCounter, 0, 66, duration);
		// uint16_t delta = EasingEquations::cubicEaseOut(titleAnimationCounter, 0, 40, duration);
		title.moveTo(title.getX(), titleY - delta);
	}
	else
	{
		setTitleAnimationState(NO_ANIMATION);
		return;
	}
	titleAnimationCounter++;
}

void BacklightView::setTitleAnimationState(TitleAnimationState newState)
{
	titleAnimationCounter = 0;
	titleAnimationState = newState;
}

void BacklightView::brightnessValueTextAnimateTextIn()
{
	int16_t duration = 15;

	if (brightnessValueTextAnimationCounter <= duration)
	{
		int16_t delta = EasingEquations::cubicEaseOut(brightnessValueTextAnimationCounter, 0, 212, duration);
		/*int16_t delta = EasingEquations::cubicEaseOut(brightnessValueTextAnimationCounter, 0, 140, duration);*/
		brightnessValueText.moveTo(brightnessValueTextX - delta, brightnessValueText.getY());
	}
	else
	{
		setbrightnessValueTextAnimationState(BRI_ANIMATE_TEXT_NO);
		brightnessValueTextX = brightnessValueText.getX();
		return;
	}
	brightnessValueTextAnimationCounter++;
}

void BacklightView::brightnessValueTextAnimateTextOut()
{
	int16_t duration = 10;

	if (brightnessValueTextAnimationCounter <= duration)
	{
		int16_t delta = EasingEquations::cubicEaseOut(brightnessValueTextAnimationCounter, 0, 232, duration);
		// int16_t delta = EasingEquations::cubicEaseOut(brightnessValueTextAnimationCounter, 0, 140, duration);
		brightnessValueText.moveTo(brightnessValueTextX + delta, brightnessValueText.getY());
	}
	else
	{
		setbrightnessValueTextAnimationState(BRI_ANIMATE_TEXT_NO);
		return;
	}
	brightnessValueTextAnimationCounter++;
}

void BacklightView::setbrightnessValueTextAnimationState(BrightnessValueTextAnimationState newState)
{
	brightnessValueTextAnimationCounter = 0;
	brightnessValueTextAnimationState = newState;
}

void BacklightView::fadeAnimationEndedCallbackHandler(const FadeAnimator<Image> &source)
{
	if (EXIT == funcState)
	{
		presenter->gotoMainScreenFromBacklightScreen();
	}
}

void BacklightView::moveAnimationEndedCallbackHandler(const MoveAnimator<Button> &source)
{
	if (&foregroundHome == &source)
	{
		if (foreground1Step == 0)
		{
			foregroundHome.setTouchable(true);
			// int animationDuration = 28;
			// foregroundHome.startMoveAnimation(0, 0, animationDuration, EasingEquations::elasticEaseOut);
			foreground1Step++;
		}
	}
}

void BacklightView::zoomAnimationEndedHandler(const ZoomAnimationImage &source)
{
	if (&middleFiled == &source)
	{
		if (MF_ANIMATE_ZOOMIN == middleFiledAnimationState)
		{
			middleFiled.startZoomAndMoveAnimation(0, 92, screenwidthreal, 265, 24);
			/*middleFiled.startZoomAndMoveAnimation(0, 56, screenwidthreal, 160, 15);*/

			middleFiledAnimationState = MF_ANIMATE_ZOOMIN_END;
		}
		else if (MF_ANIMATE_OUT == middleFiledAnimationState)
		{
			middleFiled.startZoomAndMoveAnimation(-static_cast<uint16_t>(screenwidthreal), HAL::DISPLAY_HEIGHT / 2, screenwidthreal, 1, 15);
			middleFiledAnimationState = MF_ANIMATE_NO;
		}
		else if (MF_ANIMATE_ZOOMIN_END == middleFiledAnimationState)
		{
			slider.invalidate();

			int sliderAnimationDuration = 15;
			sliderX = 48;
			/*sliderX = 29;*/
			slider.startMoveAnimation(sliderX, sliderY, sliderAnimationDuration, EasingEquations::cubicEaseOut);

			setbrightnessValueTextAnimationState(BRI_ANIMATE_TEXT_IN);
		}
	}
}

void BacklightView::buttonClickedCallbackHandler(const AbstractButton &source)
{
	if (&source == &foregroundHome)
	{
		int foregroundHomeAnimationDuration = 28;
		foregroundHome.startMoveAnimation(screenwidthreal, HAL::DISPLAY_HEIGHT, foregroundHomeAnimationDuration, EasingEquations::cubicEaseOut);

		setTitleAnimationState(ANIMATE_TEXT_OUT);
		middleFiled.startZoomAndMoveAnimation(0, HAL::DISPLAY_HEIGHT / 2, screenwidthreal, 1, 15);
		middleFiledAnimationState = MF_ANIMATE_OUT;

		backgroundFAni1.startFadeAnimation(0, 30, EasingEquations::linearEaseIn);

		int sliderAnimationDuration = 15;
		sliderX = -498;
		/*sliderX = -300;*/
		slider.startMoveAnimation(sliderX, sliderY, sliderAnimationDuration, EasingEquations::cubicEaseOut);

		setbrightnessValueTextAnimationState(BRI_ANIMATE_TEXT_OUT);

		funcState = EXIT;
	}
}

void BacklightView::newValueCallbackHandler(const Slider &slider, int value)
{
	if (&slider == &this->slider)
	{
		sliderValue = value;

		if (sliderValue == sliderValueCatch)
		{
			return;
		}

		sliderValueCatch = value;
		Unicode::snprintf(brightnessValueBuffer, 5, "%d", value);
		brightnessValueText.invalidate();
		// updateBrightnessValue(value);
	}
}

void BacklightView::updateBrightnessValue(int brightness)
{
	Unicode::snprintf(brightnessValueBuffer, 5, "%d", brightness);
	brightnessValueText.invalidate();
	presenter->setBL(brightness);
}
