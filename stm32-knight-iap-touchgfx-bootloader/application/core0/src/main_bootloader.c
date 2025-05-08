/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Rojar Smith
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Rojar Smith.
 * All rights reserved.
 *
 ******************************************************************************
 */

#include "main.h"

/* Private define ------------------------------------------------------------*/
#define DEBOUNCE_DELAY_MS 100

/* Private typedef -----------------------------------------------------------*/
// __IO uint32_t JoyPinPressed = 0;
// __IO uint32_t Joy_State;
// __IO uint32_t PreviousPinState = 0;
typedef void (*pFunction)(void);

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
JOYPin_TypeDef current_state;
JOYPin_TypeDef last_state = JOY_NONE;

unsigned char __attribute__((section(".fw_info0_section_flash")))
fw_info0_flash[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
unsigned char __attribute__((section(".fw_info1_section_flash")))
fw_info1_flash[10] = {'a', 'b', 'c', 'd'};

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);
static void SystemClock_Config(void);
static void MX_USART1_UART_Init(void);
static void Delay_MS(uint32_t ms);
static void Jump_To_App(uint32_t base_address);
static void Write_To_Internal_Ver(uint8_t ver);

int main(void)
{
	MPU_Config();
	CPU_CACHE_Enable();
	HAL_Init();
	SystemClock_Config();

	MX_USART1_UART_Init();

	BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);
	BSP_JOY_Init(JOY1, JOY_MODE_GPIO, JOY_ALL);
	// BSP_JOY_Init(JOY1, JOY_MODE_EXTI, JOY_ALL);

	const unsigned char *fidx0 =
		(const unsigned char *)(ADDRESS_FW_INFO);
	for (int i = 0; i < 10; i++)
	{
		printf("buf_flash[%d] = %d\r\n", i, fidx0[i]);
	}

	// align 4
	printf("[align 4]\r\n");
	const unsigned char *fidx1 =
		(const unsigned char *)(ADDRESS_FW_INFO + 10 + 2);
	for (int i = 0; i <= 3; i++)
	{
		printf("buf_flash[%d] = %c\r\n", i, fidx1[i]);
	}

	printf("ADDRESS_BOOTLOADER = 0x%08X\r\n", ADDRESS_BOOTLOADER);
	printf("ADDRESS_FW_INFO = 0x%08X\r\n", ADDRESS_FW_INFO);
	printf("ADDRESS_APP_0 = 0x%08X\r\n", ADDRESS_APP_0);
	printf("ADDRESS_APP_1 = 0x%08X\r\n", ADDRESS_APP_1);

	uint32_t value = 0;
	value = *(__IO uint32_t *)ADDRESS_BOOTLOADER;
	printf("Value at address 0x%08X: 0x%08X\r\n", (unsigned int)ADDRESS_BOOTLOADER,
		   (unsigned int)value);
	value = *(__IO uint32_t *)ADDRESS_FW_INFO;
	printf("Value at address 0x%08X: 0x%08X\r\n", (unsigned int)ADDRESS_FW_INFO,
		   (unsigned int)value);
	value = *(__IO uint32_t *)ADDRESS_APP_0; // 0x24080000 at AXI-SRAM
	printf("Value at address 0x%08X: 0x%08X\r\n", (unsigned int)ADDRESS_APP_0,
		   (unsigned int)value);
	value = *(__IO uint32_t *)ADDRESS_APP_1; // 0x24080000 at AXI-SRAM
	printf("Value at address 0x%08X: 0x%08X\r\n", (unsigned int)ADDRESS_APP_1,
		   (unsigned int)value);

	uint32_t print_count = 0;
	uint32_t last_print_tick = 0;
	for (;;)
	{
		if ((HAL_GetTick() - last_print_tick) >= 3000)
		{
			printf("IAP Demo - Bootloader - %lu\r\n", print_count);
			print_count++;
			last_print_tick = HAL_GetTick();
		}

		// For dev
#ifdef AUTO_JUMP_0
		if ((HAL_GetTick() - last_print_tick) >= 3000)
		{
			Write_To_Internal_Ver(1);
			Delay_MS(500);
			Jump_To_App(address, 0);
			last_print_tick = HAL_GetTick();
		}
#endif
#ifdef AUTO_JUMP_1
		if ((HAL_GetTick() - last_print_tick) >= 3000)
		{
			Write_To_Internal_Ver(0);
			Delay_MS(500);
			Jump_To_App(address, 1);
			last_print_tick = HAL_GetTick();
		}
#endif

		// Joy
		current_state = BSP_JOY_GetState(JOY1, JOY_ALL);

		if (current_state == JOY_RIGHT)
		{
			if (last_state != JOY_RIGHT)
			{
				// printf("RIGHT pressed\n"); // First time
			}
			else
			{
				// printf("RIGHT held\n"); // Each pooling
				if ((BSP_PB_GetState(BUTTON_WAKEUP) == GPIO_PIN_SET))
				{
					printf("Button `Wakeup` for jump to App0\r\n");
					Write_To_Internal_Ver(0);
					Delay_MS(500);
					Jump_To_App(ADDRESS_APP_0);
				}
			}
		}
		else if (last_state == JOY_RIGHT && current_state == JOY_NONE)
		{
			printf("RIGHT released\n");
		}
		else if (current_state == JOY_LEFT)
		{
			if (last_state != JOY_LEFT)
			{
				// printf("LEFT pressed\n"); // First time
			}
			else
			{
				// printf("LEFT held\n"); // Each pooling
				if ((BSP_PB_GetState(BUTTON_WAKEUP) == GPIO_PIN_SET))
				{
					printf("Button `Wakeup` for jump to App1\r\n");
					Write_To_Internal_Ver(1);
					Delay_MS(500);
					Jump_To_App(ADDRESS_APP_1);
				}
			}
		}
		else if (last_state == JOY_LEFT && current_state == JOY_NONE)
		{
			printf("LEFT released\n");
		}

		last_state = current_state;

		// switch (JoyPinPressed)
		// {
		// case 0x01U:
		// 	Joy_State = JOY_SEL;
		// 	break;

		// case 0x02U:
		// 	Joy_State = JOY_DOWN;
		// 	break;

		// case 0x04U:
		// 	Joy_State = JOY_LEFT;
		// 	break;

		// case 0x08U:
		// 	Joy_State = JOY_RIGHT;
		// 	break;
		// case 0x10U:
		// 	Joy_State = JOY_UP;
		// 	break;
		// default:
		// 	Joy_State = JOY_NONE;
		// 	break;
		// }
		// JoyPinPressed = 0;

		// if ((BSP_PB_GetState(BUTTON_WAKEUP) == GPIO_PIN_SET))
		// {
		// 	printf("Button `Wakeup`\r\n");
		// 	if (fw_info0_flash[0] == 0)
		// 	{
		// 		Write_To_Internal_Ver(1);
		// 		Delay_MS(500);
		// 		Jump_To_App(ADDRESS_APP_0);
		// 	}
		// 	else
		// 	{
		// 		Write_To_Internal_Ver(0);
		// 		Delay_MS(500);
		// 		Jump_To_App(ADDRESS_APP_1);
		// 	}
		// 	// Jump_To_App(address);
		// }

		HAL_Delay(10); // Reduce CPU Power
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

static void Jump_To_App(uint32_t base_address)
{
	// uint32_t baseAddress;
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
	// 2000 0000 = 00100000000000000000000000000000
	if ((*(__IO uint32_t *)base_address & 0x2BF7FFFF) == 0x20000000)
	{
		__disable_irq();
		SysTick->CTRL = 0; // Disable SysTick

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

		// Disable peripherals, Cache, MPU
		// HAL_DeInit();
		// SCB_DisableICache();
		// SCB_DisableDCache();
		// HAL_MPU_Disable();

		// Set vector table
		SCB->VTOR = (unsigned long)base_address;

		jumpAddress = *(__IO uint32_t *)(base_address + 4);
		jumpToApplication = (pFunction)jumpAddress;
		__set_MSP(*(__IO uint32_t *)base_address);
		jumpToApplication();
	}
}

static void Write_To_Internal_Ver(uint8_t ver)
{
	uint8_t *flash_address = (uint8_t *)ADDRESS_FW_INFO;
	uint8_t sector_data[131072]; // 128 x 1024
	uint8_t *sector_data_idx = &sector_data[0];

	HAL_FLASH_Unlock();

	memcpy(sector_data, flash_address, 131072);

	sector_data[0] = ver;

	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SectorError;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.Sector = FLASH_SECTOR_1;
	EraseInitStruct.Banks = FLASH_BANK_1;
	EraseInitStruct.NbSectors = 1;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
	{
		printf("IAP Demo - Boot - Error erase\r\n");
	}

	for (uint32_t i = 0; i < (131072 / 32); i++)
	{
		uint64_t fw[4];
		memcpy((char *)fw, sector_data_idx, 32);
		sector_data_idx += 32;

		HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD,
						  (uint32_t)(flash_address + i),
						  (uint64_t)((uint32_t)fw));
	}

	HAL_FLASH_Lock();
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
	MPU_InitStruct.BaseAddress = SDRAM_DEVICE_ADDR;
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
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
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

// void BSP_JOY_Callback(JOY_TypeDef JOY, uint32_t JoyPin)
// {
// 	JoyPinPressed = JoyPin;
// }

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
		HAL_UART_Transmit(&huart1, (uint8_t *)ptr++, 1, 100);
	}

	return idx;
}
