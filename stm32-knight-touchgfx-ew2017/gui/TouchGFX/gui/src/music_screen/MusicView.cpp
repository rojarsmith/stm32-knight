#include <gui/music_screen/MusicView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

MusicView::MusicView() :
    volumeValueCatch(0),
    checkSetupScreen(false),
    receivedata(false), // If receive data from arduino, set the parameter true.
    imgDiscs(BITMAP_CD_INSIDE_001_ID, BITMAP_CD_INSIDE_020_ID, 2),
    newValueCallback(this, &MusicView::newValueHandler),
    buttonClickedCallback(this, &MusicView::buttonClicked),
    radioButtonSelectedCallback(this, &MusicView::radioButtonSelectedHandler),
    animationEndedCallback(this, &MusicView::animationEnded),
    sliderClickedCallback(this, &MusicView::sliderClickedHandler),
    stopClickedCallback(this, &MusicView::stopValueHandler)
{

}

void MusicView::setupScreen()
{
    imgBackground.setBitmap(Bitmap(BITMAP_MAINBG_ID));
    imgBackground.setXY(0, 0);
    add(imgBackground);

    imgLogo.setBitmap(Bitmap(BITMAP_LOGO_SMALL_ID));
    imgLogo.setXY(5, 5);
    add(imgLogo);

    btnHome.setBitmaps(Bitmap(BITMAP_BTN_HOME_RELEASED_ID), Bitmap(BITMAP_BTN_HOME_PRESSED_ID));

    uint16_t func_btn_width = btnHome.getWidth();
    uint16_t func_btn_height = btnHome.getHeight();

    btnHome.setXY(HAL::DISPLAY_WIDTH - 26 - func_btn_width, HAL::DISPLAY_HEIGHT - func_btn_height);
    btnHome.setAction(buttonClickedCallback);
    add(btnHome);

    // Setup song list
    imgSong1_bg.setBitmap(Bitmap(BITMAP_SONG_BG_ID));
    imgSong2_bg.setBitmap(Bitmap(BITMAP_SONG_BG_ID));
    imgSong3_bg.setBitmap(Bitmap(BITMAP_SONG_BG_ID));
    imgSong4_bg.setBitmap(Bitmap(BITMAP_SONG_BG_ID));
    imgSong5_bg.setBitmap(Bitmap(BITMAP_SONG_BG_ID));

    imgFlag1.setBitmap(Bitmap(BITMAP_FLAG_TAIWAN_ID));
    imgFlag2.setBitmap(Bitmap(BITMAP_FLAG_DENMARK_ID));
    imgFlag3.setBitmap(Bitmap(BITMAP_FLAG_UNITED_STATES_ID));
    imgFlag4.setBitmap(Bitmap(BITMAP_FLAG_GERMANY_ID));
    imgFlag5.setBitmap(Bitmap(BITMAP_FLAG_SWITZERLAND_ID));

    btnSong1.setBitmaps(Bitmap(BITMAP_BTN_SONG_RELEASED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID));
    btnSong2.setBitmaps(Bitmap(BITMAP_BTN_SONG_RELEASED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID));
    btnSong3.setBitmaps(Bitmap(BITMAP_BTN_SONG_RELEASED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID));
    btnSong4.setBitmaps(Bitmap(BITMAP_BTN_SONG_RELEASED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID));
    btnSong5.setBitmaps(Bitmap(BITMAP_BTN_SONG_RELEASED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID), Bitmap(BITMAP_BTN_SONG_PRESSED_ID));

    uint16_t imgSongBgHeight = imgSong1_bg.getHeight();
    uint16_t imgSongBgHeightPitch = (HAL::DISPLAY_HEIGHT - btnHome.getHeight() - (imgSongBgHeight * 5)) / 6;
    uint16_t imgSongBgStartX = 362;

    imgSong1_bg.setXY(imgSongBgStartX, imgSongBgHeightPitch);
    imgSong2_bg.setXY(imgSongBgStartX, (imgSongBgHeightPitch * 2) + imgSongBgHeight);
    imgSong3_bg.setXY(imgSongBgStartX, (imgSongBgHeightPitch * 3) + (imgSongBgHeight * 2));
    imgSong4_bg.setXY(imgSongBgStartX, (imgSongBgHeightPitch * 4) + (imgSongBgHeight * 3));
    imgSong5_bg.setXY(imgSongBgStartX, (imgSongBgHeightPitch * 5) + (imgSongBgHeight * 4));

    imgFlag1.setXY(imgSongBgStartX + 24, imgSong1_bg.getY() + 3);
    imgFlag2.setXY(imgSongBgStartX + 24, imgSong2_bg.getY() + 3);
    imgFlag3.setXY(imgSongBgStartX + 24, imgSong3_bg.getY() + 3);
    imgFlag4.setXY(imgSongBgStartX + 24, imgSong4_bg.getY() + 3);
    imgFlag5.setXY(imgSongBgStartX + 24, imgSong5_bg.getY() + 3);

    btnSong1.setXY(imgSongBgStartX + 107, imgSong1_bg.getY() + 3);
    btnSong2.setXY(imgSongBgStartX + 107, imgSong2_bg.getY() + 3);
    btnSong3.setXY(imgSongBgStartX + 107, imgSong3_bg.getY() + 3);
    btnSong4.setXY(imgSongBgStartX + 107, imgSong4_bg.getY() + 3);
    btnSong5.setXY(imgSongBgStartX + 107, imgSong5_bg.getY() + 3);

    radioButtonGroup.add(btnSong1);
    radioButtonGroup.add(btnSong2);
    radioButtonGroup.add(btnSong3);
    radioButtonGroup.add(btnSong4);
    radioButtonGroup.add(btnSong5);

    radioButtonGroup.setRadioButtonSelectedHandler(radioButtonSelectedCallback);

    add(imgSong1_bg);
    add(imgSong2_bg);
    add(imgSong3_bg);
    add(imgSong4_bg);
    add(imgSong5_bg);

    add(imgFlag1);
    add(imgFlag2);
    add(imgFlag3);
    add(imgFlag4);
    add(imgFlag5);

    add(btnSong1);
    add(btnSong2);
    add(btnSong3);
    add(btnSong4);
    add(btnSong5);

    songValue = 1;
    radioButtonGroup.setSelected(btnSong1);

    //    uint8_t fontHeightPitch = (btnSongHeight - txtHeight) / 2;

    song1Txt.setWildcard(song1Txtbuf);
    song1Txt.setTypedText(TypedText(T_SONG_1));
    song1Txt.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
    add(song1Txt);
    song1Txt.setPosition(imgSongBgStartX + 116, btnSong1.getY() + 10, txtWidth, txtHeight);
    Unicode::snprintf(song1Txtbuf, txtHeight, "%d aaa");
    song1Txt.invalidate();

    song2Txt.setWildcard(song2Txtbuf);
    song2Txt.setTypedText(TypedText(T_SONG_2));
    song2Txt.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
    add(song2Txt);
    song2Txt.setPosition(imgSongBgStartX + 116, btnSong2.getY() + 10, txtWidth, txtHeight);
    Unicode::snprintf(song2Txtbuf, txtHeight, "%d");
    song2Txt.invalidate();

    song3Txt.setWildcard(song3Txtbuf);
    song3Txt.setTypedText(TypedText(T_SONG_3));
    song3Txt.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
    add(song3Txt);
    song3Txt.setPosition(imgSongBgStartX + 116, btnSong3.getY() + 10, txtWidth, txtHeight);
    Unicode::snprintf(song3Txtbuf, txtHeight, "%d");
    song3Txt.invalidate();

    song4Txt.setWildcard(song4Txtbuf);
    song4Txt.setTypedText(TypedText(T_SONG_4));
    song4Txt.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
    add(song4Txt);
    song4Txt.setPosition(imgSongBgStartX + 116, btnSong4.getY() + 10, txtWidth, txtHeight);
    Unicode::snprintf(song4Txtbuf, txtHeight, "%d");
    song4Txt.invalidate();

    song5Txt.setWildcard(song5Txtbuf);
    song5Txt.setTypedText(TypedText(T_SONG_5));
    song5Txt.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
    add(song5Txt);
    song5Txt.setPosition(imgSongBgStartX + 116, btnSong5.getY() + 10, txtWidth, txtHeight);
    Unicode::snprintf(song5Txtbuf, txtHeight, "%d");
    song5Txt.invalidate();

    // Setup discs image
    imgDiscs_bg.setBitmap(Bitmap(BITMAP_CD_OUTSIDE_ID));
    imgDiscs_bg.setXY(66, 33);
    add(imgDiscs_bg);

    imgDiscs.setXY(139, 106);
    imgDiscs.setDoneAction(animationEndedCallback);
    add(imgDiscs);

    btnPrevious.setBitmaps(Bitmap(BITMAP_BTN_PREVIOUS_RELEASED_ID), Bitmap(BITMAP_BTN_PREVIOUS_PRESSED_ID));
    btnPlay.setBitmaps(Bitmap(BITMAP_BTN_PLAY_RELEASED_ID), Bitmap(BITMAP_BTN_PLAY_PRESSED_ID));
    btnStop.setBitmaps(Bitmap(BITMAP_BTN_STOP_RELEASED_ID), Bitmap(BITMAP_BTN_STOP_PRESSED_ID));
    btnNext.setBitmaps(Bitmap(BITMAP_BTN_NEXT_RELEASED_ID), Bitmap(BITMAP_BTN_NEXT_PRESSED_ID));

    btnSingle.setBitmaps(Bitmap(BITMAP_BTN_SINGLE_RELEASED_ID), Bitmap(BITMAP_BTN_SINGLE_PRESSED_ID));
    btnRandom.setBitmaps(Bitmap(BITMAP_BTN_RANDOM_RELEASED_ID), Bitmap(BITMAP_BTN_RANDOM_PRESSED_ID));
    btnCycle.setBitmaps(Bitmap(BITMAP_BTN_CYCLE_RELEASED_ID), Bitmap(BITMAP_BTN_CYCLE_PRESSED_ID));

    volumeSlider.setBitmaps(Bitmap(BITMAP_VOLUMESLIDERBAR_BG_ID), Bitmap(BITMAP_VOLUMESLIDERBAR_FILLED_ID), Bitmap(BITMAP_VOLUMESLIDER_KNOB_ID));

    imgSoundMin.setBitmap(Bitmap(BITMAP_SOUND_MIN_ID));
    imgSoundMax.setBitmap(Bitmap(BITMAP_SOUND_MAX_ID));

    uint16_t imgDiscsWidth = imgDiscs_bg.getWidth();
    uint16_t imgDiscsHeight = imgDiscs_bg.getHeight();
    uint16_t volumeSliderWidth = 229;
    uint16_t volumeSliderHeight = 25;
    uint16_t ctrlbtnWidth = btnPrevious.getWidth();
    uint16_t ctrlbtnHeight = btnPrevious.getHeight();
    uint16_t ctrlbtnWidthPitch_u = (imgDiscsWidth - (btnPrevious.getWidth() * 4)) / 3;
    uint16_t ctrlbtnWidthPitch_d = (imgDiscsWidth - (btnPrevious.getWidth() * 3)) / 2;
    uint16_t ctrlbtnHeightPitch = (HAL::DISPLAY_HEIGHT - imgDiscs_bg.getY() - imgDiscsHeight - (ctrlbtnHeight * 2) - volumeSliderHeight) / 4;
    uint16_t ctrlbtnStartX = imgDiscs_bg.getX();
    uint16_t ctrlbtnStartY = imgDiscs_bg.getY() + imgDiscsHeight + ctrlbtnHeightPitch;

    btnPrevious.setXY(ctrlbtnStartX, ctrlbtnStartY);
    btnPlay.setXY(ctrlbtnStartX + ctrlbtnWidth + ctrlbtnWidthPitch_u, ctrlbtnStartY);
    btnStop.setXY(ctrlbtnStartX + (ctrlbtnWidth * 2) + (ctrlbtnWidthPitch_u * 2), ctrlbtnStartY);
    btnNext.setXY(ctrlbtnStartX + (ctrlbtnWidth * 3) + (ctrlbtnWidthPitch_u * 3), ctrlbtnStartY);

    volumeSlider.setXY(imgDiscs_bg.getX(), ctrlbtnStartY + ctrlbtnHeight + ctrlbtnHeightPitch);
    imgSoundMin.setXY(volumeSlider.getX() - imgSoundMin.getWidth() - 5, volumeSlider.getY());
    imgSoundMax.setXY(volumeSlider.getX() + volumeSliderWidth + 5, volumeSlider.getY());

    btnSingle.setXY(ctrlbtnStartX, ctrlbtnStartY + ctrlbtnHeight + volumeSliderHeight + (ctrlbtnHeightPitch * 2));
    btnRandom.setXY(ctrlbtnStartX + ctrlbtnWidth + ctrlbtnWidthPitch_d, ctrlbtnStartY + ctrlbtnHeight + volumeSliderHeight + (ctrlbtnHeightPitch * 2));
    btnCycle.setXY(ctrlbtnStartX + (ctrlbtnWidth * 2) + (ctrlbtnWidthPitch_d * 2), ctrlbtnStartY + ctrlbtnHeight + volumeSliderHeight + (ctrlbtnHeightPitch * 2));

    btnPrevious.setAction(buttonClickedCallback);
    btnPlay.setAction(buttonClickedCallback);
    btnStop.setAction(buttonClickedCallback);
    btnNext.setAction(buttonClickedCallback);

    add(btnPrevious);
    add(btnPlay);
    add(btnStop);
    add(btnNext);

    volumeSlider.setStopValueCallback(stopClickedCallback);

    volumeSlider.setNewValueCallback(newValueCallback);

    // Setup slider background and indicator positions. The background does not take up
    // all the slider widget since the indicator needs to extend beyond the background in
    // the min and max positions. This is handled by placing the background at position (18, 15)
    volumeSlider.setupHorizontalSlider(0, 0, 0, 0, 187);

    // Set the value range of the slider. Since the value us used for setting the 8bit alpha
    // value of the images, the range is set to 0-255.
    // Note that the slider indicator position range is only 192-8 = 184 pixels. This is, however, not a
    // problem just remember that in this case not all values can be set by the slider (since there is not a
    // pixel for each value)
    volumeSlider.setValueRange(0, 30);
    volumeValue = 15;
    volumeSlider.setValue(volumeValue);
    volumeSlider.invalidate();

    add(volumeSlider);
    add(imgSoundMin);
    add(imgSoundMax);

    btnSingle.setAction(buttonClickedCallback);
    btnRandom.setAction(buttonClickedCallback);
    btnCycle.setAction(buttonClickedCallback);

    add(btnSingle);
    add(btnRandom);
    add(btnCycle);



    //Rojar====================================================================
    // MCULoad must be added by the specialized menu view (to get correct z-order)
    //mcuLoadTxt.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_TEXT));
    //mcuLoadTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    //mcuLoadTxt.setHeight(100);
    //mcuLoadTxt.setWidth(100);

    //Unicode::snprintf(mcuLoadTxtValueBuffer, 5, "%d", 0);
    //mcuLoadValueTxt.setWildcard(mcuLoadTxtValueBuffer);
    //mcuLoadValueTxt.setTypedText(TypedText(T_DEMO_VIEW_MCU_LOAD_VALUE));
    //mcuLoadValueTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));


    //MCU Usage.
    //mcuLoadTxt.setXY(10, 10 - mcuLoadTxt.getTypedText().getFont()->getFontHeight());
    //mcuLoadValueTxt.setPosition(mcuLoadTxt.getRect().right(), mcuLoadTxt.getY(), 34, 14);
    //add(mcuLoadTxt);
    //add(mcuLoadValueTxt);
    //=========================================================================

    //notFirstTimeShowView = true;
    checkSetupScreen = true;
}

void MusicView::tearDownScreen()
{

}




void MusicView::handleTickEvent()
{
    /**
     * When received data from arduino,
     * set "receivedata = true" first,
     * and then changed button setting,
     * finally, set "receivedata = false".
     */
#ifdef _MSC_VER
    //playmode = PlayMode::NO_LOOP;
    //songValue = 4;
    //playstatus = PlayStatus::PLAY;
    //volumeValue = 5;
#endif
    if (receivedata == true)
    {
        if (playmode != playmode_temp)
        {
            switch (playmode)
            {
            case SINGLE:
                btnSingle.forceState(true);
                btnRandom.forceState(false);
                btnCycle.forceState(false);
                btnSingle.invalidate();
                btnRandom.invalidate();
                btnCycle.invalidate();
                playmode_temp = playmode;
                break;

            case RANDOM:
                btnSingle.forceState(false);
                btnRandom.forceState(true);
                btnCycle.forceState(false);
                btnSingle.invalidate();
                btnRandom.invalidate();
                btnCycle.invalidate();
                playmode_temp = playmode;
                break;

            case CYCLE:
                btnSingle.forceState(false);
                btnRandom.forceState(false);
                btnCycle.forceState(true);
                btnSingle.invalidate();
                btnRandom.invalidate();
                btnCycle.invalidate();
                playmode_temp = playmode;
                break;

            case NO_LOOP:
                btnSingle.forceState(false);
                btnRandom.forceState(false);
                btnCycle.forceState(false);
                btnSingle.invalidate();
                btnRandom.invalidate();
                btnCycle.invalidate();
                playmode_temp = playmode;
                break;

            default:
                break;
            }
        }

        if (playstatus == PLAY)
        {
            playstatus_temp = playstatus;
            //presenter->CDPlay();
            imgDiscs.startAnimation(imgDiscs.isAnimatedImageRunning(), false, true);
            presenter->Player_switch = true;
            setBtnPlayIcon(); // Setting btnPlay image.
        }
        else
        {
            playstatus_temp = playstatus;
            //presenter->CDPause();
            imgDiscs.stopAnimation();
            presenter->Player_switch = false;
            setBtnPlayIcon(); // Setting btnPlay image.
        }

        switch (songValue)
        {
        case 1:
            radioButtonGroup.setSelected(btnSong1);
            break;

        case 2:
            radioButtonGroup.setSelected(btnSong2);
            break;

        case 3:
            radioButtonGroup.setSelected(btnSong3);
            break;

        case 4:
            radioButtonGroup.setSelected(btnSong4);
            break;

        case 5:
            radioButtonGroup.setSelected(btnSong5);
            break;

        default:
            break;
        }

        volumeSlider.setValue(volumeValue);
        //volumeSlider.invalidate();

        receivedata = false;
    }
}

void MusicView::buttonClicked(const AbstractButton& source)
{
    if (&source == &btnPrevious)
    {
        presenter->setMP3(5, 0);
    }

    if (&source == &btnPlay)
    {
        if (playstatus == PLAY)
        {
            playstatus = PAUSE;
            playstatus_temp = playstatus;
            setBtnPlayIcon(); // Setting btnPlay image.
            presenter->CDPause();
            presenter->setMP3(1, 0);
            presenter->qstatus();
        }
        else
        {
            playstatus = PLAY;
            playstatus_temp = playstatus;
            setBtnPlayIcon(); // Setting btnPlay image.
            presenter->CDPlay();
            presenter->setMP3(2, 0);
            presenter->qstatus();
        }
    }

    if (&source == &btnStop)
    {
        if (playstatus == PLAY)
        {
            playstatus = STOP;
            playstatus_temp = playstatus;
            setBtnPlayIcon(); // Setting btnPlay image.
            presenter->CDPause();
            presenter->setMP3(8, 1);
        }
    }

    if (&source == &btnNext)
    {
        presenter->setMP3(4, 0);
    }

    if (&source == &btnSingle)
    {
        switch (playmode)
        {
        case SINGLE:
            playmode = NO_LOOP;
            playmode_temp = playmode;
            presenter->setMP3(7, 3);
            break;

        case RANDOM:
            btnRandom.forceState(false);
            btnRandom.invalidate();
            playmode = SINGLE;
            presenter->setMP3(7, 2);
            break;

        case CYCLE:
            btnCycle.forceState(false);
            btnCycle.invalidate();
            playmode = SINGLE;
            playmode_temp = playmode;
            presenter->setMP3(7, 2);
            break;

        case NO_LOOP:
            playmode = SINGLE;
            playmode_temp = playmode;
            presenter->setMP3(7, 2);
            break;

        default:
            break;
        }
    }

    if (&source == &btnRandom)
    {
        switch (playmode)
        {
        case SINGLE:
            btnSingle.forceState(false);
            btnSingle.invalidate();
            playmode = RANDOM;
            playmode_temp = playmode;
            presenter->setMP3(7, 1);
            break;

        case RANDOM:
            playmode = NO_LOOP;
            playmode_temp = playmode;
            presenter->setMP3(7, 3);
            break;

        case CYCLE:
            btnCycle.forceState(false);
            btnCycle.invalidate();
            playmode = RANDOM;
            playmode_temp = playmode;
            presenter->setMP3(7, 1);
            break;

        case NO_LOOP:
            playmode = RANDOM;
            playmode_temp = playmode;
            presenter->setMP3(7, 1);
            break;

        default:
            break;
        }
    }

    if (&source == &btnCycle)
    {
        switch (playmode)
        {
        case SINGLE:
            btnSingle.forceState(false);
            btnSingle.invalidate();
            playmode = CYCLE;
            playmode_temp = playmode;
            presenter->setMP3(7, 0);
            break;

        case RANDOM:
            btnRandom.forceState(false);
            btnRandom.invalidate();
            playmode = CYCLE;
            playmode_temp = playmode;
            presenter->setMP3(7, 0);
            break;

        case CYCLE:
            playmode = NO_LOOP;
            presenter->setMP3(7, 3);
            break;

        case NO_LOOP:
            playmode = CYCLE;
            playmode_temp = playmode;
            presenter->setMP3(7, 0);
            break;

        default:
            break;
        }
    }

    if (&source == &btnHome)
    {
        if (playstatus == PAUSE)
        {
            presenter->setMP3(8, 1);
        }
        presenter->GoToMainScreenFromMusicScreen();
    }
}

void MusicView::newValueHandler(const Slider& slider, int value)
{
    if (&slider == &volumeSlider)
    {
        if (receivedata == true) return;

        volumeValue = value;

        if (volumeValue == volumeValueCatch) {
            return;
        }

        volumeValueCatch = value;

        if (checkSetupScreen == true)
        {
            presenter->setMP3(3, volumeValue);
        }
    }
}



void MusicView::radioButtonSelectedHandler(const AbstractButton& radioButton)
{
    if (&btnSong1 == &radioButton)
    {
        songValue = 1;
    }

    if (&btnSong2 == &radioButton)
    {
        songValue = 2;
    }

    if (&btnSong3 == &radioButton)
    {
        songValue = 3;
    }

    if (&btnSong4 == &radioButton)
    {
        songValue = 4;
    }

    if (&btnSong5 == &radioButton)
    {
        songValue = 5;
    }

    if (receivedata == true) {
        return;
    }
    if (checkSetupScreen == false) {
        return;
    }

    presenter->setMP3(0, songValue);
}

/**
 * Start the animation in the reverse direction
 */
void MusicView::animationEnded(const AnimatedImage& source)
{
    //imgDiscs.startAnimation(!imgDiscs.isReverse(), false, true);
    imgDiscs.startAnimation(!imgDiscs.isAnimatedImageRunning(), false, true);
}

/**
 * Start the animation in the same direction as it was stopped.
 * Change the label text to reflect the state
 */
void MusicView::startAnimation()
{
    //imgDiscs.startAnimation(imgDiscs.isReverse(), false, true);
    imgDiscs.startAnimation(imgDiscs.isAnimatedImageRunning(), false, true);
}

/**
 * Stop, or pause, the animation.
 * Change the label text to reflect the state
 */
void MusicView::stopAnimation()
{
    imgDiscs.pauseAnimation();
}

 /**
  * 4 functions for get value from presenter
  */
void MusicView::setPlayMode(uint8_t value)
{
    switch (value)
    {
    case 0:
        playmode = CYCLE;
        break;

    case 1:
        playmode = RANDOM;
        break;

    case 2:
        playmode = SINGLE;
        break;

    case 3:
        playmode = NO_LOOP;
        break;

    default:
        break;
    }
}

void MusicView::setPlayStatus(uint8_t value)
{
    switch (value)
    {
    case 0:
        playstatus = PAUSE;
        break;

    case 1:
        playstatus = PLAY;
        break;

    case 2:
        playstatus = STOP;
        break;

    default:
        break;
    }
}

void MusicView::setVolumeValue(uint8_t value) 
{
    volumeValue = value;
}

void MusicView::setSongValue(uint8_t value)
{
    songValue = value;
}

void MusicView::setBtnPlayIcon()
{
    if (playstatus == PLAY)
    {
        btnPlay.setBitmaps(Bitmap(BITMAP_BTN_PAUSE_RELEASED_ID), Bitmap(BITMAP_BTN_PAUSE_PRESSED_ID));
        btnPlay.invalidate();
    }
    else
    {
        btnPlay.setBitmaps(Bitmap(BITMAP_BTN_PLAY_RELEASED_ID), Bitmap(BITMAP_BTN_PLAY_PRESSED_ID));
        btnPlay.invalidate();
    }
}

void MusicView::sliderClickedHandler(const Slider& source)
{

}

void MusicView::stopValueHandler(const Slider& source, int value)
{

}
