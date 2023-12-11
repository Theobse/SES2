/***************************************************************************************************
 *
 * @author Shivam Khandelwal, Preshit Harlikar
 * @file project2.c
 * @brief This file includes UART data sorting and analysis functions
 * @date October 25, 2017
 *
 * long description - The project2.c file includes functions to -
 *                      1) perform UART data sorting and analysis(project_2())
 *                      2) Transmit data analysis in a tabular format(Table_Stats())
 *
 ***************************************************************************************************/


/*----- Header-Files -------------------------------------------------------*/

#include "uart.h"
#include "project2.h"

/*----- Buffer Initialization ------------------------ ---------------------*/

CB_t Tx_Buffer;
CB_t Rx_Buffer;

/*----- Global Variables ------------------------------------- -------------*/

uint8_t Rx_Data;
uint8_t Tx_Data;
uint8_t character_count[5];

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

/******************************** Table_Stats() function definition ***********************************/

void Table_Stats()
{
	/*----- Variable and Array Declaration ------------------------ ---------------------*/

    uint8_t char_str[5][41]={NUM,ALPHA,PUNC,MISC,TOTAL};
    uint8_t l;
    uint8_t k;

    /*--------- Total Character Count ----------------------------- ---------------------*/

    character_count[4] = 0;
    for(l=0;l<4;l++){
    character_count[4] = character_count[4] + character_count[l];}

    /*-----  Table Generation and Transmission------------------------ ------------------*/

    for(k=0;k<5;k++)
    {
    	/*----- String Transmission ------------------------------*/

    	for(l=0;l<41;l++)
    	{
    		CB_buffer_add_item(&Tx_Buffer,&char_str[k][l]);
    	}

    	/*-Converting count of each character to ascii string ---*/

    	uint8_t buff[4];
    	my_itoa(character_count[k],buff,10);

    	/*----Adding count string to Transmit Buffer ------------*/

    	CB_buffer_add_item(&Tx_Buffer, &buff[1]);
    	CB_buffer_add_item(&Tx_Buffer, &buff[2]);
    	character_count[k] = 0;

    	/*--------------- Clear count string buffer -------------*/

    	for(l=0;l<4;l++){
    		buff[l] = 0;
    	}

    	/*--- Sending line feed and carriage return -------------*/

    	uint8_t line = 0x0d;
    	CB_buffer_add_item(&Tx_Buffer, &line);
    	line = 0x0a;
    	CB_buffer_add_item(&Tx_Buffer, &line);
    }

    /*--------------------- Sending line feed and carriage return -----------------------*/

    uint8_t line = 0x0d;
    CB_buffer_add_item(&Tx_Buffer, &line);
    line = 0x0a;
    CB_buffer_add_item(&Tx_Buffer, &line);

    /*----- Enabling Transmit Interrupt --------------------------- ---------------------*/

    UART0_C2 &=~(UART0_C2_TIE_MASK); /* Clear TIE bit field */
    UART0_C2 |= UART0_C2_TIE_MASK;   /*Set TIE bit field */
}


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

void project_2()
{
	/*----- Initializing MKL25Z4 clock settings --------------------------- ---------------------*/

    SystemInit();

    /*----- Initializing UART  -------------------------------------------- ---------------------*/

    UART_configure();

    /*----- Initializing Transmit(Tx) and Receive(Rx) Buffers ------------------ --------------- */

    CB_init(&Tx_Buffer,255);
    CB_init(&Rx_Buffer,255);



    uint8_t Rxd_Data;

    while(1)
    {
    	/*----- Removing Data from Rx Buffer  -------------------------------------------- ------*/

    	CB_buffer_remove_item(&Rx_Buffer, &Rxd_Data);

    	/*----- Check for Numeric characters  -------------------------------------------- ------*/

            if((Rxd_Data>47) && (Rxd_Data<58))
            {
            	character_count[0]++;
                Rxd_Data=0;
            }

        /*----- Check for Alphabetic characters  ----------------------------------------- ------*/

            else if(((Rxd_Data>64) && (Rxd_Data<91))||((Rxd_Data>96) && (Rxd_Data<123)))
            {
            	character_count[1]++;
                Rxd_Data=0;
            }

        /*----- Check for Punctuation characters  ----------------------------------------- ----*/

            else if(((Rxd_Data>32) && (Rxd_Data<48))||((Rxd_Data>57) && (Rxd_Data<65))||((Rxd_Data>90) && (Rxd_Data<97))||((Rxd_Data>122) && (Rxd_Data<127)))
            {
            	character_count[2]++;
                Rxd_Data=0;
            }

       /*----- Check for Tab character - ------------------------------------------------ ------*/

            else if(Rxd_Data==9)
            {
            	Table_Stats();
            	Rxd_Data=0;
            }

       /*----- Check for Miscellaneous characters  ---------------------------------------------*/

            else if(((Rxd_Data>90)&&(Rxd_Data<97))||(Rxd_Data==127)||(Rxd_Data==27))
            {
            	character_count[3]++;
                Rxd_Data=0;
            }
      }
 }


