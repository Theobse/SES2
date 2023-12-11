/*
 * bmp280.c
 *
 *  Created on: Nov 29, 2022
 *      Author: MJ
 */

#include "main.h"
#include "bmp280.h"

static uint8_t BMP280_read8 (BMP280_t *Bmp, uint8_t Register);
static uint16_t BMP280_read16(BMP280_t *Bmp, uint8_t Register);
static uint32_t BMP280_read24(BMP280_t *Bmp, uint8_t Register);

static void BMP280_write8(BMP280_t *Bmp, uint8_t Register, uint8_t Value);

static uint32_t BMP280_readTemperatureRaw(BMP280_t *Bmp);
static uint32_t BMP280_readPressureRaw(BMP280_t *Bmp);

static float BMP280_readTemperature (BMP280_t *Bmp);

uint8_t BMP280_init(BMP280_t *Bmp, I2C_HandleTypeDef *I2c, uint8_t address)
{
	uint8_t chipID;

	Bmp -> bmp280I2c = I2c;
	Bmp -> bmp280AddressDevice = address;

	chipID = BMP280_read8(Bmp, BMP280_CHIPID);

	if(chipID != BMP_280_DEFAULT_ID) return 1;	//	default ID
	else
	{
		Bmp -> t1 = BMP280_read16(Bmp, BMP280_DIG_T1);
		Bmp -> t2 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_T2);
		Bmp -> t3 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_T2);

		Bmp -> p1 = BMP280_read16(Bmp, BMP280_DIG_P1);
		Bmp -> p2 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P2);
		Bmp -> p3 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P3);
		Bmp -> p4 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P4);
		Bmp -> p5 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P5);
		Bmp -> p6 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P6);
		Bmp -> p7 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P7);
		Bmp -> p8 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P8);
		Bmp -> p9 = (int16_t) BMP280_read16(Bmp, BMP280_DIG_P9);

		BMP280_write8(Bmp, BMP280_CONTROL, BMP280_NORMALMODE);

		BMP280_setMode(Bmp, BMP280_NORMALMODE);
		BMP280_setPressureOversampling(Bmp, BMP280_ULTRAHIGHRES);
		BMP280_setTemperatureResolution(Bmp, BMP280_TEMPERATURE_20BIT);

		return 0;
	}
}

uint8_t BMP280_read8(BMP280_t *Bmp, uint8_t reg)
{
	uint8_t value;

	HAL_I2C_Mem_Read(Bmp -> bmp280I2c, ((Bmp ->bmp280AddressDevice) << 1), reg, 1, &value, 1, BMP280_I2C_TIMEOUT);

	return value;
}

uint16_t BMP280_read16(BMP280_t *Bmp, uint8_t reg)
{
	uint8_t value[2];

	HAL_I2C_Mem_Read(Bmp -> bmp280I2c, ((Bmp -> bmp280AddressDevice) << 1), reg, 1, value, 2, BMP280_I2C_TIMEOUT);

	return ((value[1] << 8) | value[0]);
}

uint32_t BMP280_read24(BMP280_t *Bmp, uint8_t reg)
{
	uint8_t Value[3];

	HAL_I2C_Mem_Read(Bmp -> bmp280I2c, ((Bmp -> bmp280AddressDevice) << 1), reg, 1, Value, 3, BMP280_I2C_TIMEOUT);

	return ((Value[0] << 16) | (Value[1] << 8) | Value[2]);
}

uint32_t BMP280_readTemperatureRaw(BMP280_t *Bmp)	//	RAW DATA
{
	uint32_t tmp;

	tmp = BMP280_read24(Bmp, BMP280_TEMPDATA);
	tmp >>= 4;

	return tmp;
}
uint32_t BMP280_readPressureRaw(BMP280_t *Bmp)
{
	uint32_t tmp;

	tmp = BMP280_read24(Bmp, BMP280_PRESSUREDATA);
	tmp >>= 4;

	return tmp;
}

void BMP280_write8(BMP280_t *Bmp, uint8_t reg, uint8_t value)
{
	HAL_I2C_Mem_Write(Bmp -> bmp280I2c, ((Bmp -> bmp280AddressDevice) << 1), reg, 1, &value, 1, BMP280_I2C_TIMEOUT);
}

void BMP280_setMode(BMP280_t *Bmp, uint8_t mode)
{
	//	bit7 bit6 bit5 	bit4 bit3 bit2 	bit1 bit0
	//	osrs_t[2:0]		osrs_p[2:0]		mode[1:0]
	if(mode > 3) mode = 3;
	uint8_t tmp;

	tmp = BMP280_read8(Bmp, BMP280_CONTROL);
	tmp &= 0xFC;		//	mask 1111 1100
	tmp |= mode & 0x03;	//	mask 0000 0011

	BMP280_write8(Bmp, BMP280_CONTROL, tmp);
}

void BMP280_setPressureOversampling(BMP280_t *Bmp, uint8_t oversampling)
{
	//	bit7 bit6 bit5 	bit4 bit3 bit2 	bit1 bit0
	//	osrs_t[2:0]		osrs_p[2:0]		mode[1:0]
	if (oversampling > 5) oversampling = 5;

	uint8_t tmp;

	tmp = BMP280_read8(Bmp, BMP280_CONTROL);
	tmp &= 0xE3;						//	mask 1110 0011
	tmp |= (oversampling <<2) & 0x1C;	//	mask 0001 1100

	BMP280_write8(Bmp, BMP280_CONTROL, tmp);
}

void BMP280_setTemperatureResolution(BMP280_t *Bmp, uint8_t resolution)
{
	//	bit7 bit6 bit5 	bit4 bit3 bit2 	bit1 bit0
	//	osrs_t[2:0]		osrs_p[2:0]		mode[1:0]
	if (resolution > 5) resolution = 5;

	uint8_t tmp;

	tmp = BMP280_read8(Bmp, BMP280_CONTROL);
	tmp &= 0x1F;					//	mask 0001 1111
	tmp |= (resolution <<5) & 0xE0;	//	mask 1110 0000

	BMP280_write8(Bmp, BMP280_CONTROL, tmp);
}

float BMP280_readTemperature (BMP280_t *Bmp)
{
	//	from data sheet
	int32_t var1, var2, T;
	int32_t adc_T = BMP280_readTemperatureRaw(Bmp);

	var1 = ((((adc_T>>3) - ((int32_t)(Bmp -> t1)<<1))) * ((int32_t)(Bmp -> t2))) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)(Bmp -> t1))) * ((adc_T>>4) - ((int32_t)(Bmp -> t1)))) >> 12) *	((int32_t)(Bmp -> t3))) >> 14;

	Bmp -> t_fine = var1 + var2;

	T = ((Bmp -> t_fine) * 5 + 128) >> 8;
	return (float)(T / 100.0);
}

uint8_t BMP280_readTemperatureAndPressure(BMP280_t *Bmp, float *temperature, float *pressure)
{
	//	from data sheet
	*temperature = BMP280_readTemperature(Bmp);

	int32_t var1, var2;
	uint32_t p;

	var1 = (((int32_t)(Bmp -> t_fine))>>1) - (int32_t) 64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)(Bmp -> p6));
	var2 = var2 + ((var1*((int32_t)(Bmp -> p5)))<<1);
	var2 = (var2>>2)+(((int32_t)(Bmp -> p4))<<16);
	var1 = ((((Bmp -> p3) * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)(Bmp -> p2)) * var1)>>1))>>18;
	var1 = ((((32768+var1)) * ((int32_t)(Bmp -> p1)))>>15);

	if (var1 == 0) return 1;	// avoid exception caused by division by zero

	int32_t adc_P = BMP280_readPressureRaw(Bmp);

	p = (((uint32_t)(((int32_t)1048576) - adc_P) - (var2>>12))) * 3125;

	if (p < 0x80000000) p = (p << 1) / ((uint32_t) var1);
	else p = (p / (uint32_t) var1) * 2;

	var1 = (((int32_t)(Bmp -> p9)) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
	var2 = (((int32_t)(p>>2)) * ((int32_t)(Bmp -> p8)))>>13;

	p = (uint32_t)((int32_t)p + ((var1 + var2 + (Bmp -> p7)) >> 4));

	*pressure = (float)(p / 100.0);

	return 0;
}
uint8_t BMP280_readMode(BMP280_t *Bmp)
{
	uint8_t status = (BMP280_read8(Bmp, BMP280_CONTROL) & 0x03);
	return status;
}
