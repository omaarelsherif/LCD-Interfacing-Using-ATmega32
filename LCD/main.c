/*
 * LCD
 * Author: OmarElsherif
 */

// Include libraries
#include "STD_TYPES.h"
#include "LCD_Private.h"
#include "LCD_Interface.h"
#include "DIO_Interface.h"

// Main function
void main(void)
{
	// Initialize the LCD
	LCD_VoidInit();

	// Write a message as string to LCD
	const u8 message[] = "Hello, World!";
	LCD_VoidWriteString(message);

	while(1)
	{

	}
}
