#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "STD_TYPES.h"

// Functions prototypes
void LCD_VoidInit(void);
void LCD_VoidWriteCommand(u8 command);
void LCD_VoidWriteChar(u8 Char);
void LCD_VoidWriteString(const u8* String);
void LCD_VoidWriteNumber(u8 Number);

#endif
