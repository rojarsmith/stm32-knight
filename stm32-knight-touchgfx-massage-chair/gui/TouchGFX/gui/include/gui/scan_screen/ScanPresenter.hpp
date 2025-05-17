#ifndef SCANPRESENTER_HPP
#define SCANPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScanView;

class ScanPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScanPresenter(ScanView& v);

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

    virtual ~ScanPresenter() {}

private:
    ScanPresenter();

    ScanView& view;
};

#endif // SCANPRESENTER_HPP
