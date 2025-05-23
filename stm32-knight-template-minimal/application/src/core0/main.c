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
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#ifdef STM32F746xx
#define RCC_BASE 0x40023800 // F7
#endif
#ifdef STM32H747xx
#define RCC_BASE 0x58024400 // H7
#endif

#define RCC_CFGR (volatile uint32_t *)(RCC_BASE + 0x10)

#ifdef STM32F746xx
#define HSI_FREQUENCY 16000000 // F7
#endif
#ifdef STM32H747xx
#define HSI_FREQUENCY 64000000 // H7
#endif

#define SYSTICK_BASE 0xE000E010
#define SYSTICK_CTRL_PTR (volatile uint32_t *)(SYSTICK_BASE + 0x00)
#define SYSTICK_LOAD_PTR (volatile uint32_t *)(SYSTICK_BASE + 0x04)
#define SYSTICK_VAL_PTR (volatile uint32_t *)(SYSTICK_BASE + 0x08)

#define SYSTICK_COUNTFLAG (1 << 16)
#define SYSTICK_CLKSOURCE (1 << 2)
#define SYSTICK_TICKINT (1 << 1)
#define SYSTICK_ENABLE (1 << 0)

uint32_t sysClockFreq = 0;

void SysTick_Delay_us(uint32_t us)
{
	uint32_t tmp = 0;

	uint32_t value_1 = *SYSTICK_CTRL_PTR;
	*SYSTICK_CTRL_PTR |= SYSTICK_CLKSOURCE; // Internal
	uint32_t value_2 = *SYSTICK_CTRL_PTR;
	*SYSTICK_LOAD_PTR = sysClockFreq / 1000 * us;
	uint32_t value_3 = *SYSTICK_LOAD_PTR;
	*SYSTICK_VAL_PTR = 0;
	*SYSTICK_CTRL_PTR |= SYSTICK_ENABLE;

	do
	{
		tmp = *SYSTICK_CTRL_PTR;
	} while (!(tmp & SYSTICK_COUNTFLAG));

	*SYSTICK_CTRL_PTR &= ~SYSTICK_ENABLE;

	if (tmp || value_1 || value_2 || value_3)
	{
	}
}

int main(void)
{
	uint32_t sysClockSource = (*RCC_CFGR >> 3) & 0x3;

	switch (sysClockSource)
	{
	case 0: // HSI
		sysClockFreq = HSI_FREQUENCY;
		break;
	}

	if (sysClockSource || sysClockFreq)
	{
	}

	// 10 seconds
	for (int i = 1; i <= 100; i++)
	{
		SysTick_Delay_us(100);
	}

	volatile uint32_t *value_1 = (volatile uint32_t *)SYSTICK_BASE;
	if (value_1)
	{
	}

	/* Loop forever */
	// Debug point will arrive here after 10 secends
	for (;;)
		;
}
