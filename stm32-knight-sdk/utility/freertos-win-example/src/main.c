/*
 * This is a simple main that will start the FreeRTOS-Kernel and run a periodic task
 * that only delays if compiled with the template port, this project will do nothing.
 * For more information on getting started please look here:
 * https://freertos.org/FreeRTOS-quick-start-guide.html
 */

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

/* Standard includes. */
#include <stdio.h>

/*-----------------------------------------------------------*/

typedef struct
{
    int id;
} DataItem;

static void maTask(void *parameters);
static void bgTask(void *parameters);

/*-----------------------------------------------------------*/

QueueHandle_t xQueue;

static void maTask(void *parameters)
{
    /* Unused parameters. */
    (void)parameters;
    long count = 0;

    for (;;)
    {
        /* Example Task Code */
        vTaskDelay(100); /* delay 100 ticks */
        (void)printf("ma Running %d\n", count);

        DataItem item = {count};
        if (xQueueSend(xQueue, &item, portMAX_DELAY) != pdPASS)
        {
            (void)printf("Push to queue error\n");
        }

        count++;
    }
}

static void bgTask(void *parameters)
{
    /* Unused parameters. */
    (void)parameters;
    long count = 0;

    for (;;)
    {
        /* Example Task Code */
        vTaskDelay(300); /* delay 100 ticks */
        (void)printf("bg Running %d\n", count);

        UBaseType_t uxNumberOfItems;
        uxNumberOfItems = uxQueueMessagesWaiting(xQueue);

        for (UBaseType_t i = 0; i < uxNumberOfItems; i++)
        {
            DataItem receivedItem;
            if (xQueueReceive(xQueue, &receivedItem, portMAX_DELAY) == pdTRUE)
            {
                (void)printf("bg received id=%d\n", receivedItem.id);
            }
        }

        count++;
    }
}
/*-----------------------------------------------------------*/

void main(void)
{
    xQueue = xQueueCreate(2, sizeof(DataItem));
    if (xQueue == NULL)
    {
        (void)printf("Create queue error\n");
    }

    static StaticTask_t maTaskTCB;
    static StackType_t maTaskStack[configMINIMAL_STACK_SIZE];
    static StaticTask_t bgTaskTCB;
    static StackType_t bgTaskStack[configMINIMAL_STACK_SIZE];

    (void)printf("Example FreeRTOS Project\n");

    (void)xTaskCreateStatic(maTask,
                            "ma",
                            configMINIMAL_STACK_SIZE,
                            NULL,
                            configMAX_PRIORITIES - 1U,
                            &(maTaskStack[0]),
                            &(maTaskTCB));

    (void)xTaskCreateStatic(bgTask,
                            "bg",
                            configMINIMAL_STACK_SIZE,
                            NULL,
                            configMAX_PRIORITIES - 2U,
                            &(bgTaskStack[0]),
                            &(bgTaskTCB));

    /* Start the scheduler. */
    vTaskStartScheduler();

    for (;;)
    {
        /* Should not reach here. */
    }
}
/*-----------------------------------------------------------*/

#if (configCHECK_FOR_STACK_OVERFLOW > 0)

void vApplicationStackOverflowHook(TaskHandle_t xTask,
                                   char *pcTaskName)
{
    /* Check pcTaskName for the name of the offending task,
     * or pxCurrentTCB if pcTaskName has itself been corrupted. */
    (void)xTask;
    (void)pcTaskName;
}

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
/*-----------------------------------------------------------*/
