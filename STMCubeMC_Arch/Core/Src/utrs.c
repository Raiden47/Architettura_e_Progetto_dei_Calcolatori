/**
  ******************************************************************************
  * @file           : utrs.c
  * @brief          : utrs method definition
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


#include "utrs.h"


static volatile uint32_t capture_rising = 0;
static volatile uint32_t capture_falling = 0;

static volatile uint32_t echo_time = 0;

static volatile uint8_t measuring = 0;
static volatile uint8_t measurement_ready = 0;

static volatile uint32_t measuring_since = 0;


volatile uint32_t debug_trigger_count = 0;
volatile uint32_t debug_rising_count = 0;
volatile uint32_t debug_falling_count = 0;
volatile uint32_t debug_echo_time = 0;

void UTRS_Init(void)
{
    HAL_GPIO_WritePin(
        TRIG_PORT,
        TRIG_PIN,
        GPIO_PIN_RESET
    );

    if (HAL_TIM_Base_Start(&htim1) != HAL_OK){
        Error_Handler();
    }

    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC1);
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC2);
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC3);
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC4);

    HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);


    if (HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_4) != HAL_OK){
        Error_Handler();
    }

    capture_rising = 0;
    capture_falling = 0;

    echo_time = 0;

    measuring = 0;
    measurement_ready = 0;

    measuring_since = 0;


    /*
     * Debug
     */
    debug_trigger_count = 0;
    debug_rising_count = 0;
    debug_falling_count = 0;
    debug_echo_time = 0;
}


void UTRS_Trigger(void)
{
    debug_trigger_count++;
    if (measuring){
        return;
    }

    measurement_ready = 0;
    __HAL_TIM_SET_COUNTER(
        &htim2,
        0
    );

    HAL_GPIO_WritePin(
        TRIG_PORT,
        TRIG_PIN,
        GPIO_PIN_SET
    );

    __HAL_TIM_SET_COUNTER(
        &htim1,
        0
    );

    while (__HAL_TIM_GET_COUNTER(&htim1) < 10){
    }

    HAL_GPIO_WritePin(
        TRIG_PORT,
        TRIG_PIN,
        GPIO_PIN_RESET
    );
}


volatile uint32_t debug_cc4p_after_rising = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != TIM2) return;
    if (htim->Channel != HAL_TIM_ACTIVE_CHANNEL_4) return;

    if (!measuring)
    {
        capture_rising = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);

        debug_rising_count++;

        measuring = 1;
        measuring_since = HAL_GetTick();

        TIM2->CCER |= TIM_CCER_CC4P;

        debug_cc4p_after_rising =
            (TIM2->CCER & TIM_CCER_CC4P) ? 1 : 0;
    }
    else
    {
        capture_falling = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);

        debug_falling_count++;

        echo_time = capture_falling - capture_rising;
        debug_echo_time = echo_time;

        measuring = 0;
        measurement_ready = 1;

        TIM2->CCER &= ~TIM_CCER_CC4P;
    }
}



uint16_t UTRS_ReadDistance(void)
{
    uint32_t time;
    uint32_t distance;

    if (!measurement_ready){
        return 0;
    }

    time = echo_time;

    measurement_ready = 0;
    if (time == 0){
        return 0;
    }

    distance = time / 58;

    if (distance > MAX_RANGE){
        distance = MAX_RANGE;
    }


    return (uint16_t)distance;
}


uint8_t UTRS_IsMeasuring(void)
{
    if (measuring)
    {
        if ((HAL_GetTick() - measuring_since) > 50)
        {
            measuring = 0;

            measurement_ready = 0;

            TIM2->CCER &= ~TIM_CCER_CC4P;
        }
    }


    return measuring;
}


/* ============================================================
 * Measurement Ready
 * ============================================================ */

uint8_t UTRS_MeasurementReady(void)
{
    return measurement_ready;
}
