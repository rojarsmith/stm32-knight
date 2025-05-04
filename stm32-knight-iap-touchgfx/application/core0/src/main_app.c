/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Rojar Smith
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 .
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"
#include "cmsis_os.h"

/* Private define ------------------------------------------------------------*/
#define FLASH_ADDR_APP ADDRESS_BOOTLOADER

/* Private typedef -----------------------------------------------------------*/
typedef void (*pFunction)(void);

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
SDRAM_HandleTypeDef hsdram1;

/* Definitions for TouchGFXTask */
osThreadId_t guiTaskHandle;
const osThreadAttr_t guiTask_attributes = {
    .name = "GUITask",
    .stack_size = 3048 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);
static void SystemClock_Config(void);
static void MX_USART1_UART_Init(void);
static void MX_GPIO_Init(void);
static void MX_MDMA_Init(void);
static void MX_FMC_Init(void);
static void Delay_MS(uint32_t ms);
static void Jump_To_Boot(uint32_t address);
static void GUITask(void *params);

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

    MX_USART1_UART_Init();

    BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);

    MX_GPIO_Init();
    MX_MDMA_Init();
    MX_FMC_Init();

    uint32_t address = *(__IO uint32_t *)FLASH_ORIGIN; // 0x24080000
    printf("Value at address 0x%08X: 0x%08X\n", (unsigned int)FLASH_ORIGIN, (unsigned int)address);
    printf("FLASH_ORIGIN = 0x%08X\r\n", FLASH_ORIGIN);

    osKernelInitialize();
    /* creation of TouchGFXTask */
    // guiTaskHandle = osThreadNew(TouchGFX_Task, NULL, &guiTask_attributes);
    guiTaskHandle = osThreadNew(GUITask, NULL, &guiTask_attributes);

    osKernelStart();

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
            Jump_To_Boot(address);
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

static void Jump_To_Boot(uint32_t address)
{
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
    if ((address & 0x2BF7FFFF) == 0x20000000)
    {
        //
        // Disable all interrupts
        //
        NVIC->ICER[0] = 0xFFFFFFFF;
        NVIC->ICER[1] = 0xFFFFFFFF;
        NVIC->ICER[2] = 0xFFFFFFFF;
        //
        // Clear pendings
        //
        NVIC->ICPR[0] = 0xFFFFFFFF;
        NVIC->ICPR[1] = 0xFFFFFFFF;
        NVIC->ICPR[2] = 0xFFFFFFFF;

        SysTick->CTRL = 0; // Disable SysTick

        // Set vector table
        SCB->VTOR = (unsigned long)FLASH_ADDR_APP;

        jumpAddress = *(__IO uint32_t *)(FLASH_ADDR_APP + 4);
        jumpToApplication = (pFunction)jumpAddress;
        __set_MSP(*(__IO uint32_t *)FLASH_ADDR_APP);
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
