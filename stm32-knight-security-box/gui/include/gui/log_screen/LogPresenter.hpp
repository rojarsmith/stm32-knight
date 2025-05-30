#ifndef LOG_PRESENTER_HPP
#define LOG_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class LogView;

class LogPresenter : public Presenter, public ModelListener
{
public:
    LogPresenter(LogView& v);

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

    virtual ~LogPresenter() {};

private:
    LogPresenter();

    LogView& view;
};


#endif // LOG_PRESENTER_HPP
