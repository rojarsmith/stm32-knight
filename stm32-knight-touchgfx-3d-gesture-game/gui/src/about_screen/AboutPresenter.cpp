#include <gui/about_screen/AboutView.hpp>
#include <gui/about_screen/AboutPresenter.hpp>

AboutPresenter::AboutPresenter(AboutView& v)
    : view(v)
{
}

void AboutPresenter::activate()
{

}

void AboutPresenter::deactivate()
{

}

void AboutPresenter::gestureTick(int eve, int op4)
{
    view.gestureTick(eve, op4);
}

MachineStatus* AboutPresenter::getMachineStatus()
{
    return model->getMachineStatus();
}