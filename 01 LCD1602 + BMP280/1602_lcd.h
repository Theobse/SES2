/*
 * 1602_lcd.h
 *
 *  Created on: Jan 11, 2023
 *      Author: MJ
 */

#ifndef INC_1602_LCD_H_
#define INC_1602_LCD_H_

//
//	DEFINES PORTS, PINS
//
#define LCD_REGISTERSELECT_PIN	GPIO_PIN_1
#define LCD_READWRITE_PIN		GPIO_PIN_2
#define LCD_ENABLE_PIN			GPIO_PIN_7

#define LCD_GPIO				GPIOB
#define LCD_D4_PIN				GPIO_PIN_3
#define LCD_D5_PIN				GPIO_PIN_4
#define LCD_D6_PIN				GPIO_PIN_5
#define LCD_D7_PIN				GPIO_PIN_6

//
//	DEFINES
//
#define LCD_INIT_WORD 						0x03
#define LCD_CLEAR							0x01
#define LCD_RETURN_HOME						0x02
#define LCD_START_DDRAM						0x80

#define LCD_FUNCTION_SET			   		0x20
#define LCD_4_BITS_MODE 					0
#define LCD_8_BITS_MODE 					0x10
#define LCD_1_LINE_MODE						0
#define LCD_2_LINE_MODE 					0x08
#define LCD_5_8_MODE						0
#define LCD_5_10_MODE						0x04

#define LCD_DISPLAY_OFF_ON					0x08
#define LCD_DISPLAY_OFF						0x00
#define LCD_DISPLAY_ON						0x04
#define LCD_CURSOR_OFF						0x00
#define LCD_CURSOR_ON						0x02
#define LCD_BLINK_OFF						0x00
#define LCD_BLINK_ON						0x01

#define LCD_ENTRY_MODE						0x04
#define LCD_ENTRY_MODE_MOVE_LEFT_CURSOR 	0x00
#define LCD_ENTRY_MODE_MOVE_RIGHT_CURSOR	0x02
#define LCD_ENTRY_MODE_SHIFT_DISPLAY		0x01

void LCD_init(void);
void LCD_sendCommand(uint8_t dataToSend);
void LCD_sendData(uint8_t dataToSend);
void LCD_sendText(char *textToSend);
void LCD_clearDisplay(void);
void LCD_setAddress(uint8_t x, uint8_t y);
void LCD_set1Line();
void LCD_set2Line();

#endif /* INC_1602_LCD_H_ */
