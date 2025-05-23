/**
 ******************************************************************************
 * @file    stm32h7xx_it.c
 * @author  Rojar Smith
 * @brief   Main Interrupt Service Routines for Cortex-M7.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025.
 * All rights reserved.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_it.h"

/** @addtogroup STM32H7xx_HAL_Examples
 * @{
 */

/** @addtogroup DMAMUX_SYNC
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim6;
extern DSI_HandleTypeDef hdsi;
extern LTDC_HandleTypeDef hltdc;
extern JPEG_HandleTypeDef hjpeg;
extern MDMA_HandleTypeDef hmdma_jpeg_infifo_th;
extern MDMA_HandleTypeDef hmdma_jpeg_outfifo_th;
extern DMA2D_HandleTypeDef hdma2d;

/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
#ifdef GOAL_BOOTLOADER
void SVC_Handler(void)
{
}
#endif

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
#ifdef GOAL_BOOTLOADER
void PendSV_Handler(void)
{
}
#endif

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
#ifdef GOAL_BOOTLOADER
void SysTick_Handler(void)
{
	HAL_IncTick();
}
#endif

/******************************************************************************/
/*                 STM32H7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32h7xx.s).                                               */
/******************************************************************************/

/**
 * @brief This function handles TIM6 global interrupt, DAC1_CH1 and DAC1_CH2 underrun error interrupts.
 */
void TIM6_DAC_IRQHandler(void)
{
	/* USER CODE BEGIN TIM6_DAC_IRQn 0 */

	/* USER CODE END TIM6_DAC_IRQn 0 */
	HAL_TIM_IRQHandler(&htim6);
	/* USER CODE BEGIN TIM6_DAC_IRQn 1 */

	/* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
 * @brief This function handles DSI global Interrupt.
 */
void DSI_IRQHandler(void)
{
	/* USER CODE BEGIN DSI_IRQn 0 */

	/* USER CODE END DSI_IRQn 0 */
	HAL_DSI_IRQHandler(&hdsi);
	/* USER CODE BEGIN DSI_IRQn 1 */

	/* USER CODE END DSI_IRQn 1 */
}

/**
 * @brief This function handles LTDC global interrupt.
 */
void LTDC_IRQHandler(void)
{
	/* USER CODE BEGIN LTDC_IRQn 0 */

	/* USER CODE END LTDC_IRQn 0 */
	HAL_LTDC_IRQHandler(&hltdc);
	/* USER CODE BEGIN LTDC_IRQn 1 */

	/* USER CODE END LTDC_IRQn 1 */
}

/**
 * @brief This function handles JPEG global interrupt.
 */
void JPEG_IRQHandler(void)
{
	/* USER CODE BEGIN JPEG_IRQn 0 */

	/* USER CODE END JPEG_IRQn 0 */
	HAL_JPEG_IRQHandler(&hjpeg);
	/* USER CODE BEGIN JPEG_IRQn 1 */

	/* USER CODE END JPEG_IRQn 1 */
}

/**
  * @brief This function handles DMA2D global interrupt.
  */
 void DMA2D_IRQHandler(void)
 {
   /* USER CODE BEGIN DMA2D_IRQn 0 */
 
   /* USER CODE END DMA2D_IRQn 0 */
   HAL_DMA2D_IRQHandler(&hdma2d);
   /* USER CODE BEGIN DMA2D_IRQn 1 */
 
   /* USER CODE END DMA2D_IRQn 1 */
 }
 
/**
 * @brief  Handles MDMA transfer interrupt request.
 * @retval None
 */
void MDMA_IRQHandler(void)
{
	/* USER CODE BEGIN MDMA_IRQn 0 */

	/* USER CODE END MDMA_IRQn 0 */
	HAL_MDMA_IRQHandler(&hmdma_jpeg_outfifo_th);
	HAL_MDMA_IRQHandler(&hmdma_jpeg_infifo_th);
	/* USER CODE BEGIN MDMA_IRQn 1 */

	/* USER CODE END MDMA_IRQn 1 */
}

/**
 * @brief  This function handles External line 2 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI2_IRQHandler(void)
{
}

/**
 * @brief  This function handles External line 3 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI3_IRQHandler(void)
{
}

/**
 * @brief  This function handles External line 4 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI4_IRQHandler(void)
{
}

/**
 * @brief  This function handles External lines 9 to 5 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI9_5_IRQHandler(void)
{
}

/**
 * @brief  This function handles External lines 15 to 10 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI15_10_IRQHandler(void)
{
}

/**
 * @brief  This function handles SAI DMA interrupt request.
 * @param  None
 * @retval None
 */
void AUDIO_IN_SAIx_DMAx_IRQHandler()
{
}
/**
 * @brief  This function handles DMA2 Stream 1 interrupt request.
 * @param  None
 * @retval None
 */
void AUDIO_OUT_SAIx_DMAx_IRQHandler(void)
{
}

/**
 * @brief  This function handles BDMA Channel 1 for SAI_PDM interrupt request.
 * @param  None
 * @retval None
 */
void AUDIO_IN_SAI_PDMx_DMAx_IRQHandler(void)
{
}

/**
 * @brief  This function handles SD interrupt request.
 * @param  None
 * @retval None
 */
void SDMMC1_IRQHandler(void)
{
}

/**
 * @brief  DCMI interrupt handler.
 * @param  None
 * @retval None
 */
void DCMI_IRQHandler(void)
{
}

/**
 * @brief  DMA interrupt handler.
 * @param  None
 * @retval None
 */
void DMA2_Stream3_IRQHandler(void)
{
}

/**
 * @}
 */

/**
 * @}
 */
