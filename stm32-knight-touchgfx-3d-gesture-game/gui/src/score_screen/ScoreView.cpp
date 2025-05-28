#include <gui/score_screen/ScoreView.hpp>
#include <algorithm>

ScoreView::ScoreView()
{

}

void ScoreView::setupScreen()
{
    ScoreViewBase::setupScreen();

    ms_ = presenter->getMachineStatus();

    int n = sizeof(ms_->score) / sizeof(ms_->score[0]);
    std::sort(std::begin(ms_->score), std::end(ms_->score), std::greater<int>());

    Unicode::snprintf(percentageTextBuffer, BUFFER_SIZE, "%d", ms_->score[0]);
    textAreaS1.setWildcard(percentageTextBuffer);
    textAreaS1.invalidate();

    Unicode::snprintf(percentageTextBuffer1, BUFFER_SIZE, "%d", ms_->score[1]);
    textAreaS2.setWildcard(percentageTextBuffer1);
    textAreaS2.invalidate();

    Unicode::snprintf(percentageTextBuffer2, BUFFER_SIZE, "%d", ms_->score[2]);
    textAreaS3.setWildcard(percentageTextBuffer2);
    textAreaS3.invalidate();
}

void ScoreView::tearDownScreen()
{
    ScoreViewBase::tearDownScreen();
}

void ScoreView::handleTickEvent()
{
    //if (ms_->eve != nullptr && 1 == *ms_->eve)
    //{
    //    if (1 == ms_->op4)
    //    {
    //        ReturnToMain();
    //    }
    //    *ms_->eve = 0;
    //}
}

void ScoreView::gestureTick(int eve, int op4)
{
    if (1 == eve)
    {
        if (1 == op4)
        {
            ReturnToMain();
        }
        return;
    }
}

void ScoreView::ReturnToMain()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuCarouselScreenNoTransition();
}
