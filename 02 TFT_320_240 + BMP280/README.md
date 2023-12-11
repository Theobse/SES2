## Introduction
Project uses BMP280 sensor and TFT 320 x 240 to present temperature and pressure.
Application uses touch to navigate the screen by interrupt. 

## Foto
![IMG-0044](https://user-images.githubusercontent.com/119056338/215508580-f31f81e7-e176-4e2e-9ba0-454e84ec7c1a.jpg)

## Steps
1. Project uses I2C interface form HAL library so set up interface and add handler to main.c -> (BMP280_init(&BMP280, &hi2c2, 0x76)).
2. Change port and pinout for your connections in: TFT_ILI9341.h and XPT2046.h. 
3. Configure SPI interfaces for display. App needs two SPI interfaces. First for display data and secound to use touch module form TFT.
Add handler SPI1 and SPI2 to init functions in main.c
4. Set up pin for interruption. Remember to detect <b>falling</b> slope!
5. Set up font in main.c
