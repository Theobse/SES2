/*
 * button_window.c
 *
 *  Created on: 24 sty 2023
 *      Author: MJ
 */

#include "main.h"
#include "button_window.h"

void button_window_init(button_window_t *button, uint16_t x, uint16_t y, uint16_t width, uint16_t height, char *t)
{
	button -> X_start = x;
	button -> X_width = width;
	button -> X_end = x + width;
	button -> Y_start = y;
	button -> Y_height = height;
	button -> Y_end = y + height;
	button -> text = t;
}


