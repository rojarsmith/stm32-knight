#ifndef MUSICPRESENTER_HPP
#define MUSICPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MusicView;

class MusicPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MusicPresenter(MusicView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MusicPresenter() {}

    void CDPlay();
    void CDPause();

    bool Player_switch;

    /**
     * Slide Transition : Go to main screen.
     */
    void GoToMainScreenFromMusicScreen();
    void setMP3(uint8_t fun, uint8_t value);
    void setMP3_Q(uint8_t fun, uint8_t value, int playmode, int songValue, int  playstatus, int  volumeValue);
    void mp3_status(uint8_t play_mode, uint8_t song_num, uint8_t status, uint8_t volume);
    void qstatus();

    //virtual void mcuLoadUpdated(uint8_t mcuLoad);
private:
    MusicPresenter();

    MusicView& view;
};

#endif // MUSICPRESENTER_HPP
