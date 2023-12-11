/*
 * measure_display.c
 *
 *  Created on: 24 sty 2023
 *      Author: MJ
 */

#include "main.h"
#include "bmp280.h"
#include "measure_display.h"
#include "TFT_ILI9341.h"
#include "GFX.h"
#include "GFX_EnhancedFonts.h"
#include "buttom_window.h"
#include "XPT2046.h"

//
//	VARIABLES
//
typedef enum
{
	MEASURE_STOP,
	MEASURE_START
} MeasureDisplayStatus_t;

volatile MeasureDisplayStatus_t MD_state = MEASURE_STOP;
static Buttom_window_t buttomSTART;
static Buttom_window_t buttomSTOP;
static BMP280_t	*sensor;

static void draw_strings(void);
static void draw_buttoms(void);

//
//	FUNCTIONS
//
void TFT_measure_init(BMP280_t *bmp280)
{
	MD_state = MEASURE_STOP;
	ILI9341_ClearDisplay();

	draw_buttoms();
	draw_strings();

	sensor = bmp280;
}

void draw_buttoms()
{
	//	draw START buttom
	buttom_window_init(&buttomSTART, 32, 30, 112, 30, "START");
	GFX_DrawRectangle(buttomSTART.X_start, buttomSTART.Y_start, buttomSTART.X_width, buttomSTART.Y_height, ILI9341_BLACK);

	//	draw STOP buttom
	buttom_window_init(&buttomSTOP, 176, 30, 112, 30, "STOP");
	GFX_DrawRectangle(buttomSTOP.X_start, buttomSTART.Y_start, buttomSTOP.X_width, buttomSTOP.Y_height, ILI9341_BLACK);

}

static void draw_strings(void)
{
	// puts strings
	EF_PutString((uint8_t *) (buttomSTART.text), buttomSTART.X_start, buttomSTART.Y_start, ILI9341_BLACK, BG_TRANSPARET, ILI9341_BLACK);
	EF_PutString((uint8_t *) (buttomSTOP.text), buttomSTOP.X_start, buttomSTART.Y_start, ILI9341_BLACK, BG_TRANSPARET, ILI9341_BLACK);
}

void TFT_MD_task()
{
	if(XPT2046_IsTouch() == 1)
	{
		uint16_t x, y;
		XPT2046_ReadTouchPoint(&x, &y);

		//	check STOP buttom
		if((x >= buttomSTOP.X_start) && (x <= buttomSTOP.X_end) && (y >= buttomSTOP.Y_start) && (y <= buttomSTOP.Y_end))
		{
			BMP280_setMode(sensor, BMP280_SLEEPMODE);
		}

		//	check START buttom
		if((x >= buttomSTART.X_start) && (x <= buttomSTART.X_end) && (y >= buttomSTART.Y_start) && (y <= buttomSTART.Y_end))
		{
			BMP280_setMode(sensor, BMP280_NORMALMODE);
		}
	}
}
