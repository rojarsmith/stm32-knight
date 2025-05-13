#ifndef BACKLIGHTVIEW_HPP
#define BACKLIGHTVIEW_HPP

#include <gui_generated/backlight_screen/BacklightViewBase.hpp>
#include <gui/backlight_screen/BacklightPresenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>

class BacklightView : public BacklightViewBase
{
public:
    BacklightView();
    virtual ~BacklightView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void afterTransition();
    virtual void handleTickEvent();

	uint32_t screenwidthreal = 0;
protected:
	FrontendApplication& application() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
	enum FuncState
	{
		INIT,
		EXIT
	} funcState;

	TextArea title;
	int16_t titleY;
	uint16_t titleAnimationCounter;
	enum TitleAnimationState
	{
		ANIMATE_TEXT_OUT,
		ANIMATE_TEXT_IN,
		NO_ANIMATION
	} titleAnimationState;
	void titleAnimateTextOut();
	void titleAnimateTextIn();
	void setTitleAnimationState(TitleAnimationState newState);

	ZoomAnimationImage middleFiled;
	enum MiddleFiledAnimationState
	{
		MF_ANIMATE_ZOOMIN,
		MF_ANIMATE_ZOOMIN_END,
		MF_ANIMATE_OUT,
		MF_ANIMATE_NO,
	} middleFiledAnimationState;

	MoveAnimator<Slider> slider;
	int16_t sliderX;
	int16_t sliderY;
	int sliderValue, sliderValueCatch;

	int16_t brightnessValueTextX;
	TextAreaWithOneWildcard brightnessValueText;
	Unicode::UnicodeChar brightnessValueBuffer[5];
	uint16_t brightnessValueTextAnimationCounter;
	enum BrightnessValueTextAnimationState
	{
		BRI_ANIMATE_TEXT_OUT,
		BRI_ANIMATE_TEXT_IN,
		BRI_ANIMATE_TEXT_NO
	} brightnessValueTextAnimationState;
	void brightnessValueTextAnimateTextIn();
	void brightnessValueTextAnimateTextOut();
	void setbrightnessValueTextAnimationState(BrightnessValueTextAnimationState newState);
	void updateBrightnessValue(int brightness);

	uint16_t foreground1Step;
	Box backgroundColor;

	MoveAnimator<Button> foregroundHome;

	FadeAnimator<Image> backgroundFAni1;
	FadeAnimator<Image> backgroundFAni2;

	Callback<BacklightView, const FadeAnimator<Image>& >fadeAnimationEndedCallback;
	void fadeAnimationEndedCallbackHandler(const FadeAnimator<Image>& source);

	Callback<BacklightView, const MoveAnimator<Button>& >moveAnimationEndedCallback;
	void moveAnimationEndedCallbackHandler(const MoveAnimator<Button>& source);

	Callback<BacklightView, const ZoomAnimationImage&> zoomAnimationEndedCallback;
	void zoomAnimationEndedHandler(const ZoomAnimationImage& image);

	Callback<BacklightView, const AbstractButton&> buttonClickedCallback;
	void buttonClickedCallbackHandler(const AbstractButton& source);

	Callback<BacklightView, const Slider&, int> newValueCallback;
	void newValueCallbackHandler(const Slider& slider, int value);
};

#endif // BACKLIGHTVIEW_HPP
