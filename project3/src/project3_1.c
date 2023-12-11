/***************************************************************************************************
 *
 * @author  Preshit Harlikar, Shivam Khandelwal
 * @file project3_1.c
 * @brief This file includes logging functions for host and beaglebone black
 * @date November 23, 2017
 *
 * long description - The logger.c file includes functions to -
 *                      1) project3_1()
 *                      2) data()
 *                      3) profiling()
 *
 ***************************************************************************************************/

#include "project3_1.h"

/*----- Global Variables --------------------------------------------------*/

uint8_t character_count[4]={0,0,0,0};
uint8_t char_str[4][10];
char value;
uint32_t t = 1000000;
time_t t0;

/********************************** project3_1()**********************************************************
 *
 * @name   -  project3_1()
 * @brief  -  function to initialize log and other logging functions
 *
 * long description - This function executes logging for host and beaglebone black
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** project3_1() function definition ***********************************/

void project3_1(){
    uint8_t i;
    uint8_t j;
	while(1)
	{
	    printf("\n  %s  \t",ctime(&t0));
	    printf("Initialize logger (1/0):  ");
	    scanf("%d",&i);                 								//read value from user
	    if(i==1){														//if input is 1 then initialize log
            printf("\n  %s  \t",ctime(&t0));
            printf(" Log Initialized         %d\n\n",LOG_INITIALIZED);	//print log initialized
            printf("  %s  \t",ctime(&t0));
            printf(" System Initialized      %d\n\n",SYSTEM_INITIALIZED);	//print system initialized

            while(1){
                scanf("%d",&j);

                if(j==1){												//if j==1 enable data input
                    j=0;
                    printf("  %s  \t",ctime(&t0));
                    printf(" Data Input Enabled      %d\n\n",DATA_INPUT_ENABLED);	//print data input enabled
                    data();
                }
                if(j==2){												//if j==2 enable profiling
                    j=0;
                    printf("  %s  \t",ctime(&t0));
                    printf(" Profiling Started       %d\n\n",PROFILING_STARTED);	//print profiling started
                    profiling();
                    printf("  %s  \t",ctime(&t0));
                    printf(" Profiling Completed     %d\n\n",PROFILING_COMPLETED);	//print profiling completed
                }
                if(j==3){												//if j==3 exit loop
                    j=0;
                    break;
                }
            }
            printf("  %s  \t",ctime(&t0));
            printf(" System Halted           %d\n\n",SYSTEM_HALTED);	//print system halted
	 }
         if(i==0){
	      break;
	 }
     }
}

/********************************** data()**********************************************************
 *
 * @name   -  data()
 * @brief  -  function to take data input and display data analysis
 *
 * long description - This function takes data input from user and performs data analysis
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** data() function definition ***********************************/

void data(){
    while(1){
        scanf("\n%c",&value);

        //----- Check for Numeric characters  -------------------------------------------- ------
        if((value>47) && (value<58)){												//check ascii value for numeric character
            value=atoi(&value);
            printf("  %s  \t",ctime(&t0));
            printf(" Data Received           %d     %d\n\n",DATA_RECEIVED,value);	//print the received character
			character_count[0]++;
			value=0;
        }
        //----- Check for Alphabetic characters  ----------------------------------------- ------
        else if(((value>64) && (value<91)) || ((value>96) && (value<123))){			//check ascii value for alphabetic character
            printf("  %s  \t",ctime(&t0));
            printf(" Data Received           %d     %c\n\n",DATA_RECEIVED,value);	//print the received character
			character_count[1]++;
			value=0;
        }
        //----- Check for Punctuation characters  ----------------------------------------- ----
        else if(((value>32) && (value<46))||((value>57) && (value<61))||((value>90) && (value<97))||((value>122) && (value<127))){		//check ascii value for punctuation character
			printf("  %s  \t",ctime(&t0));
			printf(" Data Received           %d     %c\n\n",DATA_RECEIVED,value);	//print the received character
			character_count[2]++;
			value=0;
        }
        //----- Check for Miscellaneous characters  ---------------------------------------------
        else if(((value>90)&&(value<97))||(value==127)||(value==27)){				//check ascii value for miscellaneous characters
			printf("  %s  \t",ctime(&t0));
			printf(" Data Received           %d     %c\n\n",DATA_RECEIVED,value);	//print the received character
			character_count[3]++;
	        value=0;
        }
        //----- Check for . character - ------------------------------------------------ ------
        else if(value==46){															//if '.' is pressed print analysis
			printf("  %s  \t",ctime(&t0));
			printf(" Data Analysis Started   %d\n\n",DATA_ANALYSIS_STARTED);		//print analysis started
			printf("  %s  \t",ctime(&t0));
			printf(" Data Alpha Count        %d     %d\n\n",DATA_ALPHA_COUNT,character_count[1]);	//print alpha count
			printf("  %s  \t",ctime(&t0));
			printf(" Data Numeric Count      %d     %d\n\n",DATA_NUMERIC_COUNT,character_count[0]);	//print numeric count
			printf("  %s  \t",ctime(&t0));
			printf(" Data Punc Count         %d     %d\n\n",DATA_PUNCTUATION_COUNT,character_count[2]);	//print punctuation count
			printf("  %s  \t",ctime(&t0));
			printf(" Data Misc Count         %d     %d\n\n",DATA_MISC_COUNT,character_count[3]);	//print miscellaneous count
			printf("  %s  \t",ctime(&t0));
			printf(" Data Analysis Completed %d\n\n",DATA_ANALYSIS_COMPLETED);	//print analysis completed
	        value=0;
        }

        if(value==47){												//if '/' is pressed disable input
			value=0;
			printf("  %s  \t",ctime(&t0));
			printf(" Data Input Disabled     %d\n\n",DATA_INPUT_DISABLED);	//print input disabled
			break;
        }
    }
}

/********************************** profiling()**********************************************************
 *
 * @name   -  data()
 * @brief  -  function to take data input and display data analysis
 *
 * long description - This function takes data input from user and performs data analysis
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** profiling() function definition ***********************************/

void profiling(){
        lib_memmove_test(10);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memmove for 10 bytes\n\n",INFO);	//print info
        lib_memmove_test(100);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memmove for 100 bytes\n\n",INFO);	//print info
        lib_memmove_test(1000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memmove for 1000 bytes\n\n",INFO);	//print info
        lib_memmove_test(5000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memmove for 5000 bytes\n\n",INFO);	//print info
        lib_memset_test(10);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memset for 10 bytes\n\n",INFO);		//print info
        lib_memset_test(100);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memset for 100 bytes\n\n",INFO);	//print info
        lib_memset_test(1000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memset for 1000 bytes\n\n",INFO);	//print info
        lib_memset_test(5000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     lib-memset for 5000 bytes\n\n",INFO);	//print info
        my_memmove_test(10);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memmove for 10 bytes\n\n",INFO);		//print info
        my_memmove_test(100);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memmove for 100 bytes\n\n",INFO);	//print info
        my_memmove_test(1000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memmove for 1000 bytes\n\n",INFO);	//print info
        my_memmove_test(5000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memmove for 5000 bytes\n\n",INFO);	//print info
        my_memset_test(10);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memset for 10 bytes\n\n",INFO);		//print info
        my_memset_test(100);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memset for 100 bytes\n\n",INFO);		//print info
        my_memset_test(1000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memset for 1000 bytes\n\n",INFO);	//print info
        my_memset_test(5000);
        printf("  %s  \t",ctime(&t0));
        printf(" Info                    %d     my-memset for 5000 bytes\n\n",INFO);	//print info
}

/********************************** lib_memmove_test()**********************************************************
 *
 * @name   -  lib_memmove_test()
 * @brief  -  function to perform profiling on library memmove function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** lib_memmove_test() function definition ***********************************/

void lib_memmove_test(uint32_t len){
    uint32_t i=0;
	uint8_t source[len];				//initialize source array
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];			//initialize destination array

	clock_t begin = clock();
	memmove(source,destination,len);	//library memmove function
	clock_t end = clock();
	double time1 = (double)((end - begin)*t) / CLOCKS_PER_SEC;		//calculate time
    printf("  %s  \t",ctime(&t0));
	printf(" Profiling Result        %d     %f\n\n",PROFILING_RESULT,time1);	//print profiling result
}

/********************************** lib_memset_test()**********************************************************
 *
 * @name   -  lib_memset_test()
 * @brief  -  function to perform profiling on library memset function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** lib_memset_test() function definition ***********************************/

void lib_memset_test(uint32_t len){
    uint8_t val = 10;
	uint8_t destination[len];			//initialize destination array

	clock_t begin = clock();
	memset(destination,val,len);		//library memset function
	clock_t end = clock();
	double time1 = (double)((end - begin)*t) / CLOCKS_PER_SEC;		//calculate time
    printf("  %s  \t",ctime(&t0));
	printf(" Profiling Result        %d     %f\n\n",PROFILING_RESULT,time1);	//print profiling result
}

/********************************** my_memmove_test()**********************************************************
 *
 * @name   -  my_memmove_test()
 * @brief  -  function to perform profiling on my_memmove function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** my_memmove_test() function definition ***********************************/

void my_memmove_test(uint32_t len){
    uint32_t i=0;
	uint8_t source[len];				//initialize source array
	while(i<(len))
	{
		source[i]=i;
		i++;
	}
	uint8_t destination[len];			//initialize destination array

	clock_t begin = clock();
	my_memmove(source,destination,len);		//my_memmove fuction
	clock_t end = clock();
	double time1 = (double)((end - begin)*t) / CLOCKS_PER_SEC;		//calculate time
    printf("  %s  \t",ctime(&t0));
	printf(" Profiling Result        %d     %f\n\n",PROFILING_RESULT,time1);	//print profiling result
}

/********************************** my_memset_test()**********************************************************
 *
 * @name   -  my_memset_test()
 * @brief  -  function to perform profiling on my_memset function
 *
 *
 * @return -  void
 *
 ******************************************************************************************************/

/*********************************** my_memset_test() function definition ***********************************/

void my_memset_test(uint32_t len){
    uint32_t val =10;

	uint8_t destination[len];			//initialize destination array

	clock_t begin = clock();
	my_memset(val,destination,len);			//my_memset fuction
	clock_t end = clock();
	double time1 = (double)((end - begin)*t) / CLOCKS_PER_SEC;		//calculate time
    printf("  %s  \t",ctime(&t0));
	printf(" Profiling Result        %d     %f\n\n",PROFILING_RESULT,time1);	//print profiling result
}
