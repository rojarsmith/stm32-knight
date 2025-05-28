#ifndef GAME2DPRESENTER_HPP
#define GAME2DPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Game2DView;

class Game2DPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Game2DPresenter(Game2DView& v);

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

    virtual ~Game2DPresenter() {};

    virtual void gestureTick(int eve, int op4);

    virtual MachineStatus* getMachineStatus();
private:
    Game2DPresenter();

    Game2DView& view;
};


#endif // GAME2DPRESENTER_HPP
