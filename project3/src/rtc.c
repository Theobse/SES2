/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file rtc.c
 * @brief This source file includes RTC functions
 * @date November 29, 2017
 *
 * long description - The rtc.c file includes functions to -
 *                      1) initialize RTC (RTC_init())
 *                      2) handle RTC_Seconds Interrupt (RTC_Seconds_IRQHandler())
 *                      3) read RTC Timer Seconds Register (RTC_read())
 *
 *
 ***************************************************************************************************/

#include "rtc.h"
#include "logger.h"
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

/********************************* RTC_init() function definition ************************************/

void RTC_init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_RTC(1);				// Enable RTC clock gate
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);			// Enable PORTC clock gate

	MCG_C1 |= MCG_C1_IRCLKEN_MASK; 				//Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  			//Internal Reference Clock -->Slow

	PORTC_PCR1 |= (PORT_PCR_MUX(1));			// Configure PTC1 as Clock input pin
	PORTC_PCR3 |= (PORT_PCR_MUX(0x5));			//Configure PTC3 as Clock output pin
	SIM_SOPT2 &= ~(SIM_SOPT2_CLKOUTSEL_MASK);	// Clear CLKOUTSEL bit field
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(4);		// Set CLKOUTSEL bit field
	SIM_SOPT1 &= ~(SIM_SOPT1_OSC32KSEL_MASK);	// Clear OSC32KSEL bit field
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(2);		//PTC3 as CLKOUT

	if (RTC_SR & RTC_SR_TIF_MASK){
		RTC_TSR = 0;   							//clears the TIF
	}

	RTC_SR |= RTC_SR_TCE(1);
	RTC_IER &= ~RTC_IER_TSIE(1); 				//Seconds interrupt disable

	NVIC_SetPriority(RTC_Seconds_IRQn,21);		// Setting RTC_Seconds interrupt priority
	NVIC_ClearPendingIRQ(RTC_Seconds_IRQn);		// Clearing pending RTC_Seconds interrupt (if any)
	NVIC_EnableIRQ(RTC_Seconds_IRQn);			// Enabling RTC_Seconds interrupt

}

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

/********************************* RTC_Seconds_IRQHandler() function definition ************************************/


void RTC_Seconds_IRQHandler(void){
	LOG(HEARTBEAT,NULL);
}

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

/********************************* RTC_read() function definition ************************************/

uint32_t RTC_read(void){
	return RTC->TSR;
}
