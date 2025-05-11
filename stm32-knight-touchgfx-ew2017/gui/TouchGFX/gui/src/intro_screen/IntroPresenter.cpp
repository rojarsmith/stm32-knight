#include <gui/intro_screen/IntroView.hpp>
#include <gui/intro_screen/IntroPresenter.hpp>

IntroPresenter::IntroPresenter(IntroView& v)
    : view(v)
{

}

void IntroPresenter::activate()
{

}

void IntroPresenter::deactivate()
{

}

/**
 * Slide Transition : Go to XX screen.
 */
void IntroPresenter::GoToMainScreenFromIntroScreen()
{
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenFromCurrentScreen();
}
