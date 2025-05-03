/**
 ******************************************************************************
 * @file    main.h
 * @author  Rojar Smith
 * @brief   Header for main.c module for Cortex-M7.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Rojar Smith.
 * All rights reserved.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "stm32h7xx_hal.h"
#include "stm32h747i_discovery.h"
#include "stm32h747i_discovery_sdram.h"
#ifdef BUILD_APP
#include "FreeRTOS.h"
#include "task.h"
#endif

/* Exported functions ------------------------------------------------------- */
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define VCP_TX_Pin       GPIO_PIN_9
#define VCP_TX_GPIO_Port GPIOA
#define VCP_RX_Pin       GPIO_PIN_7
#define VCP_RX_GPIO_Port GPIOB

#endif /* __MAIN_H */
