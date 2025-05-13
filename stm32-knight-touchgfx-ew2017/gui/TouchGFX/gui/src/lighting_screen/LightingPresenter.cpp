#include <gui/lighting_screen/LightingView.hpp>
#include <gui/lighting_screen/LightingPresenter.hpp>
#include <gui/model/Model.hpp>

LightingPresenter::LightingPresenter(LightingView& v)
    : view(v)
{
    setLED(168, 203, 228);
}

void LightingPresenter::activate()
{
    setLED(0, 0, 0);
}

void LightingPresenter::deactivate()
{

}

void LightingPresenter::gotoMainScreenFromLightingScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenFromCurrentScreen();
}

void LightingPresenter::setLED(uint8_t LED_R, uint8_t LED_G, uint8_t LED_B)
{
    model->setdata(Model::MODE_LED, 1, LED_R);
    model->setdata(Model::MODE_LED, 2, LED_G);
    model->setdata(Model::MODE_LED, 3, LED_B);
    model->senddata(Model::MODE_LED);
}
