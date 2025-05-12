#include <gui/food_screen/FoodView.hpp>
#include <gui/food_screen/FoodPresenter.hpp>
#include <gui/common/FrontendApplication.hpp>

FoodPresenter::FoodPresenter(FoodView& v)
    : view(v)
{

}

void FoodPresenter::activate()
{

}

void FoodPresenter::deactivate()
{

}

void FoodPresenter::gotoMainScreenFromFoodScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenFromCurrentScreen();
}

void FoodPresenter::printList(uint8_t* ptr)
{
    uint8_t value = 0;
    (void)value;

    for (uint8_t index = 1; index < 10; index++)
    {
        value = *(ptr + index - 1);
    }
}

void FoodPresenter::printer_status(uint8_t printer_status)
{
    if (printer_status == 1)
    {
        view.printCheck = true;
    }
}
