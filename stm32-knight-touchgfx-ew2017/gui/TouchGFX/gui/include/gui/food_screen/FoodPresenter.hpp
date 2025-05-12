#ifndef FOODPRESENTER_HPP
#define FOODPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class FoodView;

class FoodPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    FoodPresenter(FoodView& v);

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

    virtual ~FoodPresenter() {}

    /**
     * Slide Transition : Go to main screen.
     */
    void gotoMainScreenFromFoodScreen();

    void printList(uint8_t* ptr);
    void printer_status(uint8_t printer_status);
private:
    FoodPresenter();

    FoodView& view;
};

#endif // FOODPRESENTER_HPP
