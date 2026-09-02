/**
  ******************************************************************************
  * @file           : lcd.c
  * @brief          : lcd display method definition
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


#include "lcd.h"

uint8_t state = 0;

static void LCD_Enable(void){
    HAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}


static void LCD_Write4Bit(uint8_t data){
    HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN,
                      (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN,
                      (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN,
                      (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN,
                      (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    LCD_Enable();
}


static void LCD_Write(uint8_t data, uint8_t rs){
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN,
                      rs ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // Nibble alto
    LCD_Write4Bit(data >> 4);

    // Nibble basso
    LCD_Write4Bit(data & 0x0F);
}


void LCD_Command(uint8_t cmd){
    LCD_Write(cmd, 0);

    if (cmd == 0x01 || cmd == 0x02)
        HAL_Delay(2);
}


void LCD_WriteChar(char c){
    LCD_Write((uint8_t)c, 1);
}


void LCD_Print(char *str){
    while (*str)
    {
        LCD_WriteChar(*str);
        str++;
    }
}


void LCD_Clear(void){
    LCD_Command(0x01);
}


void LCD_SetCursor(uint8_t row, uint8_t col){
    uint8_t address;

    if (row == 0)
        address = 0x80 + col;
    else
        address = 0xC0 + col;

    LCD_Command(address);
}


void LCD_Init(void){
    HAL_Delay(50);

    // RS = 0
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);

    // Sequenza di inizializzazione HD44780
    LCD_Write4Bit(0x03);
    HAL_Delay(5);

    LCD_Write4Bit(0x03);
    HAL_Delay(1);

    LCD_Write4Bit(0x03);
    HAL_Delay(1);

    // Passaggio alla modalità 4 bit
    LCD_Write4Bit(0x02);
    HAL_Delay(1);

    // 4 bit, 2 righe, font 5x8
    LCD_Command(0x28);

    // Display ON, cursore OFF, blink OFF
    LCD_Command(0x0C);

    // Clear display
    LCD_Command(0x01);

    // Incremento automatico del cursore
    LCD_Command(0x06);
}


uint8_t LCD_GetState(){
	return state;
}

void LCD_DisplayOn(void){
    LCD_Command(0x0C);
    state = 1;
}

void LCD_DisplayOff(void){
    LCD_Command(0x08);
    state = 0;
}

