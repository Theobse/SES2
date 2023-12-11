/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file project2.h
 * @brief This header file includes UART data sorting and analysis function declarations.
 * @date October 25, 2017
 *
 * long description - The project2.c file includes functions declarations of functions to -
 *                      1) perform UART data sorting and analysis(project_2())
 *                      2) Transmit data analysis in a tabular format(Table_Stats())
 *
 ***************************************************************************************************/

#ifndef INCLUDES_PROJECT2_H_
#define INCLUDES_PROJECT2_H_

/*----- Macros for character strings -------------------------------------------------------*/

#define NUM "Number of Numeric Characters       : "
#define ALPHA "Number of Alphabetic Characters    : "
#define PUNC "Number of Punctuation Characters   : "
#define MISC "Number of Miscellaneous Characters : "
#define TOTAL "Total number of Characters         : "

/*----- Extern Declarations -------------------------------------------------------*/

extern uint8_t character_count[5];
extern uint8_t Rx_Data;
extern uint8_t Tx_Data;
extern CB_t Tx_Buffer;
extern CB_t Rx_Buffer;

/********************************** Table_Stats() *****************************************************
 *
 * @name   -  Table_Stats()
 * @brief  -  function to transmit analyzed data result in a tabular format.
 * @param  -  none
 *
 * long description - This function transmits data results obtained after analyzing and sorting of
 * 					  received UART characters (data).
 *
 * @return -  void
 *
 ******************************************************************************************************/

/******************************** Table_Stats() function declaration ***********************************/

void Table_Stats();

/********************************** project_2() *****************************************************
 *
 * @name   -  project_2()
 * @brief  -  function to analyze and sort received data.
 * @param  -  none
 *
 * long description - This function removes received data from receive buffer and analyzes it to
 * 					  increment count of the respective character type. On receiving Tab character,
 * 					  Table_Stats() function is called to send analyzed data results in a tabular
 * 					  format.
 *
 * @return -  void
 *
 ******************************************************************************************************/

/********************************** project_2() function definition ***********************************/

void project_2();

#endif /* INCLUDES_PROJECT2_H_ */
