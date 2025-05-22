#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/intro_screen/IntroView.hpp>
#include <gui/intro_screen/IntroPresenter.hpp>
#include <gui/home_screen/HomeView.hpp>
#include <gui/home_screen/HomePresenter.hpp>
//#include <platform/driver/lcd/LCD16bpp.hpp>
#include <platform/driver/lcd/LCD24bpp.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{
	/*reinterpret_cast<touchgfx::LCD16bpp&>(touchgfx::HAL::lcd()).enableTextureMapperAll();*/
	reinterpret_cast<touchgfx::LCD24bpp&>(touchgfx::HAL::lcd()).enableTextureMapperAll();

	/*gotoScreens_[ScreenNumber::NULL_SCREEN] = &FrontendApplication::gotoBoot;
	gotoScreens_[ScreenNumber::SCREEN_BOOT] = &FrontendApplication::gotoBoot;
	gotoScreens_[ScreenNumber::SCREEN_STANDBY] = &FrontendApplication::gotoStandby;*/
	gotoScreens_[ScreenNumber::SCREEN_INTRO] = &FrontendApplication::gotoIntro;
	gotoScreens_[ScreenNumber::SCREEN_HOME] = &FrontendApplication::gotoHome;
	/*gotoScreens_[ScreenNumber::SCREEN_PAYMENT] = &FrontendApplication::gotoPayment;
	gotoScreens_[ScreenNumber::SCREEN_PAY_RFID] = &FrontendApplication::gotoVista;
	gotoScreens_[ScreenNumber::SCREEN_CONNECT] = &FrontendApplication::gotoConnect;
	gotoScreens_[ScreenNumber::SCREEN_SCREEN1] = &FrontendApplication::gotoScreen1;*/
}

void FrontendApplication::gotoScreen(int id)
{
	(this->*(gotoScreens_[id]))();
}

void FrontendApplication::gotoIntro()
{
	transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoIntroImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoIntroImpl()
{
	makeTransition<IntroView, IntroPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoHome()
{
	transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotoHomeImpl);
	pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoHomeImpl()
{
	makeTransition<HomeView, HomePresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
