/**
  ******************************************************************************
  * @file           : lcd.h
  * @brief          : Header file for the lcd display
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
  
#ifndef __LCD__
#define __LCD__
  
#include "main.h"

#define LCD_RS_PORT    GPIOA
#define LCD_RS_PIN     GPIO_PIN_1
#define LCD_E_PORT     GPIOA
#define LCD_E_PIN      GPIO_PIN_3
#define LCD_D4_PORT    GPIOA
#define LCD_D4_PIN     GPIO_PIN_4
#define LCD_D5_PORT    GPIOA
#define LCD_D5_PIN     GPIO_PIN_6
#define LCD_D6_PORT    GPIOA
#define LCD_D6_PIN     GPIO_PIN_5
#define LCD_D7_PORT    GPIOA
#define LCD_D7_PIN     GPIO_PIN_7

extern uint8_t state;

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_WriteChar(char c);
void LCD_Print(char *str);
void LCD_Command(uint8_t cmd);
void LCD_ChangeState();
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
uint8_t LCD_GetState();

#endif
