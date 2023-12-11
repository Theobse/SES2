#ifndef INC_XPT2046_H_
#define INC_XPT2046_H_

//
//	DEFINE
//
#define XPT2046_USE_CS 1
#define XPT2046_SPI_TIMEOUT 1000

#define TOUCH_CS_Port		GPIOB
#define TOUCH_CS_Pin 		GPIO_PIN_10
#define TOUCH_IRQ_Port		GPIOA
#define TOUCH_IRQ_Pin		GPIO_PIN_8

//
//	STRUCT
//
typedef struct
{
	long double alpha_x;
	long double beta_x;
	long double delta_x;
	long double alpha_y;
	long double beta_y;
	long double delta_y;

} CalibrationData_t;

//
//	ENUM
//
typedef enum
{
	XPT2046_IDLE = 0,
	XPT2046_PRESAMPLING,
	XPT2046_TOUCHED,
	XPT2046_RELEASED

} XPT2046_Status;

//
//	FUNCTIONS HEADER
//
void XPT2046_Init(SPI_HandleTypeDef *hspi, IRQn_Type touchirqn);
void XPT2046_GetRawData(void);
void XPT2046_ReadTouchPoint(uint16_t *x, uint16_t *y);
void XPT2046_Task(void);
void XPT2046_IRQ(void);
uint8_t XPT2046_IsTouch(void);
void XPT2046_TouchPoint(uint16_t *x, uint16_t *y);

#endif /* INC_XPT2046_H_ */
