#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <touchgfx/transitions/Transition.hpp>
#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/food_screen/FoodView.hpp>
#include <gui/food_screen/FoodPresenter.hpp>

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

/**
 * SlideTransition<WEST>
 * @note : xx screen to main screen.
 */
void FrontendApplication::gotoMusicScreenFromMainScreen()
{
	transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoMusicScreenFromMainScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMusicScreenFromMainScreenImpl()
{
	makeTransition< MusicView, MusicPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoFoodScreenFromMainScreen()
{
	transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoFoodScreenFromMainScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoFoodScreenFromMainScreenImpl()
{
	makeTransition< FoodView, FoodPresenter, SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
