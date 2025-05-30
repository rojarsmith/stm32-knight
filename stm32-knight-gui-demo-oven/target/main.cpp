/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.8.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

using namespace touchgfx;

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/**
 * Add by jcc 2018.02.22
 */
extern "C"              
{
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32746g_edt_lcd.h"
	extern TIM_HandleTypeDef htim12;
}
/**
 * Define the FreeRTOS task priorities and stack sizes
 */
#define configGUI_TASK_PRIORITY                 ( tskIDLE_PRIORITY + 3 )

#define configGUI_TASK_STK_SIZE                 ( 950 )

//#define CANVAS_BUFFER_SIZE (3600)

static void GUITask(void* params)
{
	HAL::getInstance()->setDisplayOrientation(ORIENTATION_PORTRAIT);
    touchgfx::HAL::getInstance()->taskEntry();
}

/**
 * Add by jcc 2018.02.22
 */
static TaskHandle_t xHandleTaskPWM;
void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,
uint16_t pulse);
void vPWMTask( void *pvParameters )
{
    vTaskDelay(200);
    setPWM(htim12,TIM_CHANNEL_2,200-1,180);
    BSP_LCD_DisplayOn();
    vTaskDelete(xHandleTaskPWM);
}

int main(void)
{
    hw_init();
    touchgfx_init();


    /**
     * IMPORTANT NOTICE!
     *
     * The GUI task stack size might need to be increased if creating a new application.
     * The current value of 950 in this template is enough for the examples distributed with
     * TouchGFX, but is often insufficient for larger applications.
     * For reference, the touchgfx_2014 demo uses a stacksize of 2000.
     * If you experience inexplicable hard faults with your custom application, try increasing the
     * stack size.
     *
     * Also note that in FreeRTOS, stack size is in words. So a stack size of 950 actually consumes
     * 3800 bytes of memory. The configTOTAL_HEAP_SIZE define in platform/os/FreeRTOSConfig.h configures
     * the total amount of memory available for FreeRTOS, including task stacks. This value is expressed
     * in BYTES, not words. So, with a stack size of 950, your total heap should be at least 4K.
     */

    // Setup the CanvasWidgetRenderer. ONLY needed if you use CanvasWidgets
    // in your application. The CANVAS_BUFFER_SIZE can be adjusted to match
    // your needs in performance vs. RAM usage. Read more on this in the
    // TouchGFX Manual.
    //static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
    //CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    xTaskCreate(GUITask, (TASKCREATE_NAME_TYPE)"GUITask",
                configGUI_TASK_STK_SIZE,
                NULL,
                configGUI_TASK_PRIORITY,
                NULL);

 /**
 * Add by jcc 2018.02.22
 */
    xTaskCreate(vPWMTask, (TASKCREATE_NAME_TYPE)"PWMTask",
                512,NULL,1,&xHandleTaskPWM );
    
    vTaskStartScheduler();

    for (;;);

}
 /**
 * Add by jcc 2018.02.22
 */
void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,
uint16_t pulse)
{
	HAL_TIM_PWM_Stop(&timer, channel); // stop generation of pwm
	TIM_OC_InitTypeDef sConfigOC;
	timer.Init.Period = period; // set the period duration
	HAL_TIM_PWM_Init(&timer); // reinititialise with new period value
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulse; // set the pulse duration
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
	HAL_TIM_PWM_Start(&timer, channel); // start pwm generation
}
