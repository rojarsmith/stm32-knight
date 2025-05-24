#ifndef CONNECTPRESENTER_HPP
#define CONNECTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/BasePresenter.hpp>

using namespace touchgfx;

class ConnectView;

class ConnectPresenter : public BasePresenter
{
public:
    ConnectPresenter(ConnectView& v);

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

    virtual ~ConnectPresenter() {}

private:
    ConnectPresenter();

    ConnectView& view;
};

#endif // CONNECTPRESENTER_HPP
