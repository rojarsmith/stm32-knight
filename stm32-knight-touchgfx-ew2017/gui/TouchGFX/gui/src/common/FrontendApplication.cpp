#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <touchgfx/transitions/Transition.hpp>
#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

using namespace touchgfx;

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap),
	transitionCallback()
{

}

/**
 * SlideTransition<EAST>
 * @note : main screen to XX screen.
 */
void FrontendApplication::gotoMainScreenFromCurrentScreen()
{
	transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenFromCurrentScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenFromCurrentScreenImpl()
{
	makeTransition< MainView, MainPresenter, SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
