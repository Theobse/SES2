## Introduction
Project uses BMP280 sensor and LCD1602 to present temperature and pressure.

## Foto
![IMG-0046](https://user-images.githubusercontent.com/119056338/215495836-b59fd105-3f9a-44ea-b3e8-6d4b0af668a5.JPG)

## Steps
1. Project uses I2C interface form HAL library so set up interface and add handler to main.c -> (BMP280_init(&BMP280, &hi2c2, 0x76)).
2. Change port and pinout for your connections in 1602_lcd.h.
