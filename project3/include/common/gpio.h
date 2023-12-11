/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file gpio.h
 * @brief This file includes function declarations of functions to initialize GPIO pin/port.
 * @date December 01, 2017
 *
 * long description - The gpio.h file includes functions declarations of functions to -
 *                      1) initialize GPIO for nrf module(GPIO_nrf_init())
 *                      2) initialize GPIO for on-board led(GPIO_led_init())
 *
 ***************************************************************************************************/

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_

#include "MKL25Z4.h"
#include "project3.h"

#define RED_LED_INIT		(GPIOB->PDDR |= 1 << 18)	//set port B pin 18 direction as output
#define GREEN_LED_INIT		(GPIOB->PDDR |= 1 << 19)	//set port B pin 19 direction as output
#define BLUE_LED_INIT		(GPIOD->PDDR |= 1 << 1)		//set port D pin 1 direction as output

#define RED_LED_ON			(GPIOB->PCOR |= 1 << 18)	//port B pin 18 set as pin is active low
#define GREEN_LED_ON		(GPIOB->PCOR |= 1 << 19)	//port B pin 19 set as pin is active low
#define BLUE_LED_ON			(GPIOD->PCOR |= 1 << 1)		//port D pin 1 set as pin is active low

#define RED_LED_OFF			(GPIOB->PSOR |= 1 << 18)	//port B pin 18 clear as pin is active low
#define GREEN_LED_OFF		(GPIOB->PSOR |= 1 << 19)	//port B pin 19 clear as pin is active low
#define BLUE_LED_OFF		(GPIOD->PSOR |= 1 << 1)		//port D pin 1 clear as pin is active low

#define RED_LED_TOGGLE		(GPIOB->PTOR |= 1 << 18)	//port B pin 18 toggle
#define GREEN_LED_TOGGLE	(GPIOB->PTOR |= 1 << 19)	//port B pin 19 toggle
#define BLUE_LED_TOGGLE		(GPIOD->PTOR |= 1 << 1)		//port D pin 1 toggle

/********************************** GPIO_nrf_init() **********************************************************
 *
 * @name   -  GPIO_nrf_init()
 * @brief  -  function to initialize GPIO for nrf module.
 * @param  -  none
 *
 * long description - This function initializes GPIO for nrf module
 *
 * @return -  void
 *
 ********************************************************************************************************/

/************************************ GPIO_nrf_init() function declaration ***********************************/

void GPIO_nrf_init();

/********************************** GPIO_led_init() **********************************************************
 *
 * @name   -  GPIO_led_init()
 * @brief  -  function to initialize GPIO for on-board LED.
 * @param  -  none
 *
 * long description - This function initializes GPIO for on-board LED.
 *
 * @return -  void
 *
 *************************************************************************************************************/

/************************************ GPIO_led_init() function declaration ***********************************/

void GPIO_led_init();



#endif /* SOURCES_GPIO_H_ */
