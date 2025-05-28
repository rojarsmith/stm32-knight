#include <gui/mainmenucarousel_screen/MainMenuCarouselView.hpp>
#include <BitmapDatabase.hpp>

MainMenuCarouselView::MainMenuCarouselView() :
    currentState_(NO_STATE),
    carouselAnimationEnded_(this, &MainMenuCarouselView::carouselAnimationEndedhandler),
    dragDistance_(0),
    dragInsideCarousel_(false),
    dragInsideCenterButton_(false),
    hasAnimatedDrag_(false),
    first_time_(true)
{    
}

void MainMenuCarouselView::setupScreen()
{
    MainMenuCarouselViewBase::setupScreen();  

    ms_ = presenter->getMachineStatus();

    setupCarousel();
    add(carousel_);    
}

void MainMenuCarouselView::tearDownScreen()
{
    MainMenuCarouselViewBase::tearDownScreen();
}

void MainMenuCarouselView::handleTickEvent()
{
    if (first_time_)
    {
        first_time_ = false;
        static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();
    }

    //if (ms_->eve != nullptr && 1 == *ms_->eve)
    //{
    //    if (2 == ms_->op4)
    //    {      
    //        setSelectedDemoScreen(demoIDs_[carousel_.getSelectedElementIndex()]);
    //        gotoSelectedDemoScreen();
    //    }
    //    *ms_->eve = 0;
    //}

    //if (ms_->eve != nullptr && 2 == *ms_->eve)
    //{
    //    if (ms_->op4 == 1) // Up
    //    {
    //    }
    //    else if (ms_->op4 == 2) //Down
    //    {
    //    }
    //    else if (ms_->op4 == 3) //Left
    //    {
    //        static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();
    //        carousel_.selectedNext();
    //        
    //    }
    //    else if (ms_->op4 == 4) //Right
    //    {
    //        static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();
    //        carousel_.selectedPrevious();
    //    }

    //    *ms_->eve = 0;
    //}
}

void MainMenuCarouselView::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        dragDistance_ = 0;
        hasAnimatedDrag_ = false;
        dragInsideCarousel_ = carousel_.getAbsoluteRect().intersect(evt.getX(), evt.getY());
        dragInsideCenterButton_ = Rect(carousel_.getX() + ((carousel_.getWidth() - 150) / 2), carousel_.getY() + ((carousel_.getHeight() - 150) / 2), 150, 150).intersect(evt.getX(), evt.getY());
    }
    else if (evt.getType() == ClickEvent::RELEASED)
    {
        if (dragInsideCarousel_ && !hasAnimatedDrag_)
        {
            if (dragInsideCenterButton_)
            {
                currentState_ = ELEMENT_SELECTED;
                pauses_ = 4;
                carousel_.highlightSelectedElement();
            }
            else if (evt.getX() < carousel_.getX() + carousel_.getWidth() / 2)
            {
                carousel_.selectedPrevious();
            }
            else
            {
                carousel_.selectedNext();
            }
        }
    }
    View::handleClickEvent(evt);
}

void MainMenuCarouselView::handleDragEvent(const DragEvent& evt)
{
    View::handleDragEvent(evt);

    if (dragInsideCarousel_)
    {
        dragDistance_ += evt.getDeltaX();

        if (abs(dragDistance_) > 30)
        {
            dragDistance_ = 0;
            hasAnimatedDrag_ = true;
            if (abs(evt.getDeltaX()) > 0)
            {
                if (evt.getDeltaX() < 0)
                {
                    carousel_.selectedNext();
                }
                else
                {
                    carousel_.selectedPrevious();
                }
            }
        }
    }
}

void MainMenuCarouselView::setupCarousel()
{
    carousel_.setPosition(172, 172, 450, 180);
    carousel_.setCarouselAnimationEndedCallback(carouselAnimationEnded_);

    // The y position difference between the images
    uint16_t y_diff = 4;

    uint16_t widthOfSmallElements = Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_SMALL_ID).getWidth();
    uint16_t widthOfMediumElements = Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_MEDIUM_ID).getWidth();
    uint16_t widthOfLargeElements = Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_LARGE_ID).getWidth();
    uint16_t widthOfInvisibleElements = widthOfSmallElements - 30;

    uint16_t heightOfSmallElements = Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_SMALL_ID).getHeight();
    uint16_t heightOfMediumElements = Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_MEDIUM_ID).getHeight();
    uint16_t heightOfLargeElements = Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_LARGE_ID).getHeight();
    uint16_t heightOfInvisibleElements = heightOfSmallElements - 30;

    uint16_t offsetWidthForInvisibleEndElements = 20;
    uint16_t visibleWidthOfSmallElements = 50;
    uint16_t visibleWidthOfMediumElements = 80;

    carousel_.setPositionOfCarouselElement(0, 0, 
        (3 * y_diff), widthOfInvisibleElements, heightOfInvisibleElements);
    carousel_.setPositionOfCarouselElement(1, offsetWidthForInvisibleEndElements,
        (2 * y_diff), widthOfSmallElements, heightOfSmallElements);

    carousel_.setPositionOfCarouselElement(2, carousel_.getXPositionOfVisibleElement(1) + visibleWidthOfSmallElements,
        y_diff + 4, widthOfMediumElements, heightOfMediumElements);

    carousel_.setPositionOfCarouselElement(3, carousel_.getXPositionOfVisibleElement(2) + visibleWidthOfMediumElements,
        0, widthOfLargeElements, heightOfLargeElements);

    carousel_.setPositionOfCarouselElement(4, carousel_.getXPositionOfVisibleElement(3) + widthOfLargeElements - widthOfMediumElements + visibleWidthOfMediumElements,
        y_diff + 4, widthOfMediumElements, heightOfMediumElements);

    carousel_.setPositionOfCarouselElement(5, carousel_.getXPositionOfVisibleElement(4) + widthOfMediumElements - widthOfSmallElements + visibleWidthOfSmallElements,
        (2 * y_diff), widthOfSmallElements, heightOfSmallElements);

    carousel_.setPositionOfCarouselElement(6, carousel_.getXPositionOfVisibleElement(5) + offsetWidthForInvisibleEndElements + 20,
        (3 * y_diff), widthOfInvisibleElements, heightOfInvisibleElements);

    carousel_.addElement(Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_SMALL_ID), Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_MEDIUM_ID), Bitmap(BITMAP_CAROUSEL_MENU_ICONS_GAME_2D_LARGE_ID));
    carousel_.addElement(Bitmap(BITMAP_CAROUSEL_MENU_ICONS_SCORE_SMALL_ID), Bitmap(BITMAP_CAROUSEL_MENU_ICONS_SCORE_MEDIUM_ID), Bitmap(BITMAP_CAROUSEL_MENU_ICONS_SCORE_LARGE_ID));
    carousel_.addElement(Bitmap(BITMAP_CAROUSEL_MENU_ICONS_ABOUT_SMALL_ID), Bitmap(BITMAP_CAROUSEL_MENU_ICONS_ABOUT_MEDIUM_ID), Bitmap(BITMAP_CAROUSEL_MENU_ICONS_ABOUT_LARGE_ID));

    demoIDs_[0] = Defines::GAME2D;
    headlines_[0] = T_CAROUSEL_GAME_2D_HEADLINE;

    demoIDs_[1] = Defines::SCORE;
    headlines_[1] = T_CAROUSEL_SCORE_HEADLINE;

    demoIDs_[2] = Defines::ABOUT;    
    headlines_[2] = T_CAROUSEL_ABOUT_HEADLINE;

    // Set the carousel to the element that was selected last
    for (int i = 0; i < Defines::NUMBER_OF_DEMO_SCREENS; i++)
    {
        // Map demoId to position in carousel
        if (demoIDs_[i] == presenter->getSelectedDemoScreen())
        {
            carousel_.setSelectedElement(i);
        }
    }

    carousel_.setDuration(14);

}

void MainMenuCarouselView::carouselAnimationEndedhandler(const Carousel& c)
{
    if (currentState_ == ELEMENT_SELECTED)
    {
        if (pauses_-- > 0)
        {
            // Pauses implemented by just re initiating some highlight requests
            carousel_.highlightSelectedElement();
        }
        else
        {
            setSelectedDemoScreen(demoIDs_[carousel_.getSelectedElementIndex()]);
            gotoSelectedDemoScreen();
        }
    }
    else
    {        
        // Carousel moved to previous or next element
        updateDemoText();
    }
}

void MainMenuCarouselView::updateDemoText()
{
    textAreaCarouselTitle.setTypedText(TypedText(headlines_[carousel_.getSelectedElementIndex()]));
    textAreaCarouselTitle.invalidate();
}

void MainMenuCarouselView::screenSaverMinorTick()
{
    carousel_.selectedPrevious();
}

void MainMenuCarouselView::gestureTick(int eve, int op4)
{
    if (1 == eve)
    {
        if (2 == op4)
        {
            setSelectedDemoScreen(demoIDs_[carousel_.getSelectedElementIndex()]);
            gotoSelectedDemoScreen();
        }        
        return;
    }

    if (2 == eve)
    {
        if (op4 == 1) // Up
        {
        }
        else if (op4 == 2) //Down
        {
        }
        else if (op4 == 3) //Left
        {
            static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();
            carousel_.selectedNext();

        }
        else if (ms_->op4 == 4) //Right
        {
            static_cast<FrontendApplication*>(Application::getInstance())->resetScreenSaver();
            carousel_.selectedPrevious();
        } 
        return;
    }
}

void MainMenuCarouselView::setSelectedDemoScreen(Defines::DemoID demoId)
{
    selectedDemoScreen_ = demoId;
}

void MainMenuCarouselView::gotoSelectedDemoScreen()
{
    presenter->setSelectedDemoScreen(selectedDemoScreen_);

    switch (selectedDemoScreen_)
    {
    case Defines::GAME2D:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoGame2DScreenNoTransition();
        break;
    case Defines::SCORE:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoScoreScreenNoTransition();
        break;
    case Defines::ABOUT:
        static_cast<FrontendApplication*>(Application::getInstance())->gotoAboutScreenNoTransition();
        break;    
    case Defines::NUMBER_OF_DEMO_SCREENS:
    case Defines::NO_DEMO_SCREEN:
    default:
        break;
    }
}