#include <gui/backlight_screen/BacklightView.hpp>
#include <gui/backlight_screen/BacklightPresenter.hpp>
#include <gui/common/FrontendApplication.hpp>

BacklightPresenter::BacklightPresenter(BacklightView& v)
    : view(v)
{

}

void BacklightPresenter::activate()
{
    //    uint8_t pp=model->getdata(Model::MODE_PWM, 1);
//    model->setdata(Model::MODE_PWM, 1, pp);
    model->senddata(Model::MODE_PWM);
}

void BacklightPresenter::deactivate()
{

}

void BacklightPresenter::setBL(uint8_t pwm)
{
    model->setdata(Model::MODE_PWM, 1, pwm);
    model->senddata(Model::MODE_PWM);
}
uint8_t BacklightPresenter::getpwm()
{
    return model->getdata(Model::MODE_PWM, 1);
}
/**
 * Slide Transition : Go to XX screen.
 */
void BacklightPresenter::gotoMainScreenFromBacklightScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenFromCurrentScreen();
}
