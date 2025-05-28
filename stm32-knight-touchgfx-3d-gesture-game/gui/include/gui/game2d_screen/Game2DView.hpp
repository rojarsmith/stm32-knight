#ifndef GAME2DVIEW_HPP
#define GAME2DVIEW_HPP

#include <gui_generated/game2d_screen/Game2DViewBase.hpp>
#include <gui/game2d_screen/Game2DPresenter.hpp>
#include <gui/game2d_screen/GameStatusPopup.hpp>
#include <gui/game2d_screen/GameButton.hpp>
#include <gui/model/ModelSchema.hpp>

class Game2DView : public Game2DViewBase
{
public:
    Game2DView();
    virtual ~Game2DView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    virtual void ReturnToMain();
    virtual void gestureTick(int eve, int op4);

    void animateBackground();
protected:
    static const int NUMBER_OF_LIVES = 3;
    static const int DEATH_COUNTER_DELAY = 50;
    static const int GAME_PROGRESS_SPEED = 80; // Number of ticks that makes out one percentage of the game progress (~60 = 1 sec)
    int active_screen_width_;

    int gameProgressCounter;
    int gameProgressPercentage;
    int respawnCounter;
    int lives;

    int tick_counter_;

    int groundLevelY;

    GameStatusPopup gameStatusPopup;


    GameButton jumpButton;
    GameButton slideButton;

    Image lifeIndicator[NUMBER_OF_LIVES];
    ImageProgress gameProgressIndicator;

    Callback<Game2DView, const AbstractButton&> buttonClickedCallback;
    void buttonClicked(const AbstractButton& source);

    void collisionDetection();

    Callback<Game2DView, const GameStatusPopup::ReturnState> popup_button_callback_;
    void popupButtonHandler(const GameStatusPopup::ReturnState source);

    bool gameIsRunning;
    int deathTickCounter;
    void gotoStartOfGameState();
    void gotoEndOfGameStatePhase1();
    void gotoEndOfGameStatePhase2();
    void showGameElements(bool visible);

    void killNinja();
    void setupEnemies();
    void respawnNinja();
    void updateLiveIndicator();
    void updateGameStatus();
private:
    MachineStatus* ms_;
};

#endif // GAME2DVIEW_HPP
