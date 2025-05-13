#include <gui/fan_screen/FanView.hpp>
#include <gui/fan_screen/FanPresenter.hpp>

FanPresenter::FanPresenter(FanView& v)
    : view(v)
{

}

void FanPresenter::activate()
{
    setFan(0);
}

void FanPresenter::deactivate()
{
    setFan(0);
}

void FanPresenter::gotoMainScreenFromFanScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenFromCurrentScreen();
}

void FanPresenter::setFan(uint8_t fan)
{
    if (fan != model->getdata(Model::MODE_FAN, 1))
    {
        model->setdata(Model::MODE_FAN, 1, fan);
        model->senddata(Model::MODE_FAN);
    }
}
