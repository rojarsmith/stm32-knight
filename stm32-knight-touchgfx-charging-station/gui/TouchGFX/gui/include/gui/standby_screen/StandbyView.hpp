#ifndef STANDBYVIEW_HPP
#define STANDBYVIEW_HPP

#include <gui_generated/standby_screen/StandbyViewBase.hpp>
#include <gui/standby_screen/StandbyPresenter.hpp>

class StandbyView : public StandbyViewBase
{
public:
    StandbyView();
    virtual ~StandbyView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // STANDBYVIEW_HPP
