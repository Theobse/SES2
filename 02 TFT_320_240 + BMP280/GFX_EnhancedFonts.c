#include "GFX.h"
#include "GFX_EnhancedFonts.h"
#include "TFT_ILI9341.h"
#include "string.h"

//
//	Variables
//
const FONT_INFO *CurrentFont;

void EF_SetFont(const FONT_INFO *font)
{
	CurrentFont = font;
}

uint8_t EF_GetFont_CharHeight(void)
{
	return CurrentFont -> CharHeight;
}

uint8_t EF_GetFont_StartChar(void)
{
	return CurrentFont -> StartChar;
}

uint8_t EF_GetFont_EndChar(void)
{
	return CurrentFont -> EndChar;
}

uint8_t EF_GetFont_SpaceWidth(void)
{
	return CurrentFont -> SpaceWidth;
}

char EF_DecodePolish(uint8_t chMsb, uint8_t chLsb)
{
	switch(chMsb) // Check first byte
	{
	case 0xC3: // Ó, ó
		switch(chLsb) // Check second byte
		{
		case 0x93: // Ó
			return 0x84;
			break;
		case 0xB3: // ó
			return 0x8D;
			break;
		}
		break;
	case 0xC4: // Ą, Ę, Ć, ą, ę, ć
		switch(chLsb) // Check second byte
		{
		case 0x84: // Ą
			return 0x7F;
			break;
		case 0x98: // Ę
			return 0x81;
			break;
		case 0x86: // Ć
			return 0x80;
			break;
		case 0x85: // ą
			return 0x88;
			break;
		case 0x99: // ę
			return 0x8A;
			break;
		case 0x87: // ć
			return 0x89;
			break;
		}
		break;
	case 0xC5: // Ł, Ń, Ś, Ź, Ż, ł, ń, ś, ź, ż
		switch(chLsb) // Check second byte
		{
		case 0x81: // Ł
			return 0x82;
			break;
		case 0x83: // Ń
			return 0x83;
			break;
		case 0x9A: // Ś
			return 0x85;
			break;
		case 0xB9: // Ź
			return 0x86;
			break;
		case 0xBB: // Ż
			return 0x87;
			break;
		case 0x82: // ł
			return 0x8B;
			break;
		case 0x84: // ń
			return 0x8C;
			break;
		case 0x9B: // ś
			return 0x8E;
			break;
		case 0xBA: // ź
			return 0x8F;
			break;
		case 0xBC: // ż
			return 0x90;
			break;
		}
		break;
	}

	return 0;
}


uint8_t EF_PutChar(char ch, uint16_t x, uint16_t y, uint16_t EFcolor, BG_FONT Btransparent, uint16_t BG_color)
{
	uint16_t PixelHeight;
	uint8_t CharBitsLeft, WidthLoop, CharBits;

	uint8_t CharNumber = ch - EF_GetFont_StartChar();

	if(CharNumber > EF_GetFont_EndChar()) return 0;

	if(ch == ' ')
	{
		if(Btransparent == BG_COLOR)
		{
			GFX_DrawFillRectangle(x, y, SPACE_WIDTH * EF_GetFont_SpaceWidth(), CurrentFont -> CharHeight, BG_color);
		}

		return SPACE_WIDTH * EF_GetFont_SpaceWidth();
	}

	const FONT_CHAR_INFO *CurrentChar = &CurrentFont -> CharDescripton[CharNumber];
	uint8_t *CharPointer = (uint8_t *) &CurrentFont -> CharBitmaps [CurrentFont -> CharDescripton[CharNumber].CharOffset];

	for(PixelHeight = 0; PixelHeight < (CurrentFont -> CharHeight); PixelHeight++) // Each column (Width)
	{
		CharBitsLeft = CurrentChar -> CharWidth;

		for(WidthLoop = 0; WidthLoop <= ((CurrentChar -> CharWidth - 1) / 8); WidthLoop++)
		{
			uint8_t Line = (uint8_t) *CharPointer;
			if(CharBits >= 8)
			{
				CharBits = 8;
				CharBitsLeft -= 8;
			}
			else
			{
				CharBits = CharBitsLeft;
			}

			for(uint8_t i = 0; i < CharBits; i++, Line <<= 1)
			{
				if(Line & 0x80)
				{
					GFX_DrawPixel(x + (WidthLoop * 8) + i, y + PixelHeight, EFcolor);
				}
				else if (Btransparent == BG_COLOR)
				{
					GFX_DrawPixel(x + (WidthLoop * 8) + i, y + PixelHeight, BG_color);
				}
			}
			CharPointer++;
		}
	}
	return CurrentFont -> CharDescripton[CharNumber].CharWidth;
}

uint8_t EF_PutString(const uint8_t *pStr, uint16_t PosX, uint16_t PosY, uint16_t Fcolor, BG_FONT Btransparent, uint16_t BG_color)
{
	uint8_t Lenght =  strlen((char *) pStr);
	uint16_t Shift = 0;
	uint8_t CharWidth, CharToPrint;

	for(uint8_t i = 0; i < Lenght; i++)
	{
		if((pStr[i] >= 0xC3) && (pStr[i] <= 0xC5))	//	polish char
		{
			CharToPrint = EF_DecodePolish(pStr[i], pStr[i + 1]);
			i++;
		}
		else
		{
			CharToPrint = pStr[i];
		}

		CharWidth = EF_PutChar(CharToPrint, PosX + Shift, PosY, Fcolor, Btransparent, BG_color);
		Shift += CharWidth;

		if(Btransparent == BG_COLOR)
		{
			GFX_DrawRectangle(PosX + Shift, PosY, EF_GetFont_SpaceWidth(), EF_GetFont_CharHeight(), BG_color);
		}
		Shift += EF_GetFont_SpaceWidth();
	}
	return Shift - EF_GetFont_SpaceWidth();
}
