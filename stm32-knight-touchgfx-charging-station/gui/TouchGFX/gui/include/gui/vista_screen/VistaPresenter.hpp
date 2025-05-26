#ifndef VISTAPRESENTER_HPP
#define VISTAPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class VistaView;

class VistaPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    VistaPresenter(VistaView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~VistaPresenter() {}

private:
    VistaPresenter();

    VistaView& view;
};

#endif // VISTAPRESENTER_HPP
