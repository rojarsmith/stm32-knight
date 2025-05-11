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
    virtual void afterTransition();
    virtual void tearDownScreen();
protected:
    Box backgroundColor;
    FadeAnimator<Image> embeddedLogo;

    Callback<IntroView, const FadeAnimator<Image>& >fadeAnimationEndedCallback;
    void embeddedLogoFadedHandler(const FadeAnimator<Image>& source);
};

#endif // INTROVIEW_HPP
