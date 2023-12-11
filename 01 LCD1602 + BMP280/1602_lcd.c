/*
 * 1602_lcd.c
 *
 *  Created on: Jan 11, 2023
 *      Author: MJ
 */

#include "main.h"
#include "1602_lcd.h"

static void LCD_writeNibble(uint8_t dataToSend);
static uint8_t LCD_readStatus(void);
static uint8_t LCD_readNibble(void);

void LCD_init(void)
{
	HAL_GPIO_WritePin(LCD_GPIO, LCD_REGISTERSELECT_PIN | LCD_READWRITE_PIN | LCD_ENABLE_PIN, GPIO_PIN_RESET);

	//	send three times 0x03
	HAL_Delay(40);
	LCD_writeNibble(0x03);

	HAL_Delay(5);
	LCD_writeNibble(0x03);

	HAL_Delay(1);
	LCD_writeNibble(0x03);

	//	set 4 bit mode
	LCD_writeNibble(0x02);

	HAL_Delay(1);

	//	set: 2-line mode, 5 x 7 dots
	LCD_sendCommand(LCD_FUNCTION_SET | LCD_4_BITS_MODE | LCD_2_LINE_MODE | LCD_5_8_MODE);

	//	display off
	LCD_sendCommand(LCD_DISPLAY_OFF_ON | LCD_DISPLAY_OFF);

	//	clear display
	LCD_sendCommand(LCD_CLEAR);

	//	set cursor to right moving
	LCD_sendCommand(LCD_ENTRY_MODE | LCD_ENTRY_MODE_MOVE_RIGHT_CURSOR);

	//	turn on LCD
	LCD_sendCommand(LCD_DISPLAY_OFF_ON | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINK_ON);
}

static void LCD_writeNibble(uint8_t dataToSend)
{
	//	set ENABLE to HIGH
	HAL_GPIO_WritePin(LCD_GPIO, LCD_ENABLE_PIN, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LCD_GPIO, LCD_D4_PIN, (dataToSend & 0x01));
	HAL_GPIO_WritePin(LCD_GPIO, LCD_D5_PIN, (dataToSend & 0x02));
	HAL_GPIO_WritePin(LCD_GPIO, LCD_D6_PIN, (dataToSend & 0x04));
	HAL_GPIO_WritePin(LCD_GPIO, LCD_D7_PIN, (dataToSend & 0x08));

	//	set ENABLE to LOW -> data from 4 pins saved into memory
	HAL_GPIO_WritePin(LCD_GPIO, LCD_ENABLE_PIN, GPIO_PIN_RESET);
}

void LCD_sendCommand(uint8_t dataToSend)
{
	HAL_GPIO_WritePin(LCD_GPIO, LCD_REGISTERSELECT_PIN | LCD_READWRITE_PIN, GPIO_PIN_RESET);

	//	first send older bits
	LCD_writeNibble(dataToSend >> 4);
	LCD_writeNibble(dataToSend & 0x0F);

	while (LCD_readStatus() & 0x80);
}

static uint8_t LCD_readStatus(void)
{
	uint8_t status = 0;

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LCD_GPIO, LCD_REGISTERSELECT_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO, LCD_READWRITE_PIN, GPIO_PIN_SET);

	status = (LCD_readNibble() << 4);
	status |= LCD_readNibble();

	GPIO_InitStruct.Pin = LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

	return status;
}
static uint8_t LCD_readNibble(void)
{
	uint8_t reg = 0;

	HAL_GPIO_WritePin(LCD_GPIO, LCD_ENABLE_PIN, GPIO_PIN_SET);
	reg = HAL_GPIO_ReadPin(LCD_GPIO, LCD_D4_PIN);
	reg |= (HAL_GPIO_ReadPin(LCD_GPIO, LCD_D5_PIN) << 1);
	reg |= (HAL_GPIO_ReadPin(LCD_GPIO, LCD_D6_PIN) << 2);
	reg |= (HAL_GPIO_ReadPin(LCD_GPIO, LCD_D7_PIN) << 3);
	HAL_GPIO_WritePin(LCD_GPIO, LCD_ENABLE_PIN, GPIO_PIN_RESET);

	return reg;
}

void LCD_sendData(uint8_t dataToSend)
{
	HAL_GPIO_WritePin(LCD_GPIO, LCD_REGISTERSELECT_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_GPIO, LCD_READWRITE_PIN, GPIO_PIN_RESET);

	LCD_writeNibble(dataToSend >> 4);
	LCD_writeNibble(dataToSend & 0x0F);

	while(LCD_readStatus() & 0x80);
}
void LCD_sendText(char *textToSend)
{
	HAL_GPIO_WritePin(LCD_GPIO, LCD_REGISTERSELECT_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_GPIO, LCD_READWRITE_PIN, GPIO_PIN_RESET);

	while (*textToSend)
	{
		LCD_sendData((uint8_t) *textToSend++);
	}
}
void LCD_clearDisplay(void)
{
	LCD_sendCommand(LCD_CLEAR);
	HAL_Delay(2);

	LCD_sendCommand(LCD_RETURN_HOME);
	HAL_Delay(2);
}

void LCD_setAddress(uint8_t x, uint8_t y)
{
	//	Display position	 1	2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
	//	DDRAM address		00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
	//	DDRAM address		40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F

	LCD_sendCommand(LCD_START_DDRAM + x + 0x40 * y);
}

void LCD_set1Line()
{
	LCD_setAddress(0, 0);
}

void LCD_set2Line()
{
	LCD_setAddress(0, 1);
}
