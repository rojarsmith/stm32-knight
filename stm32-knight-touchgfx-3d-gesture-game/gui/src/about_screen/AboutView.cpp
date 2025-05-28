#include <gui/about_screen/AboutView.hpp>

AboutView::AboutView()
{

}

void AboutView::setupScreen()
{
    AboutViewBase::setupScreen();

    ms_ = presenter->getMachineStatus();
}

void AboutView::tearDownScreen()
{
    AboutViewBase::tearDownScreen();
}

void AboutView::handleTickEvent()
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

void AboutView::gestureTick(int eve, int op4)
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

void AboutView::ReturnToMain()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuCarouselScreenNoTransition();
}