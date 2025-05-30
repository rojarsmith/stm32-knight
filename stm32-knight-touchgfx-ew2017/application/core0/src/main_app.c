/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Rojar Smith
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Rojar Smith.
 * All rights reserved.
 *
 ******************************************************************************
 */

#include "main.h"
#include "cmsis_os.h"
#include "app_touchgfx.h"
#include "otm8009a.h"
#if !defined(_MSC_VER) && !defined(SIMULATOR)
#include "queue.h"
#endif

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef void (*pFunction)(void);

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
MDMA_HandleTypeDef hmdma_jpeg_infifo_th;
MDMA_HandleTypeDef hmdma_jpeg_outfifo_th;
SDRAM_HandleTypeDef hsdram1;
extern QSPI_HandleTypeDef hqspi;
DMA2D_HandleTypeDef hdma2d;
DSI_HandleTypeDef hdsi;
LTDC_HandleTypeDef hltdc;
CRC_HandleTypeDef hcrc;
JPEG_HandleTypeDef hjpeg;

OTM8009A_Object_t OTM8009AObj;
OTM8009A_IO_t IOCtx;

/* Definitions for TouchGFXTask */
osThreadId_t guiTaskHandle;
const osThreadAttr_t guiTask_attributes = {
    .name = "GUITask",
    .stack_size = 3048 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};
/* Definitions for videoTask */
osThreadId_t rtcTaskHandle;
const osThreadAttr_t rtcTask_attributes = {
    .name = "RTCTask",
    .stack_size = 1000 * 4,
    .priority = (osPriority_t)osPriorityLow,
};

#if !defined(_MSC_VER) && !defined(SIMULATOR)
// extern TIM_HandleTypeDef htim12;

xQueueHandle xQueueRX;
extern xQueueHandle xQueueTX;

void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);

typedef struct
{
    uint8_t mode_id;
    uint8_t data[9];
} xdata;
xdata trx,ttx;
#endif

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);
static void SystemClock_Config(void);
static void MX_USART1_UART_Init(void);
static void MX_GPIO_Init(void);
static void MX_MDMA_Init(void);
static void MX_FMC_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_DMA2D_Init(void);
static void MX_DSIHOST_DSI_Init(void);
static void MX_LTDC_Init(void);
static void MX_CRC_Init(void);
static void MX_JPEG_Init(void);
static void Delay_MS(uint32_t ms);
static void Jump_To_Boot(uint32_t address);
static void GUITask(void *params);
static void RTCTask(void *params);
void TouchGFX_Task(void *argument);

int main(void)
{
    // volatile int dbgbp_0 = 0;
    // dbgbp_0++;
// shift for HAL, FMC, FreeRTOS
#if FLASH_ORIGIN == ADDRESS_APP_0
    SCB->VTOR = (unsigned long)ADDRESS_APP_0;
#else
    SCB->VTOR = (unsigned long)ADDRESS_APP_1;
#endif

    MPU_Config();
    CPU_CACHE_Enable();
    HAL_Init();
    SystemClock_Config();

    /* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
     HSEM notification */
    /*HW semaphore Clock enable*/
    // __HAL_RCC_HSEM_CLK_ENABLE();
    /*Take HSEM */
    // HAL_HSEM_FastTake(HSEM_ID_0);
    /*Release HSEM in order to notify the CPU2(CM4)*/
    // HAL_HSEM_Release(HSEM_ID_0, 0);

    MX_USART1_UART_Init();

    BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);

    MX_GPIO_Init();
    MX_MDMA_Init();
    MX_FMC_Init();
    MX_QUADSPI_Init();
    MX_DMA2D_Init();
    MX_DSIHOST_DSI_Init();
    MX_LTDC_Init();
    MX_CRC_Init();
    MX_JPEG_Init();
    MX_TouchGFX_Init();

    //	xTaskCreate(GUITask, "GUITask",
    //	configGUI_TASK_STK_SIZE,
    //	NULL,
    //	configGUI_TASK_PRIORITY,
    //	NULL);
    //
    //	xTaskCreate(RTCTask, "RTCTask", 512,
    //	NULL, configGUI_TASK_PRIORITY - 1,
    //	NULL);
    //
    //	vTaskStartScheduler();

    uint32_t address = *(__IO uint32_t *)FLASH_ORIGIN; // 0x24080000
    printf("Value at address 0x%08X: 0x%08X\n", (unsigned int)FLASH_ORIGIN, (unsigned int)address);
    printf("FLASH_ORIGIN = 0x%08X\r\n", FLASH_ORIGIN);

    osKernelInitialize();
    /* creation of TouchGFXTask */
    guiTaskHandle = osThreadNew(TouchGFX_Task, NULL, &guiTask_attributes);
    // guiTaskHandle = osThreadNew(GUITask, NULL, &guiTask_attributes);

    /* creation of videoTask */
    rtcTaskHandle = osThreadNew(RTCTask, NULL, &rtcTask_attributes);

    xQueueRX = xQueueCreate(5, sizeof(xdata));

    osKernelStart();
    printf("Post osKernelStart()\r\n");

    // Will not arrive
    for (;;)
    {
        printf("IAP Demo - App\r\n");
#if (FLASH_ORIGIN == ADDRESS_APP_0)
        printf("Ver A\r\n");
#elif (FLASH_ORIGIN == ADDRESS_APP_1)
        printf("Ver B\r\n");
#endif
        Delay_MS(3000);
        if ((BSP_PB_GetState(BUTTON_WAKEUP) == GPIO_PIN_SET))
        {
            printf("Button `Wakeup`\r\n");
            Jump_To_Boot(ADDRESS_BOOTLOADER);
        }
    }
}

void Delay_MS(uint32_t ms)
{
    uint32_t tickstart = HAL_GetTick();
    while ((HAL_GetTick() - tickstart) < ms)
    {
        // Empty loop or low power mode
    }
}

static void Jump_To_Boot(uint32_t base_address)
{
    // Make the display black //

    // Step 1: Clear framebuffer (the screen is black)
    memset((void *)0xD0000000, 0x00, 800 * 480 * 3); // RGB888

    // Step 2: Display a black screen for one frame (send image)
    __HAL_LTDC_ENABLE(&hltdc);
    HAL_Delay(30); // >16ms wait for image refresh
    __HAL_LTDC_DISABLE(&hltdc);

    // Step 3: Turn off the panel display (even if the previous frame was not black)
    HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, OTM8009A_CMD_DISPOFF, 0x00);

    // Step 4: Wait for a few frames to make the panel actually black
    HAL_Delay(50);

    uint32_t jumpAddress;
    pFunction jumpToApplication;

    // This is testing what is AT the address,
    // which should be an initial stack pointer,
    // that needs to be in RAM
    // The first value stored in the vector table
    // is the reset value of the stack pointer
    // AXI SRAM (RAM_D1): 0x24000000~0x2407FFFF(512kb)
    // 0x24080000 reserved
    // 2408 0000 = 00100100000010000000000000000000
    // 2BF7 FFFF = 00101011111101111111111111111111
    // if ((address & 0x2BF7FFFF) == 0x20000000)
    if ((*(__IO uint32_t *)base_address & 0x2BF7FFFF) == 0x20000000)
    {
        /*
         * Since the bootloader and app use different system clock architectures,
         * jumping back is very complicated, 
         * and it is simpler to directly restart the system.
         */ 
        __disable_irq();    // Disable interrupt
        NVIC_SystemReset(); // Software restart MCU

        // The following code not work //

        //
        // Disable all interrupts
        //
        // NVIC->ICER[0] = 0xFFFFFFFF;
        // NVIC->ICER[1] = 0xFFFFFFFF;
        // NVIC->ICER[2] = 0xFFFFFFFF;
        //
        // Clear pendings
        //
        NVIC->ICPR[0] = 0xFFFFFFFF;
        NVIC->ICPR[1] = 0xFFFFFFFF;
        NVIC->ICPR[2] = 0xFFFFFFFF;

        SysTick->CTRL = 0; // Disable SysTick
        SysTick->LOAD = 0;
        SysTick->VAL = 0;

        // Set vector table
        SCB->VTOR = (unsigned long)base_address;

        jumpAddress = *(__IO uint32_t *)(base_address + 4);
        jumpToApplication = (pFunction)jumpAddress;
        __set_MSP(*(__IO uint32_t *)base_address);
        jumpToApplication();
    }
}

__attribute__((unused)) static void GUITask(void *params)
{
    const TickType_t xDelay2300ms = pdMS_TO_TICKS(2300UL);
    TickType_t xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        // printf("GUITask running...\r\n");
        printf("[Tick %lu] GUITask running...\r\n", xLastWakeTime);
        vTaskDelayUntil(&xLastWakeTime, xDelay2300ms);
    }
}

__attribute__((unused)) static void RTCTask(void *params)
{
    uint32_t
        address = *(__IO uint32_t *)ADDRESS_BOOTLOADER; // 0x24080000
    printf("Value at address 0x%08X: 0x%08X\n",
           (unsigned int)ADDRESS_BOOTLOADER, (unsigned int)address);

    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000UL);

#if !defined(_MSC_VER) && !defined(SIMULATOR)
    // setPWM(htim12, TIM_CHANNEL_2, 200-1, 20);
    LCD_SetBrightness(100); // CABC, 0~100
#endif

    for (;;)
    {
        printf("RTCTask running...\r\n");
        vTaskDelay(xDelay1000ms);
#if (FLASH_ORIGIN == 0x080A0000)
        printf("Ver B\r\n");
#endif
        if ((BSP_PB_GetState(BUTTON_WAKEUP) == GPIO_PIN_SET))
        {
            printf("Button `Wakeup`\r\n");
            Jump_To_Boot(ADDRESS_BOOTLOADER);
        }

#if !defined(_MSC_VER) && !defined(SIMULATOR)
        taskENTER_CRITICAL();

        if (xQueueRX != 0) 
        {
            if (xQueueReceive(xQueueRX, &trx, 0) == pdPASS)
            {
                if(trx.mode_id == 6)
                {
                    // int blv = trx.data[0] * 10;
                    int blv = trx.data[0];
                    LCD_SetBrightness(blv);
                }
                else if(trx.mode_id == 7)
                {
                    ttx.mode_id = 7;
                    // ttx.data[1] = LCD_GetBrightness(); // OTM8009A not support
                    xQueueSend(xQueueTX, &ttx, 500);
                }
            }
        }

        taskEXIT_CRITICAL();
#endif

    }
}

/**
 * @brief  Function implementing the TouchGFXTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_TouchGFX_Task */
__weak void TouchGFX_Task(void *argument)
{
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END 5 */
}

uint32_t getScreenWidthReal()
{
    return OTM8009A_800X480_WIDTH;
}

#if !defined(_MSC_VER) && !defined(SIMULATOR)
void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse)
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
#endif

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOJ,
                      LCD_BL_Pin | FRAME_RATE_Pin | RENDER_TIME_Pin | VSYNC_FREQ_Pin,
                      GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(MCU_ACTIVE_GPIO_Port, MCU_ACTIVE_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : LCD_BL_Pin FRAME_RATE_Pin RENDER_TIME_Pin VSYNC_FREQ_Pin */
    GPIO_InitStruct.Pin = LCD_BL_Pin | FRAME_RATE_Pin | RENDER_TIME_Pin | VSYNC_FREQ_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    /*Configure GPIO pin : PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : LCD_RESET_Pin */
    GPIO_InitStruct.Pin = LCD_RESET_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LCD_RESET_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : MCU_ACTIVE_Pin */
    GPIO_InitStruct.Pin = MCU_ACTIVE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(MCU_ACTIVE_GPIO_Port, &GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

/**
 * Enable MDMA controller clock
 */
static void MX_MDMA_Init(void)
{

    /* MDMA controller clock enable */
    __HAL_RCC_MDMA_CLK_ENABLE();
    /* Local variables */

    /* MDMA interrupt initialization */
    /* MDMA_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(MDMA_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(MDMA_IRQn);
}

/* FMC initialization function */
void MX_FMC_Init(void)
{

    /* USER CODE BEGIN FMC_Init 0 */

    /* USER CODE END FMC_Init 0 */

    FMC_SDRAM_TimingTypeDef SdramTiming = {0};

    /* USER CODE BEGIN FMC_Init 1 */
    FMC_Bank1_R->BTCR[0] &= ~FMC_BCRx_MBKEN;
    /* USER CODE END FMC_Init 1 */

    /** Perform the SDRAM1 memory initialization sequence
     */
    hsdram1.Instance = FMC_SDRAM_DEVICE;
    /* hsdram1.Init */
    hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
    hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
    hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
    /* SdramTiming */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshDelay = 7;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 7;
    SdramTiming.WriteRecoveryTime = 3;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;

    if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN FMC_Init 2 */
    BSP_SDRAM_DeInit(0);
    if (BSP_SDRAM_Init(0) != BSP_ERROR_NONE)
    {
        Error_Handler();
    }
    /* USER CODE END FMC_Init 2 */
}

/**
 * @brief QUADSPI Initialization Function
 * @param None
 * @retval None
 */
static void MX_QUADSPI_Init(void)
{
    /* USER CODE BEGIN QUADSPI_Init 0 */

    /* USER CODE END QUADSPI_Init 0 */

    /* USER CODE BEGIN QUADSPI_Init 1 */

    /* USER CODE END QUADSPI_Init 1 */
    /* QUADSPI parameter configuration*/
    hqspi.Instance = QUADSPI;
    hqspi.Init.ClockPrescaler = 3;
    hqspi.Init.FifoThreshold = 1;
    hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
    hqspi.Init.FlashSize = 1;
    hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
    hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
    hqspi.Init.DualFlash = QSPI_DUALFLASH_ENABLE;
    if (HAL_QSPI_Init(&hqspi) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN QUADSPI_Init 2 */
    BSP_QSPI_Init_t init;
    init.InterfaceMode = MT25TL01G_QPI_MODE;
    init.TransferRate = MT25TL01G_DTR_TRANSFER;
    init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;
    if (BSP_QSPI_Init(0, &init) != BSP_ERROR_NONE)
    {
        Error_Handler();
    }
    if (BSP_QSPI_EnableMemoryMappedMode(0) != BSP_ERROR_NONE)
    {
        Error_Handler();
    }
    /* USER CODE END QUADSPI_Init 2 */
}

/**
 * @brief DMA2D Initialization Function
 * @param None
 * @retval None
 */
void MX_DMA2D_Init(void)
{
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_R2M;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
    hdma2d.Init.OutputOffset = 0;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief DSIHOST Initialization Function
 * @param None
 * @retval None
 */
static void MX_DSIHOST_DSI_Init(void)
{
    /* USER CODE BEGIN DSIHOST_Init 0 */
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_Delay(20);                                      /* wait 20 ms */
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET); /* Deactivate XRES */
    HAL_Delay(10);                                      /* Wait for 10ms after releasing XRES before sending commands */
    /* USER CODE END DSIHOST_Init 0 */

    DSI_PLLInitTypeDef PLLInit = {0};
    DSI_HOST_TimeoutTypeDef HostTimeouts = {0};
    DSI_PHY_TimerTypeDef PhyTimings = {0};
    DSI_LPCmdTypeDef LPCmd = {0};
    DSI_CmdCfgTypeDef CmdCfg = {0};

    /* USER CODE BEGIN DSIHOST_Init 1 */

    /* USER CODE END DSIHOST_Init 1 */
    hdsi.Instance = DSI;
    hdsi.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;
    hdsi.Init.TXEscapeCkdiv = 4;
    hdsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
    PLLInit.PLLNDIV = 119;
    PLLInit.PLLIDF = DSI_PLL_IN_DIV3;
    PLLInit.PLLODF = DSI_PLL_OUT_DIV2;
    if (HAL_DSI_Init(&hdsi, &PLLInit) != HAL_OK)
    {
        Error_Handler();
    }
    HostTimeouts.TimeoutCkdiv = 1;
    HostTimeouts.HighSpeedTransmissionTimeout = 0;
    HostTimeouts.LowPowerReceptionTimeout = 0;
    HostTimeouts.HighSpeedReadTimeout = 0;
    HostTimeouts.LowPowerReadTimeout = 0;
    HostTimeouts.HighSpeedWriteTimeout = 0;
    HostTimeouts.HighSpeedWritePrespMode = DSI_HS_PM_DISABLE;
    HostTimeouts.LowPowerWriteTimeout = 0;
    HostTimeouts.BTATimeout = 0;
    if (HAL_DSI_ConfigHostTimeouts(&hdsi, &HostTimeouts) != HAL_OK)
    {
        Error_Handler();
    }
    PhyTimings.ClockLaneHS2LPTime = 28;
    PhyTimings.ClockLaneLP2HSTime = 33;
    PhyTimings.DataLaneHS2LPTime = 15;
    PhyTimings.DataLaneLP2HSTime = 25;
    PhyTimings.DataLaneMaxReadTime = 0;
    PhyTimings.StopWaitTime = 0;
    if (HAL_DSI_ConfigPhyTimer(&hdsi, &PhyTimings) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DSI_ConfigFlowControl(&hdsi, DSI_FLOW_CONTROL_BTA) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DSI_SetLowPowerRXFilter(&hdsi, 10000) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DSI_ConfigErrorMonitor(&hdsi, HAL_DSI_ERROR_NONE) != HAL_OK)
    {
        Error_Handler();
    }
    LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_ENABLE;
    LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_ENABLE;
    LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_ENABLE;
    LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_ENABLE;
    LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_ENABLE;
    LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_ENABLE;
    LPCmd.LPGenLongWrite = DSI_LP_GLW_ENABLE;
    LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_ENABLE;
    LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_ENABLE;
    LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_ENABLE;
    LPCmd.LPDcsLongWrite = DSI_LP_DLW_ENABLE;
    LPCmd.LPMaxReadPacket = DSI_LP_MRDP_ENABLE;
    LPCmd.AcknowledgeRequest = DSI_ACKNOWLEDGE_ENABLE;
    if (HAL_DSI_ConfigCommand(&hdsi, &LPCmd) != HAL_OK)
    {
        Error_Handler();
    }
    CmdCfg.VirtualChannelID = 0;
    CmdCfg.ColorCoding = DSI_RGB888;
    CmdCfg.CommandSize = 400;
    CmdCfg.TearingEffectSource = DSI_TE_EXTERNAL;
    CmdCfg.TearingEffectPolarity = DSI_TE_RISING_EDGE;
    CmdCfg.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
    CmdCfg.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
    CmdCfg.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
    CmdCfg.VSyncPol = DSI_VSYNC_RISING;
    CmdCfg.AutomaticRefresh = DSI_AR_DISABLE;
    CmdCfg.TEAcknowledgeRequest = DSI_TE_ACKNOWLEDGE_ENABLE;
    if (HAL_DSI_ConfigAdaptedCommandMode(&hdsi, &CmdCfg) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_DSI_SetGenericVCID(&hdsi, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DSIHOST_Init 2 */

    /* USER CODE END DSIHOST_Init 2 */
}

/**
 * @brief LTDC Initialization Function
 * @param None
 * @retval None
 */
static void MX_LTDC_Init(void)
{
    /* USER CODE BEGIN LTDC_Init 0 */

    /* USER CODE END LTDC_Init 0 */

    LTDC_LayerCfgTypeDef pLayerCfg = {0};

    /* USER CODE BEGIN LTDC_Init 1 */

    /* USER CODE END LTDC_Init 1 */
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AH;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AH;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 0;
    hltdc.Init.VerticalSync = 0;
    hltdc.Init.AccumulatedHBP = 2;
    hltdc.Init.AccumulatedVBP = 2;
    hltdc.Init.AccumulatedActiveW = 402;
    hltdc.Init.AccumulatedActiveH = 482;
    hltdc.Init.TotalWidth = 403;
    hltdc.Init.TotalHeigh = 483;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
        Error_Handler();
    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 400;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 480;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    pLayerCfg.FBStartAdress = 0xD0000000;
    pLayerCfg.ImageWidth = 400;
    pLayerCfg.ImageHeight = 480;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN LTDC_Init 2 */

    /* Configure DSI PHY HS2LP and LP2HS timings */

    __HAL_LTDC_DISABLE(&hltdc);
    DSI_LPCmdTypeDef LPCmd;

    HAL_DSI_Start(&hdsi);

    /* Configure the audio driver */
    IOCtx.Address = 0;
    IOCtx.GetTick = BSP_GetTick;
    IOCtx.WriteReg = DSI_IO_Write;
    IOCtx.ReadReg = DSI_IO_Read;
    OTM8009A_RegisterBusIO(&OTM8009AObj, &IOCtx);

    OTM8009A_Init(&OTM8009AObj, OTM8009A_FORMAT_RGB888,
                  OTM8009A_ORIENTATION_LANDSCAPE);
    HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1,
                       OTM8009A_CMD_DISPOFF, 0x00);

    LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_DISABLE;
    LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_DISABLE;
    LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_DISABLE;
    LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_DISABLE;
    LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_DISABLE;
    LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_DISABLE;
    LPCmd.LPGenLongWrite = DSI_LP_GLW_DISABLE;
    LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_DISABLE;
    LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_DISABLE;
    LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_DISABLE;
    LPCmd.LPDcsLongWrite = DSI_LP_DLW_DISABLE;
    HAL_DSI_ConfigCommand(&hdsi, &LPCmd);

    HAL_LTDC_SetPitch(&hltdc, 800, 0);
    __HAL_LTDC_ENABLE(&hltdc);
    /* USER CODE END LTDC_Init 2 */
}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void)
{
    hcrc.Instance = CRC;
    hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
    hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
    hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
    hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
    hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
    if (HAL_CRC_Init(&hcrc) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief JPEG Initialization Function
 * @param None
 * @retval None
 */
static void MX_JPEG_Init(void)
{

    /* USER CODE BEGIN JPEG_Init 0 */

    /* USER CODE END JPEG_Init 0 */

    /* USER CODE BEGIN JPEG_Init 1 */

    /* USER CODE END JPEG_Init 1 */
    hjpeg.Instance = JPEG;
    if (HAL_JPEG_Init(&hjpeg) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN JPEG_Init 2 */

    /* USER CODE END JPEG_Init 2 */
}

/**
 * @brief  Configure the MPU attributes as Write Through for SDRAM.
 * @note   The Base Address is SDRAM_DEVICE_ADDR.
 *         The Region Size is 32MB.
 * @param  None
 * @retval None
 */
static void MPU_Config(void)
{
    MPU_Region_InitTypeDef MPU_InitStruct;

    /* Disable the MPU */
    HAL_MPU_Disable();

    /* Configure the MPU as Strongly ordered for not defined regions */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = 0x00;
    MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
    MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x87;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* Configure the MPU attributes as WT for SDRAM */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = SDRAM_DEVICE_ADDR; // 0xD0000000
    MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER1;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* Configure the MPU QSPI flash */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = 0x90000000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_128MB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER2;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x0;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* Enable the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM6 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM6)
    {
        HAL_IncTick();
    }
    /* USER CODE BEGIN Callback 1 */

    /* USER CODE END Callback 1 */
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
static void CPU_CACHE_Enable(void)
{
    /* Enable I-Cache */
    SCB_EnableICache();

    /* Enable D-Cache */
    SCB_EnableDCache();
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 400000000 (Cortex-M7 CPU Clock)
 *            HCLK(Hz)                       = 200000000 (Cortex-M4 CPU, Bus matrix Clocks)
 *            AHB Prescaler                  = 2
 *            D1 APB3 Prescaler              = 2 (APB3 Clock  100MHz)
 *            D2 APB1 Prescaler              = 2 (APB1 Clock  100MHz)
 *            D2 APB2 Prescaler              = 2 (APB2 Clock  100MHz)
 *            D3 APB4 Prescaler              = 2 (APB4 Clock  100MHz)
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 5
 *            PLL_N                          = 160
 *            PLL_P                          = 2
 *            PLL_Q                          = 4
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Flash Latency(WS)              = 4
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    HAL_StatusTypeDef ret = HAL_OK;

    /*!< Supply configuration update enable */
    HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

    /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
    {
    }

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
    RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

    RCC_OscInitStruct.PLL.PLLM = 5;
    RCC_OscInitStruct.PLL.PLLN = 160;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLQ = 4;

    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }

    /* Select PLL as system clock source and configure  bus clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1);

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
    if (ret != HAL_OK)
    {
        Error_Handler();
    }

    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);

    /*
     Note : The activation of the I/O Compensation Cell is recommended with communication  interfaces
     (GPIO, SPI, FMC, QSPI ...)  when  operating at  high frequencies(please refer to product datasheet)
     The I/O Compensation Cell activation  procedure requires :
     - The activation of the CSI clock
     - The activation of the SYSCFG clock
     - Enabling the I/O Compensation Cell : setting bit[0] of register SYSCFG_CCCSR
     */

    /*activate CSI clock mondatory for I/O Compensation Cell*/
    __HAL_RCC_CSI_ENABLE();

    /* Enable SYSCFG clock mondatory for I/O Compensation Cell */
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    /* Enables the I/O Compensation Cell */
    HAL_EnableCompensationCell();
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void)
{
    while (1)
    {
    }
}

// printf to uart //
int _write(int file, char *ptr, int len)
{
    int idx;

    for (idx = 0; idx < len; idx++)
    {
        osKernelLock();
        HAL_UART_Transmit(&huart1, (uint8_t *)ptr++, 1, 100);
        osKernelUnlock();
    }

    return idx;
}
