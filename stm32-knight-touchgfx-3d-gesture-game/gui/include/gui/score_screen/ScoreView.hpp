#ifndef SCOREVIEW_HPP
#define SCOREVIEW_HPP

#include <gui_generated/score_screen/ScoreViewBase.hpp>
#include <gui/score_screen/ScorePresenter.hpp>
#include <gui/model/ModelSchema.hpp>

class ScoreView : public ScoreViewBase
{
public:
    ScoreView();
    virtual ~ScoreView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    virtual void gestureTick(int eve, int op4);
    virtual void ReturnToMain();
protected:
private:
    MachineStatus* ms_;

    static const int BUFFER_SIZE = 6;

    Unicode::UnicodeChar percentageTextBuffer[BUFFER_SIZE];
    Unicode::UnicodeChar percentageTextBuffer1[BUFFER_SIZE];
    Unicode::UnicodeChar percentageTextBuffer2[BUFFER_SIZE];
};

#endif // SCOREVIEW_HPP
