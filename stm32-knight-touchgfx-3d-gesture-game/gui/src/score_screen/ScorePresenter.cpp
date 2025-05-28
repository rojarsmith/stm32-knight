#include <gui/score_screen/ScoreView.hpp>
#include <gui/score_screen/ScorePresenter.hpp>

ScorePresenter::ScorePresenter(ScoreView& v)
    : view(v)
{
}

void ScorePresenter::activate()
{

}

void ScorePresenter::deactivate()
{

}

void ScorePresenter::gestureTick(int eve, int op4)
{
    view.gestureTick(eve, op4);
}

MachineStatus* ScorePresenter::getMachineStatus()
{
    return model->getMachineStatus();
}