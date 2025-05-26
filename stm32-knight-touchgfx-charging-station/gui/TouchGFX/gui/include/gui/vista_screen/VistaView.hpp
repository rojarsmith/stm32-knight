#ifndef VISTAVIEW_HPP
#define VISTAVIEW_HPP

#include <gui_generated/vista_screen/VistaViewBase.hpp>
#include <gui/vista_screen/VistaPresenter.hpp>

class VistaView : public VistaViewBase
{
public:
    VistaView();
    virtual ~VistaView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // VISTAVIEW_HPP
