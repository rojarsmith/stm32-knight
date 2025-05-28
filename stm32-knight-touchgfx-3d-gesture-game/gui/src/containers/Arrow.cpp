#include <gui/containers/Arrow.hpp>

Arrow::Arrow() :
    ground_y_(0),
    start_y_(350)
{
    Application::getInstance()->registerTimerWidget(this);

    setState(MOVING);
}

void Arrow::initialize()
{
    ArrowBase::initialize();
}

void Arrow::handleTickEvent()
{
    MoveAnimator<ArrowBase>::handleTickEvent();

    tick_counter_++;

    if (current_animation_state_ != STOPPED &&
        current_animation_state_ != HIT_TARGET)
    {
        if (0 == tick_counter_ % 2)
        {            
            moveRelative(-7, 0);
        }
    }

    if (current_animation_state_ == HIT_TARGET)
    {
        int fadeDuration = 30;

        if (tick_counter_ == 1)
        {            
            activeAnimation.startFadeAnimation(0, 30, EasingEquations::cubicEaseIn);
        }
        else if (tick_counter_ == fadeDuration + 5)
        {
            reset();
        }
    }
}

void Arrow::setState(AnimationState state)
{
    current_animation_state_ = state;
    tick_counter_ = 0;
}

void Arrow::setStartY(int y)
{
    start_y_ = y;
    moveTo(getX(), y);
}

void Arrow::reset()
{
    moveTo(800, getY());
    activeAnimation.setAlpha(255);
    setState(STOPPED);
}

Rect Arrow::getAttackArea()
{
    return getRect();
}