#include <gui/widget/SliderMod.hpp>

namespace touchgfx
{

SliderMod::SliderMod() :
    Container(),
    sliderOrientation(HORIZONTAL),
    currentValue(0),
    valueRangeMin(0),
    valueRangeMax(1),
    indicatorMinPosition(0),
    indicatorMaxPosition(1),
    startValueCallback(0),
    stopValueCallback(0),
    newValueCallback(0)
{
    setTouchable(true);

    // The backgroundSelectedViewPort is a container into which the bitmap for the "filled" background
    // is placed. Containers are viewports, so the dimension of this container controls how
    // much of the filled background is visible.
    backgroundSelectedViewPort.add(backgroundSelected);

    Container::add(background);
    Container::add(backgroundSelectedViewPort);
    Container::add(indicator);

    // Default value range
    setValueRange(0, 100);
}

SliderMod::~SliderMod()
{
}

void SliderMod::setBitmaps(const Bitmap& sliderBackground, const Bitmap& sliderBackgroundSelected, const Bitmap& indicatorBitmap)
{
    assert(sliderBackground.getWidth() == sliderBackgroundSelected.getWidth() &&
           sliderBackground.getHeight() == sliderBackgroundSelected.getHeight() &&
           "Slider::setBitmaps - background and backgroundFilled must have same dimensions");

    background.setBitmap(sliderBackground);
    backgroundSelected.setBitmap(sliderBackgroundSelected);
    indicator.setBitmap(indicatorBitmap);
    backgroundSelectedViewPort.setWidth(backgroundSelected.getWidth());
    backgroundSelectedViewPort.setHeight(backgroundSelected.getHeight());
}

void SliderMod::setBitmaps(const BitmapId sliderBackground, const BitmapId sliderBackgroundSelected, const BitmapId indicatorBitmap)
{
    setBitmaps(Bitmap(sliderBackground), Bitmap(sliderBackgroundSelected), Bitmap(indicatorBitmap));
}

void SliderMod::setupHorizontalSlider(uint16_t backgroundX, uint16_t backgroundY, uint16_t indicatorY, uint16_t indicatorMinX, uint16_t indicatorMaxX)
{
    assert(indicatorMinX < indicatorMaxX && "Slider::setupHorizontalSlider - indicatorMinX must be smaller than indicatorMaxX");

    sliderOrientation = HORIZONTAL;

    background.setXY(backgroundX, backgroundY);
    backgroundSelectedViewPort.setXY(backgroundX, backgroundY);
    backgroundSelected.setXY(0, 0);
    indicator.setY(indicatorY);

    uint16_t backgroundWidth = backgroundX + static_cast<uint16_t>(background.getWidth());
    uint16_t indicatorWidth = indicatorMaxX + static_cast<uint16_t>(indicator.getWidth());
    int16_t newWidth = static_cast<int16_t>(MAX(backgroundWidth, indicatorWidth));

    uint16_t backgroundHeight = backgroundY + static_cast<uint16_t>(background.getHeight());
    uint16_t indicatorHeight = indicatorY + static_cast<uint16_t>(indicator.getHeight());
    int16_t newHeight = static_cast<int16_t>(MAX(backgroundHeight, indicatorHeight));

    indicatorMinPosition = indicatorMinX;
    indicatorMaxPosition = indicatorMaxX;

    setWidth(newWidth);
    setHeight(newHeight);

    setValue(currentValue);
}

void SliderMod::setupVerticalSlider(uint16_t backgroundX, uint16_t backgroundY, uint16_t indicatorX, uint16_t indicatorMinY, uint16_t indicatorMaxY)
{
    assert(indicatorMinY < indicatorMaxY && "Slider::setupVerticalSlider - indicatorMinY must be smaller than indicatorMaxY");

    sliderOrientation = VERTICAL;

    background.setXY(backgroundX, backgroundY);
    backgroundSelectedViewPort.setXY(backgroundX, backgroundY);
    indicator.setX(indicatorX);

    uint16_t backgroundWidth = backgroundX + static_cast<uint16_t>(background.getWidth());
    uint16_t indicatorWidth = indicatorX + static_cast<uint16_t>(indicator.getWidth());
    int16_t newWidth = static_cast<int16_t>(MAX(backgroundWidth, indicatorWidth));

    uint16_t backgroundHeight = backgroundY + static_cast<uint16_t>(background.getHeight());
    uint16_t indicatorHeight = indicatorMaxY + static_cast<uint16_t>(indicator.getHeight());
    int16_t newHeight = static_cast<int16_t>(MAX(backgroundHeight, indicatorHeight));

    indicatorMinPosition = indicatorMinY;
    indicatorMaxPosition = indicatorMaxY;

    setWidth(newWidth);
    setHeight(newHeight);

    setValue(currentValue);
}

void SliderMod::setValue(int value)
{
    updateIndicatorPosition(valueToPosition(value));
}

void SliderMod::handleClickEvent(const ClickEvent& evt)
{
    if ((evt.getType() == ClickEvent::PRESSED) || (evt.getType() == ClickEvent::RELEASED))
    {
        // Communicate the start value if a listener is registered
        if ((evt.getType() == ClickEvent::PRESSED) && (startValueCallback != 0) && startValueCallback->isValid())
        {
            startValueCallback->execute(*this, currentValue);
        }

        if (sliderOrientation == HORIZONTAL)
        {
            updateIndicatorPosition(evt.getX() - getIndicatorRadius());
        }
        else
        {
            updateIndicatorPosition(evt.getY() - getIndicatorRadius());
        }

        // Communicate the stop value if a listener is registered
        if ((evt.getType() == ClickEvent::RELEASED) && (stopValueCallback != 0) && stopValueCallback->isValid())
        {
            stopValueCallback->execute(*this, currentValue);
        }
    }
}

void SliderMod::handleDragEvent(const DragEvent& evt)
{
    if (sliderOrientation == HORIZONTAL)
    {
        updateIndicatorPosition(evt.getNewX() - getIndicatorRadius());
    }
    else
    {
        updateIndicatorPosition(evt.getNewY() - getIndicatorRadius());
    }
}

int16_t SliderMod::valueToPosition(int value) const
{
    value = MAX(MIN(valueRangeMax, value), valueRangeMin);

    int coordinateOffset = ((value - valueRangeMin) * (getIndicatorPositionRangeSize() + 1)) / getValueRangeSize();

    int result = indicatorMinPosition + coordinateOffset;

    if (sliderOrientation == VERTICAL)
    {
        // Vertical slider grows as the position decreases so invert the coordinate
        result = indicatorMinPosition + (indicatorMaxPosition - result);
    }

    return result;
}

int SliderMod::positionToValue(int16_t position) const
{
    int result;

    if (position == indicatorMinPosition)
    {
        // Ensure that min coordinate always results in min value
        result = valueRangeMin;
    }
    else if (position == indicatorMaxPosition)
    {
        // Ensure that max coordinate always results in max value
        result = valueRangeMax;
    }
    else
    {
        int rounding = getIndicatorPositionRangeSize() / 2;
        int valueOffset = (((position - indicatorMinPosition) * getValueRangeSize()) + rounding) / getIndicatorPositionRangeSize();

        result = valueRangeMin + valueOffset;
    }

    if (sliderOrientation == VERTICAL)
    {
        // Vertical slider grows as the position decreases so invert the value
        result = valueRangeMin + (valueRangeMax - result);
    }

    return result;
}

void SliderMod::updateIndicatorPosition(int16_t position)
{
	//Fixex touch shift bug.
	position += shift_x;

    // Cut off positions outside the slider area
    position = MIN(MAX(position, indicatorMinPosition), indicatorMaxPosition);

    if (sliderOrientation == HORIZONTAL)
    {
        indicator.moveTo(position, indicator.getY());

        backgroundSelectedViewPort.invalidate();
        backgroundSelectedViewPort.setWidth((position - backgroundSelectedViewPort.getX()) + getIndicatorRadius());
        backgroundSelectedViewPort.invalidate();
    }
    else
    {
        indicator.moveTo(indicator.getX(), position);

        backgroundSelectedViewPort.invalidate();
        int16_t newViewPortHeight = background.getRect().bottom() - (position + getIndicatorRadius());
        backgroundSelectedViewPort.setPosition(backgroundSelectedViewPort.getX(), position + getIndicatorRadius(), backgroundSelectedViewPort.getWidth(), newViewPortHeight);
        backgroundSelected.setY(-(backgroundSelected.getHeight() - newViewPortHeight));
        backgroundSelectedViewPort.invalidate();
    }

    currentValue = positionToValue(position);

    // Communicate the new value if a listener is registered
    if ((newValueCallback != 0) && newValueCallback->isValid())
    {
        newValueCallback->execute(*this, currentValue);
    }
}

uint16_t SliderMod::getIndicatorRadius() const
{
    uint16_t result;

    if (sliderOrientation == HORIZONTAL)
    {
        result = indicator.getWidth() / 2;
    }
    else
    {
        result = indicator.getHeight() / 2;
    }

    return result;
}

void SliderMod::setValueRange(int minValue, int maxValue, int newValue)
{
    assert(minValue < maxValue && "Slider::setValueRange - minValue must be smaller than maxValue");

    valueRangeMin = minValue;
    valueRangeMax = maxValue;

    setValue(newValue);
}

void SliderMod::setValueRange(int minValue, int maxValue)
{
    int newValue = currentValue;

    if (currentValue < minValue)
    {
        newValue = minValue;
    }
    else if (currentValue > maxValue)
    {
        newValue = maxValue;
    }

    setValueRange(minValue, maxValue, newValue);
}

int SliderMod::getIndicatorPositionRangeSize() const
{
    return indicatorMaxPosition - indicatorMinPosition;
}

int SliderMod::getValueRangeSize() const
{
    return valueRangeMax - valueRangeMin;
}

} // namespace touchgfx
