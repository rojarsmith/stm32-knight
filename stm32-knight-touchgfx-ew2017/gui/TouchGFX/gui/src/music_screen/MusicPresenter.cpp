#include <gui/music_screen/MusicView.hpp>
#include <gui/music_screen/MusicPresenter.hpp>

MusicPresenter::MusicPresenter(MusicView& v)
    : view(v)
{

}

void MusicPresenter::activate()
{
    Player_switch = false;
    model->senddata(Model::MODE_RECV);
}

void MusicPresenter::deactivate()
{

}

//Rojar
void MusicPresenter::qstatus() {
    model->senddata(Model::MODE_RECV);
}

void MusicPresenter::CDPlay()
{
    if (Player_switch == false)
    {
        view.startAnimation();
        Player_switch = true;

    }
}

void MusicPresenter::CDPause()
{
    if (Player_switch == true)
    {
        view.stopAnimation();
        Player_switch = false;
    }
}

void MusicPresenter::GoToMainScreenFromMusicScreen()
{
    static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenFromCurrentScreen();
}

void MusicPresenter::setMP3(uint8_t fun, uint8_t value)
{
    model->setdata(Model::MODE_MP3, 1, fun);
    model->setdata(Model::MODE_MP3, 2, value);
    model->senddata(Model::MODE_MP3);
}

void MusicPresenter::setMP3_Q(uint8_t fun, uint8_t value, int playmode, int songValue, int  playstatus, int  volumeValue)
{
    model->setdata(Model::MODE_RECV, 1, fun);
    model->setdata(Model::MODE_RECV, 2, value);
    model->senddata(Model::MODE_RECV, playmode, songValue, playstatus, volumeValue);
}

void MusicPresenter::mp3_status(uint8_t play_mode, uint8_t song_num, uint8_t status, uint8_t volume)
{
    model->setdata(Model::MODE_MP3, 3, play_mode);
    model->setdata(Model::MODE_MP3, 5, status);
    model->setdata(Model::MODE_MP3, 4, song_num);
    model->setdata(Model::MODE_MP3, 6, volume);
    view.setPlayMode(play_mode);
    view.setPlayStatus(status);
    view.setSongValue(song_num);
    view.setVolumeValue(volume);
    view.receivedata = true;
}
