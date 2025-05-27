#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/hal/HAL.hpp>

#ifdef SIMULATOR
#include <ctime>
#ifndef _MSC_VER
#include <sys/time.h>
#endif /* _MSC_VER*/
#else

static volatile long lastUs;
extern uint32_t SystemCoreClock;
static int freqMHz;
#endif /* SIMULATOR */


Model::Model() : modelListener(0)
{
#ifndef SIMULATOR
    lastUs = touchgfx::HAL::getInstance()->getCPUCycles();
    freqMHz = SystemCoreClock / 1000000;
#endif
}


void Model::tick()
{
    Time previousTime = currentTime;

#ifdef SIMULATOR
#ifdef _MSC_VER
    time_t rawtime;
    struct tm timenow;
    time(&rawtime);
    localtime_s(&timenow, &rawtime);

    currentTime.hours = timenow.tm_hour;
    currentTime.minutes = timenow.tm_min;
    currentTime.seconds = timenow.tm_sec;
    currentTime.milliseconds = 0;

#else
    timeval timenow;
    gettimeofday(&timenow, NULL);

    currentTime.hours = (timenow.tv_sec / 60 / 60) % 24;
    currentTime.minutes = (timenow.tv_sec / 60) % 60;
    currentTime.seconds = timenow.tv_sec % 60;
    currentTime.milliseconds = timenow.tv_usec / 1000;
#endif  /*_MSC_VER*/
#else
    // Simulated time on target. Requires the mcu instrumentation class
    // to be implemented in a similar manner.
    // Correct implementation is to use the RTC instead but as this
    // is a generic demo this is not possible.

    static int milliseconds = 123456;

    long now = touchgfx::HAL::getInstance()->getCPUCycles();
    milliseconds += (now - lastUs + freqMHz / 2) / freqMHz / 1000;
    lastUs = now;
    currentTime.hours = (milliseconds / 1000 / 60 / 60) % 24;
    currentTime.minutes = (milliseconds / 1000 / 60) % 60;
    currentTime.seconds = (milliseconds / 1000) % 60;
    currentTime.milliseconds = milliseconds % 1000;

#endif /* SIMULATOR */

    if (currentTime.seconds != previousTime.seconds)
    {
        if (modelListener)
        {
            modelListener->timeUpdated(currentTime);
        }
    }
}

void Model::setOvenStartedTime(Time startTime, int hour, int minute, int second)
{
    ovenStartTime = startTime;
    ovenTotalRunningTime.hours = hour;
    ovenTotalRunningTime.minutes = minute;
    ovenTotalRunningTime.seconds = second;
}
