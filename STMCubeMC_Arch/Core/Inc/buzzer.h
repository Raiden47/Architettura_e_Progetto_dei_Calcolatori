/**
  ******************************************************************************
  * @file           : buzzer.h
  * @brief          : Header file for the buzzer modul
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
  
#ifndef __BUZZER__
#define __BUZZER__
  
#include "main.h"

#define BUZZER_PORT GPIOC
#define BUZZER_PIN  GPIO_PIN_7
#define BUZZER_START 1000
#define BUZZER_INTERVAL_SL 500
#define BUZZER_INTERVAL_MD 250
#define BUZZER_INTERVAL_HG 50

void Buzzer_Init(void);
void Buzzer_Start(uint32_t interval);
void Buzzer_Stop(void);
void Buzzer_SetInterval(uint32_t interval);
void Buzzer_Update(void);
  
  
#endif
