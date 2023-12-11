#include "main.h"
#include "XPT2046.h"
#include "TFT_ILI9341.h"
#include "GFX.h"

//
//	DEFINES
//
#define TOUCH_ROTATION ILI9341_ROTATION
#define MAX_SAMPLES 10
#define SAMPLE_INTERVAL 5

//
//	VARIABLES
//
static uint8_t ChannelSettingsX, ChannelSettingsY;
static SPI_HandleTypeDef *Xpt2046SpiHandler;
static IRQn_Type Xpt2046IrqnnHander;
static uint8_t SendBuffer[5], ReceiveBuffer[5];
volatile XPT2046_Status TouchState;
static uint8_t CalibrationMode;
static uint16_t TouchSamples[2][MAX_SAMPLES];
static uint16_t SampleCounter = 0;
static uint32_t SampleTimer = 0;

//
//	CALIBRATION DATA USED FOR EACH CORDS CALCULATION
//
#if (TOUCH_ROTATION == 0)
CalibrationData_t CalibrationData = {-.0009337, -.0636839, 250.342, -.0889775, -.00118110, 356.538}; // default calibration data
#endif
#if (TOUCH_ROTATION == 1)
CalibrationData_t CalibrationData = {-.0885542, .0016532, 349.800, .0007309, .06543699, -15.290}; // default calibration data
#endif
#if (TOUCH_ROTATION == 2)
CalibrationData_t CalibrationData = {.0006100, .0647828, -13.634, .0890609, .0001381, -35.73}; // default calibration data
#endif
#if (TOUCH_ROTATION == 3)
CalibrationData_t CalibrationData = {.0902216, .0006510, -38.657, -.0010005, -.0667030, 258.08}; // default calibration data
#endif

//
//	FUNCTIONS
//
void XPT2046_Init(SPI_HandleTypeDef *hspi, IRQn_Type touchirqn)
{
	Xpt2046SpiHandler = hspi;
	Xpt2046IrqnnHander = touchirqn;

	TouchState = XPT2046_IDLE;

#if(XPT2046_USE_CS == 1)
	HAL_GPIO_WritePin(TOUCH_CS_Port, TOUCH_CS_Pin, GPIO_PIN_SET);
#endif
	//
	// Prepare Send Buffer
	//
	//		FIRST COMMAND			SECOND COMMAND
	//     (     X    )           (     Y 	 )
	// (000 10010)(000 00000) (000 11010)(000 00000) (00000000)
	//	SendBuffer
	// (    0    )(    1    ) (    2    )(    3    ) (    4   )
		ChannelSettingsX = 0b10010000;
		ChannelSettingsY = 0b11010000;

		SendBuffer[0] = 0x80;	// Clear settings in IC
		XPT2046_GetRawData();	// Send clearing command
		HAL_Delay(1); 			// Wait for clear

		// Fulfill Send Buffer with Channel control bytes
		SendBuffer[0] = (ChannelSettingsX>>3);	//	Settings X
		SendBuffer[1] = (ChannelSettingsX<<5);
		SendBuffer[2] = (ChannelSettingsY>>3);	//	Settings Y
		SendBuffer[3] = (ChannelSettingsY<<5);
		SendBuffer[4] = 0;
}

void XPT2046_GetRawData(void)
{
#if(XPT2046_USE_CS == 1)
	HAL_GPIO_WritePin(TOUCH_CS_Port, TOUCH_CS_Pin, GPIO_PIN_RESET); 	//	CS ACTTIVE
#endif

	HAL_SPI_TransmitReceive(Xpt2046SpiHandler, SendBuffer, ReceiveBuffer, 5, XPT2046_SPI_TIMEOUT);

#if(XPT2046_USE_CS == 1)
	HAL_GPIO_WritePin(TOUCH_CS_Port, TOUCH_CS_Pin, GPIO_PIN_SET);	//	CS IDLE
#endif
}

void XPT2046_ReadRawData(uint16_t *x, uint16_t *y)
{
	*x = (uint16_t)((ReceiveBuffer[1] << 8) | (ReceiveBuffer[2]));
	*y = (uint16_t)((ReceiveBuffer[3] << 8) | (ReceiveBuffer[4]));
}

void XPT2046_ReadTouchPoint(uint16_t *x, uint16_t *y)
{
	uint16_t tempX, tempY;
	XPT2046_ReadRawData(&tempX, &tempY);

	if(CalibrationMode == 0)
	{
		*x = CalibrationData.alpha_x * tempX + CalibrationData.beta_x * tempY + CalibrationData.delta_x;
		*y = CalibrationData.alpha_y * tempX + CalibrationData.beta_y * tempY + CalibrationData.delta_y;
	}
	else
	{
		*x = tempX;
		*y = tempY;
	}
}

void XPT2046_Task(void)
{
	switch(TouchState)
	{
	case XPT2046_IDLE:
		break;

	case XPT2046_PRESAMPLING:
		if((HAL_GetTick() - SampleTimer) > SAMPLE_INTERVAL)
		{
			XPT2046_GetRawData();
			XPT2046_ReadTouchPoint(&TouchSamples[0][SampleCounter], &TouchSamples[1][SampleCounter]);
			SampleCounter++;

			if(SampleCounter == MAX_SAMPLES)
			{
				SampleCounter = 0;
				TouchState = XPT2046_TOUCHED;
			}

			if(HAL_GPIO_ReadPin(TOUCH_IRQ_Port, TOUCH_IRQ_Pin) == GPIO_PIN_SET)
			{
				TouchState = XPT2046_RELEASED;
			}

			SampleTimer = HAL_GetTick();
		}

		break;

	case XPT2046_TOUCHED:
		if((HAL_GetTick() - SampleTimer) > SAMPLE_INTERVAL)
		{
			XPT2046_GetRawData();
			XPT2046_ReadTouchPoint(&TouchSamples[0][SampleCounter], &TouchSamples[1][SampleCounter]);
			SampleCounter++;
			SampleCounter %= MAX_SAMPLES;

			if(HAL_GPIO_ReadPin(TOUCH_IRQ_Port, TOUCH_IRQ_Pin) == GPIO_PIN_SET)
			{
				TouchState = XPT2046_RELEASED;
			}

			SampleTimer = HAL_GetTick();

		}
		break;

	case XPT2046_RELEASED:
		TouchState = XPT2046_IDLE;
		SampleCounter = 0;

		//	Clearing IRQ's port and pin because we shout down IRQ earlier
		while(HAL_NVIC_GetPendingIRQ(Xpt2046IrqnnHander))
		{
			__HAL_GPIO_EXTI_CLEAR_IT(TOUCH_IRQ_Pin);
			HAL_NVIC_ClearPendingIRQ(Xpt2046IrqnnHander);

		}
		HAL_NVIC_EnableIRQ(Xpt2046IrqnnHander);
		break;
	}
}

void XPT2046_IRQ(void)
{
	//	Disable IRQ
	HAL_NVIC_DisableIRQ(Xpt2046IrqnnHander);

	TouchState = XPT2046_PRESAMPLING;
}

uint8_t XPT2046_IsTouch(void)
{
	if(TouchState == XPT2046_TOUCHED) return 1;
	return 0;
}

void XPT2046_TouchPoint(uint16_t *x, uint16_t *y)
{
	uint32_t AverageX = 0, AverageY = 0;

	for(uint8_t i = 0; i < MAX_SAMPLES; i++)
	{
		AverageX += TouchSamples[0][i];
		AverageY += TouchSamples[1][i];
	}

	*x = AverageX / MAX_SAMPLES;
	*y = AverageY / MAX_SAMPLES;

}
