#ifndef CUSTOM_CONTAINER_HPP
#define CUSTOM_CONTAINER_HPP
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>
#include <gui/model/ModelListener.hpp>

using namespace touchgfx;

class KnobPointer : public Container
{
public:
    KnobPointer();

    virtual ~KnobPointer() {};
    virtual void handleDragEvent(const DragEvent &evt);

    void setAngle(int angleInDegrees);
    int getValue(void);
    void setValue(int value);

    static const int START_DEGREE = 270;
    static const int START_DIFF_DEGREE = 20;
    static const int END_DEGREE = 90;
    static const int END_DIFF_DEGREE = 20;

private:
    int imageHeight, imageWidth;
    int angleInDegrees;
    int temperaturevalue;

protected:
    AnimationTextureMapper imgKnobPointer;
    void updateBar(int newX, int newY);
};
#endif
