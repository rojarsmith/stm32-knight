#include <gui/fan_screen/KnobPointer.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/canvas/CWRUtil.hpp>
#include <stdio.h>

KnobPointer::KnobPointer()
{
    setTouchable(true);
    // setVisible(true);
    imgKnobPointer.setBitmap(Bitmap(BITMAP_SCALEPOINTER_ID));
    imgKnobPointer.setXY(0, 0);
    imgKnobPointer.setHeight(262);
    imgKnobPointer.setWidth(262);
    /*imgKnobPointer.setHeight(158); // 480x272
    imgKnobPointer.setWidth(158);*/
    imageHeight = imgKnobPointer.getBitmap().getHeight();
    imageWidth = imgKnobPointer.getBitmap().getWidth();
    imgKnobPointer.setCameraDistance(498.0f); // 800x480
    //imgKnobPointer.setCameraDistance(300.0f);
    imgKnobPointer.setOrigo(imgKnobPointer.getBitmapPositionX() + imageWidth / 2,
                            imgKnobPointer.getBitmapPositionY() + imageHeight / 2, imgKnobPointer.getCameraDistance());
    imgKnobPointer.setCamera(imgKnobPointer.getBitmapPositionX() + imageWidth / 2,
                             imgKnobPointer.getBitmapPositionY() + imageHeight / 2);
    imgKnobPointer.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);
    add(imgKnobPointer);
    temperaturevalue = 0;
}

void KnobPointer::handleDragEvent(const DragEvent &evt)
{
    updateBar(evt.getNewX(), evt.getNewY());
}

//              | 0 degree
//              |
//  0 PI        |
//  ------------+----------
//              |
//              |
//              |
// clock direction
void KnobPointer::updateBar(int newX, int newY)
{
    int centerX, centerY;
    int min_length;

    centerX = (int)imgKnobPointer.getBitmapPositionX() + imageWidth / 2;
    centerY = (int)imgKnobPointer.getBitmapPositionY() + imageHeight / 2;

    int16_t vx = newX - centerX;
    int16_t vy = newY - centerY;
    min_length = centerX * 1 / 4;

    int length;
    int angleInDegrees = CWRUtil::angle<int>(vx, vy, length);
#ifndef __ICCARM__

#endif
    if (length < min_length)
    {
        return;
    }

    if ((angleInDegrees >= START_DEGREE) && (angleInDegrees < 360))
    {
        temperaturevalue = (angleInDegrees / 9) - 20;
        setAngle(angleInDegrees);
    }
    else if ((angleInDegrees <= END_DEGREE) && (angleInDegrees >= 0))
    {
        temperaturevalue = (angleInDegrees / 9) + 20;
        setAngle(angleInDegrees);
    }
    else if ((angleInDegrees >= (START_DEGREE - START_DIFF_DEGREE)) && (angleInDegrees <= START_DEGREE))
    {
        temperaturevalue = 10;
        angleInDegrees = START_DEGREE;
        setAngle(angleInDegrees);
    }
    else if ((angleInDegrees > END_DEGREE) && (angleInDegrees < (90 + END_DIFF_DEGREE)))
    {
        temperaturevalue = 30;
        angleInDegrees = END_DEGREE;
        setAngle(angleInDegrees);
    }
    else
    {
        ;
        ;
    }
}

void KnobPointer::setAngle(int Degree)
{
    float value = ((float)(Degree) / (float)180) * (float)3.14159;

    // angleInDegrees = Degree;

#ifndef __ICCARM__
    printf("rotate=%f\n", value);
#endif
    imgKnobPointer.updateAngles(0.0F, 0.0F, value);
}

int KnobPointer::getValue(void)
{
    return temperaturevalue;
}

void KnobPointer::setValue(int value)
{
    temperaturevalue = value;
    if (temperaturevalue == 17)
    {
        angleInDegrees = 333;
    }
    else if (temperaturevalue == 22)
    {
        angleInDegrees = 18;
    }
    else if (temperaturevalue == 27)
    {
        angleInDegrees = 63;
    }
    setAngle(angleInDegrees);
}
