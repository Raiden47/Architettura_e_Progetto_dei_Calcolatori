/**
  ******************************************************************************
  * @file           : buzzer.c
  * @brief          : buzzer method definition
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


#include "buzzer.h"

static uint8_t buzzer_enabled = 0;
static uint8_t buzzer_state = 0;

static uint32_t buzzer_interval = BUZZER_INTERVAL_SL;
static uint32_t buzzer_last_change = 0;


void Buzzer_Init(void){
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);

    buzzer_enabled = 0;
    buzzer_state = 0;
}


void Buzzer_Start(uint32_t interval){
    buzzer_interval = interval;

    buzzer_enabled = 1;
    buzzer_state = 1;

    buzzer_last_change = HAL_GetTick();

    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
}


void Buzzer_Stop(void){
    buzzer_enabled = 0;
    buzzer_state = 0;

    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}


void Buzzer_SetInterval(uint32_t interval){
    buzzer_interval = interval;
}


void Buzzer_Update(void){
    if (!buzzer_enabled)
        return;

    if (HAL_GetTick() - buzzer_last_change >= buzzer_interval){
        buzzer_last_change = HAL_GetTick();

        buzzer_state = !buzzer_state;

        if (buzzer_state){
            HAL_GPIO_WritePin(
                BUZZER_PORT,
                BUZZER_PIN,
                GPIO_PIN_SET
            );
        } else {
            HAL_GPIO_WritePin(
                BUZZER_PORT,
                BUZZER_PIN,
                GPIO_PIN_RESET
            );
        }
    }
}
