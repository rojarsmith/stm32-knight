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

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }

    void gotoScanScreenFromIntroScreen();
    void gotoMainScreenFromScanScreen();
private:
    Callback<FrontendApplication> transitionCallback;
    void gotoScanScreenFromIntroScreenImpl();
    void gotoMainScreenFromScanScreenImpl();
};

#endif // FRONTENDAPPLICATION_HPP
