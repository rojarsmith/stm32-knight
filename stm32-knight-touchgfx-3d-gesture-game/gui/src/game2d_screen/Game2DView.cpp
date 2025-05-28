#include <gui/game2d_screen/Game2DView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/Utils.hpp>

Game2DView::Game2DView() :
    buttonClickedCallback(this, &Game2DView::buttonClicked),
    popup_button_callback_(this, &Game2DView::popupButtonHandler)
{
    gameIsRunning = false;
    deathTickCounter = DEATH_COUNTER_DELAY + 1;

    // Demo supports two widths
    active_screen_width_ = (HAL::DISPLAY_WIDTH == 640) ? 640 : 800;
}

void Game2DView::setupScreen()
{
    Game2DViewBase::setupScreen();

    ms_ = presenter->getMachineStatus();
    gameStatusPopup.setMachineStatus(ms_);

    for (int i = 0; i < NUMBER_OF_LIVES; i++)
    {
        int lifeIndicatorWidth = (3 * Bitmap(BITMAP_GAME2D_LIFE_HEAD_ID).getWidth()) + (2 * (50 - Bitmap(BITMAP_GAME2D_LIFE_HEAD_ID).getWidth()));

        lifeIndicator[i].setBitmap(Bitmap(BITMAP_GAME2D_LIFE_HEAD_ID));
        lifeIndicator[i].setXY((active_screen_width_ - lifeIndicatorWidth) / 2 + (i * 50) - 186 - 130, 60);
        add(lifeIndicator[i]);
    }

    gameProgressIndicator.setBackground(Bitmap(BITMAP_GAME2D_SLIDER_BACKGROUND_ID));
    gameProgressIndicator.setXY(16, 8);
    gameProgressIndicator.setProgressIndicatorPosition(44, 11, Bitmap(BITMAP_GAME2D_PROGRESS_BAR_ID).getWidth(), Bitmap(BITMAP_GAME2D_PROGRESS_BAR_ID).getHeight());
    gameProgressIndicator.setRange(0, 100);
    gameProgressIndicator.setBitmap(BITMAP_GAME2D_PROGRESS_BAR_ID);
    gameProgressIndicator.setDirection(AbstractDirectionProgress::RIGHT);
    gameProgressIndicator.setAnchorAtZero(true);
    add(gameProgressIndicator);

    groundLevelY = 480 - 79 ;

    ninja.setGroundPosition(groundLevelY);

    arrow.setState(Arrow::STOPPED);

    // Insert elements at the correct Z-order
    // (they are already inserted in the base class)
    remove(ninja);
    remove(arrow);
    remove(ground);
    remove(imageLogo);
    add(ninja);
    add(arrow);
    add(ground);
    add(imageLogo);

    jumpButton.setBitmaps(Bitmap(BITMAP_GAME2D_JUMP_BUTTON_ID), Bitmap(BITMAP_GAME2D_JUMP_BUTTON_PRESSED_ID));
    jumpButton.setXY(0, 480 - jumpButton.getHeight());
    jumpButton.setAction(buttonClickedCallback);
    add(jumpButton);

    slideButton.setBitmaps(Bitmap(BITMAP_GAME2D_SLIDE_BUTTON_ID), Bitmap(BITMAP_GAME2D_SLIDE_BUTTON_PRESSED_ID));
    slideButton.setXY(active_screen_width_ - slideButton.getWidth(), 480 - slideButton.getHeight());
    slideButton.setAction(buttonClickedCallback);
    add(slideButton);

    gameStatusPopup.setButtonCallback(popup_button_callback_);
    add(gameStatusPopup);

    gotoEndOfGameStatePhase2();
    gameStatusPopup.setPosition(0, 0, 800, 480);
    gameStatusPopup.setupWelcome();

    HAL::getInstance()->setFrameRateCompensation(true);
}

void Game2DView::tearDownScreen()
{
    Game2DViewBase::tearDownScreen();
}

void Game2DView::handleTickEvent()
{
    tick_counter_++;

 /*   if (ms_->eve != nullptr && 1 == *ms_->eve)
    {
        if (1 == ms_->op4)
        {
            tick_counter_ = 0;
            ninja.setState(Ninja::JUMP);
            *ms_->eve = 0;
            return;
        }
        else if (2 == ms_->op4)
        {
            tick_counter_ = 0;
            ninja.setState(Ninja::SLIDE);
            *ms_->eve = 0;
            return;
        }
    }*/

    animateBackground();    

    if (gameIsRunning)
    {
        setupEnemies();
        collisionDetection();
        respawnNinja();

        updateGameStatus();
    }
    else
    {
        deathTickCounter++;
        if (deathTickCounter == DEATH_COUNTER_DELAY)
        {
            gotoEndOfGameStatePhase2();
        }
    }
}

void Game2DView::ReturnToMain()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainMenuCarouselScreenNoTransition();
}

void Game2DView::animateBackground()
{    
    if (0 == (tick_counter_ % 11)) 
    {
        ground.setOffset(ground.getXOffset() + 8, 0);
        ground.invalidate();
    }
    
    //if (0 == (tick_counter_ % 19))
    //{
    //    backgroundLayer02.setOffset(backgroundLayer02.getXOffset() + 3, 0);
    //    backgroundLayer02.invalidate();
    //}
    //else if (0 == (tick_counter_ % 29))
    //{
    //    backgroundLayer03.setOffset(backgroundLayer03.getXOffset() + 3, 0);
    //    backgroundLayer03.invalidate();
    //}
    //else if (0 == (tick_counter_ % 37))
    //{
    //    backgroundLayer04.setOffset(backgroundLayer04.getXOffset() + 3, 0);
    //    backgroundLayer04.invalidate();
    //}
    //else if (0 == (tick_counter_ % 47))
    //{
    //    backgroundLayer05.setOffset(backgroundLayer05.getXOffset() + 2, 0);
    //    backgroundLayer05.invalidate();
    //}
    //else if (0 == (tick_counter_ % 67))
    //{
    //    backgroundLayer06.setOffset(backgroundLayer06.getXOffset() + 2, 0);
    //    backgroundLayer06.invalidate();
    //}
    //else if (0 == (tick_counter_ % 89))
    //{
    //    backgroundLayer06.setOffset(backgroundLayer06.getXOffset() + 2, 0);
    //    backgroundLayer06.invalidate();
    //}
    //else if (0 == (tick_counter_ % 101))
    //{
    //    backgroundLayer07.setOffset(backgroundLayer07.getXOffset() + 1, 0);
    //    backgroundLayer07.invalidate();
    //}
    //else if (0 == (tick_counter_ % 131 ))
    //{
    //    backgroundLayer08.setOffset(backgroundLayer08.getXOffset() + 1, 0);
    //    backgroundLayer08.invalidate();
    //}
}

void Game2DView::setupEnemies()
{
    if (arrow.getRect().right() < 0)
    {
        arrow.reset();
        arrow.setState(Arrow::STOPPED);
    }

    if (ninja.getState() == Ninja::DEAD)
    {
        return;
    }

    if (arrow.getState() == Arrow::STOPPED)
    {
        int randomNumber = Utils::randomNumberBetween(0, 100);
        if (10 < randomNumber && randomNumber < 20)
        {
            arrow.setStartY(350);
            arrow.setState(Arrow::MOVING);
        }
        else if (0 < randomNumber && randomNumber <= 10)
        {
            arrow.setStartY(380);
            arrow.setState(Arrow::MOVING);
        }
    }
}

void Game2DView::respawnNinja()
{
    if (ninja.getState() == Ninja::DEAD)
    {
        respawnCounter++;
        if (respawnCounter > 200 &&
            arrow.getX() > 700)
        {
            ninja.setState(Ninja::ENTERING_GAME);
        }
    }
}

void Game2DView::buttonClicked(const AbstractButton& source)
{
    tick_counter_ = 0;

    if (&source == &jumpButton)
    {
        ninja.setState(Ninja::JUMP);
    }
    else if (&source == &slideButton)
    {
        ninja.setState(Ninja::SLIDE);
    }
}

void Game2DView::collisionDetection()
{
    if (ninja.getState() != Ninja::DEAD &&
        arrow.getAttackArea().intersect(ninja.getBodyArea()))
    {
        killNinja();
        arrow.setState(Arrow::HIT_TARGET);
    }
}

void Game2DView::popupButtonHandler(const GameStatusPopup::ReturnState source)
{
    switch (source)
    {
    case GameStatusPopup::GOTO_MENU:
        ReturnToMain();
        break;
    case GameStatusPopup::GOTO_PLAY:
        gotoStartOfGameState();
        break;
    default:
        break;
    }
}

void Game2DView::gotoStartOfGameState()
{
        gameIsRunning = true;

        Application::getInstance()->unregisterTimerWidget(&gameStatusPopup);
        gameStatusPopup.hide();
        gameProgressCounter = 0;
        gameProgressPercentage = 0;
        lives = NUMBER_OF_LIVES;
        updateLiveIndicator();

        showGameElements(true);

        ninja.reset();
        arrow.reset();
}

void Game2DView::gotoEndOfGameStatePhase1()
{
    gameIsRunning = false;
    deathTickCounter = 0;
}

void Game2DView::gotoEndOfGameStatePhase2()
{
    gameIsRunning = false;
    showGameElements(false);

    ms_->score[2] = ms_->score[1];
    ms_->score[1] = ms_->score[0];
    if (lives != 0)
    {
        ms_->score[0] = 100;
        gameStatusPopup.setupGameWon();
    }
    else
    {
        ms_->score[0] = gameProgressPercentage;
        gameStatusPopup.setupGameLost(gameProgressPercentage);
    }
    
    gameStatusPopup.show();
    Application::getInstance()->registerTimerWidget(&gameStatusPopup);
}

void Game2DView::showGameElements(bool visible)
{
    ninja.setVisible(visible);
    arrow.setVisible(visible);

    ninja.invalidate();
    arrow.invalidate();
}

void Game2DView::killNinja()
{
    ninja.setState(Ninja::DEAD);
    respawnCounter = 1;
    lives--;

    updateLiveIndicator();
}

void Game2DView::updateLiveIndicator()
{
    for (int i = 0; i < lives; i++)
    {
        lifeIndicator[i].setBitmap(Bitmap(BITMAP_GAME2D_LIFE_HEAD_ID));
        lifeIndicator[i].invalidate();
    }
    for (int i = MAX(lives, 0); i < NUMBER_OF_LIVES; i++)
    {
        lifeIndicator[i].setBitmap(Bitmap(BITMAP_GAME2D_LIFE_HEAD_OFF_ID));
        lifeIndicator[i].invalidate();
    }
}

void Game2DView::updateGameStatus()
{
    if (ninja.getState() != Ninja::DEAD)
    {
        gameProgressCounter += 8;
    }

    gameProgressPercentage = gameProgressCounter / GAME_PROGRESS_SPEED;
    if (gameProgressIndicator.getValue() != gameProgressPercentage)
    {
        gameProgressIndicator.setValue(gameProgressPercentage);
        gameProgressIndicator.invalidate();
    }

    if (gameProgressPercentage == 100)
    {
        gotoEndOfGameStatePhase2();
    }

    if (lives == 0)
    {
        gotoEndOfGameStatePhase1();
    }
}

void Game2DView::gestureTick(int eve, int op4)
{
    if (1 == eve)
    {
        if (!gameStatusPopup.isVisible()) 
        {
            if (1 == op4)
            {
                tick_counter_ = 0;
                ninja.setState(Ninja::JUMP);
                return;
            }
            else if (2 == op4)
            {
                tick_counter_ = 0;
                ninja.setState(Ninja::SLIDE);
                return;
            }
        }
        else
        {
            if (1 == op4)
            {
                ReturnToMain();
            }
            else if (2 == op4)
            {
                gotoStartOfGameState();
            }
        }
    }
}