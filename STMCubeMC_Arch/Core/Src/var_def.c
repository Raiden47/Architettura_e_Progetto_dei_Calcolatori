/**
  ******************************************************************************
  * @file           : var_def.c
  * @brief          : var_def method definition
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

#include "var_def.h"

static int time_prescaler(int t)
	switch(t){
	case 1:
		return (BOARD_CLK/TIM1_MAX_SCALER)-1;
		break;
	case 2:
		return (BOARD_CLK/TIM1_MED_SCALER)-1;
		break;
	case 3:
		return (BOARD_CLK/TIM1_MIN_SCALER)-1;
		break;
	}


