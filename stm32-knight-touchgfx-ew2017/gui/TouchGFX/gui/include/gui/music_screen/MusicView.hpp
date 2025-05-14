#ifndef MUSICVIEW_HPP
#define MUSICVIEW_HPP

#include <gui_generated/music_screen/MusicViewBase.hpp>
#include <gui/music_screen/MusicPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Slider.hpp>
// #include <gui/common/BaseViewInterface.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class MusicView : public MusicViewBase
{
public:
    MusicView();
    virtual ~MusicView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    void animationEnded(const AnimatedImage &source);
    void startAnimation();
    void stopAnimation();

    void setPlayMode(uint8_t value);
    void setPlayStatus(uint8_t value);
    void setSongValue(uint8_t value);
    void setVolumeValue(uint8_t value);
    void setBtnPlayIcon();

    void buttonClicked(const AbstractButton &source);

    uint8_t songValue, volumeValue;

    uint32_t screenwidthreal = 0;

    uint8_t volumeValueCatch;

    bool checkSetupScreen; // Checked the SetupScreen completed?
    bool receivedata;

    // ====================================================================
    // TouchArea mcuLoadArea;
    // McuLoadSlider mcuLoadSlider;
    // Callback<MusicView, const AbstractButton&> onMcuLoadClicked;
    TextArea mcuLoadTxt;
    TextAreaWithOneWildcard mcuLoadValueTxt;
    Unicode::UnicodeChar mcuLoadTxtValueBuffer[5];

    virtual void updateProcessorLoad(uint8_t mcuLoadInProcent)
    {
        Unicode::snprintf(mcuLoadTxtValueBuffer, 5, "%d", mcuLoadInProcent);
        mcuLoadValueTxt.invalidate();
    }
    //=========================================================================

protected:
    enum PlayMode
    {
        SINGLE,
        RANDOM,
        CYCLE,
        NO_LOOP
    };

    PlayMode playmode;
    PlayMode playmode_temp;

    enum PlayStatus
    {
        PAUSE,
        PLAY,
        STOP
    };

    PlayStatus playstatus;
    PlayStatus playstatus_temp;

private:
    uint8_t musicTickCounter;

    Image imgBackground, imgLogo;
    Button btnHome;
    Button btnPrevious, btnNext;
    Button btnPlay, btnStop;
    ToggleButton btnSingle, btnRandom, btnCycle;

    Slider volumeSlider;
    Image imgSoundMin, imgSoundMax;
    Image imgDiscs_bg;
    AnimatedImage imgDiscs;

    Image imgSong1_bg, imgSong2_bg, imgSong3_bg, imgSong4_bg, imgSong5_bg;
    Image imgFlag1, imgFlag2, imgFlag3, imgFlag4, imgFlag5;
    RadioButtonGroup<5> radioButtonGroup;
    RadioButton btnSong1, btnSong2, btnSong3, btnSong4, btnSong5;

    static const uint16_t txtWidth = 300;
    static const uint8_t txtHeight = 48;

    TextAreaWithOneWildcard song1Txt, song2Txt, song3Txt, song4Txt, song5Txt;
    Unicode::UnicodeChar song1Txtbuf[30], song2Txtbuf[30], song3Txtbuf[30], song4Txtbuf[30], song5Txtbuf[30];

    Callback<MusicView, const Slider &, int> newValueCallback;
    void newValueHandler(const Slider &slider, int value);

    bool tooFast;

    Callback<MusicView, const AbstractButton &> buttonClickedCallback;

    Callback<MusicView, const AbstractButton &> radioButtonSelectedCallback;
    void radioButtonSelectedHandler(const AbstractButton &radioButton);

    Callback<MusicView, const AnimatedImage &> animationEndedCallback;

    Callback<MusicView, const Slider &> sliderClickedCallback;
    void sliderClickedHandler(const Slider &slider);

    Callback<MusicView, const Slider &, int> stopClickedCallback;
    void stopValueHandler(const Slider &slider, int value);
};

#endif // MUSICVIEW_HPP
