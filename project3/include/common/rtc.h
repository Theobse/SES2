/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file rtc.h
 * @brief This header file includes RTC function declarations
 * @date November 29, 2017
 *
 * long description - The rtc.h file includes function declarations of functions to -
 *                      1) initialize RTC (RTC_init())
 *                      2) handle RTC_Seconds Interrupt (RTC_Seconds_IRQHandler())
 *                      3) read RTC Timer Seconds Register (RTC_read())
 *
 *
 ***************************************************************************************************/

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include <stdint.h>
#include "MKL25Z4.h"
#include "project3.h"


/********************************** RTC_init() ********************************************************
 *
 * @name   -  RTC_init()
 * @brief  -  function to initialize RTC
 * @param  -  none
 *
 * long description - This function configures RTC control and status registers, sets clock,oscillator,
 *                    and clock pins, enables seconds interrupt, selects clock mode.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/********************************* RTC_init() function declaration ************************************/

void RTC_init(void);

/********************************** RTC_Seconds_IRQHandler() ********************************************************
 *
 * @name   -  RTC_Seconds_IRQHandler()
 * @brief  -  function to handle RTC seconds interrupt
 * @param  -  none
 *
 * long description - This function handles RTC seconds interrupt and logs HEARTBEAT after every second.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/********************************* RTC_Seconds_IRQHandler() function declaration ************************************/

void RTC_Seconds_IRQHandler(void);

/********************************** RTC_read() ********************************************************
 *
 * @name   -  RTC_read()
 * @brief  -  function to read RTC Time Seconds Register
 * @param  -  none
 *
 * long description - This function read RTC Time Seconds Register.
 *
 * @return -  RTC->TSR value
 *
 ******************************************************************************************************/

/********************************* RTC_read() function declaration ************************************/

uint32_t RTC_read(void);


#endif /* SOURCES_RTC_H_ */
