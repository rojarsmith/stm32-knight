#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifdef SIMULATOR
#include <ctime>
#else
#include "FreeRTOS.h"
#include "queue.h"   
#include "task.h"    
#endif

static volatile long lastUs;
#if defined(_MSC_VER) || defined(SIMULATOR)
uint32_t SystemCoreClock = 200 * 1000000;
#else
extern uint32_t SystemCoreClock;
#endif
static int freqMHz;

static uint8_t mcuLoadLast = 0;

extern "C"
{

#ifndef SIMULATOR
	extern xQueueHandle xQueueRX;	
#endif
	typedef struct
	{
		uint16_t id;
		uint16_t data[9];
	}msgData;

	msgData msgRX;
}


Model::Model()
	:
	modelListener(0),
	mcuLoadActive(true)
{
#ifdef SIMULATOR
	freqMHz = SystemCoreClock / 1000000;
#else
	lastUs = touchgfx::HAL::getInstance()->getCPUCycles();
	freqMHz = SystemCoreClock / 1000000;

	//xQueueTX = xQueueCreate(1, sizeof(msgData));
	//xQueueReset(xQueueTX);
#endif
}

void Model::tick()
{
	previousTime = currentTime;

#ifdef SIMULATOR	
	time_t rawtime;
	struct tm timenow;
	time(&rawtime);
	localtime_s(&timenow, &rawtime);

	currentTime.hours =   timenow.tm_hour;
	currentTime.minutes = timenow.tm_min;
	currentTime.seconds = timenow.tm_sec;
	currentTime.milliseconds = 0;
#else
	uint8_t mcuLoadPct = touchgfx::HAL::getInstance()->getMCULoadPct();
	if (mcuLoadLast != /*mcu_load_pct*/ mcuLoadPct)
	{
		mcuLoadLast = mcuLoadPct;
		modelListener->mcuLoadUpdated(mcuLoadLast);
	}

	static int milliseconds = 123456;
	long now = touchgfx::HAL::getInstance()->getCPUCycles();
	milliseconds += (now - lastUs + freqMHz / 2) / freqMHz / 1000;
	lastUs = now;
	currentTime.hours = (milliseconds / 1000 / 60 / 60) % 24;
	currentTime.minutes = (milliseconds / 1000 / 60) % 60;
	currentTime.seconds = (milliseconds / 1000) % 60;
	currentTime.milliseconds = milliseconds % 1000;
#endif

	if (currentTime.seconds != previousTime.seconds)
	{
		if (modelListener)
		{
			modelListener->timeUpdated(currentTime);
		}
	}
}

void Model::setData(uint16_t value)
{
	msgRX.id = 1;
	msgRX.data[0] = value;

#ifndef SIMULATOR
	xQueueSend(xQueueRX, &msgRX, 0);
#endif
}

uint16_t Model::readData()
{
	return mcuLoadLast;
}
