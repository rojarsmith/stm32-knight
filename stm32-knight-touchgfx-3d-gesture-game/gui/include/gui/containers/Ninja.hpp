#ifndef NINJA_HPP
#define NINJA_HPP

#include <gui_generated/containers/NinjaBase.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

using namespace touchgfx;

class Ninja : public MoveAnimator<NinjaBase>
{
public:
    enum AnimationState
    {
        ENTERING_GAME,
        RUN,
        JUMP,
        SLIDE,
        DEAD
    };

    Ninja();
    virtual ~Ninja() {}

    virtual void initialize();
    virtual void handleTickEvent();

    void setState(AnimationState state);
    AnimationState getState()
    {
        return current_animation_state_;
    }

    void setGroundPosition(int ground);

    Rect getBodyArea();

    void reset();

protected:
    AnimationState current_animation_state_;
    int tick_counter_;

    int x_start_position_;
    int ground_y_;

    int jump_height_;
    int animation_duration_up_;
    int animation_duration_down_;
    int animation_speed_;
};

#endif // NINJA_HPP
