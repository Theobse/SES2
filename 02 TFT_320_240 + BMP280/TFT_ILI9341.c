#include "TFT_ILI9341.h"

//
//	VARIABLES
//
SPI_HandleTypeDef *tft_hspi;

static void ILI9341_HAL_Delay(uint32_t ms);
static void ILI9341_SendCommand(uint8_t command);
static void ILI9341_SendCommandAndData(uint8_t command, uint8_t *data, uint32_t lenght);
static void ILI9341_SendToTFT(uint8_t *byte, uint16_t lenght);
static void ILI9341_setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h);

//
//	BASIC FUNCTION - WRITE FOR YOUR MCU
//

void ILI9341_Init(SPI_HandleTypeDef *hspi)
{
	tft_hspi = hspi;

	uint8_t cmd, x, numArgs;
	const uint8_t *addr = initcmd;

	__HAL_SPI_ENABLE(tft_hspi);

#if (ILI9341_USE_HW_RESET == 1)
	HAL_GPIO_WritePin(TFT_RESET_GPIO_Port, TFT_RESET_Pin, GPIO_PIN_RESET);
	ILI9341_HAL_Delay(10);
	HAL_GPIO_WritePin(TFT_RESET_GPIO_Port, TFT_RESET_Pin, GPIO_PIN_SET);
	ILI9341_HAL_Delay(10);
#else
	ILI9341_SendCommand(ILI9341_SWRESET);
	ILI9341_HAL_Delay(150);
#endif

	while ((cmd = *(addr++)) > 0)
	{
		x = *(addr++);
		numArgs = x & 0x7F;
		ILI9341_SendCommandAndData(cmd, (uint8_t*) addr, numArgs);
		addr += numArgs;
		if (x & 0x80)
		{
			ILI9341_HAL_Delay(150);
		}
	}

	ILI9341_SetRotation(ILI9341_ROTATION);
}

void ILI9341_HAL_Delay(uint32_t ms)
{
	HAL_Delay(ms);
}

void ILI9341_SendCommand(uint8_t command)
{
	// 	CS LOW
#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
#endif
	//	DC to Command - DC to LOW
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET);

	//	SEND TO TFT 1 BYTE
	ILI9341_SendToTFT(&command, 1);

	//	CS HIGH
#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
#endif
}

void ILI9341_SendCommandAndData(uint8_t command, uint8_t *data, uint32_t lenght)
{
	// 	CS LOW
#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
#endif

	//	DC to Command - DC to LOW
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET);

	//	SEND TO TFT 1 BYTE
	ILI9341_SendToTFT(&command, 1);

	//	DC to Command - DC to HIGH
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);

	//	SEND TO TFT lenght BYTE
	ILI9341_SendToTFT(data, lenght);

	//	CS HIGH
#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
#endif
}

void ILI9341_SendToTFT(uint8_t *byte, uint16_t lenght)
{
	while (lenght > 0U)
	{
		/* Wait until TXE flag is set to send data */
		if (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_TXE))
		{
			*((__IO uint8_t*) &tft_hspi->Instance->DR) = (*byte);
			byte++;
			lenght--;
		}
	}
	// Wait untill SPI will be ready
	while (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_BSY) != RESET)
	{

	}
}

void ILI9341_WritePixel(uint16_t x, uint16_t y, uint16_t color)
{

	uint8_t DataToTransfer[2];

	if ((x >= 0) && (x < ILI9341_TFTWIDTH) && (y >= 0) && (y < ILI9341_TFTHEIGHT))
	{
		ILI9341_setAddrWindow(x, y, 1, 1);

		DataToTransfer[0] = color >> 8;
		DataToTransfer[1] = color & 0xFF;

		ILI9341_SendCommandAndData(ILI9341_RAMWR, DataToTransfer, 2);
	}
}

void ILI9341_setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h)
{
	uint16_t x2 = (x1 + w - 1), y2 = (y1 + h - 1);

	uint8_t DataToTransfer[4];

	DataToTransfer[0] = x1 >> 8;
	DataToTransfer[1] = x1 & 0xFF;
	DataToTransfer[2] = x2 >> 8;
	DataToTransfer[3] = x2 & 0xFF;
	ILI9341_SendCommandAndData(ILI9341_CASET, DataToTransfer, 4);

	DataToTransfer[0] = y1 >> 8;
	DataToTransfer[1] = y1 & 0xFF;
	DataToTransfer[2] = y2 >> 8;
	DataToTransfer[3] = y2 & 0xFF;
	ILI9341_SendCommandAndData(ILI9341_PASET, DataToTransfer, 4);
}

void ILI9341_ClearDisplay(void)
{
	uint32_t Lenght = ILI9341_TFTWIDTH * ILI9341_TFTHEIGHT;

	ILI9341_setAddrWindow(0, 0, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
	ILI9341_SendCommand(ILI9341_RAMWR);

#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
#endif
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);

	while (Lenght > 0U)
	{
		/* Wait until TXE flag is set to send data */
		if (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_TXE))
		{
			*((__IO uint8_t*) &tft_hspi->Instance->DR) = (ILI9341_WHITE >> 8);

			while (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_TXE) != SET)
			{

			}
			*((__IO uint8_t*) &tft_hspi->Instance->DR) = (ILI9341_WHITE & 0xFF);

			Lenght--;
		}
	}

	while (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_BSY) != RESET)
	{

	}

#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
#endif
}

void ILI9341_ClearDisplayColor(uint16_t Color)
{

	uint32_t Lenght = ILI9341_TFTWIDTH * ILI9341_TFTHEIGHT;

	ILI9341_setAddrWindow(0, 0, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
	ILI9341_SendCommand(ILI9341_RAMWR);

#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
#endif
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);

	while (Lenght > 0U)
	{
		/* Wait until TXE flag is set to send data */
		if (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_TXE))
		{
			*((__IO uint8_t*) &tft_hspi->Instance->DR) = (Color >> 8);

			while (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_TXE) != SET)
			{

			}
			*((__IO uint8_t*) &tft_hspi->Instance->DR) = (Color & 0xFF);

			Lenght--;
		}
	}

	while (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_BSY) != RESET)
	{

	}

#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
#endif
}

void ILI9341_ClearArea(uint16_t xStart, uint16_t yStart, uint16_t xStop, uint16_t yStop, uint16_t color)
{
	uint32_t Lenght = (abs(xStop - xStart + 1)) * (abs(yStop - yStart + 1));

	ILI9341_setAddrWindow(xStart, yStart, xStop, yStop);
	ILI9341_SendCommand(ILI9341_RAMWR);

#if (ILI9341_USE_CS == 1)
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
#endif

	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);

	while (Lenght > 0U)
		{
			/* Wait until TXE flag is set to send data */
			if (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_TXE))
			{
				*((__IO uint8_t*) &tft_hspi->Instance->DR) = (color >> 8);

				while (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_TXE) != SET)
				{

				}
				*((__IO uint8_t*) &tft_hspi->Instance->DR) = (color & 0xFF);

				Lenght--;
			}
		}

		while (__HAL_SPI_GET_FLAG(tft_hspi, SPI_FLAG_BSY) != RESET)
		{

		}

	#if (ILI9341_USE_CS == 1)
		HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
	#endif
}

void ILI9341_SetRotation(uint8_t rotation)
{
	if (rotation > 3) return; // can't be higher than 3

	switch (rotation)
	{
	case 0:
		rotation = (MADCTL_MX | MADCTL_BGR);
		break;

	case 1:
		rotation = (MADCTL_MV | MADCTL_BGR);
		break;

	case 2:
		rotation = (MADCTL_MY | MADCTL_BGR);
		break;

	case 3:
		rotation = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
		break;
	}

	ILI9341_SendCommandAndData(ILI9341_MADCTL, &rotation, 1);
}

