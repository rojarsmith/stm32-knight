#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/intro_screen/IntroView.hpp>
#include <gui/scan_screen/ScanView.hpp>

using namespace touchgfx;

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : 
	FrontendApplicationBase(m, heap),
	transitionCallback()
{

}

void FrontendApplication::gotoScanScreenFromIntroScreen()
{
	transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoScanScreenFromIntroScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoScanScreenFromIntroScreenImpl()
{
	makeTransition< ScanView, ScanPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreenFromScanScreen()
{
	transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenFromScanScreenImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenFromScanScreenImpl()
{
	makeTransition< MainView, MainPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
