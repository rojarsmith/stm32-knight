#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{

}

void MainPresenter::activate()
{

}

void MainPresenter::deactivate()
{

}

/**
 * Slide Transition : Go to XX screen.
 */
void MainPresenter::gotoMusicScreenFromMainScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMusicScreenFromMainScreen();
}

void MainPresenter::gotoFoodScreenFromMainScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoFoodScreenFromMainScreen();
}
