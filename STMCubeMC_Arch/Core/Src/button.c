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

#include "button.h"

int Button_Pressed(uint8_t bo, uint8_t bn){
	if(bo == GPIO_PIN_RESET && bn == GPIO_PIN_SET)
		return 1;
	else
		return 0;
}
