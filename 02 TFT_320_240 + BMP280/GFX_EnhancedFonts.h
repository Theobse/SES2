#ifndef INC_GFX_ENHANCEDFONTS_H_
#define INC_GFX_ENHANCEDFONTS_H_

#include "main.h"

//
//	DEFINE
//
#define SPACE_WIDTH 3

//
//	TYPEDEF ENUM
//
typedef enum
{
	BG_TRANSPARET = 0,
	BG_COLOR = 1
} BG_FONT;

//
//	TYPEDEF STRUCT
//
typedef struct
{
	uint8_t CharWidth;
	uint16_t CharOffset;
} FONT_CHAR_INFO;


typedef struct
{
	uint8_t CharHeight;
	uint8_t StartChar;
	uint8_t EndChar;
	uint8_t SpaceWidth;
	const FONT_CHAR_INFO *CharDescripton;
	const uint8_t *CharBitmaps;
} FONT_INFO;

//
//	FUNCTIONS
//
void EF_SetFont(const FONT_INFO *font);
uint8_t EF_GetFont_CharHeight(void);
uint8_t EF_GetFont_StartChar(void);
uint8_t EF_GetFont_EndChar(void);
uint8_t EF_GetFont_SpaceWidth(void);

uint8_t EF_PutChar(char ch, uint16_t x, uint16_t y, uint16_t EFcolor, BG_FONT Btransparent, uint16_t BG_color);
uint8_t EF_PutString(const uint8_t *pStr, uint16_t PosX, uint16_t PosY, uint16_t Fcolor, BG_FONT Btransparent, uint16_t BG_color);

#endif /* INC_GFX_ENHANCEDFONTS_H_ */
