/*
 * libLCD1602.c
 *
 *  Created on: Jun 13, 2017
 *      Author: romanp
 */
#include "stm32f0xx_hal.h"
#include "main.h"



#define LCD_OUT LCD_D4_GPIO_Port->ODR
#define LCD_PIN_MASK (LCD_E_Pin | LCD_RS_Pin | LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin)

//---Функция задержки---//
void delay(int a)
{
	HAL_Delay(1);
	/*
    volatile int i = 0;
    volatile int f = 0;
    while(f < a)
    {
        while(i<60)
            {i++;}
        f++;
    }
    */
}

//---Нужная функция для работы с дисплеем, по сути "дергаем ножкой" EN---//
void PulseLCD()
{
//    LCD_OUT &= ~LCD_E_Pin;
//    delay(220);
//    LCD_OUT |= LCD_E_Pin;
//    delay(220);
//    LCD_OUT &= (~LCD_E_Pin);
//    delay(220);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, 0);
	delay(220);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, 1);
	delay(220);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, 0);
	delay(220);
}

//---Отсылка байта в дисплей---//
void SendByte(char ByteToSend, int IsData)
{
    LCD_OUT &= (~LCD_PIN_MASK);
    LCD_OUT |= (ByteToSend & 0xF0);

    if (IsData == 1){
    	//LCD_OUT |= LCD_RS_Pin;
    	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 1);
    }
    else{
    	//LCD_OUT &= ~LCD_RS_Pin;
    	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 0);
    }

    PulseLCD();
    LCD_OUT &= (~LCD_PIN_MASK);
    LCD_OUT |= ((ByteToSend & 0x0F) << 4);

    if (IsData == 1){
    	//LCD_OUT |= LCD_RS_Pin;
    	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 1);
    }
    else{
    	//LCD_OUT &= ~LCD_RS_Pin;
    	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, 0);
    }
    PulseLCD();
}

//---Установка позиции курсора---//
void Cursor(char Row, char Col)
{
   char address;
   if (Row == 0)
   address = 0;
   else
   address = 0x40;
   address |= Col;
   SendByte(0x80 | address, 0);
}

//---Очистка дисплея---//
void ClearLCDScreen(void)
{
    SendByte(0x01, 0);
    SendByte(0x02, 0);
}

//---Инициализация дисплея---//
void InitializeLCD(void)
{
    LCD_OUT &= ~(LCD_PIN_MASK);
    delay(32000);
    delay(32000);
    delay(32000);
    LCD_OUT &= ~LCD_RS_Pin;
    LCD_OUT &= ~LCD_E_Pin;
    LCD_OUT = 0x20;
    PulseLCD();
    SendByte(0x28, 0);
    SendByte(0x0E, 0);
    SendByte(0x06, 0);
}

//---Печать строки---//
void PrintStr(char *Text)
{
    char *c;
    c = Text;
    while ((c != 0) && (*c != 0))
    {
        SendByte(*c, 1);
        c++;
    }
}

