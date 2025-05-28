#ifndef ABOUTVIEW_HPP
#define ABOUTVIEW_HPP

#include <gui_generated/about_screen/AboutViewBase.hpp>
#include <gui/about_screen/AboutPresenter.hpp>
#include <gui/model/ModelSchema.hpp>

class AboutView : public AboutViewBase
{
public:
    AboutView();
    virtual ~AboutView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    virtual void gestureTick(int eve, int op4);
    virtual void ReturnToMain();
protected:
private:
    MachineStatus* ms_;
};

#endif // ABOUTVIEW_HPP
