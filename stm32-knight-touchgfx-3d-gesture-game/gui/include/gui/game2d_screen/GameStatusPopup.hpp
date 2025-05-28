#ifndef GAMESTATUSPOPUP_HPP
#define GAMESTATUSPOPUP_HPP

#include <touchgfx/containers/ModalWindow.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class GameStatusPopup : public ModalWindow
{
public:
    enum ReturnState
    {
        GOTO_MENU,
        GOTO_PLAY
    };

    GameStatusPopup();
    virtual ~GameStatusPopup();

    virtual void handleTickEvent();

    void setupWelcome();
    void setupGameWon();
    void setupGameLost(int percentage);

    void setButtonCallback(GenericCallback<const ReturnState >& callback);
    void setMachineStatus(MachineStatus* ms);;
private:
    static const int BUFFER_SIZE = 6;
    static const int X_POS_SHIFT = 50;

    Button backButton;
    Button playButton;

    TextArea headline;
    TextAreaWithOneWildcard percentageText;
    Unicode::UnicodeChar percentageTextBuffer[BUFFER_SIZE];

    Image ribbon;
    ImageProgress progressBar;
    Image progressBarIcon;    
    TextArea tinfo1_;
    Image info1_;
    TextArea tinfo2_;
    Image info2_;

    Callback<GameStatusPopup, const AbstractButton&> buttonClickedCallback;
    void buttonClicked(const AbstractButton& source);

    GenericCallback<const ReturnState >* popupButtonCallback;

    MachineStatus* ms_;
};

#endif
