#ifndef ARROW_HPP
#define ARROW_HPP

#include <gui_generated/containers/ArrowBase.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

class Arrow : public MoveAnimator<ArrowBase>
{
public:
    enum AnimationState
    {
        MOVING,
        STOPPED,
        HIT_TARGET
    };

    Arrow();
    virtual ~Arrow() {}

    virtual void initialize();
    virtual void handleTickEvent();

    void setState(AnimationState state);
    AnimationState getState()
    {
        return current_animation_state_;
    }

    void setStartY(int y);

    void reset();

    Rect getAttackArea();

protected:
    AnimationState current_animation_state_;
    int tick_counter_;

    int ground_y_;
    int start_y_;
};

#endif // ARROW_HPP
