#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>
#include <gui/widget/ContainerDeskPage1.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/hal/HAL.hpp>

ContainerDeskPage1::ContainerDeskPage1()
	:
	flashStage(FLASH_NONE),
	StepStage(STEP_NONE),
	wait_time(step_wait_time),
	buttonClickedCallback(this, &ContainerDeskPage1::buttonClickedHandler),
	imageMoveAnimationEndedCallback(this, &ContainerDeskPage1::imageMoveAnimationEndedHandler),
	boxFadeAnimationEndedCallback(this, &ContainerDeskPage1::boxFadeAnimationEndedHandler)
{
	backgroundColor.setPosition(0, 0, 700, 480);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, 148, 255)); //Blue

	add(backgroundColor);

	indicatorLight.setPosition(0, 0, 77, 77);
	indicatorLight.setColor(touchgfx::Color::getColorFromRGB(255, 216, 0)); //Blue
	indicatorLight.setVisible(false);
	indicatorLight.setFadeAnimationEndedAction(boxFadeAnimationEndedCallback);

	add(indicatorLight);

	int bax = button_block_begin_x;
	int bay = button_block_begin_y;

	buttonRelex.setBitmaps(Bitmap(BITMAP_ICON_RELEX02_120X120_ID), Bitmap(BITMAP_ICON_RELEX01_120X120_ID));
	buttonRelex.setXY(bax, bay);
	buttonRelex.setAction(buttonClickedCallback);
	buttonRelex.setVisible(true);

	buttonRelexLabel.setXY(bax + 30, bay + Bitmap(BITMAP_ICON_RELEX02_120X120_ID).getHeight() + button_block_label_y_spacing);
	buttonRelexLabel.setColor(Color::getColorFromRGB(255, 255, 255));
	buttonRelexLabel.setTypedText(TypedText(T_ICON_RELEX));

	add(buttonRelex);
	add(buttonRelexLabel);

	bax += Bitmap(BITMAP_ITEM1R_100X100_ID).getWidth() + button_block_begin_x_spacing;
	buttonWholeBody.setBitmaps(Bitmap(BITMAP_ICON_WHOLEBODY02_120X120_ID), Bitmap(BITMAP_ICON_WHOLEBODY01_120X120_ID));
	buttonWholeBody.setXY(bax, bay);
	buttonWholeBody.setAction(buttonClickedCallback);
	buttonWholeBody.setVisible(true);

	buttonWholeBodyLabel.setXY(bax + 33, bay + Bitmap(BITMAP_ICON_WHOLEBODY02_120X120_ID).getHeight() + button_block_label_y_spacing);
	buttonWholeBodyLabel.setColor(Color::getColorFromRGB(255, 255, 255));
	buttonWholeBodyLabel.setTypedText(TypedText(T_ICON_WHOLE_BODY));

	add(buttonWholeBody);
	add(buttonWholeBodyLabel);

	bax += Bitmap(BITMAP_ITEM1R_100X100_ID).getWidth() + button_block_begin_x_spacing;
	buttonWaist.setBitmaps(Bitmap(BITMAP_ICON_WAIST02_120X120_ID), Bitmap(BITMAP_ICON_WAIST01_120X120_ID));
	buttonWaist.setXY(bax, bay);
	buttonWaist.setAction(buttonClickedCallback);
	buttonWaist.setVisible(true);

	
	buttonWaistLabel.setXY(bax + 10, bay + Bitmap(BITMAP_ICON_WAIST02_120X120_ID).getHeight() + button_block_label_y_spacing);
	//buttonWaistLabel.setXY(bax + 33, bay + Bitmap(BITMAP_ICON_WAIST02_120X120_ID).getHeight() + button_block_label_y_spacing);
	buttonWaistLabel.setColor(Color::getColorFromRGB(255, 255, 255));
	buttonWaistLabel.setTypedText(TypedText(T_ICON_WAIST));
	buttonWaistLabel.setWidth(100);

	add(buttonWaist);
	add(buttonWaistLabel);

	bax = button_block_begin_x;
	bay += Bitmap(BITMAP_ITEM1R_100X100_ID).getHeight() + button_block_begin_y_spacing;
	buttonStretch.setBitmaps(Bitmap(BITMAP_ICON_STRETCH02_120X120_ID), Bitmap(BITMAP_ICON_STRETCH01_120X120_ID));
	buttonStretch.setXY(bax, bay);
	buttonStretch.setAction(buttonClickedCallback);
	buttonStretch.setVisible(true);

	buttonStretchLabel.setXY(bax + 23, bay + Bitmap(BITMAP_ICON_STRETCH02_120X120_ID).getHeight() + button_block_label_y_spacing);
	buttonStretchLabel.setColor(Color::getColorFromRGB(255, 255, 255));
	buttonStretchLabel.setTypedText(TypedText(T_ICON_STRETCH));

	add(buttonStretch);
	add(buttonStretchLabel);

	bax += Bitmap(BITMAP_ITEM1R_100X100_ID).getWidth() + button_block_begin_x_spacing;
	buttonExMode.setBitmaps(Bitmap(BITMAP_ICON_EXMODE02_120X120_ID), Bitmap(BITMAP_ICON_EXMODE01_120X120_ID));
	buttonExMode.setXY(bax, bay);
	buttonExMode.setAction(buttonClickedCallback);
	buttonExMode.setVisible(true);

	buttonExModeLabel.setXY(bax + 10, bay + Bitmap(BITMAP_ICON_EXMODE02_120X120_ID).getHeight() + button_block_label_y_spacing);
	//buttonExModeLabel.setXY(bax + 25, bay + Bitmap(BITMAP_ICON_EXMODE02_120X120_ID).getHeight() + button_block_label_y_spacing);
	buttonExModeLabel.setColor(Color::getColorFromRGB(255, 255, 255));
	buttonExModeLabel.setTypedText(TypedText(T_ICON_EXMODE));
	buttonExModeLabel.setWidth(100);

	add(buttonExMode);
	add(buttonExModeLabel);

	backgroundStep.setBitmap(Bitmap(BITMAP_STEP_BACKGROUND_10_130X480_ID));
	backgroundStep.setPosition(540, 0, 130, HAL::DISPLAY_HEIGHT);
	add(backgroundStep);

	stepAni.setPosition(540, HAL::DISPLAY_HEIGHT, 130, 910);
	add(stepAni);

	blockShadow.setBitmap(Bitmap(BITMAP_SHADOW_20_10X480_ID));
	blockShadow.setXY(540, 0);
	blockShadow.setAlpha(150);
	add(blockShadow);

	stepIdx.setBitmap(Bitmap(BITMAP_STEP_IDX_130X130_ID));
	//int dbg1 = HAL::DISPLAY_HEIGHT / 2 - Bitmap(BITMAP_STEP_IDX_130X130_ID).getHeight() / 2;
	stepIdx.setXY(540, HAL::DISPLAY_HEIGHT / 2 - Bitmap(BITMAP_STEP_IDX_130X130_ID).getHeight() / 2);
	stepIdx.setAlpha(150);
	add(stepIdx);


}

ContainerDeskPage1::~ContainerDeskPage1()
{
}

void ContainerDeskPage1::end()
{
	stopStepAnimaion();
	stopFlashButton();
	Application::getInstance()->unregisterTimerWidget(this);
}

void ContainerDeskPage1::buttonClickedHandler(const AbstractButton& source)
{
	Application::getInstance()->registerTimerWidget(this);

	if (&source == &buttonRelex)
	{
		stopFlashButton();
		flashButton(buttonRelex.getX() + 20, buttonRelex.getY() + 20);
	}
	else if (&source == &buttonWholeBody)
	{
		stopFlashButton();
		flashButton(buttonWholeBody.getX() + 20, buttonWholeBody.getY() + 20);
	}
	else if (&source == &buttonWaist)
	{
		stopFlashButton();
		flashButton(buttonWaist.getX() + 20, buttonWaist.getY() + 20);
	}
	else if (&source == &buttonStretch)
	{
		stopFlashButton();
		flashButton(buttonStretch.getX() + 20, buttonStretch.getY() + 20);
	}
	else if (&source == &buttonExMode)
	{
		stopFlashButton();
		flashButton(buttonExMode.getX() + 20, buttonExMode.getY() + 20);
	}

	showStepAnimaion(source);
}

void ContainerDeskPage1::flashButton(int x, int y)
{
	indicatorLight.setXY(x, y);
	indicatorLight.setAlpha(255);
	indicatorLight.setVisible(true);
	indicatorLight.setFadeAnimationEndedAction(boxFadeAnimationEndedCallback);
	indicatorLight.startFadeAnimation(50, 60, EasingEquations::linearEaseIn);
	flashStage = FLASH_BEGIN;
}

void ContainerDeskPage1::boxFadeAnimationEndedHandler(const FadeAnimator<Box>& source)
{
	if (FLASH_BEGIN == flashStage){
		indicatorLight.startFadeAnimation(255, 60, EasingEquations::linearEaseIn);
		flashStage = FLASH_WAIT;
	}
	else if (FLASH_WAIT == flashStage){
		indicatorLight.startFadeAnimation(255, 120, EasingEquations::linearEaseIn);
		flashStage = FLASH_REVERT;
	}
	else if (FLASH_REVERT == flashStage){
		indicatorLight.startFadeAnimation(50, 60, EasingEquations::linearEaseIn);
		flashStage = FLASH_BEGIN;
	}
}

void ContainerDeskPage1::stopFlashButton()
{
	flashStage = FLASH_NONE;
	indicatorLight.setVisible(false);
	indicatorLight.setFadeAnimationEndedAction(boxFadeAnimationEndedCallback);
	indicatorLight.invalidate();
}

void ContainerDeskPage1::pauseFlashButton()
{
	flashStage = FLASH_NONE;
	indicatorLight.setVisible(true);
	indicatorLight.setAlpha(255);
	indicatorLight.invalidate();
}

void ContainerDeskPage1::showStepAnimaion(const AbstractButton& source)
{
	buttonIdx = &source;
	stepAni.clearMoveAnimationEndedAction();
	stepAni.setMoveAnimationEndedAction(imageMoveAnimationEndedCallback);
	stepAni.startMoveAnimation(670, stepAni.getY(), 30, EasingEquations::linearEaseIn);
	StepStage = STEP_0;
}

void ContainerDeskPage1::showStepAnimaionAction2(const AbstractButton& source)
{
	if (&source == &buttonRelex)
	{
		stepAni.setBitmap(Bitmap(BITMAP_STEP_BACKGROUND_12_130X910_ID));
	}
	else if (&source == &buttonWholeBody)
	{
		stepAni.setBitmap(Bitmap(BITMAP_STEP_BACKGROUND_11_130X910_ID));
	}
	else if (&source == &buttonWaist)
	{
		stepAni.setBitmap(Bitmap(BITMAP_STEP_BACKGROUND_12_130X910_ID));
	}
	else if (&source == &buttonStretch)
	{
		stepAni.setBitmap(Bitmap(BITMAP_STEP_BACKGROUND_11_130X910_ID));
	}
	else if (&source == &buttonExMode)
	{
		stepAni.setBitmap(Bitmap(BITMAP_STEP_BACKGROUND_12_130X910_ID));
	}
	stepAni.setPosition(540, HAL::DISPLAY_HEIGHT, 130, 910);
	backgroundStep.invalidate();
//	stepAni.setMoveAnimationEndedAction(imageMoveAnimationEndedCallback);
	stepAni.startMoveAnimation(540, step_begin_height, 60, EasingEquations::linearEaseIn);
	StepStage = STEP_1;
}

void ContainerDeskPage1::stopStepAnimaion()
{
	stepAni.setPosition(540, HAL::DISPLAY_HEIGHT, 130, 910);
	stepAni.invalidate();
	StepStage = STEP_NONE;
}

void ContainerDeskPage1::imageMoveAnimationEndedHandler(const MoveAnimator<Image>& source)
{
	if (STEP_0 == StepStage)
	{
		StepStage = STEP_0_WAIT;
	}
	if (STEP_1 == StepStage)
	{
		StepStage = STEP_1_WAIT;
	}
	else if (STEP_2 == StepStage)
	{
		StepStage = STEP_2_WAIT;
	}
	else if (STEP_3 == StepStage)
	{
		StepStage = STEP_3_WAIT;
	}
	else if (STEP_4 == StepStage)
	{
		StepStage = STEP_4_WAIT;
	}
	else if (STEP_5 == StepStage)
	{
		StepStage = STEP_5_WAIT;
	}
	else if (STEP_6 == StepStage)
	{
		StepStage = STEP_6_WAIT;
	}	
	else if (STEP_7 == StepStage)
	{
		pauseFlashButton();
	}
}

void ContainerDeskPage1::handleTickEvent()
{
	if (STEP_0_WAIT == StepStage)
	{
		wait_time--;
		if (wait_time <= 0){
			wait_time = step_wait_time / 4;
			StepStage = STEP_1;
			showStepAnimaionAction2(*buttonIdx);
		}
	}
	if (STEP_1_WAIT == StepStage)
	{
		wait_time--;
		if (wait_time <= 0){
			wait_time = step_wait_time;
			StepStage = STEP_2;
			stepAni.startMoveAnimation(540, step_begin_height - step_block_height, 60, EasingEquations::linearEaseIn);
		}
	}
	else if (STEP_2_WAIT == StepStage)
	{
		wait_time--;
		if (wait_time <= 0){
			wait_time = step_wait_time;
			StepStage = STEP_3;
			stepAni.startMoveAnimation(540, step_begin_height - step_block_height * 2, 60, EasingEquations::linearEaseIn);
		}
	}
	else if (STEP_3_WAIT == StepStage)
	{
		wait_time--;
		if (wait_time <= 0){
			wait_time = step_wait_time;
			StepStage = STEP_4;
			stepAni.startMoveAnimation(540, step_begin_height - step_block_height * 3, 60, EasingEquations::linearEaseIn);
		}
	}
	else if (STEP_4_WAIT == StepStage)
	{
		wait_time--;
		if (wait_time <= 0){
			wait_time = step_wait_time;
			StepStage = STEP_5;
			stepAni.startMoveAnimation(540, step_begin_height - step_block_height * 4, 60, EasingEquations::linearEaseIn);
		}
	}
	else if (STEP_5_WAIT == StepStage)
	{
		wait_time--;
		if (wait_time <= 0){
			wait_time = step_wait_time;
			StepStage = STEP_6;
			stepAni.startMoveAnimation(540, step_begin_height - step_block_height * 5, 60, EasingEquations::linearEaseIn);
		}
	}
	else if (STEP_6_WAIT == StepStage)
	{
		wait_time--;
		if (wait_time <= 0){
			wait_time = step_wait_time;
			StepStage = STEP_7;
			stepAni.startMoveAnimation(540, step_begin_height - step_block_height * 6, 60, EasingEquations::linearEaseIn);
		}
	}	
}
