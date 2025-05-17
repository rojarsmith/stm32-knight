#include <gui/scan_screen/ScanView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

ScanView::ScanView() :
	frameTick(0),
	aniManState(ANIMAN_NONE),
	aniManStateCach(ANIMAN_NONE),
	scanningDotRe(false),
	textAreaFadeAnimationEndedCallback(this, &ScanView::textAreaFadeAnimationEndedHandler),
	aniManCurrent(0),
	aniManInventory(0),
	aniManInventoryCach(0),
	aniManCurrentAlpha(0),
	aniManTargetAlpha(0),
	aniManCurrentScale(0),
	aniManTargetScale(0),
	aniManMoveInventory(0),
	aniManMoveInventoryCach(0),
	aniManMov(false),
	sleepTicks(0),
#ifndef SIMULATOR
	screenwidthreal(getScreenWidthReal())
#else
	screenwidthreal(HAL::DISPLAY_WIDTH)
#endif
{

}

void ScanView::setupScreen()
{
    ScanViewBase::setupScreen();

	backgroundColor.setPosition(0, 0, screenwidthreal, HAL::DISPLAY_HEIGHT);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

	add(backgroundColor);


	aniMan.setBitmap(Bitmap(BITMAP_ANI1_01_ID));
	//int aniManBeginX = (HAL::DISPLAY_WIDTH / 2) - (Bitmap(BITMAP_ANI1_01_ID).getWidth() / 2);
	//int aniManBeginY = (HAL::DISPLAY_HEIGHT / 2) - (Bitmap(BITMAP_ANI1_01_ID).getHeight() / 2);

	aniMan.setXY(0, 0);
	aniMan.setWidth(screenwidthreal);
	aniMan.setHeight(HAL::DISPLAY_HEIGHT);
	//aniMan.setCameraDistance(300.0f);
	aniMan.setBitmapPosition(screenwidthreal / 2 - Bitmap(BITMAP_ANI1_01_ID).getWidth() / 2, HAL::DISPLAY_HEIGHT / 2 - Bitmap(BITMAP_ANI1_01_ID).getHeight() / 2);
	aniMan.setOrigo(aniMan.getBitmapPositionX() + aniMan.getBitmap().getWidth() / 2, aniMan.getBitmapPositionY() + aniMan.getBitmap().getHeight() / 2, aniMan.getCameraDistance());
	aniMan.setScale(0.1f);
	aniMan.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);
	aniMan.setWidth(screenwidthreal);
	aniMan.setHeight(HAL::DISPLAY_HEIGHT);
	aniMan.setAlpha(255);
	add(aniMan);
	aniMan.invalidate();


	int scanningTitleX = 30;
	int16_t brightnessValueTextY = 30;
	scanningTitle.setPosition(scanningTitleX, brightnessValueTextY, 310, 70);
	scanningTitle.setTypedText(TypedText(T_SCAN_TITLE));
	scanningTitle.setColor(Color::getColorFromRGB(0, 176, 80));
	scanningTitle.setAlpha(0);
	add(scanningTitle);

	for (int i = 0; i <= 2; i++)
	{
		int scanningDotX = scanningTitleX + 275 + i * 30;
		int16_t brightnessValueDotY = brightnessValueTextY;
		scanningDot[i].setPosition(scanningDotX, brightnessValueDotY, 310, 70);
		scanningDot[i].setTypedText(TypedText(T_SCAN_DOT));
		scanningDot[i].setColor(Color::getColorFromRGB(0, 176, 80));
		scanningDot[i].setAlpha(0);
		scanningDot[i].setFadeAnimationEndedAction(textAreaFadeAnimationEndedCallback);
		add(scanningDot[i]);
	}


	indicator.setWidth(100);
	indicator.setHeight(100);
	indicator.setXY(100, 100);
	add(indicator);


	indicator2.setWidth(100);
	indicator2.setHeight(100);
	indicator2.setXY(100, 100);
	add(indicator2);
}

void ScanView::tearDownScreen()
{
    ScanViewBase::tearDownScreen();
}

void ScanView::afterTransition()
{
	int scanningTitleAnimationDuration = 30;
	scanningTitle.setFadeAnimationEndedAction(textAreaFadeAnimationEndedCallback);
	scanningTitle.startFadeAnimation(255, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);

	scanningDot[0].startFadeAnimation(255, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);

	startAniMan(-15, 4, 255, 1.0, ANIMAN_2);
}

void ScanView::handleTickEvent()
{
	int scanningTitleAnimationDuration = 15;
	int diff = 0;
	switch (aniManState)
	{
	case ANIMAN_2:
		setSleepTick(60, ANIMAN_3);
		break;
	case ANIMAN_3:
		diff = Bitmap(BITMAP_ANI1_10_ID).getId() - aniMan.getBitmap().getId();
		startAniMan(diff, 2, 255, 1.5f, ANIMAN_4);

		break;
	case ANIMAN_4:
		indicator.setWidth(100);
		indicator.setHeight(100);
		indicator.setXY(350, 150);
		indicator.start(15, 1, 2);
		indicator2.setWidth(100);
		indicator2.setHeight(100);
		indicator2.setXY(500, 150);
		indicator2.start(15, 1, 2);
		setSleepTick(60, ANIMAN_5);
		break;
	case ANIMAN_5:
		diff = Bitmap(BITMAP_ANI1_07_ID).getId() - aniMan.getBitmap().getId();
		startAniMan(diff, 2, 255, 1.8f, ANIMAN_6);
		break;
	case ANIMAN_6:
		indicator.setWidth(200);
		indicator.setHeight(200);
		indicator.setXY(220, 150);
		indicator.start(15, 1, 2);
		setSleepTick(60, ANIMAN_7);
		aniManMov = true;
		break;
	case ANIMAN_7:
		diff = Bitmap(BITMAP_ANI1_01_ID).getId() - aniMan.getBitmap().getId();
		startAniMan(diff, 2, 255, 1.0f, ANIMAN_9);


		scanningTitle.startFadeAnimation(0, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
		scanningDot[0].startFadeAnimation(0, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
		scanningDot[1].startFadeAnimation(0, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
		scanningDot[2].startFadeAnimation(0, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
		break;
	case ANIMAN_8:
		//setMoveAniMan(60, ANIMAN_9);
		//setSleepTick(60, ANIMAN_9);
		break;
	case ANIMAN_9:
		getApplication().gotoMainScreenFromScanScreen();
		break;
	default:
		break;
	}

	renderAniMan(frameTick);
	sleepTick();
	moveAniMan(frameTick);

	frameTick++;
}

void ScanView::textAreaFadeAnimationEndedHandler(const FadeAnimator<TextArea>& source)
{
	int scanningTitleAnimationDuration = 30;

	if (&source == &scanningDot[0] && false == scanningDotRe)
	{
		scanningDot[1].startFadeAnimation(255, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
	}
	else if (&source == &scanningDot[1] && false == scanningDotRe)
	{
		scanningDot[2].startFadeAnimation(255, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
	}
	else if (&source == &scanningDot[2] && false == scanningDotRe)
	{
		scanningDotRe = true;
		scanningDot[0].startFadeAnimation(50, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
	}
	else if (&source == &scanningDot[0] && true == scanningDotRe)
	{
		scanningDot[1].startFadeAnimation(50, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
	}
	else if (&source == &scanningDot[1] && true == scanningDotRe)
	{
		scanningDot[2].startFadeAnimation(50, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
	}
	else if (&source == &scanningDot[2] && true == scanningDotRe)
	{
		scanningDotRe = false;
		scanningDot[0].startFadeAnimation(255, scanningTitleAnimationDuration, EasingEquations::linearEaseIn);
	}
}

void ScanView::startAniMan(const int inventory, const int frequency, const int alpha, const float scale, AniManStates next)
{
	aniManInventory = inventory;
	aniManInventoryCach = inventory;
	aniManFrequency = frequency;
	aniManCurrentAlpha = aniMan.getAlpha();
	aniManTargetAlpha = alpha;
	aniManCurrentScale = aniMan.getScale();
	aniManTargetScale = scale;
	aniManStateCach = next;
	aniManState = ANIMAN_RUNNING;
}

void ScanView::renderAniMan(const int tick)
{
	if (0 != tick % aniManFrequency)
	{
		return;
	}

	if (0 == aniManInventory)
	{
		return;
	}
	else if (aniManInventory > 0)
	{
		int idx = aniMan.getBitmap().getId() + 1;
		if (idx > Bitmap(BITMAP_ANI1_15_ID).getId())
		{
			idx = Bitmap(BITMAP_ANI1_01_ID).getId();
		}
		aniMan.setBitmap(Bitmap(idx));
		aniMan.setWidth(HAL::DISPLAY_WIDTH);
		aniMan.setHeight(HAL::DISPLAY_HEIGHT);
		aniMan.setAlpha(aniManTargetAlpha - (aniManTargetAlpha - aniManCurrentAlpha) / aniManInventoryCach * aniManInventory);
		aniMan.setScale(aniManTargetScale - (aniManTargetScale - aniManCurrentScale) / aniManInventoryCach * aniManInventory);
		aniMan.invalidate();
		aniManInventory--;

		if (0 == aniManInventory)
		{
			aniManState = aniManStateCach;
		}
	}
	else if (aniManInventory < 0)
	{
		int idx = aniMan.getBitmap().getId() - 1;
		if (idx < Bitmap(BITMAP_ANI1_01_ID).getId())
		{
			idx = Bitmap(BITMAP_ANI1_15_ID).getId();
		}
		aniMan.setBitmap(Bitmap(idx));
		aniMan.setWidth(HAL::DISPLAY_WIDTH);
		aniMan.setHeight(HAL::DISPLAY_HEIGHT);
		aniMan.setAlpha(aniManTargetAlpha - (aniManTargetAlpha - aniManCurrentAlpha) / aniManInventoryCach * aniManInventory);
		aniMan.setScale(aniManTargetScale - (aniManTargetScale - aniManCurrentScale) / aniManInventoryCach * aniManInventory);

		if (aniManMov) //Special hard code.
		{
			int dx = 237 - (237 - (int)aniMan.getBitmapPositionX()) / aniManInventoryCach * aniManInventory;
			int dy = 51 - (51 - (int)aniMan.getBitmapPositionY()) / aniManInventoryCach * aniManInventory;

			aniMan.setBitmapPosition(dx, dy);
		}

		aniMan.invalidate();
		aniManInventory++;

		if (0 == aniManInventory)
		{
			aniManState = aniManStateCach;
		}
	}
}

void ScanView::setSleepTick(const int inventory, AniManStates next)
{
	sleepTicks = inventory;
	aniManStateCach = next;
	aniManState = ANIMAN_RUNNING;
}

void ScanView::sleepTick()
{
	if (0 == sleepTicks)
	{
		return;
	}

	sleepTicks--;

	if (0 == sleepTicks)
	{
		aniManState = aniManStateCach;
	}
}

void ScanView::setMoveAniMan(const int inventory, AniManStates next)
{
	aniManMoveInventory = inventory;
	aniManMoveInventoryCach = inventory;
	aniManStateCach = next;
	aniManState = ANIMAN_RUNNING;
}
void ScanView::moveAniMan(const int tick)
{
	if (0 == aniManMoveInventory)
	{
		return;
	}

	//int dx = 237 - ( 237 - (int)aniMan.getBitmapPositionX() ) / aniManMoveInventoryCach * aniManMoveInventory;
	//int dy = 51 - (51 - (int)aniMan.getBitmapPositionY()) / aniManMoveInventoryCach * aniManMoveInventory;
	aniMan.setBitmapPosition(237, 51);
	aniMan.invalidate();
	aniManMoveInventory--;

	if (0 == aniManMoveInventory)
	{
		aniManState = aniManStateCach;
	}
}
