#include <gui/containers/Ninja.hpp>
#include <BitmapDatabase.hpp>

Ninja::Ninja()
{
    Application::getInstance()->registerTimerWidget(this);

    x_start_position_ = 182;
}

void Ninja::initialize()
{
    NinjaBase::initialize();
}

void Ninja::handleTickEvent()
{
    MoveAnimator<NinjaBase>::handleTickEvent();

    tick_counter_++;

    if (tick_counter_ == 1)
    {
        activeAnimation.setAlpha(255);
    }

    if (current_animation_state_ == RUN || current_animation_state_ == ENTERING_GAME)
    {
        int enteringGameAnimationDuration = 50;

        if (tick_counter_ == 1)
        {
            activeAnimation.setBitmaps(BITMAP_NINJA_RUN_01_ID, BITMAP_NINJA_RUN_10_ID);
            activeAnimation.setXY(0, 0);
            activeAnimation.setUpdateTicksInterval(3);

            setWidth(activeAnimation.getWidth());
            setHeight(activeAnimation.getHeight());

            if (current_animation_state_ == ENTERING_GAME)
            {
                moveTo(-47, ground_y_);
                setMoveAnimationDelay(0);                
                startMoveAnimation(x_start_position_, ground_y_, enteringGameAnimationDuration, EasingEquations::circEaseOut);
            }

            activeAnimation.startAnimation(false, false, true);
        }
        else if (current_animation_state_ == ENTERING_GAME && tick_counter_ == enteringGameAnimationDuration)
        {
            current_animation_state_ = RUN;
        }
    }
    else if (current_animation_state_ == JUMP)
    {
        if (tick_counter_ == 1)
        {
            if (current_animation_state_ == JUMP)
            {
                activeAnimation.setBitmaps(BITMAP_NINJA_JUMP_01_ID, BITMAP_NINJA_JUMP_10_ID);
            }
            activeAnimation.startAnimation(false, false, false);
            activeAnimation.setUpdateTicksInterval(animation_speed_);
            activeAnimation.invalidate();

            setWidth(activeAnimation.getWidth());
            setHeight(activeAnimation.getHeight());

            setMoveAnimationDelay(0);
            startMoveAnimation(getX(), getY() - jump_height_, animation_duration_up_, EasingEquations::cubicEaseInOut, EasingEquations::cubicEaseOut);
        }
        else if (tick_counter_ == animation_duration_up_)
        {
            setMoveAnimationDelay(0);
            startMoveAnimation(getX(), ground_y_, animation_duration_down_, EasingEquations::cubicEaseInOut, EasingEquations::cubicEaseIn);
        }
        else if (tick_counter_ == (animation_duration_up_ + animation_duration_down_))
        {
            setState(RUN);
        }
    }
    else if (current_animation_state_ == SLIDE)
    {
        if (tick_counter_ == 1)
        {
            if (current_animation_state_ == SLIDE)
            {
                activeAnimation.setBitmaps(BITMAP_NINJA_SLIDE_01_ID, BITMAP_NINJA_SLIDE_10_ID);
            }
            activeAnimation.startAnimation(false, false, false);
            activeAnimation.setUpdateTicksInterval(animation_speed_);
            activeAnimation.invalidate();

            setWidth(activeAnimation.getWidth());
            setHeight(activeAnimation.getHeight());

            setMoveAnimationDelay(0);
            startMoveAnimation(getX(), getY() - jump_height_, animation_duration_up_, EasingEquations::cubicEaseInOut, EasingEquations::cubicEaseOut);
        }
        else if (tick_counter_ == animation_duration_up_)
        {
            setMoveAnimationDelay(0);
            startMoveAnimation(getX(), ground_y_, animation_duration_down_, EasingEquations::cubicEaseInOut, EasingEquations::cubicEaseIn);
        }
        else if (tick_counter_ == (animation_duration_up_ + animation_duration_down_))
        {
            setState(RUN);
        }
    }
    else if (current_animation_state_ == DEAD)
    {
        if (tick_counter_ == 1)
        {
            activeAnimation.setBitmaps(BITMAP_NINJA_DEAD_01_ID, BITMAP_NINJA_DEAD_10_ID);

            setWidth(activeAnimation.getWidth());
            setHeight(activeAnimation.getHeight());

            //moveRelative(-118, 6);

            if (getY() != ground_y_)
            {
                setMoveAnimationDelay(0);
                startMoveAnimation(getX(), ground_y_ + 4, 20, EasingEquations::cubicEaseInOut, EasingEquations::cubicEaseIn);
            }

            activeAnimation.setFadeAnimationDelay(40);
            activeAnimation.startFadeAnimation(0, 20, EasingEquations::cubicEaseIn);

            activeAnimation.setUpdateTicksInterval(3);
            activeAnimation.startAnimation(false, false, false);
        }
    }
}

void Ninja::setState(AnimationState newState)
{
    if (!(current_animation_state_ == RUN ||
        newState == RUN || newState == DEAD ||
        (current_animation_state_ == DEAD && newState == ENTERING_GAME) ||
        (current_animation_state_ == RUN && newState == SLIDE)))
    {
        return;
    }

    if (newState == JUMP)
    {
        jump_height_ = 50;
        animation_duration_up_ = 56;
        animation_duration_down_ = 56;
        animation_speed_ = 3;
        tick_counter_ = 0;
    }
    else if (newState == SLIDE)
    {
        jump_height_ = -20;
        animation_duration_up_ = 76;
        animation_duration_down_ = 16;
        animation_speed_ = 3;
        tick_counter_ = 0;
    }
    else
    {
        tick_counter_ = 0;
    }

    current_animation_state_ = newState;
}

void Ninja::setGroundPosition(int ground)
{
    ground_y_ = ground - getHeight() + 10;
    setY(ground_y_);
}

Rect Ninja::getBodyArea()
{
    return Rect(getX() + 1, getY() + 1, getWidth() - 1, getHeight() - 1);
}

void Ninja::reset()
{
    current_animation_state_ = DEAD;
    moveTo(-47, getY());
    setState(ENTERING_GAME);
    invalidate();
}