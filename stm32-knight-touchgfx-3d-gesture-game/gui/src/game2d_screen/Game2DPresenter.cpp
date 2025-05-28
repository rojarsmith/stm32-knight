#include <gui/game2d_screen/Game2DView.hpp>
#include <gui/game2d_screen/Game2DPresenter.hpp>

Game2DPresenter::Game2DPresenter(Game2DView& v)
    : view(v)
{
}

void Game2DPresenter::activate()
{

}

void Game2DPresenter::deactivate()
{

}

void Game2DPresenter::gestureTick(int eve, int op4)
{
    view.gestureTick(eve, op4);
}

MachineStatus* Game2DPresenter::getMachineStatus()
{
    return model->getMachineStatus();
}