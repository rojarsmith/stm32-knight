#ifndef STANDBYPRESENTER_HPP
#define STANDBYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class StandbyView;

class StandbyPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    StandbyPresenter(StandbyView& v);

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

    virtual ~StandbyPresenter() {}

private:
    StandbyPresenter();

    StandbyView& view;
};

#endif // STANDBYPRESENTER_HPP
