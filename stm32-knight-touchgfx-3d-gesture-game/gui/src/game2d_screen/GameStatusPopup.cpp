#include <gui/game2d_screen/GameStatusPopup.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Application.hpp>

GameStatusPopup::GameStatusPopup() :
    buttonClickedCallback(this, &GameStatusPopup::buttonClicked),
    popupButtonCallback(0)
{    
    setBackground(BITMAP_GAME2D_MENU_BACKGROUND_ID);
    setShadeColor(Color::getColorFromRGB(0x0, 0x31, 0x3D));
    setShadeAlpha(230);

    add(ribbon);

    backButton.setBitmaps(Bitmap(BITMAP_GAME2D_BACK_BUTTON_ID), Bitmap(BITMAP_GAME2D_BACK_BUTTON_PRESSED_ID));
    backButton.setXY(147 + X_POS_SHIFT, 366);
    backButton.setAction(buttonClickedCallback);
    add(backButton);

    playButton.setBitmaps(Bitmap(BITMAP_GAME2D_PLAY_BUTTON_ID), Bitmap(BITMAP_GAME2D_PLAY_BUTTON_PRESSED_ID));
    playButton.setXY(319 + X_POS_SHIFT, 366);
    playButton.setAction(buttonClickedCallback);
    add(playButton);

    headline.setColor(Color::getColorFromRGB(0x64, 0x40, 0x1D));
    add(headline);

    Unicode::snprintf(percentageTextBuffer, BUFFER_SIZE, "%d", 0);
    percentageText.setWildcard(percentageTextBuffer);
    percentageText.setTypedText(TypedText(T_GAME2D_POPUP_PERCENTAGE)); //Must or some strange null error.
    percentageText.setColor(Color::getColorFromRGB(0x64, 0x40, 0x1D));
    add(percentageText);

    progressBar.setRange(0, 100);
    progressBar.setDirection(AbstractDirectionProgress::RIGHT);
    progressBar.setAnchorAtZero(true);
    add(progressBar);

    add(progressBarIcon);

    tinfo1_.setTypedText(TypedText(T_GEST_INFO_2S));
    tinfo1_.setXY(60 - 4, 424 - 165);
    tinfo1_.setColor(Color::getColorFromRGB(0x64, 0x40, 0x1D));
    add(tinfo1_);        

    info1_.setBitmap(Bitmap(BITMAP_CAROUSEL_MENU_HAND2_ID));
    info1_.setXY(60 + 5, 344 - 160);
    add(info1_);
    
    tinfo2_.setTypedText(TypedText(T_GEST_INFO_1S));
    tinfo2_.setXY(456 + 108, 424 - 165);
    tinfo2_.setColor(Color::getColorFromRGB(0x64, 0x40, 0x1D));
    add(tinfo2_);

    info2_.setBitmap(Bitmap(BITMAP_CAROUSEL_MENU_HAND3_ID));
    info2_.setXY(456 + 120, 344 - 160);
    add(info2_);

    Application::getInstance()->registerTimerWidget(this);
}

GameStatusPopup::~GameStatusPopup()
{
}

void GameStatusPopup::handleTickEvent()
{
    //if (isVisible() && ms_->eve != nullptr && 1 == *ms_->eve)
    //{
    //    if (1 == ms_->op4)
    //    {
    //        ReturnState returnState = GOTO_MENU;           
    //        popupButtonCallback->execute(returnState);  
    //    }
    //    else if (2 == ms_->op4)
    //    {
    //        ReturnState returnState = GOTO_PLAY;
    //        popupButtonCallback->execute(returnState);
    //    }
    //    *ms_->eve = 0;
    //}
}

void GameStatusPopup::setupWelcome()
{
    progressBar.setVisible(false);
    progressBarIcon.setVisible(false);
    percentageText.setVisible(false);

    headline.setTypedText(TypedText(T_GAME2D_POPUP_WELCOME));
    headline.setPosition(windowBackground.getX() + ((getBackgroundWidth() - 400) / 2), 0, 400, 100);
    headline.setBaselineY(259);

    ribbon.setBitmap(Bitmap(BITMAP_GAME2D_RIBBON_TITLE_ID));
    ribbon.setXY(25 + X_POS_SHIFT, 6);

    invalidate();
}

void GameStatusPopup::setupGameWon()
{
    progressBar.setVisible(true);
    progressBarIcon.setVisible(true);
    percentageText.setVisible(true);

    headline.setTypedText(TypedText(T_GAME2D_POPUP_WON));
    headline.setPosition(windowBackground.getX() + ((getBackgroundWidth() - 200) / 2), 0, 200, 30);
    headline.setBaselineY(209);

    ribbon.setBitmap(Bitmap(BITMAP_GAME2D_RIBBON_VICTORY_ID));
    ribbon.setXY(0 + X_POS_SHIFT, 0);

    progressBar.setBackground(Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_ID));
    progressBar.setXY(157 + X_POS_SHIFT, 274);
    progressBar.setProgressIndicatorPosition(73, 17, Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_WON_ID).getWidth(), Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_WON_ID).getHeight());
    progressBar.setBitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_WON_ID);
    progressBar.setValue(100);

    progressBarIcon.setBitmap(Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_VICTORY_ICON_ID));
    progressBarIcon.setXY(progressBar.getX() + 2, progressBar.getY() + 9);

    Unicode::snprintf(percentageTextBuffer, BUFFER_SIZE, "%d", 100);
    percentageText.setPosition(windowBackground.getX() + (getBackgroundWidth() - 300) / 2, 0, 300, 30);
    percentageText.setBaselineY(250);
    invalidate();
}

void GameStatusPopup::setupGameLost(int percentage)
{
    progressBar.setVisible(true);
    progressBarIcon.setVisible(true);
    percentageText.setVisible(true);

    headline.setTypedText(TypedText(T_GAME2D_POPUP_LOST));
    headline.setPosition(windowBackground.getX() + ((getBackgroundWidth() - 200) / 2), 0, 200, 30);
    headline.setBaselineY(209);

    ribbon.setBitmap(Bitmap(BITMAP_GAME2D_RIBBON_GAME_OVER_ID));
    ribbon.setXY(0 + X_POS_SHIFT, 16);

    progressBar.setBackground(Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_ID));
    progressBar.setXY(157 + X_POS_SHIFT, 274);
    progressBar.setProgressIndicatorPosition(73, 17, Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_LOST_ID).getWidth(), Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_LOST_ID).getHeight());
    progressBar.setBitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_LOST_ID);
    progressBar.setValue(percentage);

    progressBarIcon.setBitmap(Bitmap(BITMAP_GAME2D_POPUP_PROGRESS_BAR_HEAD_ICON_ID));
    progressBarIcon.setXY(progressBar.getX() + 8, progressBar.getY() + 2);

    Unicode::snprintf(percentageTextBuffer, BUFFER_SIZE, "%d", percentage);
    percentageText.setPosition(windowBackground.getX() + (getBackgroundWidth() - 300) / 2, 0, 300, 30);
    percentageText.setBaselineY(250);
    invalidate();
}

void GameStatusPopup::setButtonCallback(GenericCallback<const ReturnState >& callback)
{
    popupButtonCallback = &callback;
}

void GameStatusPopup::buttonClicked(const AbstractButton& source)
{
    ReturnState returnState = (&source == &backButton) ? GOTO_MENU : GOTO_PLAY;

    if (popupButtonCallback && popupButtonCallback->isValid())
    {
        popupButtonCallback->execute(returnState);
    }
}

void GameStatusPopup::setMachineStatus(MachineStatus* ms)
{
    ms_ = ms;
}