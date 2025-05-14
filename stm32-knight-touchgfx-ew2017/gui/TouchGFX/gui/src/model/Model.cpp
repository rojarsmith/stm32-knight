#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#if !defined(_MSC_VER) && !defined(SIMULATOR)
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#endif

extern "C"
{
#if !defined(_MSC_VER) && !defined(SIMULATOR)
    extern xQueueHandle xQueueRX;
    xQueueHandle xQueueTX;
#endif

    typedef struct
    {
        uint8_t mode_id;
        uint8_t data[9];
    } mdata;
    mdata mrx;
}

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
#if !defined(_MSC_VER) && !defined(SIMULATOR)
    if (xQueueTX != 0)
    {
        if (xQueueReceive(xQueueTX, &mrx, 0) == pdPASS)
        {
            if (mrx.mode_id == MODE_PWMG)
            {
                // TODO: Implement receive queue
            }
        }
    }
#endif
}

uint8_t Model::getdata(mode_ID id, uint8_t index)
{
    if ((id > 0) && (id <= 6) && (index < 10))
    {
        switch (id)
        {
        case MODE_FAN:
            return fan[index];
            break;
        case MODE_PWM:
            return pwm[index];
            break;
        case MODE_PWMG:
            pwmg[0] = MODE_PWMG;
            pwmg[index] = 0;
            break;
        default:
            break;
        }
    }

    return 0;
}

void Model::setdata(mode_ID id, uint8_t index, uint8_t value)
{
    if (id == MODE_LED)
    {
    }
    if ((id > 0) && (id <= 6) && (index < 10))
    {
        switch (id)
        {
            // case MODE_LED:
            //     led[index] = value;
            //     break;

        case MODE_FAN:
            fan[index] = value;
            break;

        case MODE_MP3:
            mp3[index] = value;
            break;

        // case MODE_PNT:
        //     food[index] = value;
        //     break;
        case MODE_PWM:
            pwm[0] = MODE_PWM;
            pwm[index] = value;
            break;
        case MODE_RECV:

            break;
        default:
            break;
        }
    }
}

bool Model::senddata(mode_ID id)
{
    if ((id > 0) && (id <= 6))
    {
        switch (id)
        {
        case MODE_PWM:
            mrx.mode_id = pwm[0];
            for (uint8_t i = 0; i < 9; i++)
            {
                mrx.data[i] = pwm[i + 1];
            }

            break;
        default:
            break;
        }
#if !defined(_MSC_VER) && !defined(SIMULATOR)
        xQueueSend(xQueueRX, &mrx, 0);
#endif
        return 1;
    }
    else
    {
        return 0;
    }
}

bool Model::senddata(mode_ID id, int playmode, int songValue, int playstatus, int volumeValue)
{
    if ((id > 0) && (id <= 5))
    {
        switch (id)
        {
        case MODE_LED:
            // mrx.mode_id = led[0];
            // mrx.data[0] = led[1];
            // mrx.data[1] = led[2];
            // mrx.data[2] = led[3];
            //                 for (uint8_t i = 0; i < 10; i++)
            //                 {
            //                     xQueueSend(xQueueRX,(void *)&led[i], (TickType_t)10);
            //                 }
            //                 for (uint8_t i = 0; i < 9; i++)
            //                 {
            //                     mrx.data[i] = led[i + 1];
            //                 }

            break;

        case MODE_FAN:
            // mrx.mode_id = fan[0];
            // mrx.data[0] = fan[1];
            //                 for (uint8_t i = 0; i < 10; i++)
            //                 {
            //                     xQueueSend(xQueueRX,(void *)&fan[i], (TickType_t)10);
            //                 }
            //                 for (uint8_t i = 0; i < 9; i++)
            //                 {
            //                     mrx.data[i] = fan[i + 1];
            //                 }
            break;

        case MODE_MP3:
            if (playstatus == 2)
            {
                return 1;
            }

            // mrx.mode_id = mp3[0];
            // mrx.data[0] = mp3[1];
            // mrx.data[1] = mp3[2];
            // if (mp3[1] == 9) mrx.mode_id = 6;
            //                 for (uint8_t i = 0; i < 10; i++)
            //                 {
            //                     xQueueSend(xQueueRX,(void *)&mp3[i], (TickType_t)10);
            //                 }
            //                 for (uint8_t i = 0; i < 9; i++)
            //                 {
            //                     mrx.data[i] = mp3[i + 1];
            //                 }
            mp3[1] = 0;
            break;

        case MODE_PNT:
            // mrx.mode_id = food[0];
            //                 for (uint8_t i = 0; i < 10; i++)
            //                 {
            //                     xQueueSend(xQueueRX,(void *)&food[i], (TickType_t)10);
            //                 }
            // for (uint8_t i = 0; i < 9; i++)
            //{
            //     mrx.data[i] = food[i + 1];
            // }
            break;
        case MODE_PWM:
            mrx.mode_id = pwm[0];
            for (uint8_t i = 0; i < 9; i++)
            {
                mrx.data[i] = pwm[i + 1];
            }
            break;
        case MODE_RECV:
            // mrx.mode_id = MODE_RECV;
            mrx.mode_id = 6;
            for (uint8_t i = 0; i < 9; i++)
            {
                mrx.data[i] = 0;
            }
            // dbg1 = 0;

            break;
        default:
            break;
        }
#if !defined(_MSC_VER) && !defined(SIMULATOR)
        // xQueueSend(xQueueRX, &mrx, 0);
        // xQueueSend(xQueueRX, &mrx, 100);

#endif
        //
        return 1;
    }
    else
    {
        return 0;
    }
}
