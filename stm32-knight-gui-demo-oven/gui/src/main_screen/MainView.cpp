#include <gui/main_screen/MainView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

MainView::MainView() :
    currentState(OVEN_STOPPED),
    selectedRecipeIndex(-1),
    ovenContainerMoveAnimationEndedCallback(this, &MainView::ovenContainerMoveAnimationEndedHandler)
{

}

void MainView::setupScreen()
{
    setState(OVEN_STOPPED);

    ovenContainerBottom.setMoveAnimationEndedAction(ovenContainerMoveAnimationEndedCallback);

    temperatureScrollingWheel.setXY(37, 53);
    ovenContainerTop.add(temperatureScrollingWheel);

    humidityScrollingWheel.setXY(306, 53);
    ovenContainerTop.add(humidityScrollingWheel);

    timerScrollingWheel.setXY(37, 620 - ovenContainerTop.getHeight() - ovenContainerCenter.getHeight());
    ovenContainerBottom.add(timerScrollingWheel);

    temperatureScrollingWheel.setSelectedItem(4);
    humidityScrollingWheel.setSelectedItem(6);
    timerScrollingWheel.setSelectedItems(10, 56, 5);
}

void MainView::tearDownScreen()
{

}

void MainView::setState(State newState)
{
    currentState = newState;

    switch (currentState)
    {
    case MainView::OVEN_STOPPED:
        startOvenButton.setBitmaps(Bitmap(BITMAP_BUTTON_START_NORMAL_ID), Bitmap(BITMAP_BUTTON_START_PRESSED_ID));
        enableTopBar(true);


        if (hotairFan.isAnimatedImageRunning())
        {
            hotairFan.stopAnimation();
        }

        if (topBarButtonUpper.getState())
        {
            upperHeat.startAnimation(true, false, false);
        }

        if (topBarButtonLower.getState())
        {
            lowerHeat.startAnimation(true, false, false);
        }

        if (topBarButtonGrill.getState())
        {
            grill.startAnimation(true, false, false);
        }

        break;
    case MainView::OVEN_STARTED:
    {
        presenter->ovenStarted(timerScrollingWheel.getSelectedHour(), timerScrollingWheel.getSelectedMinute(), timerScrollingWheel.getSelectedSecond());

        startOvenButton.setBitmaps(Bitmap(BITMAP_BUTTON_STOP_NORMAL_ID), Bitmap(BITMAP_BUTTON_STOP_PRESSED_ID));

        enableTopBar(false);

        if (topBarButtonHotAir.getState())
        {
            hotairFan.startAnimation(false, true, true);
        }

        if (topBarButtonUpper.getState())
        {
            upperHeat.startAnimation(false, true, false);
        }

        if (topBarButtonLower.getState())
        {
            lowerHeat.startAnimation(false, true, false);
        }

        if (topBarButtonGrill.getState())
        {
            grill.startAnimation(false, true, false);
        }
    }
        break;
    default:
        break;
    }

    startOvenButton.invalidate();
}

void MainView::enableTopBar(bool enable)
{
    topBarButtonUpper.setTouchable(enable);
    topBarButtonLower.setTouchable(enable);
    topBarButtonHotAir.setTouchable(enable);
    topBarButtonGrill.setTouchable(enable);
    topBarButtonRecipes.setTouchable(enable);

    temperatureScrollingWheel.setTouchable(enable);
    humidityScrollingWheel.setTouchable(enable);
    timerScrollingWheel.setTouchable(enable);

    int alpha = enable ? 255 : 80;

    topBarButtonUpper.setAlpha(alpha);
    topBarButtonLower.setAlpha(alpha);
    topBarButtonHotAir.setAlpha(alpha);
    topBarButtonGrill.setAlpha(alpha);
    topBarButtonRecipes.setAlpha(alpha);

    topBarButtonUpper.invalidate();
    topBarButtonLower.invalidate();
    topBarButtonHotAir.invalidate();
    topBarButtonGrill.invalidate();
    topBarButtonRecipes.invalidate();
}

void MainView::bottomBarButtonHandler()
{
    switch (currentState)
    {
    case MainView::OVEN_STOPPED:
        setState(OVEN_STARTED);
        break;
    case MainView::OVEN_STARTED:
        setState(OVEN_STOPPED);
        break;

    default:
        break;
    }
}

void MainView::topBarButtonRecipesPressedHandler()
{
    int animationDuration = 400 / MS_PER_TICK;

    if (recipesContainer.getX() > 0)
    {
        ovenContainerTop.setMoveAnimationDelay(0);
        ovenContainerCenter.setMoveAnimationDelay(0);
        ovenContainerBottom.setMoveAnimationDelay(0);
        ovenContainerTop.startMoveAnimation(ovenContainer.getX(), -ovenContainerTop.getHeight() - 200, animationDuration - 4, EasingEquations::cubicEaseInOut);
        ovenContainerCenter.startMoveAnimation(-ovenContainerCenter.getWidth(), ovenContainerCenter.getY(), animationDuration, EasingEquations::cubicEaseInOut);
        ovenContainerBottom.startMoveAnimation(ovenContainer.getX(), 1024, animationDuration, EasingEquations::cubicEaseInOut);

        recipesContainer.setMoveAnimationDelay(animationDuration - 4);
        recipesContainer.startMoveAnimation(0, recipesContainer.getY(), animationDuration - 4, EasingEquations::cubicEaseInOut);
        selectRecipeButton.setMoveAnimationDelay(2 * animationDuration - 4);
        selectRecipeButton.startMoveAnimation(selectRecipeButton.getX(), 920, 12, EasingEquations::cubicEaseInOut);

    }
    else
    {
        ovenContainerTop.setMoveAnimationDelay(animationDuration - 8);
        ovenContainerCenter.setMoveAnimationDelay(animationDuration + 5);
        ovenContainerBottom.setMoveAnimationDelay(animationDuration + 10);
        ovenContainerTop.startMoveAnimation(ovenContainer.getX(), 0, animationDuration, EasingEquations::cubicEaseInOut);
        ovenContainerCenter.startMoveAnimation(0, ovenContainerCenter.getY(), animationDuration, EasingEquations::cubicEaseInOut);
        ovenContainerBottom.startMoveAnimation(ovenContainer.getX(), ovenContainerCenter.getRect().bottom(), animationDuration, EasingEquations::cubicEaseInOut);

        recipesContainer.setMoveAnimationDelay(0);
        recipesContainer.startMoveAnimation(recipesContainer.getWidth(), recipesContainer.getY(), animationDuration, EasingEquations::cubicEaseInOut);
        selectRecipeButton.setMoveAnimationDelay(0);
        selectRecipeButton.startMoveAnimation(selectRecipeButton.getX(), 1024, 12, EasingEquations::cubicEaseInOut);
    }
}

void MainView::selectRecipeButtonPressedHandler()
{
    selectedRecipeIndex = radioButtonGroup.getSelectedRadioButtonIndex();
        
    switch (radioButtonGroup.getSelectedRadioButtonIndex())
    {
    case -1:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_NORMAL_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_PRESSED_ID));
        break;
    case 0:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_ROAST_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_ROAST_ACTIVE_ID));
        break;
    case 1:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_STEAK_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_STEAK_ACTIVE_ID));
        break;
    case 2:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_CHICKEN_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_CHICKEN_ACTIVE_ID));
        break;
    case 3:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_BURGERS_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_BURGERS_ACTIVE_ID));
        break;
    case 4:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_SEAFOOD_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_SEAFOOD_ACTIVE_ID));
        break;
    case 5:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_FISH_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_FISH_ACTIVE_ID));
        break;
    case 6:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_PRAWNS_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_PRAWNS_ACTIVE_ID));
        break;
    case 7:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_CRAB_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_CRAB_ACTIVE_ID));
        break;
    case 8:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_EGGS_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_EGGS_ACTIVE_ID));
        break;
    case 9:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_PIZZA_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_PIZZA_ACTIVE_ID));
        break;
    case 10:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_SAUSAGES_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_SAUSAGES_ACTIVE_ID));
        break;
    case 11:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_BACON_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_BACON_ACTIVE_ID));
        break;
    case 12:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_FRIES_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_FRIES_ACTIVE_ID));
        break;
    case 13:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_VEGETABLES_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_VEGETABLES_ACTIVE_ID));
        break;
    case 14:
        topBarButtonRecipes.setBitmaps(Bitmap(BITMAP_TOP_ICONS_RECIPES_BREAD_ACTIVE_ID), Bitmap(BITMAP_TOP_ICONS_RECIPES_BREAD_ACTIVE_ID));
        break;
    default:
        break;
    }
    topBarButtonRecipes.invalidate();

    topBarButtonRecipesPressedHandler();
}

void MainView::ovenContainerMoveAnimationEndedHandler(const MoveAnimator<Container>& container)
{
    // When the OvenContainer has been animated in check if a new recipe has been selected
    if (ovenContainer.getX() == 0 && selectedRecipeIndex >= 0)
    {
        int temperatureIndex = 0;
        int humidityIndex = 0;
        int timerHourIndex = 0;
        int timerMinuteIndex = 0;
        int timerSecondIndex = 0;

        // Random selections
        switch (selectedRecipeIndex)
        {
        case 0:
        case 3:
            temperatureIndex = 2;
            humidityIndex = 4;
            timerHourIndex = 8;
            timerMinuteIndex = 48;
            timerSecondIndex = 2;
            break;
        case 5:
        case 14:
            temperatureIndex = 4;
            humidityIndex = 5;
            timerHourIndex = 9;
            timerMinuteIndex = 50;
            timerSecondIndex = 3;
            break;
        case 1:
        case 2:
            temperatureIndex = 2;
            humidityIndex = 2;
            timerHourIndex = 9;
            timerMinuteIndex = 21;
            timerSecondIndex = 4;
            break;
        case 11:
        case 13:
            temperatureIndex = 3;
            humidityIndex = 3;
            timerHourIndex = 10;
            timerMinuteIndex = 20;
            timerSecondIndex = 5;
            break;
        case 4:
        case 6:
            temperatureIndex = 8;
            humidityIndex = 11;
            timerHourIndex = 7;
            timerMinuteIndex = 52;
            timerSecondIndex = 3;
            break;
        case 9:
        case 10:
            temperatureIndex = 6;
            humidityIndex = 12;
            timerHourIndex = 8;
            timerMinuteIndex = 50;
            timerSecondIndex = 4;
            break;
        case 7:
        case 8:
            temperatureIndex = 4;
            humidityIndex = 24;
            timerHourIndex = 10;
            timerMinuteIndex = 11;
            timerSecondIndex = 3;
            break;
        case 12:
        case 15:
            temperatureIndex = 5;
            humidityIndex = 14;
            timerHourIndex = 9;
            timerMinuteIndex = 10;
            timerSecondIndex = 5;
            break;
        default:
            break;
        }

        temperatureScrollingWheel.setSelectedItem(temperatureIndex);
        humidityScrollingWheel.setSelectedItem(humidityIndex);
        timerScrollingWheel.setSelectedItems(timerHourIndex, timerMinuteIndex, timerSecondIndex);

        selectedRecipeIndex = -1;
    }
}

void MainView::updateRemainingTime(Time time, Time ovenStartTime, Time ovenTotalRunningTime)
{
    if (currentState == OVEN_STARTED)
    {
        Time timeElapsed(time - ovenStartTime);
        Time timeRemaining(ovenTotalRunningTime - timeElapsed);

        timerScrollingWheel.setTime(timeRemaining.hours, timeRemaining.minutes, timeRemaining.seconds);

        if (timerScrollingWheel.getSelectedHour() == 0 && 
            timerScrollingWheel.getSelectedMinute() == 0 &&
            timerScrollingWheel.getSelectedSecond() == 0)
        {
            setState(OVEN_STOPPED);
        }
    }
}