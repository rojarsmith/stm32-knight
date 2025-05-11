#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
	FrontendApplication(Model& m, FrontendHeap& heap);
	virtual ~FrontendApplication() {}

	virtual void handleTickEvent()
	{
		model.tick();
		FrontendApplicationBase::handleTickEvent();
	}

	/**
	 * SlideTransition<EAST>
	 * @note : main screen to XX screen.
	 */
	void gotoMainScreenFromCurrentScreen();
private:
	Callback<FrontendApplication> transitionCallback;

	/**
	 * SlideTransition<EAST>
	 * @note : main screen to XX screen.
	 */
	void gotoMainScreenFromCurrentScreenImpl();
};

#endif // FRONTENDAPPLICATION_HPP
