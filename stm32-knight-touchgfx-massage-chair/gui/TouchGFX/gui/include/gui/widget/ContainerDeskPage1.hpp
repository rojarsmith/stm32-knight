#ifndef CONTAINER_DESK_PAGE_1_HPP
#define CONTAINER_DESK_PAGE_1_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/widget/ContainerDeskPageBase.hpp>

using namespace touchgfx;

class ContainerDeskPage1 : public ContainerDeskPageBase
{
public:
	ContainerDeskPage1();
	virtual ~ContainerDeskPage1();

	virtual void handleTickEvent();

	void end();

protected:

private:
	enum FlashStage
	{
		FLASH_BEGIN,
		FLASH_WAIT,
		FLASH_REVERT,
		FLASH_NONE
	} flashStage;

	enum StepStage
	{	
		STEP_0,
		STEP_0_WAIT,
		STEP_1,
		STEP_1_WAIT,
		STEP_2,
		STEP_2_WAIT,
		STEP_3,
		STEP_3_WAIT,
		STEP_4,
		STEP_4_WAIT,
		STEP_5,
		STEP_5_WAIT,
		STEP_6,
		STEP_6_WAIT,
		STEP_7,
		STEP_NONE
	} StepStage;

	const static int button_block_begin_x = 60;
	const static int button_block_begin_y = 60;
	const static int button_block_begin_x_spacing = 45;
	const static int button_block_begin_y_spacing = 80;
	const static int button_block_label_y_spacing = 1;
	const static int step_wait_time = 120;
	const static int step_begin_height = 175;
	const static int step_block_height = 130;

	int wait_time;

	Button buttonRelex;
	Button buttonWholeBody;
	Button buttonWaist;
	Button buttonStretch;
	Button buttonExMode;
	const AbstractButton* buttonIdx;
	TextArea buttonRelexLabel;
	TextArea buttonWholeBodyLabel;
	TextArea buttonWaistLabel;
	TextArea buttonStretchLabel;
	TextArea buttonExModeLabel;
	Image stepIdx;
	Image backgroundStep;
	Image blockShadow;
	FadeAnimator<Box> indicatorLight;
	MoveAnimator<Image> stepAni;
	Box backgroundColor;
	
	void flashButton(int x, int y);
	void stopFlashButton();
	void pauseFlashButton();	
	void showStepAnimaion(const AbstractButton& source);
	void showStepAnimaionAction2(const AbstractButton& source);
	void stopStepAnimaion();

	void buttonClickedHandler(const AbstractButton& source);
	Callback<ContainerDeskPage1, const AbstractButton&> buttonClickedCallback;

	Callback<ContainerDeskPage1, const MoveAnimator<Image>&> imageMoveAnimationEndedCallback;
	void imageMoveAnimationEndedHandler(const MoveAnimator<Image>& source);

	Callback<ContainerDeskPage1, const FadeAnimator<Box>&> boxFadeAnimationEndedCallback;
	void boxFadeAnimationEndedHandler(const FadeAnimator<Box>& source);
};

#endif /* CONTAINER_DESK_PAGE_1_HPP */
