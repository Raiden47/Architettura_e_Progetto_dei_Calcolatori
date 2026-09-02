/**
  ******************************************************************************
  * @file           : var_def.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application variables.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef __BUTTON__
#define __BUTTON__

#include <stdint.h>
#include "stm32f3xx_hal.h"
#include "main.h"

// To be removed
#define BOARD_CLK 64000000
#define TIM1_MAX_SCALER 1000000
#define TIM1_MED_SCALER 32000000
#define TIM1_MIN_SCALER 64000000

int Button_Pressed(uint8_t, uint8_t);

#endif //__BUTTON__
