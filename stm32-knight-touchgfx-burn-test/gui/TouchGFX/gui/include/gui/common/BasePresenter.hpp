#ifndef BASE_PRESENTER_HPP
#define BASE_PRESENTER_HPP

#include <mvp/Presenter.hpp>
#include <gui/common/BaseViewInterface.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/model/ModelListener.hpp>

using namespace touchgfx;

class BasePresenter : public Presenter, public ModelListener
{
public:
    BasePresenter(BaseViewInterface& view);

    void backOptionSelected();
    void mcuLoadSelected();
    virtual void mcuLoadUpdated(uint8_t mcuLoad);

    void viewStartupDone();
private:
    BaseViewInterface& viewInterface;

    void showProcessorLoad();
};

#endif
