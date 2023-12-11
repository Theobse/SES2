/*
 * smart_dorm.c
 *
 *  Created on: Apr 14, 2018
 *      Author: chili
 */

#include "main.h"
#include "stm32f0xx_hal.h"
#include "smart_dorm.h"
#include "lcd.h"
#include "real_time.h"
#include "pi_client.h"
#include "alarm.h"
#include "bluetooth_client.h"
#include <string.h>
#include <stdlib.h>

// Import all peripheral structures
extern DAC_HandleTypeDef hdac1;
extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

#define UPDATE_PERIOD 20

#define LEFT 0x55
#define RIGHT 0x56

// LED state macros
#define __GREEN_ON() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET)
#define __YELLOW_ON() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET)
#define __RED_ON() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET)
#define __GREEN_OFF() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET)
#define __YELLOW_OFF() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET)
#define __RED_OFF() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET)

// state variables
int IRQ_Count = 0;
int secs = 0;
int alarm_pos = 0;

int last_update = 0;
bool update = false;
bool panic = false;
bool alarm_next = false;

int hour_int = -1;
int min_int = -1;

State state = idle;
Info current_info = {.high = 10, .low = 1, .current = 5};
DisplayInfo displayed = calendar;

// USART Data buffers
uint8_t command_UPDATE[4] = {'U', 'P', 'D', 'T'};
uint8_t command_TIME[4] = {'T', 'I', 'M', 'E'};
char buf[80];
char single[1];
uint8_t single2[1];
int posb = 0; // USART1
int posc = 0; // USART2
bool received = false;
bool command = false;
uint8_t control_word[15];
bool transmit = false;
bool change_display = false;

void app_main() {
    // HAL_Delay(60000);
    init();
    HAL_UART_Receive_IT(&huart2, single2, 1);


    while(true) {

        if(state == err) {
            init();
        }

        if(update) {
            update = false;
            fetch();
        }

        if(received) {
            received = false;
            __YELLOW_OFF();
            clear_screen();
            HAL_Delay(100);
            lcd_write(buf);
            HAL_Delay(100);
            posb = 0;
        }

        if(secs == 60) {
            secs = 0;
            int_time(&hour_int, &min_int);
            panic = alarm_search(hour_int, min_int);
            if(min_int - last_update > 5 || min_int - last_update < 0) {
                last_update = min_int;
                fetch();
            }
        }

        if(change_display) {
            displayNext();
            change_display = false;
        }

        if(command) {
            command = false;
            posc = 0;
            interpret_command((char *)control_word);

        }

        if(panic) {
            panic = false;
            sound_alarm();
        }
        HAL_UART_Receive_IT(&huart2, single2, 1);
    }
}

void sound_alarm() {
    //HAL_TIM_Base_Start_IT(&htim3);
   HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
//    HAL_DACEx_TriangleWaveGenerate(&hdac1, DAC_CHANNEL_1, 4095);
   int start = secs;
    while(secs - start < 10) {
        if(secs % 2 == 0) {
            for(int i = 0; i < 4096; i+=16) {
                HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, i);
            } for(int i = 4095; i >= 0; i-=16) {
                HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, i);
            }
        }
    }
    HAL_DAC_Stop(&hdac1, DAC_CHANNEL_1);
}

void end_alarm() {
    HAL_TIM_Base_Stop_IT(&htim3);
    HAL_DAC_Stop(&hdac1, DAC_CHANNEL_1);
}

void displayNext() {
    // IDEA: Make more display states (Current, high, low, etc.)
    // UPDATE this state every state display change
    // __ F CONDITION
    // HI: __ LO: __
    if(displayed == calendar) {
        // display 2-line weather
        displayed = weather;
        write_weather();

    } else if(displayed == weather) {
        displayed = news;
        write_headlines();
    } else {
        displayed = calendar;
        write_time();
    }
}

void write_headlines() {
    clear_screen();
    HAL_Delay(100);
    lcd_write(current_info.headline);
    HAL_Delay(3000);
    for(int i = 0; i < 24; i++) {
        shift(LEFT);
        HAL_Delay(1000);
    }
}

void write_weather() {
    char weather1[17];
    char weather2[17];
    sprintf(weather1, "%d F  %s", current_info.current, current_info.condition);
    sprintf(weather2, "HI: %d, LO: %d", current_info.high, current_info.low);

    clear_screen();
    HAL_Delay(100);
    position_cursor(1, 1);
    HAL_Delay(100);
    lcd_write(weather1);
    HAL_Delay(100);
    position_cursor(2, 1);
    HAL_Delay(100);
    lcd_write(weather2);
    HAL_Delay(100);
}

void fetch() {
    // RETURN FORMAT:
    //   CURRENT,HIGH,LOW,HEADLINE
    __YELLOW_ON();
    HAL_UART_Transmit_IT(&huart1, command_UPDATE, 4);
    while(!transmit);
    transmit = false;
    HAL_Delay(100);

    HAL_UART_Receive_IT(&huart1, (uint8_t *) single, 1);
    while(!received);
    received = false;
    posb = 0;

    if(!strcmp(buf, "ERR\n")) {
        state = err;
        return;
    }

    char * token;
    int temp;
    // Update weather
    token = strtok(buf, ",");
    temp = atoi(token);
    current_info.current = temp;
    token = strtok(NULL, ",");
    temp = atoi(token);
    current_info.high = temp;
    token = strtok(NULL, ",");
    temp = atoi(token);
    current_info.low = temp;

    token = strtok(NULL, ",");
    strcpy(current_info.condition, token);

    //headline
    token = strtok(NULL, ",");
    strcpy(current_info.headline, token);
    __YELLOW_OFF();
}

void error_handler() {
    __GREEN_OFF();
    __RED_ON();
    init();
    __RED_OFF();
    state = idle;
    app_main();
}

void init() {
    // Add all starts of peripherals here (i.e. HAL_TIM2_Base_Start_IT)
    // init_time();
    __YELLOW_ON();
    alarm_init();
    lcd_init();
    clear_screen();
    HAL_Delay(100);
    HAL_TIM_Base_Start_IT(&htim2);

    // make allocations
    current_info.condition = malloc(8);
    current_info.headline = malloc(26);

    // request time
    HAL_UART_Transmit_IT(&huart1, (uint8_t *) command_TIME, 4);
    while(!transmit);
    transmit = false;
    HAL_UART_Receive_IT(&huart1, (uint8_t *) single, 1);
    while(!received);
    received = false;
    posb = 0;


    // set clock
    char * token;

    int year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t mins;
    // YYYY/MM/DD
    token = strtok(buf, ","); // YEAR
    year = atoi(token);
    token = strtok(NULL, ",");
    month = atoi(token); // MONTH
    token = strtok(NULL, ",");
    day = atoi(token); // DAY


    //HH:MM
    token = strtok(NULL, ",");
    hours = atoi(token); //HOUR
    token = strtok(NULL, ",");
    mins = atoi(token); //MINUTE

    set_time(hours, mins);
    set_date(0, day, month, year);

    fetch();
    alarm_init();
    HAL_Delay(100);
    write_time();

    HAL_Delay(100);
    __YELLOW_OFF();
    __GREEN_ON();
}

void write_time() {
    clear_screen();
    HAL_Delay(100);
    char buf3[17];
    lcd_write(get_time(buf3));
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim) {
    if(htim->Instance == TIM2) {
        IRQ_Count++;
        if(IRQ_Count == 1000) {
            IRQ_Count = 0;
            secs++;
        }
        if(secs % 15 == 0 && IRQ_Count == 0) {
            change_display = true;
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart) {
    // FIX PYTHON CLIENT TO INCLUDE NULL TERMINATOR
    if(huart->Instance == USART1) {
        __YELLOW_ON();
        buf[posb++] = single[0];
        if(single[0] != '\n' && single[0] != '\0') {
            HAL_UART_Receive_IT(&huart1, (uint8_t *) single, 1);
        } else {
            buf[posb] = '\0';
            received = true;
            __YELLOW_OFF();
        }
    }

    if(huart->Instance == USART2) {
        __YELLOW_ON();
        control_word[posc++] = single2[0];
        if(single2[0] != '\n' && single2[0] != '\0') {
            HAL_UART_Receive_IT(&huart2, (uint8_t *) single2, 1);

        } else {
            command = true;
            __YELLOW_OFF();
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef * huart) {
    if(huart->Instance == USART1) {
        // HAL_UART_Receive_IT(&huart1, (uint8_t *) single, 1);
        transmit = true;
    }
}
