/**
  ******************************************************************************
  * @file           : utrs.h
  * @brief          : Header for infr.c file.
  *                   This file contains the common defines of the ultrasonic management.
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

#ifndef __UTRS__
#define __UTRS__

#include "main.h"

#define TRIG_PORT GPIOA
#define TRIG_PIN  GPIO_PIN_9

#define ECHO_PORT GPIOA
#define ECHO_PIN  GPIO_PIN_10

#define MAX_RANGE 400
#define MED_RANGE 200
#define MIN_RANGE 100
#define STOP_RANGE 25

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

void UTRS_Init(void);
void UTRS_Trigger(void);
uint16_t UTRS_ReadDistance(void);
uint8_t UTRS_IsMeasuring(void);
uint8_t UTRS_MeasurementReady(void);

#endif /*__UTRS__*/






