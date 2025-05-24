#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

	void gotoScreen(int id);

	typedef void(FrontendApplication::*GotoScreen)();
	GotoScreen gotoScreens_[9];

    void gotoIntro();
	void gotoHome();
    void gotoPayment();
    void gotoConnect();

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }

	void gotoIntroImpl();
	void gotoHomeImpl();
    void gotoPaymentImpl();
    void gotoConnectImpl();
private:
    Callback<FrontendApplication> transitionCallback;
};

#endif // FRONTENDAPPLICATION_HPP
