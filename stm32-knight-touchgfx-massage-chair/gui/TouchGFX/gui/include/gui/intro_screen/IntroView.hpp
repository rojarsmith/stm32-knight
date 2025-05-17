#ifndef INTROVIEW_HPP
#define INTROVIEW_HPP

#include <gui_generated/intro_screen/IntroViewBase.hpp>
#include <gui/intro_screen/IntroPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class IntroView : public IntroViewBase
{
public:
    IntroView();
    virtual ~IntroView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
	virtual void afterTransition();
	virtual void handleTickEvent();
protected:
	FrontendApplication& getApplication() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
	enum ScreenStage
	{
		SCREEN_REVEAL,
		SCREEN_WAIT,
		SCREEN_LEAVE,
		SCREEN_CHANGE_SCREEN
	} screenStage;

	uint32_t screenwidthreal = 0;
	Box backgroundColor2;
	FadeAnimator<Box> backgroundColor;
	FadeAnimator<Image> logo;

	Callback<IntroView, const FadeAnimator<Box>& >boxFadeAnimationEndedCallback;
	void boxFadeAnimationEndedHandler(const FadeAnimator<Box>& source);

	Callback<IntroView, const FadeAnimator<Image>& >imageFadeAnimationEndedCallback;
	void imageFadeAnimationEndedHandler(const FadeAnimator<Image>& source);
};

#endif // INTROVIEW_HPP
