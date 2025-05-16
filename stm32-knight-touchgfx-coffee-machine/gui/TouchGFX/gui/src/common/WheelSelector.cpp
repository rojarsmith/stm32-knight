#include <gui/common/AppConfig.hpp>
#include <gui/common/WheelSelector.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

/**
 * For 7" Display, coffee machine GUI, 2017 Munich electronics show.
 */

WheelSelector::WheelSelector() :
    currentAnimationState(NO_ANIMATION),
    elementSelectedAction(0),
    //    textMoveEndedCallback(this, &WheelSelector::textMoveEndedHandler)
    imageMoveEndedCallback(this, &WheelSelector::imageMoveEndedHandler)
{
}

WheelSelector::~WheelSelector()
{
}

//void WheelSelector::setup(int width, int height, int textXPosition, int textYPosition, TEXTS wheelText)
void WheelSelector::setup(int width, int height, int imgXPosition, int imgYPosition, const uint16_t img_id)
{
    changeSelect = false;

    setWidth(width);
    setHeight(height);
    setTouchable(true);

    selectedImageYPosition = imgYPosition;

    imgContainer.setPosition(0, 0, getWidth(), getHeight());
    add(imgContainer);

    image.setBitmap(Bitmap(img_id));
    image.setXY(imgXPosition, imgYPosition);
    image.setMoveAnimationEndedAction(imageMoveEndedCallback);
    imgContainer.add(image);

    /**
     * 1 image, size = 113*114
     * 5 images, size = 133*570
     * select target image, get Y = 184
     * When drag down, the topCutOff = 184 + 16 = 200
     * When drag up, the bottomCutOff = 184 - (570 - 114) - 16 = -288
     */

#if   LCD_RESOLUTION == 13
    item_height = 114;
#elif LCD_RESOLUTION == 17
    item_height = 142;
#endif


    CutOffValue = 16;
    topCutOff = selectedImageYPosition + CutOffValue;
    bottomCutOff = selectedImageYPosition - (image.getHeight() - item_height) - CutOffValue;

    //    textContainer.setPosition(0, 0, getWidth(), getHeight());
    //    add(textContainer);
    //
    //    text.setTypedText(TypedText(wheelText));
    //    text.setXY(textXPosition, selectedTextYPosition);
    //    text.setMoveAnimationEndedAction(textMoveEndedCallback);
    //    textContainer.add(text);
    //
    //    spaceBetweenTextRows = text.getTypedText().getFont()->getMinimumTextHeight() * 2; // For blank lines between texts;
    //
    //    // Prepare textSelected (if colors are different)
    //    // Position of textSelectedContainer (y coordinate) updated later in setTextColor()
    //    textSelectedContainer.setPosition(textContainer.getX(), textContainer.getY(), textContainer.getWidth(), 0);
    //    add(textSelectedContainer);
    //
    //    textSelectedBackground.setPosition(0, 0, textSelectedContainer.getWidth(), 0);
    //    textSelectedContainer.add(textSelectedBackground);
    //
    //    textSelected.setTypedText(text.getTypedText());
    //    // Position of textSelected updated later in setTextColor()
    //    textSelected.setXY(text.getX(), text.getY());
    //    textSelected.setMoveAnimationEndedAction(textMoveEndedCallback);
    //    textSelectedContainer.add(textSelected);
    //    // Hide selected text, shown when normal/selected colors differ, see setTextColor()
    //    textSelectedContainer.setVisible(false);
    //
    //    topCutOff = selectedTextYPosition + (spaceBetweenTextRows / 2);
    //    bottomCutOff = topCutOff - text.getHeight() - (spaceBetweenTextRows / 3);
    //
    reset();
}

//void WheelSelector::setTextColor(int16_t normalColor, int16_t selectedColor, uint16_t selectedBackgroundColor, int selectedYOffset, int selectedHeight)
//{
//    text.setColor(normalColor);
//    if (normalColor != selectedColor)
//    {
//        selectedAreaYOffset = selectedYOffset;
//        textSelectedBackground.setHeight(selectedHeight);
//        textSelectedBackground.setColor(selectedBackgroundColor);
//        textSelectedContainer.setY(textContainer.getY() + selectedAreaYOffset);
//        textSelectedContainer.setHeight(selectedHeight);
//        textSelected.setColor(selectedColor);
//        textSelected.setY(text.getY() - selectedAreaYOffset);
//        textSelectedContainer.setVisible(true);
//    }
//    else
//    {
//        textSelectedContainer.setVisible(false);
//    }
//    text.invalidate(); // This also overlaps with textSelected which is therefore also redrawn
//}

void WheelSelector::handleDragEvent(const DragEvent& evt)
{
    if (currentAnimationState == ANIMATING_DRAG)
    {
        lockSlider();
        //        moveText(text.getY() + evt.getDeltaY());
        moveImage(image.getY() + evt.getDeltaY());
    }
}

void WheelSelector::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        if (currentAnimationState != NO_ANIMATION)
        {
            //            text.cancelMoveAnimation();
            //            textSelected.cancelMoveAnimation();

            image.cancelMoveAnimation();
        }
        currentAnimationState = ANIMATING_DRAG;
    }
    else if (evt.getType() == ClickEvent::RELEASED && currentAnimationState == ANIMATING_DRAG)
    {
        snap();
    }
}

void WheelSelector::handleGestureEvent(const GestureEvent& evt)
{
    if (evt.getType() == GestureEvent::SWIPE_VERTICAL)
    {
        currentAnimationState = ANIMATING_GESTURE;

        int delta = evt.getVelocity() * 5;
        //        int newYPosition = text.getY() + delta;
        int newYPosition = image.getY() + delta;
        adjustForBoundries(newYPosition);

        int distanceToMove = newYPosition - image.getY();
        int distanceToMoveABS = (distanceToMove > 0) ? distanceToMove : -distanceToMove;
        int duration = distanceToMoveABS / 10;
        duration = (duration < 2) ? 2 : duration;

        //        animateMoveText(newYPosition, duration, EasingEquations::cubicEaseOut);
        animateMoveImage(newYPosition, duration, EasingEquations::cubicEaseOut);
    }
}

void WheelSelector::snap()
{
    //    int deltaUp = (spaceBetweenTextRows - (text.getY() - selectedTextYPosition)) % spaceBetweenTextRows;
    int deltaUp = (item_height - (image.getY() - selectedImageYPosition)) % item_height;

    // Invert % value for negative values
//    deltaUp = (deltaUp > 0) ? deltaUp : spaceBetweenTextRows + deltaUp;
    deltaUp = (deltaUp > 0) ? deltaUp : item_height + deltaUp;

    //   int deltaDown = spaceBetweenTextRows - deltaUp;
    int deltaDown = item_height - deltaUp;

    if (deltaUp < deltaDown)
    {
        //        animateMoveText(text.getY() + deltaUp, 10, EasingEquations::backEaseInOut);
        animateMoveImage(image.getY() + deltaUp, 10, EasingEquations::backEaseInOut);
    }
    else
    {
        //        animateMoveText(text.getY() - deltaDown, 10, EasingEquations::backEaseInOut);
        animateMoveImage(image.getY() - deltaDown, 10, EasingEquations::backEaseInOut);
    }
    currentAnimationState = ANIMATING_SNAP;
}


int WheelSelector::getSelectedIndex()
{
    //   return (selectedTextYPosition - text.getY()) / spaceBetweenTextRows;
    return (selectedImageYPosition - image.getY()) / item_height;
}

void WheelSelector::setSelectedIndex(int index, int duration, EasingEquation equation)
{
    //    int newYPosition = selectedTextYPosition - (spaceBetweenTextRows * index);
    int newYPosition = selectedImageYPosition - (item_height * index);
    adjustForBoundries(newYPosition);

    if (duration == 0)
    {
        //        moveText(newYPosition);
        moveImage(newYPosition);
    }
    else
    {
        currentAnimationState = ANIMATING_GESTURE;
        //        animateMoveText(newYPosition, duration, equation);
        animateMoveImage(newYPosition, duration, equation);
    }
}

//void WheelSelector::textMoveEndedHandler(const MoveAnimator<TextArea>& text)
void WheelSelector::imageMoveEndedHandler(const MoveAnimator<Image>& image)
{
    if (currentAnimationState == ANIMATING_GESTURE)
    {
        //if (!text.isRunning() && !textSelected.isRunning())
        if (!image.isMoveAnimationRunning())
        {
            snap();
        }
    }
    else if (currentAnimationState == ANIMATING_SNAP)
    {
        currentAnimationState = NO_ANIMATION;
        if (elementSelectedAction && elementSelectedAction->isValid())
        {
            elementSelectedAction->execute(*this, getSelectedIndex());
        }
        changeSelect = true;
    }
    else
    {
        currentAnimationState = NO_ANIMATION;
    }
}


void WheelSelector::adjustForBoundries(int& newYValue)
{
    if (newYValue > topCutOff)
    {
        newYValue = topCutOff;
    }
    else if (newYValue < bottomCutOff)
    {
        newYValue = bottomCutOff;
    }
}

//void WheelSelector::moveText(int newYPosition)
void WheelSelector::moveImage(int newYPosition)
{
    //    adjustForBoundries(newYPosition);
    //
    //    text.moveTo(text.getX(), newYPosition);
    //    if (textSelectedContainer.isVisible())
    //    {
    //        textSelected.moveTo(text.getX(), newYPosition - selectedAreaYOffset);
    //    }

    adjustForBoundries(newYPosition);
    image.moveTo(image.getX(), newYPosition);
}


//void WheelSelector::animateMoveText(int newYPosition, int duration, EasingEquation equation)
void WheelSelector::animateMoveImage(int newYPosition, int duration, EasingEquation equation)
{
    //    text.startMoveAnimation(text.getX(), newYPosition, duration, EasingEquations::linearEaseNone, equation);
    //    if (textSelectedContainer.isVisible())
    //    {
    //        textSelected.startMoveAnimation(text.getX(), newYPosition - selectedAreaYOffset, duration, EasingEquations::linearEaseNone, equation);
    //    }

    image.startMoveAnimation(image.getX(), newYPosition, duration, EasingEquations::linearEaseNone, equation);
}

void WheelSelector::reset()
{
    //    moveText(selectedTextYPosition);
    moveImage(selectedImageYPosition);
}

bool WheelSelector::getWheelDragStatus()
{
    return changeSelect;
}

void WheelSelector::setWheelDragStatus()
{
    changeSelect = false;
}
